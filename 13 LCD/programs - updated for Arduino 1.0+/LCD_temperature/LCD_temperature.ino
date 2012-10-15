//Jeremy Blum's Arduino Tutorial Series - Episode 13 - LCDs
//Sample Code - LCD Temperature Display
//http://www.jeremyblum.com
//Debouncing code from Tutorial 2: http://jeremyblum.com/2011/01/10/arduino-tutorial-2-now-with-more-blinky-things/
//I2C Code from Tutorial 7: http://jeremyblum.com/2011/02/13/arduino-tutorial-7-i2c-and-processing/
//LiquidCrystal library by David A. Mellis, Limor Fried (http://www.ladyada.net), and Tom Igoe
//http://www.arduino.cc/en/Tutorial/LiquidCrystal

//Include Wire I2C Library
#include  <Wire.h>
int temp_address = 72;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
};

int switchPin = 8;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean celcius = true;

void setup() {
  //Mode Button
  pinMode(switchPin, INPUT);
  
   //Create a Wire Object
  Wire.begin();
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("ROOM TEMPERATURE");
  
  lcd.setCursor(11,1);
  lcd.print("mode>");
  
  //Make progress characters
  lcd.createChar(0, degree);
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(switchPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}

void loop() {
  
  //Handle Temperature
  //Send Request
  Wire.beginTransmission(temp_address); //Start talking
  Wire.send(0); //Ask for Register zero
  Wire.endTransmission(); //Complete Transmission
  Wire.requestFrom(temp_address, 1); //Request 1 Byte
  while(Wire.available() == 0); //wait for response
  int c = Wire.receive(); // Get the temp in c
  //do some math...
  int f = round(c*9.0/5.0 +32.0);
  
  
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH)
  {
    if (celcius) celcius = false;
    else celcius = true;
    
    //Erase old characters
    lcd.setCursor(0,1);
    lcd.print("           ");
  }
  lastButton = currentButton;
 
    
 lcd.setCursor(0,1);
 if (celcius)
 {
   lcd.print(c);
   lcd.write((byte)0);
   lcd.print("C");
 }
 else
 {
   lcd.print(f);
   lcd.write((byte)0);
   lcd.print("F");
 }
   
}
