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
int mode=0;
byte push = A1;
byte left = A0;
byte right = A2;

int state_left;
int state_right;
int state_push;

#define DEBOUNCE 200

/**************  Clock  ******************************/
int count=0;
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

//  wtv020sd16p.playVoice(4);
  
}
 
void loop()  {
  state_push = digitalRead(push);
  state_right = digitalRead(right);
  state_left = digitalRead(left);
  
// Select mode
  if(state_right == 0)  {
    delay(DEBOUNCE);
    mode++;
  }
  if(state_left == 0)  {
    delay(DEBOUNCE);
    mode--;
  }  
  if(mode <= 0)  {
    mode = 0;
  }
  if(mode >= 5)  {
    mode = 5;
  }

// Display
  if(mode == 0) {
    display_main();
    }
  if(state_push == 1 && mode == 1) {
    display_clock();
    }  
  if(state_push == 1 && mode == 2) {
    display_game();
    }

//Function    
  if(state_push == 0 && mode == 1)  {
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count=1;
  }
  while(count == 1)  {
    now_aday();
  }

  if(state_push == 0 && mode == 2)  {
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count=2;
  }
  while(count == 2)  {
    lander_game();
  }

Serial.print(mode);
Serial.print("    ");
Serial.println(count);


//  // Clock mode
//  state_push = digitalRead(push);
//  if(state_push == 0)  {
//    delay(200);
//    uView.clear(PAGE);
//    i = 1;
//  }    
//  while(i == 1)  {
//    display_clock();
//  } 
//  
//  // Game mode
//  state_right = digitalRead(right);
//  if(state_right == 0)  {
//    delay(200);
//    uView.clear(PAGE);
//    uView.setFontType(1); 
//    uView.setCursor(0,  0);			
//    uView.print("Lander");	
//    uView.setCursor(0,  15);			
//    uView.print("  Game");
//    uView.setCursor(0, 30);			
//    uView.print("----->");
//    uView.display();
//    delay(2000);
//    uView.clear(PAGE);
//    i = 2;
//  }
//  while(i == 2)  {
//    lander_game(); 
//  }
}

void display_main() {
  uView.clear(PAGE);
  uView.setFontType(0); 
  uView.setCursor(0,  0);      
  uView.print("Chiang Mai");  
  uView.setCursor(0,  15);      
  uView.print("Maker Club");
  uView.setFontType(1); 
  uView.setCursor(0, 30);   
  uView.print(" Watch");
  uView.display();
}

void display_clock()  {
  uView.clear(PAGE);
  uView.setFontType(1); 
  uView.setCursor(0,  0);      
  uView.print("Mode :");  
  uView.setCursor(0,  15);      
  uView.print("Clock");
  uView.setCursor(0, 30);   
//  uView.print(" [ ^ m ^]");
  uView.display();  
}

void display_game()  {
  uView.clear(PAGE);
  uView.setFontType(1); 
  uView.setCursor(0,  0);      
  uView.print("Mode :");  
  uView.setCursor(0,  15);      
  uView.print("Lander Game");
//  uView.setCursor(0, 30);   
//  uView.print(" [ ^ m ^]");
  uView.display();  
}



