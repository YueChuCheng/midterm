#include <Wire.h>
#include <SPI.h>
#include "animation.h"
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`

#define Logo_width 128
#define Logo_height 64


//設定腳位
SSD1306Wire  display(0x3c, 21, 22);

const int buttonPin_right = 19; 
const int buttonPin_left = 32;
void setup() {
  pinMode(buttonPin_right, INPUT);
  pinMode(buttonPin_left, INPUT);
  display.init(); //初始化(init)
  display.setContrast(255); //數值介於0~255，調整對比
  display.clear();//清除螢幕和緩衝區(clear)
  display.drawXbm(35, 0,64, 128, walk_0_img);
  //印出想顯示的畫面  display.drawXbm(X座標, Y座標, 圖片寬度, 圖片高度, 圖片名稱);
  display.display(); //顯示畫面(display)
}

void loop() { 



//Game initial
/*
      display.clear();
      display.drawString(0, 0, "Ready?");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(0, 0, "3");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(0, 0, "2");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(0, 0, "1");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(0, 0, "Go!");
      display.display(); 
      delay(1000);
*/
//Game Start
int buttonState_right;
int buttonState_left;
int x=0;
int i=0;
int idle_time=0;
int state=-1;
int playSpeed=20;
int point=0;
int wintime=0;
int playtime=0;
    while(playtime-wintime<=3){
      playtime++;
  buttonState_right = digitalRead(buttonPin_right);
  state=1/*random(0, 3)*/;
  switch(state){

     
     //向右走
     case (1): 
      while(i!=20){
        buttonState_right = digitalRead(buttonPin_right);
        buttonState_left = digitalRead(buttonPin_left);
          display.clear();
          display.drawXbm(35+i*playSpeed, 0,64, 128,*( idle+x));
          display.display();
          x++;
          i++;
          delay(100);
          if(x==2){
             x=0;
          }
          if(buttonState_left==HIGH){
             display.drawXbm(-35, 7,64, 128,*(  rock_left));
             display.display();          
            
            }
          if(buttonState_right==HIGH){
           
             display.drawXbm(100,7 ,64, 128,*(rock_right));
             display.display(); 
            
             
             if(i<=4){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(100, 7,64, 128,*(  rock_right));
               display.display();          
               point++;
               delay(1000);
               wintime++;
               break; 
              } 
                    
            }
           
         
      }
      i=0;
      while(idle_time!=2){  
         
           display.clear();
           display.drawXbm(35, 0,64, 128,*( idle+x));
           x++;
           display.display(); 
           delay(200);
           if(x==2){
           x=0;
            }
            idle_time++;
          }
          idle_time=0;
          
         
     break;
    //向右走結束



     //向左走
     case (2): 
      while(i!=20){
         buttonState_right = digitalRead(buttonPin_right);
      display.clear();
          display.drawXbm(35-i*playSpeed, 0,64, 128,*( idle+x));
          x++;
          i++;
          display.display(); 
          delay(100);
     
          if(x==2){
             x=0;
          }
          if(buttonState_right==HIGH){
            
             display.drawXbm(-35, 7,64, 128,*(  rock_left));
             display.display();          
             
             if(i<=4){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(-35, 7,64, 128,*(  rock_left));
               display.display();          
               point++;
               delay(1000);
              break; 
              }
                     
            }
          
      }
      i=0;

        while(idle_time!=2){  
           display.clear();
           display.drawXbm(35, 0,64, 128,*( idle+x));
           x++;
           display.display(); 
           delay(200);
           if(x==2){
           x=0;
            }
            idle_time++;
          }
          idle_time=0;
          break;
        //向左走結束


       //向上走
           case (3): 
      while(i!=20){
         buttonState_right = digitalRead(buttonPin_right);
      display.clear();
          display.drawXbm(35, 0+i*playSpeed,64, 128,*( idle+x));
          x++;
          i++;
          display.display(); 
          delay(100);
     
          if(x==2){
             x=0;
          }
          if(buttonState_right==HIGH){
             display.clear();
             display.drawXbm(100,7 ,64, 128,*(rock_right));
             display.display(); 
             display.drawXbm(35, 0,64, 128,*( idle+x));
             display.display(); 
             delay(500); 
                     
            }
             
          
      }
      i=0;

        while(idle_time!=2){  
           display.clear();
           display.drawXbm(35, 0,64, 128,*( idle+x));
           x++;
           display.display(); 
           delay(200);
           if(x==2){
           x=0;
            }
            idle_time++;
          }
          idle_time=0;
          break;
         //向上走結束


        //向下走
           case (4): 
      while(i!=20){
         buttonState_right = digitalRead(buttonPin_right);
      display.clear();
          display.drawXbm(35, 0-i*playSpeed,64, 128,*( idle+x));
          x++;
          i++;
          display.display(); 
          delay(100);
     
          if(x==2){
             x=0;
          }
          if(buttonState_right==HIGH){
             display.clear();
             display.drawXbm(-35, 7,64, 128,*(  rock_left));
             display.display(); 
             display.drawXbm(35, 0,64, 128,*( idle+x));
             display.display(); 
             delay(500); 
             break;         
            }
          
      }
      i=0;

        while(idle_time!=2){  
           display.clear();
           display.drawXbm(35, 0,64, 128,*( idle+x));
           x++;
           display.display(); 
           delay(200);
           if(x==2){
           x=0;
            }
            idle_time++;
          }
          idle_time=0;
          break;
        //向下走結束

          
}
     
      
  
}


/*buttonState_right = digitalRead(buttonPin_right);
   if (buttonState_right == HIGH) {
      display.clear();
      display.drawXbm(i, 0,64, 128,*( walk+i));
      display.display(); 
      delay(200);
      i++;
      if(i==8){
      i=0;
      }
    }

else if(buttonState_right == LOW){
int x=0;
while(1){  
  display.clear();
      display.drawXbm(i, 0,64, 128,*( idle+x));
      x++;
      display.display(); 
      delay(200);
     
   if(x==2){
      x=0;
      }
      buttonState_right = digitalRead(buttonPin_right);

if(buttonState_right == HIGH){
    break;
      }
}
}*/
 display.clear();
      display.drawString(0, 0, "You Lose");
      display.display(); 
      delay(10000);
    
}
  
 
