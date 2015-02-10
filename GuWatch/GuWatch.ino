#include <MicroView.h>
#include <Wire.h>
#include "RTClib.h"

#define AXISX  A1
#define AXISY  A2
#define AXISZ  A3

//Instantiate objects from class definitions
RTC_DS1307 RTC;

/**************  Clock  ******************************/
int xout = 0,  yout = 0,  zout = 0;
int i=0;
int clocksize = 24;

static uint8_t x0,  y0,  x1,  y1;
static float radianshour,  radiansmin,  radianssec,  hourx,  houry,  minx,  miny,  secx,  secy;
static boolean drawnFirst  =  false;

/**************  Game  ******************************/
int buttonPin = A0;     	// push button pin
int buttonState = 0;		// variable to store the pushbutton status
float y=5;
float v=0;
float r=0;

void setup () {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);
  pinMode(AXISX,  INPUT);
  pinMode(AXISY,  INPUT);
  pinMode(AXISZ,  INPUT);
//  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  uView.begin();		// init and start MicroView
  
  uView.clear(PAGE);	// erase the display memory buffer
}
 
void loop() {
  xout = analogRead(AXISX);
  yout = analogRead(AXISY);
  zout = analogRead(AXISZ);
  //lander_game();
  Serial.print(xout);
  Serial.print("  ");
  Serial.println(yout);

  if(xout <= 230)  {
    uView.clear(PAGE);
    i = 2;
  }
  while(i == 2)  {
    lander_game();
    yout = analogRead(AXISY);
    if(yout >= 300)  {
      uView.clear(PAGE);
      i = 0;
    }
  }
  
  if(yout <= 230)  {
    uView.clear(PAGE);
    i = 1;
  }
  while(i == 1)  {
    display_clock();
    
    yout = analogRead(AXISY);
    if(yout >= 250)  {
      uView.clear(PAGE);
      i = 0;
    }
  }
  
  uView.setCursor(0,  0);			
  uView.print("Hello :)");	
  uView.display();

}
/***********************  Function Game  ************************************/
void flame()  {
  uView.line(y+1,20,y+1+r,20);
}

void restart()  {
  uView.clear(PAGE);
  y=5;
  v=0;
  uView.line(63,0,63,47);
}

void drawship(){
  uView.pixel(y-2, 20);
  uView.pixel(y-1, 19);
  uView.pixel(y-1, 21);
  uView.pixel(y, 19);
  uView.pixel(y, 21);
  uView.pixel(y+1, 19);
  uView.pixel(y+1, 21);
  uView.pixel(y+1, 18);
  uView.pixel(y+1, 22);
  uView.pixel(y+2, 17);
  uView.pixel(y+2, 23);
}

void  lander_game()  {
  uView.line(63,0,63,47);
  xout = analogRead(AXISX);
  if (xout >= 250) {
    v=v+0.00005;    // gravity
  } 
  else {
    v=v-0.0001;    // thrust if pressed	
    r=6;
  }
  
  uView.setColor(BLACK);
  drawship();  // erase
  flame();
  y=y+v;
  if(r>0){r=r-.04;}
  uView.setColor(WHITE);
  drawship();
  flame();
  
  uView.display();
  if (y>61)  {
    if(v>0.02)  {  // near base and too fast
      uView.setCursor(0,0);
      uView.print("Crash :(");
      uView.display();
      delay(2000);
      restart();
    }
    else  {
      uView.setCursor(0,0);
      uView.print("You win :)");
      uView.display();
      delay(2000);
      restart();
    }
  } 
  if (y<0)  {  // too high
    uView.setCursor(0,0);
    uView.print("Lost :(");
    uView.display();
    delay(2000);
    restart();
  }
    
}


/********************  Function Clock  ********************************/
void display_clock()  {
  uView.setFontType(0); 		// set font type 0, please see declaration in MicroView.cpp
  uView.setCursor(27,0);		// points cursor to x=27 y=0
  	
  // Draw face
  uView.print(12);			
  uView.setCursor(30,  uView.getLCDHeight()-uView.getFontHeight());
  uView.print(6);
  uView.setCursor(0,  uView.getLCDHeight() /2-(uView.getFontHeight()/2));
  uView.print(9);
  uView.setCursor(uView.getLCDWidth()-uView.getFontWidth(),  uView.getLCDHeight()/2-(uView.getFontHeight()/2));
  uView.print(3);
  uView.display();			// display the memory buffer drawn
	
  if (drawnFirst) {
    uView.line(32,  24,  32+hourx,  24+houry,  WHITE,  XOR);
    uView.line(32,  24,  32+minx,  24+miny,  WHITE,  XOR);
    uView.line(32,  24,  32+secx,  24+secy,  WHITE,  XOR);
  } 
  	
  // get the time from the clock chip
  DateTime now = RTC.now();
  
  // convert hms into radians
  radianshour = (((now.hour() * 360) / 12) + 270) * (PI / 180);
  radiansmin = (((now.minute() * 360) / 60) + 270) * (PI / 180);
  radianssec = (((now.second() * 360) / 60) + 270) * (PI / 180);
  		
  // calculate clock hand endpoints		
  hourx = cos(radianshour) * (clocksize / 2.5);
  houry = sin(radianshour) * (clocksize / 2.5);
  
  minx = cos(radiansmin) * (clocksize / 1.4);
  miny = sin(radiansmin) * (clocksize / 1.4);
  
  secx = cos(radianssec) * (clocksize / 1.1);
  secy = sin(radianssec) * (clocksize / 1.1);
  			
  // draw the clock face	
  uView.line(32,  24,  32+hourx,  24+houry,  WHITE,  XOR);
  uView.line(32,  24,  32+minx,  24+miny,  WHITE,  XOR);
  uView.line(32,  24,  32+secx,  24+secy,  WHITE,  XOR);
  	
  drawnFirst  =  true;
  uView.display();
  	
  drawnFirst  =  false;
  uView.clear(PAGE);
}
