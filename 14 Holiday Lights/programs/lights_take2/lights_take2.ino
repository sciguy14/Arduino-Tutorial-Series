//Jeremy Blum's Arduino Tutorial Series - Episode 14 - Lights and Sound Holiday Special
//Sample Code 2 - Driving all 50 LEDs using an array powered by both stereo channels
//http://www.jeremyblum.com
//WS2801 Library and Helper Functions by Adafruit http://www.adafruit.com

/* 
  The circuit:
 * A0 from Amplififed Left Channel
 * A1 from Amplified Right Channel
 * Digital 2 to Light Clock Line
 * Digital 3 to Light Data Line
 * Don't forget to connect all your grounds!
 */

//SPI Library
#include "SPI.h"

//RGB LED Library
//You can download it here: https://github.com/adafruit/Adafruit-WS2801-Library/archive/master.zip
//Install it in your library folder and restart the Arduino IDE
#include "Adafruit_WS2801.h"

//Analog Input Pins
int left_channel = 0;
int right_channel = 1;

//Light Control Pins
int light_data = 3;
int light_clk = 2;

//Set Strip Constants
const int length = 50;
const int half = length/2;

//Library Setup
Adafruit_WS2801 strip = Adafruit_WS2801(length, light_data, light_clk);

//Set up arrays for cycling through all the pixels.  I'm assuming you have an even number of lights.
uint32_t left_array[half];
uint32_t right_array[half];

void setup()
{
  //Fill pixel arrays with zeros
  for(int i=0; i<half;i++)
  {
    left_array[i] = 0;
    right_array[i] = 0;
  }
  
  //Initialize Strip
  strip.begin();
  strip.show(); 
  
  
}

void loop()
{
  //Set the hue (0-255) and 24-bit color depending on left channel value
  byte hue_left = constrain(map(analogRead(left_channel), 0, 400, 0, 255), 0, 255);
  uint32_t color_left = Wheel(hue_left);
  
  //Set the hue (0-255) and 24-bit color depending on right channel value
  byte hue_right = constrain(map(analogRead(right_channel), 0, 400, 0, 255), 0, 255);
  uint32_t color_right = Wheel(hue_right);
  
  //Shift the current values.
  for (int i = 0; i<half-1; i++)
  {
    left_array[i] = left_array[i+1];
    right_array[i] = right_array[i+1];
  }
  
  //Fill in the new value at the end of each array
  left_array[half-1] = color_left;
  right_array[half-1] = color_right;
  
  //Go through each Pixel on the strip and set its color
  for (int i=0; i<half; i++)
  {
    //set pixel color
    strip.setPixelColor(i, left_array[i]);
    strip.setPixelColor(length-i-1, right_array[i]);
  }


  //Display the new values
  strip.show();
  
  //sample delay
  delay(40);

}

/* Helper functions */
//http://www.ladyada.net/products/rgbledpixel/

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
