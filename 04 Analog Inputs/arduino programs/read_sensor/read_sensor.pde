//Program by Jeremy Blum
//www.jeremyblum.com

//Reads and analog sensor and displays the value
int sensePin = 0;

void setup()
{
  //Note: We don't need to specifiy sensePin as an
  //input, since it defaults to that when we read it

  //This is the default value, but we can set it anyways
  analogReference(DEFAULT); //5V Reference on UNO
  
  //Allows us to listen to serial communications from the arduino
  Serial.begin(9600); 
}

void loop()
{
  // print the button state to a serial terminal
  Serial.println(analogRead(sensePin)); 
  delay(500);
  //wait half a second, then print again.
}
