#include <M5StickC.h>
#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include "time.h"
#include "AXP192.h"
#include "SHT3X.h"
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "bmm150.h"
#include "bmm150_defs.h"

SHT3X sht3x; 
BMM150 bmm = BMM150();
bmm150_mag_data value_offset;
Adafruit_BMP280 bme;

const char* ssid       = "Teddylove1230";
const char* password   = "Teddylove1230";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 18000; 
const int   daylightOffset_sec = 0700; 
const int A = 37;
const int B = 39;
int tcount = 0700;
int last_value = 0;
int current_value = 0;
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

void calibrate(uint32_t timeout)
{
  int16_t value_x_min = 0;
  int16_t value_x_max = 0;
  int16_t value_y_min = 0;
  int16_t value_y_max = 0;
  int16_t value_z_min = 0;
  int16_t value_z_max = 0;
  uint32_t timeStart = 0;

  bmm.read_mag_data();  
  value_x_min = bmm.raw_mag_data.raw_datax;
  value_x_max =+ bmm.raw_mag_data.raw_datax;
  value_y_min = bmm.raw_mag_data.raw_datay;
  value_y_max = bmm.raw_mag_data.raw_datay;
  value_z_min = bmm.raw_mag_data.raw_dataz;
  value_z_max = bmm.raw_mag_data.raw_dataz;
  delay(100);

  timeStart = millis();
  
  while((millis() - timeStart) < timeout)
  {
    bmm.read_mag_data();
    
    /* Update x-Axis max/min value */
    if(value_x_min > bmm.raw_mag_data.raw_datax)
    {
      value_x_min = bmm.raw_mag_data.raw_datax;
      // Serial.print("Update value_x_min: ");
      // Serial.println(value_x_min);

    } 
    else if(value_x_max < bmm.raw_mag_data.raw_datax)
    {
      value_x_max = bmm.raw_mag_data.raw_datax;
      // Serial.print("update value_x_max: ");
      // Serial.println(value_x_max);
    }

    /* Update y-Axis max/min value */
    if(value_y_min > bmm.raw_mag_data.raw_datay)
    {
      value_y_min = bmm.raw_mag_data.raw_datay;
      // Serial.print("Update value_y_min: ");
      // Serial.println(value_y_min);

    } 
    else if(value_y_max < bmm.raw_mag_data.raw_datay)
    {
      value_y_max = bmm.raw_mag_data.raw_datay;
      // Serial.print("update value_y_max: ");
      // Serial.println(value_y_max);
    }

    /* Update z-Axis max/min value */
    if(value_z_min > bmm.raw_mag_data.raw_dataz)
    {
      value_z_min = bmm.raw_mag_data.raw_dataz;
      // Serial.print("Update value_z_min: ");
      // Serial.println(value_z_min);

    } 
    else if(value_z_max < bmm.raw_mag_data.raw_dataz)
    {
      value_z_max = bmm.raw_mag_data.raw_dataz;
      // Serial.print("update value_z_max: ");
      // Serial.println(value_z_max);
    }
    
    Serial.print(".");
    delay(1);

  }

  value_offset.x = value_x_min + (value_x_max - value_x_min)/2;
  value_offset.y = value_y_min + (value_y_max - value_y_min)/2;
  value_offset.z = value_z_min + (value_z_max - value_z_min)/2;
}
uint8_t sleep_counter = 0;
int dot[6][6][2] {
  {{35,35}},
  {{15,15},{55,55}},
  {{15,15},{35,35},{55,55}},
  {{15,15},{15,55},{55,15},{55,55}},
  {{15,15},{15,55},{35,35},{55,15},{55,55}},
  {{15,15},{15,35},{15,55},{55,15},{55,35},{55,55}},
  };

float accX = 0;
float accY = 0;
float accZ = 0;
float temp = 0;

#define NSTARS 789
uint8_t sx[NSTARS] = {};
uint8_t sy[NSTARS] = {};
uint8_t sz[NSTARS] = {};

uint8_t za, zb, zc, zx;
inline uint8_t __attribute__((always_inline)) rng()
{
  zx++;
  za = (za^zc^zx);
  zb = (zb+za);
  zc = (zc+((zb>>1)^za));
  return zc;
}

void setup() {
 Wire.begin(0,26); 
 M5.begin();
 M5.MPU6886.Init();
 Serial.begin(115200);
 pinMode(A, INPUT);
 pinMode(B, INPUT);
 Serial.println("\n");
  za = random(256);
  zb = random(256);
  zc = random(256);
  zx = random(256);
 M5.Lcd.setRotation(2);
 M5.Lcd.fillScreen(BLACK);
 M5.Lcd.setTextSize(1);
 sync();
   if(bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    Serial.println("Chip ID can not read!");
    while(1);
  } else {
    Serial.println("Initialize done!");
  }
  if (!bme.begin(0x76)){  
      Serial.println("Could not find a valid BMP280 sensor, check wiring!");
      while (1);
  }
  calibrate(10);
  Serial.print("\n\rCalibrate done..");
}

uint8_t setup_flag = 1;

void loop() {
  
  randomSeed(19);
  unsigned long t0 = micros();
  uint8_t spawnDepthVariation = random(155);

  for(int i = 0; i < NSTARS; ++i)
  {
    if (sz[i] <= 1)
    {
      sx[i] = 160 - 120 + rng();
      sy[i] = rng();
      sz[i] = spawnDepthVariation--;
    }
    else
    {
      int old_screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 40;
      int old_screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 80;

      // This is a faster pixel drawing function for occassions where many single pixels must be drawn
      M5.Lcd.drawPixel(old_screen_x, old_screen_y,TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1)
      {
        //int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
        //int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;
        int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 40;
        int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 80;
  
        if (screen_x >= 0 && screen_y >= 0 && screen_x < 80 && screen_y < 160)
        {
          uint8_t r, g, b;
         r = random(255) - sz[i];
         g = random(255) - sz[i];
         b = random(255) - sz[i];
          M5.Lcd.drawPixel(screen_x, screen_y, M5.Lcd.color565(r,g,b));
        }
        else
          sz[i] = 0; // Out of screen, die.
      }
    }
  }
  unsigned long t1 = micros();
current_value = digitalRead(A);
if(current_value != last_value) {
  if(current_value ==0) {
  sync();
  Serial.println("Button A pressed");  
  sync_time();
  }
  last_value = current_value;
}
current_value = digitalRead(B);
if(current_value != last_value) {
  if(current_value ==0) {
    Serial.println("Button B pressed");
     dice_roll();
  M5.Lcd.setRotation(2);
  stardrop();  
  M5.Lcd.setRotation(2);
  M5.Lcd.setCursor(40, 0, 2);
  M5.Lcd.setTextColor(WHITE);
  m5.Lcd.setTextSize(0); 
  }
  last_value = current_value;
    M5.Lcd.setRotation(2);
  M5.Lcd.fillScreen(BLACK);
}
 M5.update();  
 // Display information with accel data 
    M5.IMU.getAccelData(&accX,&accY,&accZ);
    if (accZ > 1.9 ) { timeday(); tempdata(); }
    if (accY > 1.8 ) { tempdata(); timeday(); }
    if (accX > 1.7 ) { compus(); tempdata(); timeday();  }
     
}

void compus() {
  bmmcal();
  bmm150_mag_data value;
  bmm.read_mag_data();

  value.x = bmm.raw_mag_data.raw_datax - value_offset.x;
  value.y = bmm.raw_mag_data.raw_datay - value_offset.y;
  value.z = bmm.raw_mag_data.raw_dataz - value_offset.z;

  float xyHeading = atan2(value.x, value.y);
  float zxHeading = atan2(value.z, value.x);
  float heading = xyHeading;

  if(heading < 0)
    heading += 2*PI;
  if(heading > 2*PI)
    heading -= 2*PI;
  float headingDegrees = heading * 180/M_PI; 
  float xyHeadingDegrees = xyHeading * 180 / M_PI;
  float zxHeadingDegrees = zxHeading * 180 / M_PI;
  M5.Lcd.setRotation(2);
  stardrop();  
  M5.Lcd.setRotation(3);
  Serial.print("Heading: ");
  Serial.println(headingDegrees);
  Serial.print("xyHeadingDegrees: ");
  Serial.println(xyHeadingDegrees);
  Serial.print("zxHeadingDegrees: ");
  Serial.println(zxHeadingDegrees);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.printf("[Compass heading] \nDegrees: %2.1f\n", headingDegrees);
  M5.Lcd.print("xyHeading: ");
  M5.Lcd.println(xyHeadingDegrees);
  M5.Lcd.print("zxHeading: ");
  M5.Lcd.println(zxHeadingDegrees);

  delay(2999);
  M5.Lcd.setRotation(2);
  M5.Lcd.fillScreen(BLACK);
}

void bmmcal() {
     if(!setup_flag){
     setup_flag = 1;

     if(bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    Serial.println("Chip ID can not read!");
    while(1);
  } else {
    Serial.println("Initialize done!");
  }
  if (!bme.begin(0x76)){  
      Serial.println("Could not find a valid BMP280 sensor, check wiring!");
      while (1);
  }
  calibrate(10);
  Serial.print("\n\rCalibrate done..");
 }
}


void tempdata() {
  M5.MPU6886.getTempData(&temp);
  bmmcal();  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setRotation(2);
  stardrop();  
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0, 0, 2);
  float tmp = 0.0;
  float hum = 0.0;
  float ftmp = 0.0;
    if(sht3x.get()==0){
    tmp = sht3x.cTemp;
    hum = sht3x.humidity;
    ftmp = sht3x.fTemp;
  }

  M5.Lcd.printf("Temperature: %2.1fC \nHumidity: %2.0f%%\n Temperature: %2.1fF\n+", tmp, hum, ftmp);
  M5.Lcd.printf("Temperature: %.2f C\n", temp);
  float pressure = bme.readPressure();
  M5.Lcd.printf("pressure: %2.1f\n", pressure);
  delay(2882);
  M5.Lcd.setRotation(2);
  M5.Lcd.fillScreen(BLACK);
}

void axcel() {
    M5.IMU.Init();
    while(1) {
    M5.IMU.getAccelData(&accX,&accY,&accZ);
    if (accX > 1.5 ||  accY > 1.5 ) {
      break;
    }
  }
}

void stardrop() {
   unsigned long t0 = micros();
  uint8_t spawnDepthVariation = 987;

  for(int i = 0; i < NSTARS; ++i)
  {
    if (sz[i] <= 1)
    {
      sx[i] = 160 - 120 + rng();
      sy[i] = rng();
      sz[i] = spawnDepthVariation--;
    }
    else
    {
      int old_screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 40;
      int old_screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 80;

      M5.Lcd.drawPixel(old_screen_x, old_screen_y,TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1)
      {
        //int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
        //int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;
        int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 40;
        int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 80;
  
        if (screen_x >= 0 && screen_y >= 0 && screen_x < 80 && screen_y < 160)
        {
          uint8_t r, g, b;
  
          //rq = rainbow(map(r%60,130,110,90,110));
          //g = rainbow(map(r%39,230,120,100,110));
          //b = rainbow(map(r%230,230,120,150,210)); 
          //rq=g=b= rainbow(map(r%230,230,120,150,210));
          r=random(255) - sz[i];
          g=random(255) - sz[i]; 
          b=random(255) - sz[i];
          M5.Lcd.drawPixel(screen_x, screen_y, M5.Lcd.color565(r,g,b));
        }
        else
          sz[i] = 0; // Out of screen, die.
      }
    }
  }
  unsigned long t1 = micros();
}

void ntplocaltime() {
  struct tm timeinfo;
   if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
   }
   Serial.println("Checking remote server time.");
   Serial.println(&timeinfo, "%A, %B %d %Y");
   Serial.println(&timeinfo, "24Hour time: %H:%M.%S");
   Serial.println(&timeinfo, "12Hour time: %I:%M.%S");
   if(getLocalTime(&timeinfo)) {
    // Set real time clock 
    RTC_TimeTypeDef TimeStruct;
      TimeStruct.Hours   = timeinfo.tm_hour;
      TimeStruct.Minutes = timeinfo.tm_min;
      TimeStruct.Seconds = timeinfo.tm_sec;
      M5.Rtc.SetTime(&TimeStruct);
    // Set real time data
    RTC_DateTypeDef DateStruct;
      DateStruct.WeekDay = timeinfo.tm_wday;
      DateStruct.Month = timeinfo.tm_mon + 1;
      DateStruct.Date = timeinfo.tm_mday;
      DateStruct.Year = timeinfo.tm_year + 1900;
      M5.Rtc.SetData(&DateStruct);     
   }
 
}
void sync_time() {
    M5.Lcd.setRotation(3);
    M5.Lcd.setTextSize(2);
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
    M5.Lcd.setCursor(27, 15);
    M5.Lcd.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
    M5.Lcd.setCursor(27, 50);
    M5.Lcd.setTextSize(1);
    M5.Lcd.printf("Date: %04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    axcel();
}

void timeday() {
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setRotation(2);
    stardrop();
     M5.Lcd.setCursor(3, 1);
     M5.Lcd.setRotation(3);
     M5.Lcd.setTextSize(2);  
     M5.Lcd.println(&timeinfo, "%I:%M.%S");
     M5.Lcd.setCursor(1, 30);
     M5.Lcd.setTextSize(1);   
     M5.Lcd.println(&timeinfo, "%A, %B %d");
     M5.Lcd.setTextSize(2);
     M5.Lcd.println(&timeinfo, "%Y");
     M5.Lcd.setRotation(2);
     M5.Lcd.setTextSize(1);
     delay(3000);
}

void sync() {
 WiFi.begin(ssid, password);
 Serial.printf("Connecting to %s ", ssid);
 while (WiFi.status() != WL_CONNECTED) {
  delay(500); 
  Serial.print(".");
 } 
Serial.println(" CONNECTED");
configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); 
ntplocaltime();
Serial.println("Closeing connection..");
WiFi.disconnect(true);
WiFi.mode(WIFI_OFF);
}


void dice_roll(void) {
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_RED); 
  M5.Lcd.setCursor(0, 1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("SHAKE ME");   
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(1, 0, 2);
  M5.update();
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("\n\n BATTERY: %.3f\n", M5.Axp.GetBatPower());
  M5.Lcd.printf("USB-C POWER:\r\nV: %.3fv  I: %.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());  
  delay(450);
  while(1) {
    M5.IMU.getAccelData(&accX,&accY,&accZ);
    if (accX > 1.5 ||  accY > 1.5 ) {
      break;
    }
  }
  M5.Lcd.fillScreen(TFT_RED);
  delay(300); 
  int number = random(0, 6);
  draw_dice(5,5,number);
  delay(300);
  number = random(0, 6);
  draw_dice(85,5,number);
  delay(2500);
}

void draw_dice(int16_t x, int16_t y, int n) {
  M5.Lcd.fillRect(x, y, 70, 70, WHITE);
  for(int d = 0; d < 6; d++) {
    if (dot[n][d][0] > 0) {
        M5.Lcd.fillCircle(x+dot[n][d][0], y+dot[n][d][1], 7, TFT_BLACK);
    }
  }
} 
