//Jeremy Blum's Arduino Tutorial Series - Episode 15 - GPS Tracking
//Sample Code 2 - Logging GPS Data to an SD Card
//http://www.jeremyblum.com
//TinyGPS Library and Helper Functions by Mikal Hart http://arduiniana.org/libraries/tinygps/


#include <TinyGPS.h>
#include <SD.h>
#include <stdlib.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It uses an Arduino Mega with a GPS attached to Serial3 at 4800 buad.
*/

TinyGPS gps;
static char dtostrfbuffer[20];
int CS = 53;
int LED = 13;

//Define String
String SD_date_time = "invalid";
String SD_lat = "invalid";
String SD_lon = "invalid";
String dataString ="";

static void gpsdump(TinyGPS &gps);
static bool feedgps();
static void print_float(float val, float invalid, int len, int prec, int SD_val);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);

void setup()
{
  pinMode(CS, OUTPUT);  //Chip Select Pin for the SD Card
  pinMode(LED, OUTPUT);  //LED Indicator
  
  //Serial interfaces
  Serial.begin(115200);
  Serial3.begin(4800);
  
  //Connect to the SD Card
  if(!SD.begin(CS))
  {
    Serial.println("Card Failure");
    return;
  }
  
  
  Serial.print("Testing TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
  Serial.print("Sizeof(gpsobject) = "); Serial.println(sizeof(TinyGPS));
  Serial.println();
  Serial.println("Sats HDOP Latitude Longitude Fix  Date       Time       Date Alt     Course Speed Card  Distance Course Card  Chars Sentences Checksum");
  Serial.println("          (deg)    (deg)     Age                        Age  (m)     --- from GPS ----  ---- to London  ----  RX    RX        Fail");
  Serial.println("--------------------------------------------------------------------------------------------------------------------------------------");
}

void loop()
{
  bool newdata = false;
  unsigned long start = millis();
  
  // Every second we print an update
  while (millis() - start < 1000)
  {
    if (feedgps())
      newdata = true;
  }
  
  gpsdump(gps);
  
  //Write the newest information to the SD Card
  dataString = SD_date_time + "," + SD_lat + "," + SD_lon;
  if(SD_date_time != "invalid")
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);
    
  //Open the Data CSV File
  File dataFile = SD.open("LOG.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(dataString);
    Serial.println(dataString);
    dataFile.close();
  }
  else
  {
    Serial.println("\nCouldn't open the log file!");
  }
}

static void gpsdump(TinyGPS &gps)
{
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  static const float LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  
  print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
  print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);
  gps.f_get_position(&flat, &flon, &age); 
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 9, 5, 1); //LATITUDE
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 10, 5, 2); //LONGITUDE
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);

  print_date(gps); //DATE AND TIME

  print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 8, 2, 0);
  print_float(gps.f_course(), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2, 0);
  print_float(gps.f_speed_kmph(), TinyGPS::GPS_INVALID_F_SPEED, 6, 2, 0);
  print_str(gps.f_course() == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(gps.f_course()), 6);
  print_int(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0UL : (unsigned long)TinyGPS::distance_between(flat, flon, LONDON_LAT, LONDON_LON) / 1000, 0xFFFFFFFF, 9);
  print_float(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : TinyGPS::course_to(flat, flon, 51.508131, -0.128002), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2, 0);
  print_str(flat == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(TinyGPS::course_to(flat, flon, LONDON_LAT, LONDON_LON)), 6);

  gps.stats(&chars, &sentences, &failed);
  print_int(chars, 0xFFFFFFFF, 6);
  print_int(sentences, 0xFFFFFFFF, 10);
  print_int(failed, 0xFFFFFFFF, 9);
  Serial.println();
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  feedgps();
}

static void print_float(float val, float invalid, int len, int prec, int SD_val)
{
  char sz[32];
  if (val == invalid)
  {
    strcpy(sz, "*******");
    sz[len] = 0;
        if (len > 0) 
          sz[len-1] = ' ';
    for (int i=7; i<len; ++i)
        sz[i] = ' ';
    Serial.print(sz);
    if(SD_val == 1) SD_lat = sz;
    else if(SD_val == 2) SD_lon = sz;
  }
  else
  {
    Serial.print(val, prec);
    if (SD_val == 1) SD_lat = dtostrf(val,10,5,dtostrfbuffer);
    else if (SD_val == 2) SD_lon = dtostrf(val,10,5,dtostrfbuffer);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1);
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(" ");
  }
  feedgps();
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
  {
    Serial.print("*******    *******    ");
    SD_date_time = "invalid";
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d   ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
    SD_date_time = sz;
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  feedgps();
}

static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  feedgps();
}

static bool feedgps()
{
  while (Serial3.available())
  {
    if (gps.encode(Serial3.read()))
      return true;
  }
  return false;
}
