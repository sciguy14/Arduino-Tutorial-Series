/*
Arduino Tutorials
Episode 2
Switch1 Program
Written by: Jeremy Blum
*/

int switchPin = 8;
int ledPin = 13;

void setup()
{
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (digitalRead(switchPin) == HIGH)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}
