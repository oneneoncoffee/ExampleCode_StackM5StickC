#include <M5StickC.h>
#include <Wire.h>
#include "AdafruitSensor.h"
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include "bmm150defs.h"
#include "AXP192.h"
#include "SHT3X.h"
#include "Seeed_BMP280.h"
BMM150 bmm = BMM150();
bmm150_mag_data value_offset;
Adafruit_BMP280 bme;
Adafruit_Sensor *bmp_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bme.getPressureSensor();
const int BTNA = 37;
const int BTNB = 39;
#include "I2C_BM8563.h"
#define BM8563_I2C_SDA 21
#define BM8563_I2C_SCL 22 
#define LED_PIN 10
I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire1);
int last_value = 0;
int current_value = 0;
SHT3X sht3x; 

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

  while ((millis() - timeStart) < timeout)
  {
    bmm.read_mag_data();

    /* Update x-Axis max/min value */
    if (value_x_min > bmm.raw_mag_data.raw_datax)
    {
      value_x_min = bmm.raw_mag_data.raw_datax;
      // Serial.print("Update value_x_min: ");
      // Serial.println(value_x_min);

    }
    else if (value_x_max < bmm.raw_mag_data.raw_datax)
    {
      value_x_max = bmm.raw_mag_data.raw_datax;
      // Serial.print("update value_x_max: ");
      // Serial.println(value_x_max);
    }

    /* Update y-Axis max/min value */
    if (value_y_min > bmm.raw_mag_data.raw_datay)
    {
      value_y_min = bmm.raw_mag_data.raw_datay;
      // Serial.print("Update value_y_min: ");
      // Serial.println(value_y_min);

    }
    else if (value_y_max < bmm.raw_mag_data.raw_datay)
    {
      value_y_max = bmm.raw_mag_data.raw_datay;
      // Serial.print("update value_y_max: ");
      // Serial.println(value_y_max);
    }

    /* Update z-Axis max/min value */
    if (value_z_min > bmm.raw_mag_data.raw_dataz)
    {
      value_z_min = bmm.raw_mag_data.raw_dataz;
      // Serial.print("Update value_z_min: ");
      // Serial.println(value_z_min);

    }
    else if (value_z_max < bmm.raw_mag_data.raw_dataz)
    {
      value_z_max = bmm.raw_mag_data.raw_dataz;
      // Serial.print("update value_z_max: ");
      // Serial.println(value_z_max);
    }

    Serial.print(".");
    delay(1);

  }

  value_offset.x = value_x_min + (value_x_max - value_x_min) / 2;
  value_offset.y = value_y_min + (value_y_max - value_y_min) / 2;
  value_offset.z = value_z_min + (value_z_max - value_z_min) / 2;
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  Wire.begin(0, 26);
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);
  pinMode(M5_BUTTON_HOME, INPUT);

  if (bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    Serial.println("Chip ID can not read!");
    while (1);
  } else {
    Serial.println("Initialize done!");
  }
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  calibrate(10);
  Serial.print("\n\rCalibrate done..");

  /* Default settings from datasheet. */
  bme.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
Wire1.begin(BM8563_I2C_SDA, BM8563_I2C_SCL);
rtc.begin();   
M5.IMU.Init();
pinMode(BTNA, INPUT);
pinMode(BTNB, INPUT);
pinMode(LED_PIN, OUTPUT);
Wire.begin(0,26);
digitalWrite(LED_PIN, LOW); 
delay(500); 
digitalWrite(LED_PIN, HIGH); 
delay(500); 
}

void LED() {
digitalWrite(LED_PIN, HIGH); 
delay(500); 
digitalWrite(LED_PIN, LOW); 
delay(500);    
digitalWrite(LED_PIN, LOW); 
delay(500); 
digitalWrite(LED_PIN, HIGH); 
delay(500); 
}

void error_chk() {
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
    Serial.printf(".");
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
}  

void loop() {
error_chk();  
current_value = digitalRead(BTNB);
if(current_value != last_value) {
  if(current_value ==0) {
  LED();
  main_prog();  
  delay(1000);
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
  LED();
  main_prog();
  }
  last_value = current_value;
}
frame_clear();

  float tmp = 0.0;                       
  float hum = 0.0;
  float ftmp = 0.0;
    if(sht3x.get()==0){
    tmp = sht3x.cTemp;
    hum = sht3x.humidity;
    ftmp = sht3x.fTemp;
  }
  M5.Lcd.setTextSize(1.9);
  M5.Lcd.print("\r\n");
  M5.Lcd.print(" Altitude:\r\n");
  M5.Lcd.setTextSize(2.1);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.print(" >");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.printf("%2.2f \n", bme.readAltitude(3294)); // geoinfo.msl.mt.gov East Missoula Elevation: 3249   
  M5.Lcd.setTextSize(1.9);
  M5.Lcd.print("\r\n");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print(" Humidity ");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%2.0f%%\n", hum);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf(" Pressure ");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%2.2f hPa\n", bme.readPressure()/100);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf(" H2O Boil point:");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%2.2f *C\n", bme.waterBoilingPoint(bme.readPressure()/100));
current_value = digitalRead(BTNA);
if(current_value != last_value) {
  if(current_value ==0) {
  M5.Axp.SetLDO2(true);      
  LED();
   M5.Axp.LightSleep(SLEEP_SEC(5));
  }
  last_value = current_value;
}
  delay(1999);
}


void main_prog() {
  frame_1();
  delay(779);
  frame_clear();
  delay(779);
  frame_2();
  delay(1000);
  frame_3();
  delay(3000);
  frame_4();
  delay(1000);
}

void frame_clear() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRect(0, 0, 149, 80, BLUE);
  M5.Lcd.setCursor(3, 1, 1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillRect(2, 2, 139, 69, BLACK);
}

void frame_4() {
  LED();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRect(0, 0, 149, 80, BLUE);
  M5.Lcd.setCursor(1, 4, 1);
  M5.Lcd.fillRect(2, 2, 139, 69, BLACK);
  M5.Lcd.setTextSize(1);
  //This will show raw pressure data: 
  //M5.Lcd.printf("\nPressure:\n%2.2f\n", pressure);
  //float pressure = bme.readPressure();
  //float tmp = dht12.readTemperature(); // Works with ENV not ENVII
  //float hum = dht12.readHumidity();
  float tmp = 0.0;                       // Works with (ENV ENVII)
  float hum = 0.0;
  float ftmp = 0.0;
    if(sht3x.get()==0){
    tmp = sht3x.cTemp;
    hum = sht3x.humidity;
    ftmp = sht3x.fTemp;
  }
  M5.Lcd.setTextSize(2.8);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Temp:       ");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(4.8);
  M5.Lcd.printf("%2.1fF \n", ftmp);
  M5.Lcd.setTextColor(RED);
  delay(3000);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRect(0, 0, 149, 80, BLUE);
  M5.Lcd.setCursor(3, 1, 1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillRect(2, 2, 139, 69, BLACK);
  M5.Lcd.setTextSize(4.8);
  M5.Lcd.printf("%2.0f%%\n", hum);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2.8);
  M5.Lcd.print(" Humidity ");
  delay(3000);
  M5.Lcd.setTextSize(1.8);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRect(0, 0, 149, 80, BLUE);
  M5.Lcd.setCursor(5, 4, 1);
  M5.Lcd.fillRect(2, 2, 139, 69, BLACK);
  M5.Lcd.setTextSize(1.8);
  M5.Lcd.setTextColor(WHITE); 
  M5.Lcd.printf("Fahrenheit:");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%2.1f *F", ftmp);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf("\n Celsius:");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%.2f *C \n", tmp);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf(" Altitude:");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%2.2f \n", bme.readAltitude(3294)); // geoinfo.msl.mt.gov East Missoula Elevation: 3249   
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf(" Pressure ");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%2.2f hPa\n", bme.readPressure()/100);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf(" H2O Boil point:");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.printf("%2.2f *C\n", bme.waterBoilingPoint(bme.readPressure()/100));
  delay(4000);
}

void frame_2() {
  sensors_event_t temp_event;
  bmp_temp->getEvent(&temp_event);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRect(0, 0, 149, 80, BLUE);
  M5.Lcd.setCursor(3, 1, 1);
  M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("Temperature:");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.print("  ");
  M5.Lcd.print(temp_event.temperature);
  M5.Lcd.println(" *C");
  float tempcf = 0;
  tempcf = (temp_event.temperature * 1.8) + 32;
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.print("  ");
  M5.Lcd.print(tempcf);
  M5.Lcd.print(" *F");
}

void frame_3() {
   M5.Lcd.fillScreen(BLACK);
   M5.Lcd.drawRect(0, 0, 149, 80, BLUE);
   M5.Lcd.setTextSize(1);
   M5.Lcd.setCursor(1, 20, 1);
   M5.Lcd.setTextColor(WHITE);
   M5.Lcd.printf("AXP Temp:");
   M5.Lcd.setTextColor(RED); 
   M5.Lcd.printf("%.1fC \r\n", M5.Axp.GetTempInAXP192());
   M5.Lcd.setCursor(3, 40);
   M5.Lcd.setTextColor(WHITE);
   M5.Lcd.printf("Bat:");
   M5.Lcd.setTextColor(RED); 
   M5.Lcd.printf("V:%.3fvI:%.3fma\r\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatCurrent());
   M5.Lcd.setCursor(3, 50);  
   M5.Lcd.setTextColor(WHITE);
   M5.Lcd.printf("USB:");
   M5.Lcd.setTextColor(RED);
   M5.Lcd.printf("V:%.3fvI:%.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
   M5.Lcd.setCursor(3, 60);
   M5.Lcd.setTextColor(WHITE);    
   M5.Lcd.printf("Bat power ");
   M5.Lcd.setTextColor(RED); 
   M5.Lcd.printf("%.3fmw", M5.Axp.GetBatPower());
   M5.update();
}

void frame_1() {
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  bmm150_mag_data value;
  bmm.read_mag_data();
  float pressure = bme.readPressure();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRect(0, 0, 149, 80, BLUE);
  M5.Lcd.setCursor(3, 1, 1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println(F("Temperature:"));
  M5.Lcd.setTextColor(RED);
  M5.Lcd.print("  ");
  M5.Lcd.print(temp_event.temperature);
  M5.Lcd.println(" *C");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println(" Pressure:");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.print("  ");
  M5.Lcd.print(pressure_event.pressure);
  //M5.Lcd.printf("[%1.0f]", pressure);
  M5.Lcd.println("hPa");
}
