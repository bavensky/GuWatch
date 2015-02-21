/******************************************************************************
* Project  : Gu Watch                                                         *
* Compiler : Arduino 1.5.5                                                    *
* Board    : Micro view                                                       *
* Shield   : -                                                                *
* Device   : RTC DS1307                                                       *
*          : MPU6050                                                          *
* Author   : Bavensky :3                                                      *
* E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
* Date     : 20/02/2015 [dd/mm/yyyy]                                          *
*******************************************************************************/

#include <MicroView.h>
#include <Wire.h>
#include "RTClib.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro(0x69);
int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

//Instantiate objects from class definitions
RTC_DS1307 RTC;
/**************  Variable  ***************************/
int mode;
/**************  Clock  ******************************/
int i=0;
int clocksize = 24;

static uint8_t x0,  y0,  x1,  y1;
static float radianshour,  radiansmin,  radianssec,  hourx,  houry,  minx,  miny,  secx,  secy;
static boolean drawnFirst  =  false;

/**************  Game  ******************************/
int buttonPin  =  A0;     	// push button pin
int buttonState  =  0;		// variable to store the pushbutton status
float y  =  5;
float v  =  0;
float r  =  0;

void setup () {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);

//  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  uView.begin();		// init and start MicroView
  uView.clear(PAGE);	// erase the display memory buffer
  
  accelgyro.initialize();   
}
 
void loop()  {
  
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//  Serial.print(ax);
//  Serial.print("\t");
//  Serial.print(ay);
//  Serial.println("\t");

// Mode 
  // Clock mode
  if(ax <= -15000)  {
    uView.clear(PAGE);
    i = 1;
  }    
  while(i == 1)  {
    display_clock();
  } 
  
  // Game mode
  if(ay > 5000)  {
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
  
  uView.setFontType(1); 
  uView.setCursor(0,  0);			
  uView.print("Hello ");	
  uView.setCursor(0,  15);			
  uView.print("  World");
  uView.setCursor(0, 30);			
  uView.print("(^^)/");
  uView.display();

}

