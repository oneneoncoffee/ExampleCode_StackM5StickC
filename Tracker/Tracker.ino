// Menu Version 2.4 M5 Stick C 
// WiFi Scanner basic functions 
//
// Program OutLine: 
// Button A (Run menu item)
// Button B (Slect menu item)
// Red Led blink on slect  
// Sketch uses 766570 bytes (58%) of program storage space. Maximum is 1310720 bytes.
// Global variables use 40244 bytes (12%) of dynamic memory, leaving 287436 bytes for local variables. Maximum is 327680 bytes.

#include <M5StickC.h>
#include <WiFi.h>
#include <esp_wifi.h> 
#include <Update.h>
#include "AXP192.h"
#define RED_LED_PIN 10

const int Button_A = 37;
const int Button_B = 39;
      int last_value = 0;
      int current_value = 0;
      int menuIndex = 0;
      int menuCount = 6;

String menuTitle[] = {" Start Scanning", " Battery info", " Scan ESSIDs", " ESSIDs Traffic", " Scan with info.", " ESSIDs Encryption"}; 
     

TFT_eSprite batSprite = TFT_eSprite(&M5.Lcd);

void setup() {
pinMode(RED_LED_PIN, OUTPUT);
digitalWrite(RED_LED_PIN, LOW); 
delay(30); 
digitalWrite(RED_LED_PIN, HIGH);
M5.begin();
M5.Lcd.setRotation(3);
batSprite.createSprite(160, 80);
M5.Axp.EnableCoulombcounter();
M5.Lcd.fillScreen(BLACK);
menu_main();
}

void menu_main() {
M5.Lcd.setTextSize(1);
M5.Lcd.setTextColor(WHITE);
M5.Lcd.setCursor(0,0);
M5.Lcd.print("-=[ Main Menu ]=-");
// Menu Debug code uncomment for Numbered listing. 
// NOTE: Menu Index object starts at zero to 4 total.
//M5.Lcd.setCursor(0, 14);
//M5.Lcd.println(menuIndex);
M5.Lcd.setCursor(0,0); 
M5.Lcd.setTextColor(YELLOW);
M5.Lcd.setCursor(0, 4 * 3);
for (int i = 0; i < menuCount; i++) {
  M5.Lcd.printf("%s\n", menuTitle[i].c_str());  
}
M5.Lcd.setTextColor(WHITE);
M5.Lcd.setCursor(0, 80-16);
M5.Lcd.println("Button A: Run");
M5.Lcd.println("Button B: Select");
}

void Button_logic() {
M5.update();
M5.Lcd.setCursor(0, 4 * 3);
for (int i = 0; i < menuCount; i++) {
  if (menuIndex == i) {
   M5.Lcd.setTextColor(BLACK, GREEN);
   M5.Lcd.println("*");
   } else { 
   M5.Lcd.setTextColor(BLACK); 
   M5.Lcd.println(" "); 
   }
}
current_value = digitalRead(Button_B);
if(current_value != last_value) {
  if(current_value == 0) {
    menuIndex++;
    menuIndex = menuIndex % menuCount;
    M5.Lcd.fillScreen(BLACK);
    delay(30);

  }
  
  last_value = current_value;
}
current_value = digitalRead(Button_A);
if(current_value != last_value) {
  if(current_value == 0) {
    switch (menuIndex) {
    case 0: 
          Led_flash(); 
          Start_scanning();
          break;
    case 1:
          Led_flash(); 
          battery_loop();
          break;
    case 2:
          Led_flash(); 
          ScanNetwork();
          break;
    case 3:
          Led_flash(); 
          ScanFindNetworks();
          break;
    case 4:
          Led_flash();
          Scan_info_loop();    
          break;
    case 5: 
          Led_flash();
          Scan_encryption_type();
          break;                          
    default:  
          Led_flash();
          break;
    }
  }
  last_value = current_value;
}
menu_main();
}

void Led_flash() {
    digitalWrite(RED_LED_PIN, HIGH); 
    delay(30); 
    digitalWrite(RED_LED_PIN, LOW);
    delay(30); 
    digitalWrite(RED_LED_PIN, LOW); 
    delay(30); 
    digitalWrite(RED_LED_PIN, HIGH);
    delay(30); 

}

void loop() {
Button_logic();
}

void Start_scanning() {  
ScanNetwork();
ScanFindNetworks();
ScanChannel();
}

void Scan_info_loop() {
M5.Lcd.fillScreen(BLACK);
int var = 0;
while (var < 5) {
ScanChannel_loop();
var++;
M5.Lcd.setCursor(1,30);
M5.Lcd.fillScreen(BLACK); 
M5.Lcd.setTextColor(YELLOW);
M5.Lcd.print("Loop pass ");
M5.Lcd.print(var); 
M5.Lcd.println(" of 5 total.");
delay(50);
}
M5.Lcd.fillScreen(BLACK);
}

void battery_loop() {
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setCursor(0,0);   
int var = 0;
while (var < 333) {
    batSprite.fillSprite(BLACK);
    batSprite.setCursor(0, 0, 1);
    batSprite.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
    batSprite.setCursor(0, 10);
    batSprite.printf("Bat:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatCurrent());
    batSprite.setCursor(0, 30);  
    batSprite.printf("USB:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
    batSprite.setCursor(0, 50);    
    batSprite.printf("5V-In:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVinVoltage(), M5.Axp.GetVinCurrent());
    batSprite.setCursor(0, 70);    
    batSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
    batSprite.pushSprite(0, 0);
    var++;
    delay(40);
}
delay(250); 
M5.Lcd.fillScreen(BLACK); 
}

void ScanFindNetworks() {  
WiFi.mode(WIFI_STA);
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setTextColor(GREEN);
M5.Lcd.setCursor(0,0); 
M5.Lcd.println("Searching for networks.");
WiFi.disconnect();
int n = WiFi.scanNetworks();
if (n == 0) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(1,1);
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("No networks in range.");
            } else {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(1,1);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.print(n);
  M5.Lcd.println(" networks found"); 
              }    
if (n >= 100) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(1,1); 
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("ESSID's 100+");
  M5.Lcd.println("Heavy WiFi traffic detected.");                    
} else if (n >= 60) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(1,1); 
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("60 ESSID's active.");
  }

  delay(750);
  M5.Lcd.fillScreen(BLACK);
}

void ScanNetwork() {
  WiFi.mode(WIFI_STA);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("Scanning Networks.");
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  if (n == 0) { 
  M5.Lcd.setCursor(1,1);
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.println("No networks found");  
  } else {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(1,1);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print(n);
        M5.Lcd.println(" networks found");
        M5.Lcd.setCursor(1,1);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print(n);
        M5.Lcd.println(" networks found");
        delay(70);
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.setCursor(1,10);
        for (int i = 0; i < 9; ++i) {
            // Print SSID and RSSI for each network found
            M5.Lcd.print(i + 1);
            M5.Lcd.print(":");
            M5.Lcd.print(WiFi.SSID(i));
            M5.Lcd.print("(");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.print(")");
            M5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"":"");
            delay(400);
        }   delay(40);
            M5.Lcd.fillScreen(BLACK);
            M5.Lcd.setCursor(1,1);
            for (int i = 9; i < n; ++i) {
            // Print SSID and RSSI for each network found
            M5.Lcd.print(i + 1);
            M5.Lcd.print(":");
            M5.Lcd.println(WiFi.SSID(i));
            M5.Lcd.print("(");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.print(")");
            M5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"":"");
            delay(400);
        }   delay(40);
  }

  delay(240); 
  M5.Lcd.fillScreen(BLACK);
}

void ScanChannel_loop() {
 WiFi.mode(WIFI_STA);
 M5.Lcd.setTextColor(GREEN);
 M5.Lcd.setCursor(1,1);
 M5.Lcd.println("Scanning..");
 WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  if (n == 0) { 
  M5.Lcd.setCursor(1,1);
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.println("No networks found");  
  } else {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(1,1);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print(n);
        M5.Lcd.println(" networks found");
        delay(70);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.setCursor(1,1);
            for (int i = 2; i < n; ++i) {
            // Print SSID and RSSI for each network found
            M5.Lcd.setCursor(1,1);
            M5.Lcd.print(i + 1);
            M5.Lcd.print(":");
            M5.Lcd.println(WiFi.SSID(i));
            M5.Lcd.print("Signal RSSI(");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.println(")");
            M5.Lcd.setTextColor(RED);
            M5.Lcd.println(WiFi.BSSIDstr(i));
            M5.Lcd.print("Channel:");
            M5.Lcd.println(WiFi.channel(i));
            M5.Lcd.setTextColor(GREEN);
            M5.Lcd.println("Scanning..");
            M5.Lcd.setTextColor(BLUE);
            delay(900);
            M5.Lcd.fillScreen(BLACK);
        }   delay(40);
  }
}

void ScanChannel() {
  WiFi.mode(WIFI_STA);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("Scanning with more info.");
  WiFi.disconnect();
  delay(100);
  M5.Lcd.fillScreen(BLACK);
  int n = WiFi.scanNetworks();
  if (n == 0) { 
  M5.Lcd.setCursor(1,1);
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.println("No networks found");  
  } else {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(1,1);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print(n);
        M5.Lcd.println(" networks found");
        M5.Lcd.setCursor(1,1);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print(n);
        M5.Lcd.println(" networks found");
        delay(70);
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.setCursor(1,10);
        for (int i = 0; i < 2; ++i) {
            // Print SSID and RSSI for each network found
            M5.Lcd.print(i + 1);
            M5.Lcd.print(":");
            M5.Lcd.print(WiFi.SSID(i));
            M5.Lcd.print("(");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.println(")");
            M5.Lcd.setTextColor(RED);
            M5.Lcd.println(WiFi.BSSIDstr(i));
            M5.Lcd.print("Channel:");
            M5.Lcd.println(WiFi.channel(i));
            M5.Lcd.setTextColor(BLUE);
            delay(700);
        }   delay(40);
            M5.Lcd.fillScreen(BLACK);
            M5.Lcd.setCursor(1,1);
            for (int i = 2; i < n; ++i) {
            // Print SSID and RSSI for each network found
            M5.Lcd.setCursor(1,1);
            M5.Lcd.print(i + 1);
            M5.Lcd.print(":");
            M5.Lcd.println(WiFi.SSID(i));
            M5.Lcd.print("Signal RSSI(");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.println(")");
            M5.Lcd.setTextColor(RED);
            M5.Lcd.println(WiFi.BSSIDstr(i));
            M5.Lcd.print("Channel:");
            M5.Lcd.println(WiFi.channel(i));
            M5.Lcd.setTextColor(GREEN);
            M5.Lcd.println("Scanning..");
            M5.Lcd.setTextColor(BLUE);
            delay(900);
            M5.Lcd.fillScreen(BLACK);
        }   delay(40);
  }
  
M5.Lcd.fillScreen(BLACK); 
}

void Scan_encryption_type() {
  WiFi.mode(WIFI_STA);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN); 
  M5.Lcd.setCursor(1,1);
  M5.Lcd.println("Scanning with more info.");
  WiFi.disconnect();
  int n = WiFi.scanNetworks();
  if (n == 0) { 
  M5.Lcd.setCursor(1,1);
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.println("No networks found");  
  } else {
    for (int i = 0; i < n; ++i) {
    M5.Lcd.print(WiFi.SSID(i)); 
    if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN) { 
      M5.Lcd.setTextColor(RED); 
      M5.Lcd.println("OPEN");  
      M5.Lcd.setTextColor(GREEN); }
    if(WiFi.encryptionType(i) == WIFI_AUTH_WEP) { 
      M5.Lcd.setTextColor(BLUE); 
      M5.Lcd.print(":WEP"); 
      M5.Lcd.setTextColor(GREEN); }
    if(WiFi.encryptionType(i) == WIFI_AUTH_WPA_PSK) {
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.print(":WPA_PSK"); 
      M5.Lcd.setTextColor(GREEN); }
    if(WiFi.encryptionType(i) == WIFI_AUTH_WPA2_PSK) { 
      M5.Lcd.setTextColor(PINK);
      M5.Lcd.print(":WPA2_PSK");
      M5.Lcd.setTextColor(GREEN); }
    if(WiFi.encryptionType(i) == WIFI_AUTH_WPA2_ENTERPRISE) { 
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.print(":WPA2_ENTERPRISE"); 
      M5.Lcd.setTextColor(GREEN); } 
    M5.Lcd.println(" "); 
    delay(400);   
    }
    M5.Lcd.fillScreen(BLACK); 
  }
  
}
