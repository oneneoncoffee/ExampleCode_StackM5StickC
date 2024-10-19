#include <M5StickC.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRutils.h>

static constexpr const size_t record_number     = 256;
static constexpr const size_t record_length     = 240;
static constexpr const size_t record_size       = record_number * record_length;
static constexpr const size_t record_samplerate = 17000;
static int16_t prev_y[record_length];
static int16_t prev_h[record_length];
static size_t rec_record_idx  = 2;
static size_t draw_record_idx = 0;
static int16_t *rec_data;


// Define switch 
int currentBrand = 0;

// Remote IR power codes 
uint32_t samsungPower = 0xE0E040BF;
uint32_t sonyPower = 0xA90;
uint32_t lgPower = 0x20DF10EF;
uint32_t panasonicPower = 0x400401FB;
uint32_t toshibaPower = 0x2FD48B7;
uint32_t sharpPower = 0x5EA1B04F;
uint32_t philipsPower = 0x0C; 
// Define sketch pinout
const uint16_t kIrLedPin = 9;
IRsend irsend(kIrLedPin);
#define g10 10
#define g26 26
#define g36 0
#define NSTARS 788
uint8_t sx[NSTARS] = {};
uint8_t sy[NSTARS] = {};
uint8_t sz[NSTARS] = {};
uint8_t za, zb, zc, zx;
// Define custom random colors
uint16_t blueColor = M5.Lcd.color565(0,0,random(100,256));
uint16_t redColor = M5.Lcd.color565(random(100,256),0,0);
uint16_t greenColor = M5.Lcd.color565(0, random(100,255), 0);
// Define static colors 
#define GRAY 808080
inline uint8_t __attribute__((always_inline)) rng() {
    zx++;
    za = (za ^ zc ^ zx);
    zb = (zb + za);
    zc = (zc + ((zb >> 1) ^ za));
    return zc;
}
uint32_t PowerOffCodes[] = {
  0x20DF10EF,      //Samsung
  0xE0E019E6,      //Samsung AA56
  0xE0E040BF,      //LG
  0x0D5F2A,        //TCL 55P715 TV
  0x10EF38C7,      //Panasonic
  0x40040100BCBD,  // Panasonic ON/OFF
  0x40040500BCB9,  // Panasonic soundbar
  0xA55A50AF,      //Sony
  0xF50,           //Sony KDL-EX540 TV
  0xA8B47,         //Sony BD-S1500
  0x10C8E11E,      //Acer K132
  0xF7C03F,        //Philips
  0x4FB040BF,      //Toshiba
  0xB24D50AF,      //Sharp
  0x48B748B7,      //Sanyo
  0x330000FF,      //Sanyo PLV-Z4
  0x878968B7,      // Hitachi
  0x9D9A5F,        // Vizio
  0x20DF23DC,      // Vizio
  0x1AE6409F,      // Hisence
  0x1FE48B7,       // JVC  
  0x010D48B7,      // JVC
  0x31CEB847,      // Mitsubishi
  0x20DF23DC,      // Daewoo
  0xF7C03F,        // Grundig
  0xA3C8D728,      // Bang & Gulfsen
  0xB14CE957,      // Funai
  0xE0E09966,      // RCA
  0x30CF13EC,      // Piooneer
  0xF7C87F,        // Thomson
  0xD7E84B1C,      // Akai
  0x20DF10EF,      // NEC ON/OFF
  0xFD2502FD,      // NEC Soundcore Infini Pro
  0x4FB30CF,       // Goodmans GDSBT1000P
  0x00FF30CF,      // NEC Smart Reveiver VX/CX
  0x00FF0CF3,      // NEC Smart Reveiver
  0x00FEA857,      // Generic VEON TV (eg model SR0322016)
  0xC8052900C,     // VU+ Duo2 CR6 Set-top Box
  0x000800FF,      // Humax HMS-1000T DVB-T2 DVR
  0x2662BA45,      // Fetch TV Mini
  0xE13E13EC,      // Hi-Fi Amp & Receivers
  0x7E817E81,      // Yamaha V1900
  0x7E817E88,      // Yamaha AV Receivers
  0x00FF708F,      // Remote AI Vacumm Cleaners (BACK TO Charging Base)
  0x2FD807F,       // Hitachi 
  0xA25D02FD,      // Sanyo
  0xE0E09966,      // Mitsubishi
};
int menuIndex = 0;
String menuItems[] = {
  "Flashlight Hat ", 
  "Tech-B-Gone    ", 
  "Sleep mode     ",
  "Remote (ON/OFF)",
};
int totalMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);

void setup() {

  pinMode(g26, OUTPUT);
  pinMode(g36, OUTPUT);
  pinMode(g10, OUTPUT);
  digitalWrite(g26, HIGH);
  digitalWrite(g36, HIGH);
  digitalWrite(g10, HIGH);
    za = random(256);
    zb = random(256);
    zc = random(256);
    zx = random(256);

    M5.begin();
    irsend.begin();
    M5.Lcd.setRotation(5);
    M5.Lcd.fillScreen(TFT_BLACK);
while(true) {
M5.Lcd.setTextColor(random(0xFFFF));
M5.Lcd.setCursor(1,40);
M5.Lcd.setTextSize(3);
M5.Lcd.print(" CoSMoS ");
M5.Lcd.setTextSize(1);
M5.Lcd.setCursor(1, 10);
M5.Lcd.setTextColor(RED, BLACK); 
M5.Lcd.print("You hold the keys to...");
stars();
M5.update();
if (M5.BtnA.isPressed()) {
  M5.Lcd.fillScreen(TFT_WHITE);
  M5.Lcd.setRotation(3);
digitalWrite(g26, HIGH);
digitalWrite(g36, HIGH);
digitalWrite(g10, HIGH);
break;
}
}
M5.Lcd.fillScreen(TFT_BLACK);
M5.Lcd.setTextSize(1);
M5.Lcd.setRotation(5);
showMenu();
}   

void loop() {
M5.update();
if (M5.BtnA.wasPressed()) {
  menuIndex = (menuIndex + 1) % totalMenuItems; 
  showMenu();
}
if (M5.BtnB.wasPressed()) {
executeMenuAction();
}
}

void showMenu() {
  M5.Lcd.fillScreen(TFT_BLACK);
  for (int i=0; i< 3; i++) {  
  M5.Lcd.drawCircle(random(1, M5.Lcd.width()-1),random(2, M5.Lcd.height()-5), random(1, 14), redColor);
  M5.Lcd.drawCircle(random(3, M5.Lcd.width()-1),random(5, M5.Lcd.height()-4), random(1, 14), greenColor);
  M5.Lcd.drawCircle(random(1, M5.Lcd.width()-4),random(15, M5.Lcd.height()-3), random(1, 14), blueColor);
  M5.Lcd.drawCircle(random(3, M5.Lcd.width()-2),random(20, M5.Lcd.height()-2), random(1, 14), greenColor);
  M5.Lcd.drawCircle(random(1, M5.Lcd.width()-2),random(3, M5.Lcd.height()-3), random(1, 14), random(0xFFFF));
  }
  for (int i=0; i< 3; i++) {
  M5.Lcd.drawCircle(random(8, M5.Lcd.width()-8),random(31, M5.Lcd.height()-2), random(1, 30), random(0xFFFF));
  }
  M5.Lcd.setCursor(1,20);
  M5.Lcd.setTextSize(1);
  for (int i=0; i < totalMenuItems; i++) {
if (i == menuIndex) {
  M5.Lcd.setTextColor(YELLOW);
} else {
  M5.Lcd.setTextColor(WHITE);
}
M5.Lcd.println(menuItems[i]); 
  }
}

void executeMenuAction() {
  switch(menuIndex) {
    case 0:
    M5.Lcd.fillScreen(BLACK);
    Led_Light();
    showMenu(); 
    break;
    case 1: 
    M5.Lcd.fillScreen(BLACK);
    tech_be_gone();
    showMenu();
    break;
    case 2: 
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextSize(1);
    M5.Lcd.print("Entering sleep mode...");
    delay(1009);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, 0); 
    M5.Axp.DeepSleep();
    showMenu();
    break;
    case 3:
    BadREmote();
    break;
  }
}

void BadREmote() {
M5.Lcd.fillScreen(BLACK);
while(true) {
M5.Lcd.setTextSize(1);
M5.Lcd.setTextColor(GREEN,BLACK);
M5.Lcd.setCursor(0,32);
M5.Lcd.print("Long press buttons to exit");
M5.Lcd.setCursor(10,10);
M5.Lcd.setTextSize(2);
M5.Lcd.setTextColor(WHITE, BLUE);

switch (currentBrand) {
  case 0:
  M5.Lcd.print("Samsung    ");
  break;
  case 1:
  M5.Lcd.print("Sony       ");
  break;
  case 2:
  M5.Lcd.print("LG         ");
  break;
  case 3:
  M5.Lcd.print("Panasonic ");
  break;
}
M5.update();
if (M5.BtnA.wasPressed()) {
  currentBrand = (currentBrand + 1) % 4;
}
if (M5.BtnB.wasPressed()) {
switch (currentBrand) {
  case 0:
  M5.Lcd.setCursor(10,10);  
  M5.Lcd.setTextColor(random(0xFFFF), BLUE);
  M5.Lcd.print("Samsung    ");
  M5.Lcd.setTextSize(2);
  irsend.sendNEC(samsungPower, 32);
  delay(500);
  irsend.sendNEC(0x20DF10EF, 32);
  delay(500);
  irsend.sendNEC(0xE0E019E6, 32);
  delay(500);
  break;
  case 1:  
  M5.Lcd.setCursor(10,10);
  M5.Lcd.setTextColor(random(0xFFFF), BLUE);
  M5.Lcd.print("Sony       ");
  M5.Lcd.setTextSize(2);
  irsend.sendSony(sonyPower, 12);
  delay(500);  
  irsend.sendSony(0xA55A50AF, 32);
  delay(500);
  irsend.sendSony(0xF50, 12);
  delay(500);
  irsend.sendSony(0xA8B47, 12);
  delay(500);
  break;
  case 2:
  M5.Lcd.setCursor(10,10);  
  M5.Lcd.setTextColor(random(0xFFFF), BLUE);
  M5.Lcd.print("LG         ");
  M5.Lcd.setTextSize(2);
  irsend.sendNEC(lgPower, 32);
  break;
  case 3:  
  M5.Lcd.setCursor(10,10);  
  M5.Lcd.setTextColor(random(0xFFFF), BLUE);
  M5.Lcd.print("Panasonic ");
  M5.Lcd.setTextSize(2);
  irsend.sendPanasonic(panasonicPower, 32);
  break;
}
M5.update();
if (M5.BtnA.pressedFor(2000)) {
M5.Lcd.fillScreen(BLACK);
break; break;
}
if (M5.BtnB.pressedFor(1000)) {
M5.Lcd.fillScreen(BLACK);
break; break;
}

}

}
}

void tech_be_gone() {
M5.Lcd.fillScreen(BLACK);
M5.Lcd.print("[OK!]");
while(true) {
M5.update();
if (M5.BtnB.pressedFor(1000)) {
M5.Lcd.fillScreen(BLACK);
break;
}

  for (uint8_t i = 0; i < sizeof(PowerOffCodes) / sizeof(PowerOffCodes[0]); i++) {
    M5.update();
if (M5.BtnA.pressedFor(1001)) {

for (int i = 0; i < 10; i++) {
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setCursor(0,0);
M5.Lcd.setTextSize(1);
M5.Lcd.setTextColor(RED, GRAY);
M5.Lcd.printf("PRESS B BUTTON\n FOR EXIT.");
delay(66);
M5.Lcd.fillScreen(BLACK);
M5.Lcd.setTextColor(GRAY, BLACK);
M5.Lcd.setCursor(0,0);
M5.Lcd.printf("PRESS B BUTTON\n FOR EXIT.");
delay(98);
}
break; break;
}
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Sending code %d\n", i + 1);
    irsend.sendNEC(PowerOffCodes[i], 32);
    M5.Lcd.setCursor(0,10);
    M5.Lcd.printf("TV/AI-BE-GONE\n");
    delay(500);
    irsend.sendSony(PowerOffCodes[i], 32); 
    M5.Lcd.setCursor(0,10);
    M5.Lcd.printf("TV/AI-BE-GONE\n");
    M5.update();
if (M5.BtnB.pressedFor(1000)) {
M5.Lcd.fillScreen(BLACK);
break; break;
}
  }
    M5.Lcd.setCursor(0,10);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Sending other codes.    \n");
    delay(500); 
    irsend.sendSony(0xA90, 12);     
    M5.Lcd.setCursor(0,10);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Sending Sony code.     \n");
    delay(500); 
    irsend.sendPanasonic(0x400401FB, 32);
    M5.Lcd.setCursor(0,10);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Sending Panasonic code.   \n");
    delay(500);
    irsend.sendNEC(0xE0E040BF, 32);
    M5.Lcd.setCursor(0,10);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Sending Samsung code.      \n");
    delay(500);
    irsend.sendNEC(toshibaPower, 32);
    M5.Lcd.setCursor(0,10);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Sending Toshiba code.      \n");
    delay(500); 
    irsend.sendNEC(sharpPower, 32);
    M5.Lcd.setCursor(0,10);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Sending Sharp code.        \n");
    delay(500);
    irsend.sendNEC(philipsPower, 12);
    M5.Lcd.setCursor(0,10);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Sending Philips code.      \n");
    delay(500);
}

}

void Led_Light() {
while(true) { 
M5.update();
if (M5.BtnA.pressedFor(1000)) {
  M5.Lcd.fillScreen(BLACK);
  break;
}
M5.update();
if (M5.BtnA.isPressed()) {
M5.Lcd.setTextColor(WHITE, BLACK);
M5.Lcd.setTextSize(3);
M5.Lcd.setCursor(3,3);
M5.Lcd.drawRect(1, 1, 59, 30, TFT_RED);
M5.Lcd.print("ON ");
digitalWrite(g26, LOW);
digitalWrite(g36, LOW);
digitalWrite(g10, LOW);
}
M5.update();
if (M5.BtnB.isPressed()) {
M5.Lcd.setTextColor(WHITE, BLACK);
M5.Lcd.setTextSize(3);
M5.Lcd.setCursor(3,3);
M5.Lcd.drawRect(1, 1, 59, 30, TFT_RED);
M5.Lcd.print("OFF");
digitalWrite(g26, HIGH);
digitalWrite(g36, HIGH);
digitalWrite(g10, HIGH);
}
M5.update();
if (M5.BtnB.pressedFor(1000)) {
  M5.Lcd.fillScreen(BLACK);
  break;
}
}
}

void stars() {
    unsigned long t0            = micros();
    uint8_t spawnDepthVariation = 155;
    for (int i = 0; i < NSTARS; ++i) {
        if (sz[i] <= 1) {
            sx[i] = 160 - 120 + rng();
            sy[i] = rng();
            sz[i] = spawnDepthVariation--;
        } else {
            int old_screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 80;
            int old_screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 190;
            M5.Lcd.drawPixel(old_screen_x, old_screen_y, TFT_BLACK);
            M5.Lcd.drawPixel(old_screen_x+1, old_screen_y+1, TFT_BLACK);
            sz[i] -= 2;
            if (sz[i] > 1) {
                int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 80;
                int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 190;
                if (screen_x >= 0 && screen_y >= 0 && screen_x < 190 &&
                    screen_y < 160) {
                    uint8_t r, g, b;
                    r = random(0x00FF); 
                    g = random(0xFF00);
                    b = random(0xFFFF) - sz[i];
                    M5.Lcd.drawPixel(screen_x, screen_y,
                                     M5.Lcd.color565(r, g, b));
                    M5.Lcd.drawPixel(screen_x+1, screen_y+1, 
                                     M5.Lcd.color565(random(0xFF00), random(0xFF0F), random(0xF0FF)));
                } else
                    sz[i] = 0;  // Out of screen, die.
            }
        }
    }
    unsigned long t1 = micros();
    Serial.println(1.0 / ((t1 - t0) / 1000000.0));
}
