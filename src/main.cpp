#include <Arduino.h>
#include <U8g2lib.h>

// By using "SW_I2C" (Software I2C), we can assign the displays to ANY pins we want
// without worrying about the ESP32's internal hardware conflicts!

// Screen 1 (Player 1)
// clock (SCL) = 22, data (SDA) = 21
U8G2_SSD1306_128X64_NONAME_F_SW_I2C screen1(U8G2_R0, /* clock=*/ 22, /* data=*/ 21, /* reset=*/ U8X8_PIN_NONE);

// Screen 2 (Player 2)
// clock (SCL) = 33, data (SDA) = 32
U8G2_SSD1306_128X64_NONAME_F_SW_I2C screen2(U8G2_R0, /* clock=*/ 33, /* data=*/ 32, /* reset=*/ U8X8_PIN_NONE);

#define BTN1_PIN 14
#define BTN2_PIN 27

// --- Game Settings ---
long p1_time_ms = 5 * 60 * 1000; // 5 minutes (in milliseconds)
long p2_time_ms = 5 * 60 * 1000;

// 0 = Paused/Not started, 1 = Player 1's clock is ticking, 2 = Player 2's clock is ticking
int active_player = 0; 
unsigned long last_update_time = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);

  screen1.begin();
  screen2.begin();
}

// A helper function to draw the time on a specific screen
void drawTime(U8G2 &screen, long time_ms, bool isActive) {
  screen.clearBuffer();
  
  if (time_ms < 0) time_ms = 0; // Don't go below zero
  
  // Math to figure out minutes, seconds, and tenths of a second
  int seconds = (time_ms / 1000) % 60;
  int minutes = (time_ms / 60000);
  int tenths = (time_ms / 100) % 10;

  char timeStr[10];
  if (minutes > 0) {
    // If over a minute, show MM:SS
    sprintf(timeStr, "%d:%02d", minutes, seconds);
  } else {
    // If under a minute, show SS.d (e.g. 45.2) for a dramatic finish!
    sprintf(timeStr, "%02d.%d", seconds, tenths); 
  }

  screen.setFont(u8g2_font_logisoso28_tr); // Very large, beautiful font for time
  
  // Math to center the text perfectly on the screen
  int width = screen.getStrWidth(timeStr);
  int x = (128 - width) / 2;
  screen.drawStr(x, 45, timeStr);
  
  // Show a tiny indicator of whose turn it is
  if (isActive) {
    screen.setFont(u8g2_font_ncenB08_tr);
    screen.drawStr(25, 60, "YOUR TURN");
  } else if (time_ms == 0) {
    screen.setFont(u8g2_font_ncenB08_tr);
    screen.drawStr(20, 60, "OUT OF TIME!");
  }

  screen.sendBuffer();
}

void loop() {
  // Calculate how much time has passed since the last exact loop
  unsigned long current_time = millis();
  unsigned long delta = current_time - last_update_time;
  last_update_time = current_time;

  int btn1 = digitalRead(BTN1_PIN);
  int btn2 = digitalRead(BTN2_PIN);

  // Game Logic: If a player smacks their button, pass the turn to the other player!
  if (btn1 == LOW && active_player != 2) {
    active_player = 2; 
  }
  if (btn2 == LOW && active_player != 1) {
    active_player = 1; 
  }

  // Deduct the exact milliseconds from the active player's clock
  if (active_player == 1) {
    p1_time_ms -= delta;
    if (p1_time_ms <= 0) {
      p1_time_ms = 0;
      active_player = 0; // Game over
    }
  } else if (active_player == 2) {
    p2_time_ms -= delta;
    if (p2_time_ms <= 0) {
      p2_time_ms = 0;
      active_player = 0; // Game over
    }
  }

  // Update both screens!
  drawTime(screen1, p1_time_ms, active_player == 1);
  drawTime(screen2, p2_time_ms, active_player == 2);
  }