/******************************************************************************
* Project  : Gu Watch                                                         *
* Compiler : Arduino 1.5.5                                                    *
* Board    : Micro view                                                       *
* Shield   : -                                                                *
* Device   : RTC DS1307                                                       *
*          : 3 Button                                                         *
*          : wtv020m01 Audio module                                           *
* Author   : Bavensky :3                                                      *
* E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
* Date     : 03/09/2015 [dd/mm/yyyy]                                          *
*******************************************************************************/

#include <MicroView.h>
#include <Wtv020sd16p.h>
#include <Wire.h>
#include "RTClib.h"

//Instantiate objects from class definitions
RTC_DS1307 RTC;
/**************  Variable  ***************************/
int mode;
byte push = A0;
byte left = A1;
byte right = A2;


int state_left;
int state_right;
int state_push;
/**************  Clock  ******************************/
int i=0;
int clocksize = 24;

static uint8_t x0,  y0,  x1,  y1;
static float radianshour,  radiansmin,  radianssec,  hourx,  houry,  minx,  miny,  secx,  secy;
static boolean drawnFirst  =  false;

/**************  Game  ******************************/
float y  =  5;
float v  =  0;
float r  =  0;

/*************  Music  ******************************/
int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 5;  // The pin number of the data pin.
int busyPin = 6;  // The pin number of the busy pin.

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);


void setup () {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);

  pinMode(push, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  
  wtv020sd16p.reset();
  
//  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  uView.begin();		// init and start MicroView
  uView.clear(PAGE);	// erase the display memory buffer

}
 
void loop()  {
  uView.setFontType(0); 
  uView.setCursor(0,  0);			
  uView.print("Chiang Mai");	
  uView.setCursor(0,  15);			
  uView.print("Maker Club");
  uView.setCursor(0, 30);		
  uView.print(" [ ^ m ^]");
  uView.display();

//  wtv020sd16p.playVoice(4);

//-------  Mode  ------// 
  // Clock mode
  state_push = digitalRead(push);
  if(state_push == 0)  {
    delay(200);
    uView.clear(PAGE);
    i = 1;
  }    
  while(i == 1)  {
    display_clock();
  } 
  
  // Game mode
  state_right = digitalRead(right);
  if(state_right == 0)  {
    delay(200);
    uView.clear(PAGE);
    uView.setFontType(1); 
    uView.setCursor(0,  0);			
    uView.print("Lander");	
    uView.setCursor(0,  15);			
    uView.print("  Game");
    uView.setCursor(0, 30);			
    uView.print("----->");
    uView.display();
    delay(2000);
    uView.clear(PAGE);
    i = 2;
  }
  while(i == 2)  {
    lander_game(); 
  }
}

