/***********************  Function Game  ************************************/
void lander_game()  {

  uView.line(63,0,63,47);  // วาดเส้นพื้น
  
  state_left = digitalRead(left);
  state_right = digitalRead(right);
  if (state_left == 1) {
    v = v+0.00005;    // เร่งเครื่องขึ้น
  } 
  if(state_left == 0) {
    v = v-0.0002;    // ลดระดับลง
    r = 6;
  }
  if(state_right == 0)  {
    delay(200);
    uView.clear(PAGE);
    i = 0;
  }

  uView.setColor(BLACK);
  drawship();  // วาดรูปจรวจ
  flame();    // แสดงผล
  y  =  y  +  v;
  
  if(r  >  0)  {
    r = r - 0.02;
  }
  
  uView.setColor(WHITE);
  drawship();
  flame();
  uView.display();
  
  
  if(y  >  61)  {
    if(v  >  0.05)  {  // near base and too fast
      uView.setCursor(0,0);
      uView.print("Crash  :(");
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
  
  if(  y  <  0)  {  // too high
    uView.setCursor(0,0);
    uView.print("Lost :(");
    uView.display();
    delay(2000);
    restart();
  }
 
}

void flame()  {
  uView.line(y+1,20,y+1+r,20);
}

void restart()  {
  uView.clear(PAGE);
  y  =  5;
  v  =  0;
  uView.line(63,0,63,47); // วาดเส้นพื้น 
}

void drawship()  {
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

