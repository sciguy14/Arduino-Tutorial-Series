//Program by Jeremy Blum
//www.jeremyblum.com
//Uses commands from computer to control arduino

int ledPin = 13;

void setup()
{
  //Create Serial Object
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //Have the arduino wait to receive input
  while (Serial.available() == 0);
  
  //Read the Input
  int val = Serial.read() - '0';
  
  if (val == 1) 
  {
    Serial.println("Led is On"); 
    digitalWrite(ledPin, HIGH);
  }
  else if (val == 0)
  {
    Serial.println("Led is Off");
    digitalWrite(ledPin, LOW);
  }
  else
  {
    Serial.println("Invalid!");
  }
  Serial.flush();
  
  
}
