#include <MicroView.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;;


void setup() {
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
  uView.begin();				
}

void loop () {
  uView.clear(PAGE);
  
  DateTime now = rtc.now();
  
  uView.setFontType(1); 
  uView.setCursor(0,0);
  uView.print(" GU Watch");
 
  uView.setFontType(0);
  uView.setCursor(6,16);
  uView.print(now.hour(), DEC);
  uView.print(":");
  uView.print(now.minute(), DEC);
  uView.print(":");
  uView.print(now.second(), DEC);
  uView.print("  ");
  
  uView.setCursor(0,32);
  uView.print(now.day(), DEC);
  uView.print("/");
  uView.print(now.month(), DEC);
  uView.print("/");
  uView.print(now.year(), DEC);
  uView.print("  ");
  uView.display();
}



