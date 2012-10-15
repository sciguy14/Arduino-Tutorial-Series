//Jeremy Blum's Arduino Tutorial Series - Episode 13 - LCDs
//Sample Code - LCD Progress Bar
//http://www.jeremyblum.com
//LiquidCrystal library by David A. Mellis, Limor Fried (http://www.ladyada.net), and Tom Igoe
//http://www.arduino.cc/en/Tutorial/LiquidCrystal

/* 
  The circuit:
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


byte p20[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};
byte p40[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte p60[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};
byte p80[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};
byte p100[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Jeremy's Display");
  
  //Make progress characters
  lcd.createChar(0, p20);
  lcd.createChar(1, p40);
  lcd.createChar(2, p60);
  lcd.createChar(3, p80);
  lcd.createChar(4, p100);
}

void loop() {
 lcd.setCursor(0,1);
 lcd.print("                ");   
 
 for (int i = 0; i<16; i++)
 {
   
   for (int j=0; j<5; j++)
   {
      lcd.setCursor(i, 1);   
      lcd.write(j);
      delay(100);
    } 
   
    
 }

  
}
