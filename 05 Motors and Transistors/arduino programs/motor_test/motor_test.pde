//Program by Jeremy Blum
//www.jeremyblum.com
//Test Motor Speed Using a Transistor

//Define Pins
int motorPin = 9;

void setup()
{
  //Set the PWM Motor pin as an output
  pinMode(motorPin, OUTPUT);
}

void loop()
{
  //Increase Motor Speed from 0 -> 255
  for (int i=0; i<=255; i++)
  {
    analogWrite(motorPin, i);
    delay(10);
  }
  
  delay(500); //Hold it!
  
  //Decrease Motor Speed from 255 -> 0
  for(int i=255; i>=0; i--)
  {
    analogWrite(motorPin, i);
    delay(10);
  }
  
  delay(500); //Hold it!
  
}
