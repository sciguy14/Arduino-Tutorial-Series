//Program by Jeremy Blum
//www.jeremyblum.com
//Send data from a POT over serial to the computer

//Define Pins
int potPin = 0;

void setup()
{
  //Create Serial Object (9600 Baud)
  Serial.begin(9600);
}

void loop()
{
  int val = map(analogRead(potPin), 0, 1023, 0, 255);
  Serial.println(val);
  delay(50);
  
}
