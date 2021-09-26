#include <Adafruit_NeoPixel.h>

#define PIN 2

#define NUMPIXELS 100

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  leds.begin();
  byte mat[3][10][10]
  ={
    
  };
int i=0;
  for(unsigned int f=0;f<10;f++){
    for(unsigned int c=0;c<10;c++){
      leds.setPixelColor(i,mat[0][c][f],mat[1][c][f],mat[2][c][f]);
      i++;
    }
  }
  leds.show();
}

void loop()
{
}