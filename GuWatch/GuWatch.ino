#include <MicroView.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;;


void setup() 
{
  Wire.begin();
  rtc.begin();
  //rtc.adjust(DateTime(__DATE__, __TIME__));
  uView.begin();				
}

void loop () {
  uView.clear(PAGE);
  
  DateTime now = rtc.now();
  
  uView.setFontType(0); 
  uView.setCursor(0,0);
  uView.print(" GU Watch ");
 
  uView.setFontType(0);
  uView.setCursor(6,16);
  if(now.hour() < 10) uView.print("0");
  uView.print(now.hour(), DEC);
  uView.print(":");
  if(now.minute() < 10) uView.print("0");
  uView.print(now.minute(), DEC);
  uView.print(":");
  if(now.second() < 10) uView.print("0");
  uView.print(now.second(), DEC);
  uView.print("  ");
  
  uView.setCursor(0,32);
  if(now.day() < 10) uView.print("0");
  uView.print(now.day(), DEC);
  uView.print("/");
  if(now.month() < 10) uView.print("0");
  uView.print(now.month(), DEC);
  uView.print("/");
  uView.print(now.year(), DEC);
  uView.print("  ");
  uView.display();
}



