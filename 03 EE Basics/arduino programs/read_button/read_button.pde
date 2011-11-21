//Reads the State of a Button and displays it on the screen

int buttonPin = 8;

void setup()
{
  //sets the button pin as an input
  pinMode(buttonPin, INPUT);  
  
  //Allows us to listen to serial communications from the arduino
  Serial.begin(9600); 
}

void loop()
{
  // print the button state to a serial terminal
  Serial.println(digitalRead(buttonPin)); 
  delay(1000);
  //wait one second, then print again.
}
