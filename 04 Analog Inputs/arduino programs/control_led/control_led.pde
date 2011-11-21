//Program by Jeremy Blum
//www.jeremyblum.com

//Control LED brightness with sensor
int sensePin = 0;
int ledPin = 9;

void setup()
{
  //Note: We don't need to specifiy sensePin as an
  //input, since it defaults to that when we read it

  //The LED pin needs to be set as an output
  pinMode(ledPin, OUTPUT);

  //This is the default value, but we can set it anyways
  analogReference(DEFAULT); //5V Reference on UNO
  
}

void loop()
{
  // read the sensor
  int val = analogRead(sensePin);
  val = constrain(val, 750, 900);
  int ledLevel = map(val, 750, 900, 255, 0);
  analogWrite(ledPin, ledLevel);
  
  
}
