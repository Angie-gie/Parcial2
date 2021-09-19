#include <Adafruit_NeoPixel.h>

#define PIN 2

#define NUMPIXELS 100

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  byte a=207;
  leds.begin();
  for(unsigned int i=0;i<NUMPIXELS;i+=2){
    leds.setPixelColor(i,a,97,62);
  	leds.setPixelColor(i+1,20,0,255);
  }
  leds.show();
}

void loop()
{
}