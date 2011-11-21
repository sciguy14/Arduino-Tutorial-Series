//Program by Jeremy Blum
//www.jeremyblum.com
//Changes LED brightness using voltag input instead of PWM

//Include SPI library
#include <SPI.h>

//When Using the SPI library, you only have to worry
//about picking your slave select
//By Default, 11 = MOSI, 12 = MISO, 13 = CLK
int SS = 10;   //SPI Slave Select

void setup()
{
  
  //Set Pin Direction
  //Again, the other SPI pins are configured automatically
  pinMode(SS, OUTPUT);
  
  //Initialize SPI
  SPI.begin();
  
}

//This will set 1 LED to the specififed level
void setLed(int reg, int level)
{
  digitalWrite(SS, LOW);
  SPI.transfer(reg);
  SPI.transfer(level);
  digitalWrite(SS, HIGH);
}

void loop()
{
  for(int i=0; i<=2; i++)
  {
    for (int j=50; j<=255; j++)
    {
      setLed(i,j);
      delay(20);
    }
    delay(500);
    for (int j=255; j>=50; j--)
    {
      setLed(i,j);
      delay(20);
    }
  }
}


