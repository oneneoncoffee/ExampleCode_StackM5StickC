// 
// Please note this clock is 24 hour standard time.
//
// NTP server http://0.north-america.pool.ntp.org/   
// https://www.ntppool.org/en/  
// pool.ntp.org: public ntp time server for everyone.
//  NTP server urls: 
// http://0.north-america.pool.ntp.org/   
// https://www.ntppool.org/en/  
//
// Timezone urls: 
// https://www.timeanddate.com/  
// https://en.wikipedia.org/wiki/List_of_UTC_time_offsets
// So with much reading I found the following to be effective daylight offset in Sec = -7  (timezone maps are available on-line)  GMT offset = -25200       
// https://en.wikipedia.org/wiki/List_of_UTC_time_offsets
// pool.ntp.org: public ntp time server for everyone.
// NTP is an internet protocol that’s used to synchronise the clocks on computer networks to within a few milliseconds of universal coordinated time (UTC). 
// It enables devices to request and receive UTC from a server that, in turn, receives precise time from an atomic clock.
// The pool.ntp.org project is a big virtual cluster of timeservers providing reliable easy to use NTP service for millions of clients.
// The pool is being used by hundreds of millions of systems around the world. 
// It's the default "time server" for most of the major Linux distributions and many networked appliances such as smart devices / internet of things etc.  
// With a little luck and searching you will find the correct settings for your timezone. 
//
// How do I use the timezone map and find the GMT offset in milliseconds?
// You need to adjust the UTC offset for your timezone in milliseconds. 
// You can do so with this simple math trick:
// UTC -7*60*60 = −25200
// 
// Daylight saving time? 
// The website timeanddate.com is awesome for finding the current UTC/GMT offset.
// And you can use this website to search by state anywhere in the world for timezone offsets.  
// UTC -6*60*60 = -21600 
// 

#include <M5StickC.h> 
#include <WiFi.h> 
#include "Timex.h"
const char* ssid = "Teddylove1230";
const char* password = "Teddylove1230";
char* server = "0.north-america.pool.ntp.org";
int timezone = -21600; 
int tcount = 170; 
bool timeToDo(int tbase) {
  tcount++; 
  if (tcount == tbase) {
    tcount = 0; 
    return true;
  } else { return false; }
}
bool lcd = true; 
unsigned long runTime = 0;
float sx = 0, sy = 0;
uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

void setup() {
M5.begin(); 
M5.Lcd.setRotation(1); 
M5.Lcd.fillScreen(BLACK);
background(); 
}

void loop() {
    M5.update(); 
    button_code();   
    display_time(); 
}


void button_code() {
  if (M5.BtnA.pressedFor(2000)) {
    timeSync(); 
  } else {
  if (M5.BtnA.wasPressed()) { background();  }
  }
  if (M5.BtnB.wasPressed()) {
  if (lcd) {
    M5.Lcd.writecommand(ST7735_DISPOFF);
    M5.Axp.ScreenBreath(0);
    lcd = !lcd;   
  } else {
  M5.Lcd.writecommand(ST7735_DISPON); 
  M5.Axp.ScreenBreath(255); 
  lcd = !lcd;  
  }
  }
}

void background() {
 int rz = random(0, 126);
  for (int px = 1; px < 180; px++)
  {
    for (int py = 0; py < 70; py++)
    {
      float x0 = (map(px, 0, rz, -250000/2, -242500/2)) / 100000.0; //scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
      float yy0 = (map(py, 0,rz , -75000/4, -61000/4)) / 100000.0; //scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
      float xx = 0.0;
      float yy = 0.0;
      int iteration = 0;
      int max_iteration = 30;
      while ( ((xx * xx + yy * yy) < 4)  &&  (iteration < max_iteration) )
      {
        float xtemp = xx * xx - yy * yy + x0;
        yy = 2 * xx * yy + yy0;
        xx = xtemp;
        iteration++;
      } 
      int color = rainbow((3*iteration+64)%128);
      yield();
      M5.Lcd.drawPixel(px,py, color);
  
    }
  }  
}

void display_time() {
 if (timeToDo(1000)) {
  M5.Lcd.setTextSize(3); 
  M5.Rtc.GetTime(&RTC_TimeStruct); 
  M5.Rtc.GetData(&RTC_DateStruct);
  M5.Lcd.setTextColor(BLACK, RED);  
  M5.Lcd.setCursor(11, 15);  
  M5.Lcd.drawRect(8,10, 149, 30, WHITE); 
  M5.Lcd.fillRect(10,13, 145, 22, RED);
  M5.Lcd.printf("%2d:%2d.%2d\n",RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
  M5.Lcd.setCursor(27, 50);
  M5.Lcd.setTextSize(2); 
  M5.Lcd.setTextColor(BLACK, RED);     
  M5.Lcd.drawRect(25, 48, 124, 20, WHITE); 
  M5.Lcd.printf("%02d-%02d-%04d\n", RTC_DateStruct.Month, RTC_DateStruct.Date,  RTC_DateStruct.Year);  
  delay(45);  
 } 
}

unsigned int rainbow(int value)
{

  byte red = 0; 
  byte green = 0;
  byte blue = 0; 

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  if (quadrant == 4) {
    blue = 70 - 3 * (value % 32);
    red = random(0, 128);
    green = 0;
  }
  return (red << 11) + (green << 5) + (blue << 8) + blue;
}

void timeSync() {
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.setCursor(1,1); 
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Connecting to network,"); 
  M5.Lcd.printf("%s\n", ssid); 
  delay(1500); 
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.setCursor(20, 15); 
  WiFi.begin(ssid, password); 
  while(WiFi.status() != WL_CONNECTED) {
    display_time(); 
  }
  M5.Lcd.setCursor(14, 15); 
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.println("Connected to network."); 
  delay(1000); 
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.setCursor(20,15); 
  configTime(timezone, 0, server);
  struct tm timeInfo; 
  if (getLocalTime(&timeInfo)) {
   RTC_TimeTypeDef TimeStruct;
      TimeStruct.Hours   = timeInfo.tm_hour;
      TimeStruct.Minutes = timeInfo.tm_min;
      TimeStruct.Seconds = timeInfo.tm_sec;
      M5.Rtc.SetTime(&TimeStruct); 
      RTC_DateTypeDef DateStruct;
      DateStruct.WeekDay = timeInfo.tm_wday;
      DateStruct.Month = timeInfo.tm_mon + 1;
      DateStruct.Date = timeInfo.tm_mday;
      DateStruct.Year = timeInfo.tm_year + 1900;
      M5.Rtc.SetData(&DateStruct);
      M5.Lcd.setCursor(20,15);
      M5.Lcd.setTextSize(1); 
      M5.Lcd.setTextColor(BLUE, BLACK);  
      M5.Lcd.println("SYNC form Server to RTC device finished!"); 
      delay(1500);
      M5.Lcd.fillScreen(BLACK); 
      M5.Lcd.setTextSize(2);
      M5.Rtc.GetTime(&RTC_TimeStruct);
      M5.Rtc.GetData(&RTC_DateStruct);
      M5.Lcd.setCursor(27, 15);
      M5.Lcd.setTextColor(RED,BLACK); 
      M5.Lcd.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
      M5.Lcd.setCursor(27, 50);
      M5.Lcd.setTextSize(1);
      M5.Lcd.setTextColor(GREEN,BLACK); 
      M5.Lcd.printf("Date: %04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date); 
   delay(1500); 
  }
}
