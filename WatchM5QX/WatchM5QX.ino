// StackM5Stick C - 24 Hour clock & push button WiFi scanner 

#include <I2C_BM8563.h>
#include <M5StickC.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <time.h>
#include <WiFiUdp.h>
const int BTNA = 37;
const int BTNB = 39;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
#define BM8563_I2C_SDA 21
#define BM8563_I2C_SCL 22
I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire1);
const char *ssid = "xxxxxxxxx";
const char *password = "xxxxxxxxx";
int hour;
int minute;
int second;
int Epoch;
int last_value = 0;
int current_value = 0;

String formattedDate;
String dayStamp;

String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
RTC_DateTypeDef RTC_DateStruct;

void setup() {
M5.begin();
Serial.begin(115200);
M5.Lcd.setRotation(3);
WiFi.begin(ssid, password);
Wire1.begin(BM8563_I2C_SDA, BM8563_I2C_SCL);
rtc.begin();
M5.Lcd.setTextSize(1);
M5.Lcd.println("Connecting to: ");
M5.Lcd.println(ssid);
while ( WiFi.status() != WL_CONNECTED ) {
delay (500);
M5.Lcd.print(".");
}
timeTest();
  Serial.println("");
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setCursor(1,1);
M5.Lcd.println("");
timeClient.begin();
//  Set offset in Seconds for timezone 
// GMT +1 = 3600 
// GMT +2 = 7200
// GMT +3 = 10800
// GMT +4 = 14400
// GMT +5 = 18000
// GMT +6 = 21600   
// GMT +7 = 25200
// GMT +8 = 28800
timeClient.setTimeOffset(21600);
delay (1000);
timeClient.update();
Epoch = timeClient.getEpochTime();
hour = timeClient.getHours();
minute = timeClient.getMinutes();
second = timeClient.getSeconds();
M5.Lcd.setRotation(3);
M5.Lcd.print("Setting up ...\nEpoch:");
M5.Lcd.println(Epoch);
M5.Lcd.print("TIME: ");
M5.Lcd.print(hour);
M5.Lcd.print(":");
M5.Lcd.print(minute);
M5.Lcd.print(":");
M5.Lcd.println(second);
M5.Lcd.print("IP address:");
M5.Lcd.println(WiFi.localIP());
delay(5000);  
M5.Lcd.fillScreen(BLACK);
I2C_BM8563_TimeTypeDef timeStruct;
timeStruct.hours = hour;
timeStruct.minutes = minute;
timeStruct.seconds = second;
rtc.setTime(&timeStruct);

// Manual Real time clock set 
//  RTC_DateTypeDef DateStruct;
//  DateStruct.WeekDay = 2;
//  DateStruct.Month = 8;
//  DateStruct.Date = 6;
//  DateStruct.Year = 2021;
//  M5.Rtc.SetData(&DateStruct);
//  timeTest();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}

void timeTest() {
   //Get a time structure (Just a test)
 
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

  //Print complete date:
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);

}

void loop() {
I2C_BM8563_TimeTypeDef timeStruct;
M5.Lcd.setTextSize(2);
M5.Lcd.setCursor(30,1);
rtc.getTime(&timeStruct);
int n = WiFi.scanNetworks();
timeClient.update();
delay(100);
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setTextSize(3);
M5.Lcd.setTextColor(ORANGE);
M5.Lcd.setCursor(1, 1);
timeClient.forceUpdate();
M5.Lcd.printf("%02d %02d %02d\n",timeStruct.hours, timeStruct.minutes, timeStruct.seconds);
//M5.Lcd.println(timeClient.getFormattedTime());
delay(10);
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setCursor(1, 1);
M5.Lcd.printf("%02d:%02d.%02d\n",timeStruct.hours, timeStruct.minutes, timeStruct.seconds);
delay(11);
current_value = digitalRead(BTNB);
if(current_value != last_value) {
  if(current_value ==0) { 
  delay(100);
  M5.Axp.SetLDO2(false); 
  
  M5.Axp.DeepSleep(SLEEP_SEC(20)); 
  M5.Axp.PowerOff();     
  }
  last_value = current_value;
}
current_value = digitalRead(BTNA);
if(current_value != last_value) {
  if(current_value ==0) {
  M5.Axp.SetLDO2(true);      
  scan_Networks();
  }
  last_value = current_value;
}

}


void scan_Networks() {
M5.Lcd.setCursor(3, 20);
M5.Lcd.setTextSize(1);
int n = WiFi.scanNetworks();
  if (n == 0) {
        M5.Lcd.println("no networks found");
    } else {
        M5.Lcd.setCursor(1,40);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print(n);
        M5.Lcd.println(" networks found");
        delay(70);
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(1,1);
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
            M5.Lcd.print(WiFi.SSID(i));
            M5.Lcd.print("(");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.print(")");
            M5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"":"");
            delay(400);
        }   delay(40);
    }
M5.Lcd.setTextColor(ORANGE);
delay(700);
}
