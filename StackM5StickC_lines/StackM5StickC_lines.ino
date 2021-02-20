#include <M5StickC.h>
#define DEG2RAD 0.0874532925

int segment = 0;
unsigned int col = 0;
int delta = -1;

  byte red = 31; 
  byte green = 0;
  byte blue = 0;
  byte state = 0;

void setup(void) {
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);
}


void loop() {
  randomSeed(360);
 fillArc(random(110), random(120), segment*6, 1, random(190)-segment/4, random(160)-segment/4, 3, rainbow(col));
  segment+=delta;
  col+=1;
  if (col>191) col = 0;
  if (segment <0) delta = 1;
  if (segment >298) delta = -3; 
 fillArc(random(19, 31), random(29, 87), segment*6, 1, random(19, 41)-segment/4, random(29,8)-segment/6, 4, rainbow(col));
 
}


int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{

  byte seg = 6;
  byte inc = 9; 
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {
    float sx = cos((i - 90) * DEG2RAD + random(i, 40));
    float sy = sin((i - 90) * DEG2RAD + random(i, 30));
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;
    float sx2 = cos((i + seg - 90) * DEG2RAD - random(i));
    float sy2 = sin((i + seg - 90) * DEG2RAD - random(i));
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;


   M5.Lcd.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
   M5.Lcd.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
  }
}

unsigned int brightness(unsigned int colour, int brightness)
{
  byte red  = colour >> 11;
  byte green = (colour & 0x7E0) >> 5;
  byte blue   = colour & 0x1F;

  blue = (blue * brightness)/100;
  green = (green * brightness)/100;
  red = (red * brightness)/100;

  return (red << 11) + (green << 5) + blue;
}

unsigned int rainbow(byte value)
{

    switch (state) {
      case 0:
        green ++;
        if (green == 64) {
          green = 63;
          state = 1;
        }
        break;
      case 1:
        red--;
        if (red == 255) {
          red = 0;
          state = 2;
        }
        break;
      case 2:
        blue ++;
        if (blue == 32) {
          blue = 31;
          state = 3;
        }
        break;
      case 3:
        green --;
        if (green == 255) {
          green = 0;
          state = 4;
        }
        break;
      case 4:
        red ++;
        if (red == 32) {
          red = 31;
          state = 5;
        }
        break;
      case 5:
        blue --;
        if (blue == 255) {
          blue = 0;
          state = 0;
        }
        break;
      case 6: 
      red = random(255);
      green = random(255);
      blue = random(255);
      break;
    }
    return red << 11 | green << 5 | blue;
}
