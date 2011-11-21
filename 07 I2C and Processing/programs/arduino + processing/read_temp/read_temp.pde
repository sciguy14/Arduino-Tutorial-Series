//Program by Jeremy Blum
//www.jeremyblum.com
//Reads Temp in Celcius and Shows it on Computer

//Include Wire I2C Library
#include  <Wire.h>
int temp_address = 72;

void setup()
{
  //Create Serial Object (9600 Baud)
  Serial.begin(9600);
  
  //Create a Wire Object
  Wire.begin();
}

void loop()
{
  //Send Request
  Wire.beginTransmission(temp_address); //Start talking
  Wire.send(0); //Ask for Register zero
  Wire.endTransmission(); //Complete Transmission
  Wire.requestFrom(temp_address, 1); //Request 1 Byte
  while(Wire.available() == 0); //wait for response
  int c = Wire.receive(); // Get the temp
  
  //do some math...
  int f = round(c*9.0/5.0 +32.0);
  
  Serial.print(c);
  Serial.print("C,");
  Serial.print(f);
  Serial.print("F.");
  
  delay(500);
  
  
}
