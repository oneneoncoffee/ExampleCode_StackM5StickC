// Program : Mandelbrot set random seed fractal generator. 
// For: StackM5Stick C / C PLUS

#include <math.h>
#include <M5StickC.h>
#include <time.h>
const int A = 37;
const int B = 39;

unsigned long delayStart = 0;
bool delayRunning = false;

const int16_t
  bits        = 16,   // Fractional resolution
  pixelWidth  = 320,  // TFT dimensions
  pixelHeight = 240,
  iterations  = 25;  // Fractal iteration limit or 'dwell'
float
  centerReal  = -0.6, // Image center point in complex plane
  centerImag  =  0.0,
  rangeReal   =  7.0, // Image coverage in complex plane
  rangeImag   =  7.0;
  
void setup() {
M5.begin();
M5.Lcd.setRotation(3);
randomSeed(millis());
delayStart = millis();
delayRunning = true;
}

void loop() {
if (delayRunning && ((millis() - delayStart) >= 20000)) {
  delayRunning = false;
  randomSeed(millis());  
}
for( int j = 0; j <= 70; j++) { mandelbrot_set1(); }
  centerReal  = -0.6, // Image center point in complex plane
  centerImag  =  0.0,
  rangeReal   =  random(7.0), // Random image coverage in complex plane
  rangeImag   =  random(7.0); // 
for( int i = 0; i <= 60; i++) {   mandelbrot_set2(); }
  centerReal  = -0.4, 
  centerImag  =  0.0,
  rangeReal   =  7.0, 
  rangeImag   =  7.0;
  for( int v = 0; v <= 40; v++) {   mandelbrot_set3(); }
  centerReal  = -0.8, // Image center point in complex plane
  centerImag  =  0.0,
  rangeReal   =  random(7.5), // Image coverage in complex plane
  rangeImag   =  random(7.5); 
}


void mandelbrot_set1() {
int64_t n, a, b, b2, a2, posReal, posImag;
uint32_t startTime, elapsedTime;

  int32_t
    startReal   = (int64_t)((centerReal - rangeReal * 0.5)   * (float)(1 << bits)),
    startImag   = (int64_t)((centerImag + rangeImag * 0.5)   * (float)(1 << bits)),
    incReal     = (int64_t)((rangeReal / (float)pixelWidth)  * (float)(1 << bits)),
    incImag     = (int64_t)((rangeImag / (float)pixelHeight) * (float)(1 << bits));
  
  startTime = millis();
  posImag = startImag;
  for (int y = 0; y < pixelHeight; y++) {
    posReal = startReal;
    for (int x = 0; x < pixelWidth; x++) {
      a = posReal;
      b = posImag;
      for (n = iterations; n > 0 ; n--) {
        a2 = (a * a) >> bits;
        b2 = (b * b) >> bits;
        if ((a2 + b2) >= (16 << bits)) 
          break;
        b  = posImag + ((a * b) >> (bits - 1));
        a  = posReal + a2 - b2;
      }
      M5.Lcd.drawPixel(x, y, (n * 29)<<8 | (n * 67));
    posReal -= incReal;
    }
    posImag += incImag;
  }
  
  elapsedTime = millis()-startTime;
  
  rangeReal *= 0.95;
  rangeImag *= 0.95;
}


void mandelbrot_set2() {   

int64_t n, a, b, b2, a2, posReal, posImag;
uint32_t startTime, elapsedTime;

  int32_t
    startReal   = (int64_t)((centerReal - rangeReal * 0.5)   * (float)(1 << bits)),
    startImag   = (int64_t)((centerImag + rangeImag * 0.5)   * (float)(1 << bits)),
    incReal     = (int64_t)((rangeReal / (float)pixelWidth)  * (float)(1 << bits)),
    incImag     = (int64_t)((rangeImag / (float)pixelHeight) * (float)(1 << bits));
  
  startTime = millis();
  posImag = startImag;
  for (int y = 0; y < pixelHeight; y++) {
    posReal = startReal;
    for (int x = 0; x < pixelWidth; x++) {
      a = posReal;
      b = posImag;
      for (n = iterations; n > 0 ; n--) {
        a2 = (a * a) >> bits;
        b2 = (b * b) >> bits;
        if ((a2 + b2) >= (16 << bits)) 
          break;
        b  = posImag + ((a * b) >> (bits - 1));
        a  = posReal + a2 - b2;
      }
      M5.Lcd.drawPixel(y, x, (n * 29)<<8 | (n * 67));
    posReal += incReal;
    }
    posImag -= incImag;
  }
  
  elapsedTime = millis()-startTime;
  
  rangeReal *= 0.95;
  rangeImag *= 0.95;
}



void mandelbrot_set3() {   

int64_t n, a, b, b2, a2, posReal, posImag;
uint32_t startTime, elapsedTime;

  int32_t
    startReal   = (int64_t)((centerReal - rangeReal * 0.5)   * (float)(1 << bits)),
    startImag   = (int64_t)((centerImag + rangeImag * 0.5)   * (float)(1 << bits)),
    incReal     = (int64_t)((rangeReal / (float)pixelWidth)  * (float)(1 << bits)),
    incImag     = (int64_t)((rangeImag / (float)pixelHeight) * (float)(1 << bits));
  
  startTime = millis();
  posImag = startImag;
  for (int x = 0; x < pixelHeight; x++) {
    posReal = startReal;
    for (int y = 0; y < pixelWidth; y++) {
      a = posReal;
      b = posImag;
      for (n = iterations; n > 0 ; n--) {
        a2 = (a * a) >> bits;
        b2 = (b * b) >> bits;
        if ((a2 + b2) >= (16 << bits)) 
          break;
        b  = posImag + ((a * b) >> (bits - 1));
        a  = posReal + a2 - b2;
      }
      M5.Lcd.drawPixel(x, y, (n * 19)<<6 | (n * 47));
    posReal += incReal;
    }
    posImag -= incImag;
  }
  
  elapsedTime = millis()-startTime;
    
  rangeReal *=0.54; 
  rangeImag *=0.69;
  delayRunning = true; // shuffel the cards 
}
