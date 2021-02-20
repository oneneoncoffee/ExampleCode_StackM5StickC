//  Magic numbers 
//  A random number picker for the StackM5StickC


#define IWIDTH  320
#define IHEIGHT 30

#define WAIT 10

#include <M5StickC.h>

TFT_eSprite img = TFT_eSprite(&M5.Lcd); 

void setup(void) {
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLUE);
}

void loop() {

  while (1)
  {
    img.createSprite(IWIDTH, IHEIGHT);
    img.fillSprite(TFT_BLACK); 

    for (int pos = IWIDTH; pos > 0; pos--)
    {
      build_banner("Magic numbers       ", pos);
      img.pushSprite(0, 0);

      delay(WAIT);
    }

    img.deleteSprite();
    numberBox(random(100), 4, 40);
    numberBox(random(100), 4, 100);
    
  }
}


void build_banner(String msg, int xpos)
{
  int h = IHEIGHT;
  while (h--) img.drawFastHLine(0, h, IWIDTH, rainbow(h * 4));

  img.fillRect  (IWIDTH / 2 - 20, IHEIGHT / 2 - 10, 40, 20, TFT_YELLOW);
  img.fillCircle(IWIDTH / 2, IHEIGHT / 2, 10, TFT_ORANGE);
  img.setTextSize(1);           // Font size scaling is x1
  img.setTextFont(4);           // Font 4 selected
  img.setTextColor(TFT_BLACK);  // Black text, no background colour
  img.setTextWrap(false);       // Turn of wrap so we can print past end of sprite
  img.setCursor(xpos, 2);  // Print text at xpos
  img.print(msg);
  img.setCursor(xpos - IWIDTH, 2); // Print text at xpos - sprite width
  img.print(msg);
}

void numberBox(int num, int x, int y)
{
  // Create a sprite 80 pixels wide, 50 high (8kbytes of RAM needed)
  img.createSprite(80, 50);

  // Fill it with black
  img.fillSprite(TFT_BLACK);

  // Draw a backgorund of 2 filled triangles
  img.fillTriangle(  0, 0,  0, 49, 40, 25, TFT_RED);
  img.fillTriangle( 79, 0, 79, 49, 40, 25, TFT_DARKGREEN);

  // Set the font parameters
  img.setTextSize(1);           // Font size scaling is x1
  img.setFreeFont(&FreeSerifBoldItalic24pt7b);  // Select free font
  img.setTextColor(TFT_WHITE);  // White text, no background colour

  // Set text coordinate datum to middle centre
  img.setTextDatum(MC_DATUM);

  // Draw the number in middle of 80 x 50 sprite
  img.drawNumber(num, 40, 25);

  // Push sprite to TFT screen CGRAM at coordinate x,y (top left corner)
  img.pushSprite(x, y);

  // Delete sprite to free up the RAM
  img.deleteSprite();
}

unsigned int rainbow(byte value)
{
  byte red   = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue  = 0; // Blue is the bottom 5 bits

  byte sector = value >> 5;
  byte amplit = value & 0x1F;

  switch (sector)
  {
    case 0:
      red   = 0x1F;
      green = amplit;
      blue  = 0;
      break;
    case 1:
      red   = 0x1F - amplit;
      green = 0x1F;
      blue  = 0;
      break;
    case 2:
      red   = 0;
      green = 0x1F;
      blue  = amplit;
      break;
    case 3:
      red   = 0;
      green = 0x1F - amplit;
      blue  = 0x1F;
      break;
  }

  return red << 11 | green << 6 | blue;
}
