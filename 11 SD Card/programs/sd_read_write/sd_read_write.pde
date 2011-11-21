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

float refresh_rate = 0.0;

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
  
  //Read the Configuration information (COMMANDS.txt)
  File commandFile = SD.open("COMMANDS.txt");
  if (commandFile)
  {
    Serial.println("Reading Command File");
    
    float decade = pow(10, (commandFile.available() - 1));
    while(commandFile.available())
    {
      float temp = (commandFile.read() - '0');
      refresh_rate = temp*decade+refresh_rate;
      decade = decade/10;
    }
    Serial.print("Refresh Rate = ");
    Serial.print(refresh_rate);
    Serial.println("ms");
  }
  else
  {
    Serial.println("Could not read command file.");
    return;
  }
  
}

void loop()
{
  
  String dataString = "Hello";
  
  //Open a file to write to
  //Only one file can be open at a time
  File logFile = SD.open("LOG.txt", FILE_WRITE);
  if (logFile)
  {
    logFile.println(dataString);
    logFile.close();
    Serial.println(dataString);
  }
  else
  {
    Serial.println("LOG.txt");
    Serial.println("Couldn't open log file");
  }
  delay(refresh_rate);
}
