#include <M5StickC.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRutils.h>
const uint16_t kIrLedPin = 9;
IRsend irsend(kIrLedPin);

uint32_t tvPowerOffCodes[] = {
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
  0x1AE6409F,      // Hisence
  0x1FE48B7,       // JVC
  0x31CEB847,      // Mitsubishi
  0x20DF23DC,      // Daewoo
  0xF7C03F,        // Grundig
  0xA3C8D728,      // Bang & Gulfsen
  0xB14CE957,      // Funai
  0xE0E09966,      // RCA
  0x30CF13EC,      // Piooneer
  0xF7C87F,        // Thomson
  0x0xD7E84B1C,    // Akai
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
};

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(BLUE, GRAY);
    M5.Lcd.print("TV-B-GONE");
  irsend.begin();
  M5.Lcd.setTextSize(1);
}

void loop() {

  for (uint8_t i = 0; i < sizeof(tvPowerOffCodes) / sizeof(tvPowerOffCodes[0]); i++) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Sending code %d\n", i + 1);
    //irsend.sendNEC(tvPowerOffCodes[i], 32);
    delay(500);
  }
}
