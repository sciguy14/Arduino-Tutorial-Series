//Jeremy Blum's Arduino Tutorial Series - Episode 14 - Lights and Sound Holiday Special
//Sample Code 1 - Blinking an RGB LED chain to mono music
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

//Library Setup
Adafruit_WS2801 strip = Adafruit_WS2801(50, light_data, light_clk);

void setup()
{
  //Initialize Serial Connection (for debugging)
  Serial.begin(9600);
 
  //Initialize Strip
  strip.begin();
  strip.show();
  
  
}

void loop()
{
  
  //Print out some Debug Info
  Serial.print("L: ");
  Serial.print(analogRead(left_channel));
  Serial.print("     R: ");
  Serial.println(analogRead(right_channel));



  //Set the hue (0-255) depending on left channel value
 byte hue = constrain(map(analogRead(left_channel), 0, 400, 0, 255), 0, 255);
  
  //convert the hue to a 24-bit color
  uint32_t color = Wheel(hue);
  
  //Go through each Pixel on the strip and set its color
  for (int i=0; i<strip.numPixels(); i++)
  {
    //set pixel color
    strip.setPixelColor(i, color);
  }


  //Display the new values
  strip.show();
  
  //sample delay
  delay(100);

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
