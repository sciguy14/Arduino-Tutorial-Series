//Program by Jeremy Blum
//www.jeremyblum.com
//Use hardware Debounced Switch to Control Interrupt

//Setup the Button
int buttonInt = 0; //AKA digital pin 2

//Setup the LEDs
int yellowLED = 11;
int redLED = 10;
int greenLED = 9;
int nullLED = 6;
volatile int selectedLED = greenLED;

//Setup the Distance Sensor
int distPin = 0;

void setup()
{
  pinMode (redLED, OUTPUT);
  pinMode (greenLED, OUTPUT);
  pinMode (yellowLED, OUTPUT);
  pinMode (nullLED, OUTPUT);
  attachInterrupt(buttonInt, swap, RISING);
}

void swap()
{
  if (selectedLED == greenLED)
    selectedLED = redLED;
  else if (selectedLED == redLED)
    selectedLED = yellowLED;
  else if (selectedLED == yellowLED)
    selectedLED = nullLED;
  else
    selectedLED = greenLED;
}

void loop()
{
  //Read Distance Sensor
  int dist = analogRead(distPin);
  int brightness = map(dist, 0, 1023, 0, 255);
  
  //Control LED Brightness
  analogWrite(selectedLED, brightness);

}
