//Program by Jeremy Blum
//www.jeremyblum.com
//Controls a Servo Motor

//Include Servo Library
#include <Servo.h>

//Define Pins
int servoPin = 9;

//Create Servo Object
Servo jeremysServo;

void setup()
{
 
  //Attaches the Servo to our object
  jeremysServo.attach(servoPin);
}

void loop()
{

  //We can Turn a Servo to 180 degrees
  for (int i = 0; i <=180; i=i+20)
  {
    jeremysServo.write(i);
    delay(1000);
  }
  
}
