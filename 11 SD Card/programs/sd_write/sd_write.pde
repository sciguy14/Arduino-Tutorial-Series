//Program by Jeremy Blum
//www.jeremyblum.com
//SD Card Demonstration
//Based on Example by Tom Igoe

#include <SD.h>

//Set by default for the SD Card Library
//MOSI = Pin 11
//MISO = Pin 12
//SCLK = PIN 13
//We always need to set the CS Pin
int CS_pin = 10;
int pow_pin = 8;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing Card");
  //CS Pin is an output
  pinMode(CS_pin, OUTPUT);
  
  //Card will Draw Power from Pin 8, so set it high
  pinMode(pow_pin, OUTPUT);  
  digitalWrite(pow_pin, HIGH);
  
  if (!SD.begin(CS_pin))
  {
      Serial.println("Card Failure");
      return;
  }
  Serial.println("Card Ready");
  
}

void loop()
{
  String dataString = "Hello";
  
  //Open a file to write to
  //Only one file can be open at a time
  
  File dataFile = SD.open("log.txt", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }
  delay(5000);
}
