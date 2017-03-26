#include <TM1638.h>
#include <TM1638QYF.h>
#include <RTClib.h>
#include <Wire.h>

TM1638QYF module(3, 2, 5);//dataPin,clockPin,strobePin
RTC_DS1307 rtc;
String son,hr,mn,sc;
word buttons;

void setup()
{
Serial.begin(9600);
  #ifdef AVR
    Wire.begin();
  #else
    Wire1.begin();
  #endif

    rtc.begin();
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
    rtc.writeSqwPinMode(ON);//OFF,ON,SquareWave1HZ,SquareWave4kHz,SquareWave8kHz,SquareWave32kHz 
    
    if(! rtc.isrunning()) {
      Serial.println("RTC Calismiyor");
      rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
      rtc.writeSqwPinMode(ON);//OFF,ON,SquareWave1HZ,SquareWave4kHz,SquareWave8kHz,SquareWave32kHz 
      }
 }

void loop()
{
  
//get the button
//S1 = 1, S2 = 2, S3 = 4, S4 = 8
//S5 = 16, S6 = 32, S7 = 64, S8 = 128
//S9 = 256, S10 = 512, S11 = 1024, S12 = 2048
//S13 = 4096, S14 = 8192, S15 = 16384, S16 = 32768
//module.clearDisplay();
//buttons=module.getButtons();
//module.setDisplayToDecNumber(buttons,0,false);
//delay(1000);
//module.setDisplayToHexNumber(buttons,0,false);
//delay(1000);
//module.setDisplayToBinNumber(buttons,0);
//delay(1000);
//if(buttons==1) module.setDisplayToString("merhaba 1", 0);
//delay(1000);
//module.setDisplayToString(String("HALDUN2"), 0);
//delay(1000);
//*****************************
if(rtc.isrunning()) {
  DateTime now=rtc.now();
  if(now.hour()<10) hr="0"+String(now.hour());
      else hr=String(now.hour());
  if(now.minute()<10) mn="0"+String(now.minute());
      else mn=String(now.minute());
  if(now.second()<10) sc="0"+String(now.second());
      else sc=String(now.second());    
  
  Serial.print(now.day(),DEC);
  Serial.print('/');
  Serial.print(now.month(),DEC);
  Serial.print('/');
  Serial.print(now.year(),DEC);
  Serial.print(' ');
  Serial.println(hr+":"+mn+":"+sc);
 
  son="  "+hr+mn+sc;
  module.setDisplayToString(son, 0b00010100);
  delay(1000);
 }
}
