#define IW 320 
#define IH 40
#define WAIT 30
#define AX 230
#define IW2 50
#define IH2 50
#include "catimages.h"
#include <M5StickC.h> 
#include <pgmspace.h>  // PROGMEM support header
TFT_eSprite img = TFT_eSprite(&M5.Lcd);

void setup() {
M5.begin();
randomSeed(millis());
M5.Lcd.fillScreen(BLUE);
M5.Lcd.setRotation(3);
M5.Lcd.setCursor(1,1);
M5.Lcd.println("[Setup Finished]");
delay(AX);
M5.Lcd.fillScreen(BLACK);
img.setColorDepth(16); // Set color depth to 16
img.createSprite(IW,IH); // Create the sprite Width & Height  
img.fillSprite(WHITE); //

for(int pos = IW; pos > 0; pos--) {
build_banner("oneko the digital pet... Loading oneko..                           ",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite(); // Free up memory 
M5.Lcd.fillScreen(BLACK);
}

void loop() {

int randomNumber;
randomNumber = random(12);

switch(randomNumber) {  
case 1:
for (int i = 0; i <= random(255); i++) {
cat_sleep_normal2();
}
break; 

case 2:
for (int i = 0; i <= random(203); i++) {
cat_run_fast();  
}
break;
 
case 3:
for (int i = 0; i <= random(300); i++) {
cat_sleep_normal();
}
break; 

case 4:
for (int i = 0; i <= random(100); i++) {
digipet();
}
break;

case 5:
for (int i = 0; i <= random(5); i++) {
cat_wink_left();
}
break; 

case 6:
for (int i = 0; i <= random(200); i++) {
cat_alert_normal();
}
break;

case 7:
for (int i = 0; i <= random(155); i++) {
cat_wink_normal();  
}
break;

case 8:
for (int i = 0; i <= random(11); i++) {
cat_wink_right();  
}
break;

case 9:
for (int i = 0; i <= random(355); i++) {
cat_run();  
}
break; 

case 10:
for (int i = 0; i <= random(160); i++) {
cat_lookingDown2();  
}
break; 

case 11:
for (int i = 0; i <= random(160); i++) {
digipet();
cat_lookingDown2();  
}
break;

case 12: 
for (int i = 0; i <= random(111); i++) {
cat_diging();  
}
break;

}

}

void cat_diging() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_dig1, IW2, IH2, TFT_WHITE);
delay(WAIT+random(211));
M5.Lcd.drawXBitmap(x, y, cat_dig1, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(211));
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_BLACK);  
}

void cat_lookingDown2() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_lookingDown, IW2, IH2, TFT_WHITE);
delay(WAIT+random(111));
M5.Lcd.drawXBitmap(x, y, cat_lookingDown, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_dig1, IW2, IH2, TFT_WHITE);
delay(WAIT+random(111));
M5.Lcd.drawXBitmap(x, y, cat_dig1, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(111));
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_BLACK);
}

void cat_normal() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT);
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK);
}

void cat_normal2() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(156));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK);
}

void cat_wink_right() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wink, IW2, IH2, TFT_WHITE);
delay(WAIT+random(156));
M5.Lcd.drawXBitmap(x, y, cat_wink, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK); 
}

void cat_wink_left() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wink2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(156));
M5.Lcd.drawXBitmap(x, y, cat_wink2, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK); 
}

void cat_wink_normal() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wink, IW2, IH2, TFT_WHITE);
delay(WAIT+random(156));
M5.Lcd.drawXBitmap(x, y, cat_wink, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_wink2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(156));
M5.Lcd.drawXBitmap(x, y, cat_wink2, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK); 

}

void digipet() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_wake1, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake1, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_wake2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake2, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK);
}

void cat_sleep_normal() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_sleep, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_sleep, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_sleep2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_sleep2, IW2, IH2, TFT_BLACK);
}

void cat_run_fast() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_WHITE);
delay(random(191));
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_WHITE);
delay(random(192));
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_WHITE);
delay(random(193));
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_BLACK);  
}

void cat_run() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_WHITE);
delay(WAIT+random(350));
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(250));
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_WHITE);
delay(WAIT+random(350));
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_WHITE);
delay(WAIT+random(350));
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(350));
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_WHITE);
delay(WAIT+random(350));
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_BLACK);
}

void cat_sleep_normal2() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(650));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_wink, IW2, IH2, TFT_WHITE);
delay(WAIT+random(650));
M5.Lcd.drawXBitmap(x, y, cat_wink, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_board, IW2, IH2, TFT_WHITE);
delay(WAIT+random(550));
M5.Lcd.drawXBitmap(x, y, cat_board, IW2, IH2, TFT_BLACK);
}

void cat_alert_normal() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_alert, IW2, IH2, TFT_WHITE);
delay(WAIT+random(150));
M5.Lcd.drawXBitmap(x, y, cat_alert, IW2, IH2, TFT_BLACK);
}

void banner_noback(String msg, int xpos) {
  img.setTextSize(1);
  img.setTextColor(BLUE);
  img.setCursor(xpos, 1);
  img.setTextFont(4);    // Options number
  img.setTextWrap(false); // Buggy if set to true - Options true / false 
  img.setCursor(xpos - IW, 2);
  img.print(msg);
}

void build_banner(String msg, int xpos) {
  int h = IH;
  while (h--) img.drawFastHLine(0, h, IW, RGBVAL(h * 4));
  img.drawRect(IW - 1, IH - 1, 40, 320, WHITE);
  img.setTextSize(1);
  img.setTextColor(BLACK);
  img.setCursor(xpos, 1);
  img.setTextFont(4);    // Options number
  img.setTextWrap(false); // Buggy if set to true - Options true / false 
  img.setCursor(xpos - IW, 2);
  img.print(msg);
}

unsigned int RGBVAL(byte value) {
  byte red = 0;  // Do basic color wheel by switch sector
  byte blue = 0;
  byte green = 0;

  byte sector = value >> 5;
  byte amplit = value & 0x1F;

  switch (sector) {
  case 0: 
  red = 0x1F;
  green = amplit;
  blue = 0;
  break;
  case 1:
  red = 0x1F - amplit;
  green = 0x1F;
  blue = 0;
  break;
  case 2:
  red = 0;
  green = 0x1F;
  blue = amplit;
  break;
  case 3:
  red = 0;
  green = 0x1F - amplit;
  blue = 0x1F;
  break;   
  }
return red << 11 | green << 6 | blue;
}
