//Jeremy Blum's Arduino Tutorial Series - Episode 12 - RFID Cards
//Sample Code - RFID Security
//http://www.jeremyblum.com
//Some Code Adapted from http://www.cooking-hacks.com
//Some code from arudino Tone Library: http://arduino.cc/en/Tutorial/Tone
//Some code from my 5th Arduino Tutorial on Motor Control: http://jeremyblum.com/2011/01/31/arduino-tutorial-5-motors-and-transistors/
//Code Updated on 1/21/2012 to comply with Arduino 1.0 Changes

#include <Servo.h>
#include "pitches.h"
byte data[5];  //For holding the ID we receive
int val = 0;
byte jeremy[5] = {0x3E,0x00,0xFC,0xBD,0x88};
byte david[5]  = {0x3E,0x00,0xFC,0xFF,0xA5};
int j_melody[] = {NOTE_G4,0,NOTE_A4,0, NOTE_B4,0,NOTE_A4,0,NOTE_B4,0, NOTE_C5,0};
int j_noteDurations[] = {8,8,8,8,8,4,8,8,8,8,8,4};
int d_melody[] = {NOTE_C4,0,NOTE_D4,0,NOTE_F4,0,NOTE_D4,0,NOTE_F4,0,NOTE_G4,0};
int d_noteDurations[] = {8,8,8,8,8,4,8,8,8,8,8,4};
int fail_melody[] = {NOTE_G2,0,NOTE_F2,0,NOTE_D2,0};
int fail_noteDurations[] = {8,8,8,8,8,4};
int speaker_pin = 8;
int servoPin = 9;

//Create Servo Object
Servo doorLock;

 void setup()
 {
   
   //Attaches the Servo to our object
   doorLock.attach(servoPin);
   
   // Start serial port 19200 bps
   Serial.begin(19200);
   
   // Setting Auto Read Mode - EM4102 Decoded Mode - No password
   // command: FF 01 09 87 01 03 02 00 10 20 30 40 37
   Serial.write(0xFF);  //Header
   Serial.write(0x01);  //Reserved
   Serial.write(0x09);  //Length (Command + Data)
   Serial.write(0x87);  //Command (0x87 sets auto mode behavior
   Serial.write(0x01);  //Data 1: Enable Auto-Read
   Serial.write(0x03);  //Data 2: Mode – Parity decoded – Manchester RF/64
   Serial.write(0x02);  //Data 3: Total number of block to be read (2)
   Serial.write((byte)0x00);  //Data 4: No password expected
   Serial.write(0x10);  //Data 5: Password byte 1
   Serial.write(0x20);  //Data 6: Password byte 2
   Serial.write(0x30);  //Data 7: Password byte 3
   Serial.write(0x40);  //Data 8: Password byte 4
   Serial.write(0x37);  //Checksum
   
   delay(500);
   while(Serial.available()>0)
   {
     Serial.read();
   }
   Serial.println();
   Serial.println("RFID module started in Auto Read Mode, Waiting for Card...");
 }

 void loop()
 {
 
   val = Serial.read();
   while (val != 0xff)
   {  //On Successful read, first byte will always be 0xFF
      val = Serial.read();
      delay(1000);
   }
   
   //we already read the header (0xff)
   Serial.read();              // reserved
   Serial.read();              // length
   Serial.read();              // command (indicates tag data)
   data[0] = Serial.read();    // we read data 1
   data[1] = Serial.read();    // we read data 2
   data[2] = Serial.read();    // we read data 3
   data[3] = Serial.read();    // we read data 4
   data[4] = Serial.read();    // we read data 5
   Serial.read();              // checksum
   
   // Indentify RFID Card
   boolean j_card = true;
   boolean d_card = true;
   Serial.print("Card found - Code: ");
   for (int i=0; i<5; i++)
   {
     if (data[i] < 16) Serial.print("0");
     Serial.print(data[i], HEX);
      
     //cross-check
     if (data[i] != jeremy[i]) j_card = false;
     if (data[i] != david[i]) d_card = false;
   }
   Serial.println();
   
   if (j_card) 
   {
     Serial.println("Hello Jeremy!");
     for (int i = 0; i < 12; i++)
     {
       int j_noteDuration = 1000/j_noteDurations[i];
       tone(speaker_pin, j_melody[i],j_noteDuration);
       int j_pauseBetweenNotes = j_noteDuration * 1.30;
       delay(j_pauseBetweenNotes);
       noTone(speaker_pin);
     }
   }
   else if (d_card)
   {
     Serial.println("Hello David!");
     for (int i = 0; i < 12; i++)
     {
       int d_noteDuration = 1000/d_noteDurations[i];
       tone(speaker_pin, d_melody[i],d_noteDuration);
       int d_pauseBetweenNotes = d_noteDuration * 1.30;
       delay(d_pauseBetweenNotes);
       noTone(speaker_pin);
     }
   }
   else
   {
     Serial.println("Not Recognized!  Get out of Here!");
     for (int i = 0; i < 6; i++)
     {
       int fail_noteDuration = 1000/fail_noteDurations[i];
       tone(speaker_pin, fail_melody[i],fail_noteDuration);
       int fail_pauseBetweenNotes = fail_noteDuration * 1.30;
       delay(fail_pauseBetweenNotes);
       noTone(speaker_pin);
     }
   }
   
   //Unlock Door for Authorized Users
   if (d_card || j_card)
   {
        doorLock.write(180);
        delay(5000);
        doorLock.write(0);
   }
   
   Serial.println();
 }
