//Program by Jeremy Blum
//www.jeremyblum.com
//Uses commands from computer to control arduino

//Define Pins
int ledPin = 13;

void setup()
{
  //Create Serial Object (9600 Baud)
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);  
}

void loop()
{

  
  //Now we play the waiting game.
  while (Serial.available() == 0);
  
  //read the incoming byte
  int val = Serial.read();
  
  Serial.println(val);

  
}
