//Reads the State of a Pot and displays on screen

int potPin = 0;

void setup()
{
  //sets the button pin as an input
  pinMode(potPin, INPUT);  
  
  //Allows us to listen to serial communications from the arduino
  Serial.begin(9600); 
}

void loop()
{
  // print the button state to a serial terminal
  Serial.println(analogRead(potPin)); 
  delay(1000);
  //wait one second, then print again.
}
