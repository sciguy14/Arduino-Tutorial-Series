//Program by Jeremy Blum
//www.jeremyblum.com
//Turn on an LED if a room is dim, and motion is detected

//Define Pins
int motionPin = 0;
int lightPin = 1;
int ledPin = 9;

//Distance Variables
int lastDist = 0;
int currentDist = 0;

//Threshold for Movement
int thresh = 200;

void setup()
{
  //The LED pin needs to be set as an output
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // read the sensor
  int lightVal = analogRead(lightPin);
  currentDist = analogRead(motionPin);
  
  //Does the current distance deviate from the last distance by more than the threshold?
  if ((currentDist > lastDist + thresh || currentDist < lastDist - thresh) && lightVal < 800)
  {
    digitalWrite(ledPin, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  
  lastDist = currentDist;
  
  
}
