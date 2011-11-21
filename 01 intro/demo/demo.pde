/*
Jeremy's First Program
It's awesome!
*/

int ledPin = 13;

void setup()
{
  //initialize pins as outputs
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
