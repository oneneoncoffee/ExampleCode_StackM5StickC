#include <M5StickC.h>
#include "I2C_BM8563.h"
#define BM8563_I2C_SDA 21
#define BM8563_I2C_SCL 22 
#define LED_PIN 10
const int BTNA = 37;
const int BTNB = 39;
int last_value = 0;
int current_value = 0;
#include "DHT12.h"
#include "SHT3X.h"
#include <Wire.h>
#include "Seeed_BMP280.h"
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "bmm150.h"
#include "bmm150_defs.h"
DHT12 dht12; 
SHT3X sht3x; 
BMM150 bmm = BMM150();
bmm150_mag_data value_offset;
Adafruit_BMP280 bme;
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
  value_x_max = bmm.raw_mag_data.raw_datax;
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
    
   
    delay(1);

  }

  value_offset.x = value_x_min + (value_x_max - value_x_min)/2;
  value_offset.y = value_y_min + (value_y_max - value_y_min)/2;
  value_offset.z = value_z_min + (value_z_max - value_z_min)/2;
}
I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire1);

void setup() {
Serial.begin(115200);
Wire1.begin(BM8563_I2C_SDA, BM8563_I2C_SCL);
rtc.begin();
M5.begin();
M5.IMU.Init();
M5.Lcd.setRotation(3);
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setCursor(1,1);
pinMode(BTNA, INPUT);
pinMode(BTNB, INPUT);
Wire.begin(0,26);
  if(bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    M5.Lcd.printf("BMM150 [OK]");
  } else {
  }
  if (!bme.begin(0x76)){  
      M5.Lcd.setTextColor(BLACK, WHITE);
      M5.Lcd.printf("Error: Could not find a valid BMP280 sensor.");
  }
  calibrate(10); 
  bme.setSampling(Adafruit_BMP280::MODE_NORMAL,
  Adafruit_BMP280::SAMPLING_X2,
  Adafruit_BMP280::SAMPLING_X16,
  Adafruit_BMP280::FILTER_X16,
  Adafruit_BMP280::STANDBY_MS_500);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // ON
  delay(500); 
  digitalWrite(LED_PIN, HIGH); // OFF
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setRotation(0);
}
float temp = 0;
uint8_t setup_flag = 1;
uint8_t btnB_flag =1;
long int flag =0;
void loop() {   
  M5.Lcd.fillScreen(BLACK);   
  M5.IMU.getTempData(&temp);
  int t = 444; 
  I2C_BM8563_DateTypeDef dateStruct;
  // Manual Adjust date 
  //dateStruct.weekDay = 6;
  //dateStruct.month = 3;
  //dateStruct.date = 6;
  //dateStruct.year = 2021;
  //rtc.setDate(&dateStruct);
  
  I2C_BM8563_TimeTypeDef timeStruct;
  // Manual Adjust time
  //timeStruct.hours   = 9;
  //timeStruct.minutes = 25;
  //timeStruct.seconds = 30;
  //rtc.setTime(&timeStruct);
 
  rtc.getDate(&dateStruct);
  rtc.getTime(&timeStruct);
    
  M5.Lcd.setRotation(0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setRotation(3);  
  datebuff();
  M5.Lcd.setCursor(11, 15);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf ("%02d", timeStruct.hours);

  random_color_wheel();
  M5.Lcd.printf(":");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf("%02d", timeStruct.minutes);
  random_color_wheel();
  M5.Lcd.printf(":");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf("%02d", timeStruct.seconds);           
               delay(t);
  M5.Lcd.setCursor(11, 15);
  M5.Lcd.printf("               \n");             
  M5.Lcd.setCursor(11, 15);
  datebuff(); 
  M5.Lcd.fillScreen(BLACK);
  datebuff();
  M5.Lcd.printf("%02d %02d %02d \n",              
                timeStruct.hours,
                timeStruct.minutes,
                timeStruct.seconds
               );         
               delay(t);  
               datebuff();   
  M5.Lcd.setCursor(11, 15);
  M5.Lcd.printf("               \n");   
  M5.Lcd.setCursor(11, 15);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf("%02d",timeStruct.hours);
  random_color_wheel();
  M5.Lcd.printf(":");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf("%02d",timeStruct.minutes);
  random_color_wheel();
  M5.Lcd.printf(":");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf("%02d\n",timeStruct.seconds);         
               delay(t);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(19, 45);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("DATE:"); 
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.printf("%02d/%02d/%04d \n",
                dateStruct.month,
                dateStruct.date,
                dateStruct.year
                );
               delay(t);
 
  datebuff();
  if(bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    M5.Lcd.fillScreen(WHITE);
    for(int x=0; x<5000; x++) {
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(BLACK, WHITE);
    M5.Lcd.setCursor(1,1);
    M5.Lcd.printf("Warning: ENVII hat removed form watch.");
    }
    M5.Axp.DeepSleep(SLEEP_SEC(120));
    M5.Axp.PowerOff();
  } else {
  }
  if (!bme.begin(0x76)){  
    M5.Lcd.fillScreen(WHITE);
    for(int x=0; x<5000; x++) {
    M5.Lcd.setTextSize(1);   
    M5.Lcd.setTextColor(BLACK, WHITE);
    M5.Lcd.setCursor(1,1);
    M5.Lcd.printf("Warning: Error ENVII hat Failure.");
    }
    M5.Axp.DeepSleep(SLEEP_SEC(120));
    M5.Axp.PowerOff();
  }
  calibrate(10);
  M5.Lcd.fillScreen(BLACK);
current_value = digitalRead(BTNA);
if(current_value != last_value) {
if(current_value ==0) {
   btnA_RUN();
}
  last_value = current_value; 
}
current_value = digitalRead(BTNB);
if(current_value != last_value) {
  if(current_value ==0) {
  btnB_RUN();
  }
  last_value = current_value;
}
if( btnB_flag ==0) {
  flag++;
  if (flag>=3) { btnB_flag = 1; flag = 0; }
  M5.Lcd.setCursor(1, 1);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(1);
  float pressure = bme.readPressure();
  //float tmp = dht12.readTemperature(); // Works with ENV not ENVII
  //float hum = dht12.readHumidity();
  float tmp = 0.0;                       // Works with (ENV/ENVII) WTF? 
  float hum = 0.0;
  float ftmp = 0.0;
    if(sht3x.get()==0){
    tmp = sht3x.cTemp;
    hum = sht3x.humidity;
    ftmp = sht3x.fTemp;
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(1,1);
  random_color_wheel();
  M5.Lcd.printf("Temp:%2.1fF\n", ftmp);
  random_color_wheel();
  M5.Lcd.printf("Humidity %2.0f%% ", hum);
  random_color_wheel();
  M5.Lcd.printf("\nPressure:\n%2.2f\n", pressure);
  M5.Lcd.setTextSize(1.8); 
  delay(t+3600);  
  M5.Lcd.setCursor(1,1);
  M5.Lcd.fillScreen(BLACK);
  random_color_wheel();
  M5.Lcd.printf("Humidity: %2.0f%% \n", hum);
  random_color_wheel();
  M5.Lcd.printf("Pressure:%2.1f\n", pressure);
  random_color_wheel();
  M5.Lcd.printf("Fahrenheit:%2.1fF", ftmp);
  random_color_wheel();
  M5.Lcd.printf("\nCelsius:%.2fC \n", temp);
  random_color_wheel();
  M5.Lcd.printf("Altitude:\n%2.2f \n", bme.readAltitude(3294)); // geoinfo.msl.mt.gov East Missoula Elevation: 3249   
  random_color_wheel();
  M5.Lcd.printf("Pressure %2.2f hPa\n", bme.readPressure()/100);
  random_color_wheel();
  M5.Lcd.printf("H2O Boil point:%2.2fC\n", bme.waterBoilingPoint(bme.readPressure()/100));
  delay(3000);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0, 1);
    M5.Lcd.setTextSize(1);
    for(int y=0; y < 3; y++) {
    for(int x=0; x < 3; x++) {
    M5.Lcd.setCursor(1,1);  
    M5.Lcd.setTextColor(BLACK, WHITE);
    M5.Lcd.printf("VOLTAGE:\n");
    delay(300);
    M5.Lcd.setCursor(1,1);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("VOLTAGE:\n");
    delay(300);
    }
    M5.Lcd.printf("Battery:%.3f/%.3fmw\r\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatPower());
    M5.Lcd.printf("APS:%.3f \r\n", M5.Axp.GetAPSVoltage());
    M5.Lcd.printf("USB V:%.3fv/I:%.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
    delay(400);
    M5.Lcd.setCursor(1,1);
    } 
  M5.Lcd.fillScreen(BLACK);
}
  M5.Lcd.fillScreen(BLACK);
}

void datebuff() {
  int t = 20;
  I2C_BM8563_DateTypeDef dateStruct;
  rtc.getDate(&dateStruct);
  M5.Lcd.setCursor(11, 15);
  M5.Lcd.printf("               \n");     
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(19, 45);
  delay(t);
    M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(19, 45);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("DATE:"); 
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.printf("%02d/%02d/%04d \n",
                dateStruct.month,
                dateStruct.date,
                dateStruct.year
                );
               delay(t);
   M5.Lcd.setCursor(111,45);
  switch (dateStruct.month) {
    case 1: M5.Lcd.printf("Jan"); break;
    case 2: M5.Lcd.printf("Feb"); break;
    case 3: M5.Lcd.printf("Mar"); break;
    case 4: M5.Lcd.printf("Apr"); break;
    case 5: M5.Lcd.printf("May"); break;
    case 6: M5.Lcd.printf("Jun"); break;
    case 7: M5.Lcd.printf("Jul"); break;
    case 8: M5.Lcd.printf("Aug"); break;
    case 9: M5.Lcd.printf("Sep"); break;
    case 10: M5.Lcd.printf("Oct"); break;
    case 11: M5.Lcd.printf("Nov"); break;
    case 12: M5.Lcd.printf("Dec"); break;
  };
  delay(t);             
  M5.Lcd.setCursor(0, 58);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("%.2fC", temp);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(11, 15);
  M5.Lcd.setTextSize(3); 
}

void btnA_RUN() {  
  for(int x=0; x < 200; x++) {
  delay(140);
current_value = digitalRead(BTNB);
if(current_value != last_value) {
if(current_value ==0) {
        M5.Axp.SetLDO2(false);
        M5.Axp.LightSleep(SLEEP_SEC(330));
        M5.Axp.SetLDO2(true);     //M5.Axp.DeepSleep(SLEEP_SEC(30));
}
  last_value = current_value; 
}

  M5.Lcd.fillScreen(BLACK);  
  M5.Lcd.setTextSize(5);  
  M5.Lcd.setCursor(0,0);
  random_color_wheel();
  I2C_BM8563_TimeTypeDef timeStruct;
  rtc.getTime(&timeStruct); 
  M5.Lcd.setCursor(0,0);
    if(timeStruct.hours == 00) {  
  M5.Lcd.printf ("12", timeStruct.hours);
  random_color_wheel();
  M5.Lcd.printf(":");
  random_color_wheel();
  M5.Lcd.printf("%02d",timeStruct.minutes);
  random_color_wheel();
  M5.Lcd.printf(".");
  random_color_wheel();
  M5.Lcd.printf("%02d",timeStruct.seconds); 
  random_color_wheel();
  random_color_wheel();
  M5.Lcd.printf("A");
  random_color_wheel();
  M5.Lcd.printf("M\n");
  M5.Lcd.setCursor(5,50);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("%03d", x);
  } else {
  M5.Lcd.printf("%02d",timeStruct.hours%12); 
  random_color_wheel();
  M5.Lcd.printf(":");  
  random_color_wheel();            
  M5.Lcd.printf("%02d",timeStruct.minutes);
  random_color_wheel();
  M5.Lcd.printf(".");
  random_color_wheel();
  M5.Lcd.printf("%02d",timeStruct.seconds); 
  random_color_wheel();
  if(timeStruct.hours >=12) {
  random_color_wheel();
  M5.Lcd.printf("P");
  random_color_wheel();
  M5.Lcd.printf("M\n");
  M5.Lcd.setCursor(100,70);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("%03d", x); 
  timeStruct.hours == timeStruct.hours%12;
  if(timeStruct.hours == 0) {
    timeStruct.hours == 12;
  }
  } else { 
    if(timeStruct.hours == 0) {
      timeStruct.hours == 12; 
    } 
    random_color_wheel();
    M5.Lcd.printf("A");
    random_color_wheel();
    M5.Lcd.printf("M\n");
   M5.Lcd.setCursor(5,50);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("%03d", x);
   }
   delay(140); 
  }        
  }
}

void btnB_RUN() {
  btnB_flag = 0;
  float pressure = bme.readPressure();
  //float tmp = dht12.readTemperature(); // Works with ENV not ENVII
  //float hum = dht12.readHumidity();
  float tmp = 0.0;                       // Works with (ENV/ENVII) WFT? 
  float hum = 0.0;
  float ftmp = 0.0;
    if(sht3x.get()==0){
    tmp = sht3x.cTemp;
    hum = sht3x.humidity;
    ftmp = sht3x.fTemp;
  }
 M5.Lcd.fillScreen(BLACK);
 random_color_wheel();
 M5.Lcd.setCursor(1, 1);
 M5.Lcd.setTextSize(1.9);
 M5.Lcd.printf("Temperature data:\n");
 M5.Lcd.printf("Humidity: %2.0f%% \nPressure:%2.1f\nFahrenheit:%2.1fF", hum, pressure, ftmp);
 M5.Lcd.printf("\nCelsius:%.2fC \n", temp);
 M5.Lcd.printf("Altitude: %2.2f \n", bme.readAltitude(3294)); // East Missoula 
 M5.Lcd.printf("Pressure %2.2f hPa\n", bme.readPressure()/100);
 M5.Lcd.printf("H2O Boil point:%2.2fC", bme.waterBoilingPoint(bme.readPressure()/100)); 
 delay(4600);
 M5.update();
 M5.Lcd.setTextColor(WHITE); 
 M5.Lcd.setCursor(11, 15);
 M5.Lcd.setTextSize(3);
}

void random_color_wheel() {
 randomSeed(255);
 uint8_t red, green, blue; // color vlaues 
 red = random(255) ^ random(100);
 green = random(255) ^ random(100);
 blue = random(255) ^ random(100);
 M5.Lcd.setTextColor(M5.Lcd.color565(red,green,blue));
}
