//Program by Jeremy Blum
//www.jeremyblum.com
//Uses pot data from arduino to draw stuff

import processing.serial.*;
Serial port;
float brightness = 0;

void setup()
{
  size(500,500);
  port = new Serial(this, "COM3", 9600);
  port.bufferUntil('\n');  
}

void draw()
{
  background(0,0,brightness);
}
  
void serialEvent (Serial port)
{
  brightness = float(port.readStringUntil('\n'));
}
