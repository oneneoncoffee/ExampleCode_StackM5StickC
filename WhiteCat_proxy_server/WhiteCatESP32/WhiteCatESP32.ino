// 
//  Project Name: White Cat 
//  Sketch Filename: WhiteCatESP32.ino 
//  Include Defs. Filename: Array_db.h 
//  Database images Filename: catimages.h
//  
/////////////

#include <WiFi.h>
#include <SPI.h>
#include <WiFiClient.h>
#include <WiFiAP.h> 
#include <Ethernet.h>
#include "catimages.h"
#include "Array_db.h"
#include <M5StickC.h> 

// Set your Static IP address 
IPAddress local_IP(192, 168, 1, 184); 
IPAddress gateway(192, 168, 1, 1);
IPAddress LocalServer(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); 
IPAddress secondaryDNS(8, 8, 4, 4); 

void setup() {
M5.begin();
delay(AX); 
randomSeed(millis());
M5.Lcd.fillScreen(BLUE);
M5.Lcd.setTextColor(WHITE, BLUE); 
M5.Lcd.setRotation(3);
M5.Lcd.setCursor(1,1);
M5.Lcd.println("Starting..");
M5.Lcd.println("WiFi station Active, \nEssid:WhiteCat"); 
M5.Lcd.println("MAC ADDRESS:\n"+WiFi.macAddress()); 
Ethernet.begin(mac, local_IP, LocalServer, gateway, subnet);
WiFi.softAP(ssid, pass);
M5.Lcd.println("Password: whitecat1");
server.begin(); 
M5.Lcd.println("[Setup Finished]"); 
for(int i = 0; i <=2; i++) { delay(XX+XX); }
M5.Lcd.fillScreen(BLACK);
img.setColorDepth(16); // Set color depth to 16
img.createSprite(IW,IH); // Create the sprite Width & Height  
img.fillSprite(WHITE); //

for(int pos = IW; pos > 0; pos--) {
build_banner("Hello I am WhiteCat ...",pos);
img.pushSprite(0,0);
cat_normal(); 
}

img.deleteSprite(); // Free up memory 
M5.Lcd.fillScreen(BLACK);
}


void loop() {
// DO SERVER CLIENT LOOP & exit to random cats.
for (int i = 0; i <= XX; i++) {
check_board();  
}

// DO RANDOM CATS 
int randomNumber;
randomNumber = random(30);
switch(randomNumber) {  

case 1:
for (int i = 0; i <= random(255); i++) {
cat_sleep_normal2();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 2:
for (int i = 0; i <= random(203); i++) {
cat_run_fast();  
}
random_message();
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;
 
case 3:
for (int i = 0; i <= random(300); i++) {
cat_sleep_normal();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 4:
for (int i = 0; i <= random(100); i++) {
digipet();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 5:
for (int i = 0; i <= random(5); i++) {
cat_wink_left();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 6:
for (int i = 0; i <= random(200); i++) {
cat_alert_normal();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 7:
for (int i = 0; i <= random(155); i++) {
cat_wink_normal();  
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 8:
for (int i = 0; i <= random(11); i++) {
cat_wink_right();  
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 9:
for (int i = 0; i <= random(355); i++) {
cat_run();  
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
random_message();
break; 

case 10:
for (int i = 0; i <= random(160); i++) {
cat_lookingDown2();  
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 11:
for (int i = 0; i <= random(160); i++) {
digipet();
cat_lookingDown2();  
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 12: 
for (int i = 0; i <= random(111); i++) {
cat_diging();  
random_message();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 13: 
for (int i = 0; i <= random(200); i++) {
  cat_wink_left();
  cat_wink_right();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 14:
for (int i = 0; i <= random(30); i++) { cat_normal(); }
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 15: 
random_message(); 
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 16: 
random_move(); 
for (int i = 0; i <= random(30); i++) {
random_move();
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 17: 
for (int i = 0; i <= random(30); i++) {
  random_move_color(); 
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 18: 
for (int i = 0; i <= random(20); i++) {
cat_normal3(); 
}
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 19:
for (int i = 0; i <= XX; i++) { check_board(); }
random_move_color(); 
break;

case 20: 
for (int i = 0; i <= XX; i++) { check_board(); }
random_move_color(); 
random_message(); 
break; 

case 21: 
for (int i = 0; i <= random(AX); i++) { check_board(); }
random_move_color(); 
cat_diging();
break; 

case 22: check_board(); 
for (int i = 0; i <= random(17); i++) {
  random_move_color2();
  random_move_color(); 
  random_move_color2();
} 
break;

case 23: check_board();
for (int i = 0; i <= random(34); i++) {
  cat_dig();
}
break; 

case 24: break; 
case 25: break; 
case 26: break; 
case 27: break; 
case 28: break;
case 29: break; 
case 30: break;

default:  cat_normal(); 
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
}

void cat_dig() {
int x = 30;
int y = 30;  
for (int i = 0; i <= 7; i++) {
M5.Lcd.drawXBitmap(x, y, cat_board, IW2, IH2, TFT_WHITE);
delay(WAIT+random(211));
M5.Lcd.drawXBitmap(x, y, cat_board, IW2, IH2, TFT_BLACK);  
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(111));
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_dig1, IW2, IH2, TFT_WHITE);
delay(WAIT+random(111));
M5.Lcd.drawXBitmap(x, y, cat_dig1, IW2, IH2, TFT_BLACK);
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_WHITE);
delay(WAIT+random(111));
M5.Lcd.drawXBitmap(x, y, cat_dig2, IW2, IH2, TFT_BLACK);
}
}

void cat_normal() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT);
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK);
}

void random_move() {
for (int i = 0; i <= 10; i++) {  
int x = random(IW); 
int y = random(IH); 
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_WHITE);
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_WHITE);
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_WHITE);
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_BLACK);  
} 
}

void random_move_color() {
for (int i = 0; i <= 10; i++) {  
int x = random(IW); 
int y = random(IH); 
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, random(0xFFFF));
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, random(0xFFFF));
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, random(0xFFFF));
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_BLACK);  
check_board();  
} 
}

void random_move_color2() {
  for (int i = 0; i <= 18; i++) {  
int x = random(IW)+random(3); 
int y = random(IH)+random(3); 
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_WHITE);
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run1, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(y, x, cat_run1, IW2, IH2, random(0xFFFF));
delay(random(100));
M5.Lcd.drawXBitmap(y, x, cat_run1, IW2, IH2, TFT_BLACK); 
delay(random(90)); 
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_WHITE);
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run2, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(y, x, cat_run2, IW2, IH2, random(0xFFFF));
delay(random(90));
M5.Lcd.drawXBitmap(y, x, cat_run2, IW2, IH2, TFT_BLACK); 
M5.Lcd.drawXBitmap(y, x, cat_run3, IW2, IH2, random(0xFFFF));
delay(random(99));
M5.Lcd.drawXBitmap(y, x, cat_run3, IW2, IH2, TFT_BLACK);  
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_WHITE);
delay(random(100));
M5.Lcd.drawXBitmap(x, y, cat_run3, IW2, IH2, TFT_BLACK);  
} 
}

void cat_normal2() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_WHITE);
delay(WAIT+random(156));
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, TFT_BLACK);
}
void cat_normal3() {
int x = 30;
int y = 30;
M5.Lcd.drawXBitmap(x, y, cat_wake, IW2, IH2, CRT(256));
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
for (int i = 0; i <= 5; i++) {  
int x = 30;
int y = 30+i;
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
}

void cat_run() {
for (int i = 0; i <= 6; i++) {
int x = 30+i;
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
  int h = IH;
  img.setTextSize(2);
  // Note: make sure to set this outside our loops,
  // or it will flash random wild colors to our text. 
  // img.setTextColor(random(0xFFFF)); // set random color.
  img.setCursor(xpos, 1);
  img.setTextFont(2);    // Options number
  img.setTextWrap(false);  
  img.setCursor(xpos - IW, 2);
  while (h--) img.drawFastHLine(0, h, IW, BLACK);
  img.print(msg);
}

void random_message() {
for (int i = 0; i <= random(AX); i++) { check_board(); }
M5.Lcd.fillScreen(BLACK);

img.createSprite(IW,IH); // Create the sprite Width & Height  
img.fillSprite(BLACK); // fill our sprite background as black.  

int i = random(25); 
switch (i) {

case 0:
img.setTextColor(random(0xFFFF)); // set random color.
for(int pos = IW; pos > 0; pos--) {
banner_noback("I solemnly swear that...",pos);
img.pushSprite(0,0);
cat_normal(); 
}
for(int pos = IW; pos > 0; pos--) {
  banner_noback("I am up to no good!",pos);
  img.pushSprite(0,0);
  cat_normal();
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 1:
img.setTextColor(random(0xFFFF)); // set random color.
for(int pos = IW; pos > 0; pos--) {
banner_noback("You can't make everyone happy.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 2:
img.setTextColor(random(0xFFFF)); // set random color.
for(int pos = IW; pos > 0; pos--) {
banner_noback("Do not take life too seriously.. ",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 3:
img.setTextColor(random(0xFFFF)); // set random color.
for(int pos = IW; pos <= 0; pos--) {
banner_noback("if you want the rainbow, deal with rain.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 4:
img.setTextColor(random(0xFFFF)); // set random color.
for(int pos = IW; pos > 0; pos--) {
banner_noback("When nothing is going right, go fish",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 5:
img.setTextColor(random(0xFFFF)); // set random color.
for(int pos = IW; pos > 0; pos--) {
banner_noback("Remember to take it easy..",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 6: 
img.setTextColor(random(0xFFFF)); // set random color.
for(int pos = IW; pos > 0; pos--) {
banner_noback("I could agree with you, ",pos);
img.pushSprite(0,0);
cat_normal(); 
}
for(int pos = IW; pos > 0; pos--) {
banner_noback("but then we'd both be wrong.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 7:
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("I am a liability!",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 8: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 9: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Evil grows in the dark!",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 10: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Meeow! Meeow!",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 11: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Remember to look up...",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 12: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("All good things are wild.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 13: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("FREE as in freedom....",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 14: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Joy is within..",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 15: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Work hard; Play hard..",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 16: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Sometimes BEER is a good thing.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 17: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("It's wine time bro.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 18: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Give it 100% today..",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 19: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Coffee break already! ",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 20: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Fuck around & find out...",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 21: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("I will rock your socks off..",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 22: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Caffeine, caffeine, caffeine!",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 23: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("I am down with the underground.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

case 24: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Don't be evil? don't be google.",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;

case 25: 
img.setTextColor(random(0xFFFF)); // set random color. 
for(int pos = IW; pos > 0; pos--) {
banner_noback("I'm not a watch..",pos);
img.pushSprite(0,0);
cat_normal(); 
}
for(int pos = IW; pos > 0; pos--) {
banner_noback("IDEA: finger sized computer?",pos);    
cat_wink_right(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break; 

default: 
for(int pos = IW; pos > 0; pos--) {
banner_noback("Q:A tree's final moment of revenge?",pos);
img.pushSprite(0,0);
cat_normal(); 
}
for(int pos = IW; pos > 0; pos--) {
banner_noback("A: Papercut!",pos);
img.pushSprite(0,0);
cat_normal(); 
}
img.deleteSprite();  
M5.Lcd.fillScreen(BLACK);
for (int i = 0; i <= random(AX); i++) { check_board(); }
break;


}
}

void build_banner(String msg, int xpos) {
  int h = IH;
  while (h--) img.drawFastHLine(0, h, IW, RGBVAL(h * 4.99));
  img.drawRect(IW - 1, IH - 1, 40, 320, WHITE);
  img.setTextSize(1);
  img.setTextColor(BLACK);
  img.setCursor(xpos, 1);
  img.setTextFont(4);    // Options number
  img.setTextWrap(false); // Buggy if set to true - Options true / false 
  img.setCursor(xpos - IW, 2);
  img.print(msg); 
}
