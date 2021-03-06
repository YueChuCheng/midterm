#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <Wire.h> 
#include "animation.h"
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include "images.h"
//#include"animate.h"
#define Logo_width 128
#define Logo_height 64
SSD1306Wire  display(0x3c, 21, 22);
int mel[2]={1109,740};
int m=0;
int ledp[10]={2,4,16,17,27,26,19,13,12};
const int buttonPin_right = 19; 
int freq = 5000;
int ledchannel = 0;
int resolution = 8;
int channel=0;
int speedconfirm=0;
const char* ssid = "iPhone";
const char* password = "maggie9907";
int buttonState_right=0;
int buttonState_left=0;
int buttonState_top=0;
int buttonState_down=0;
int i=0;
int c=0;
char webSite[2000];
const int buttonPin_left = 32;
int ledlife[3]={32,33,25};
int speedtime=0;
int x=0;
int w=0;
int idle_time=0;
int state=-1;
int playSpeed=5;
int point=0;
int wintime=0;
int playtime=0;
int losetime=0;
WebServer server(80);
int ledPins[3] = { 11,10,9
  /*19, 11, 10, 9, 13,1,27,14,12,18*/}; 
int val = 0;
int gametone[2]={330,262};
const int led = 23;
void Changescene() {
    for (int i=1; i < 33; i++) {
        display.setColor(WHITE);
        display.drawRect(64-2*i, 32-i, 4*i, 2*i);
         display.display();
        display.fillRect(64-2*i, 32-i, 4*i, 2*i);
         display.display();
        delay(100);
    }
    delay(700);
    for (int i=32; i > 0; i--) {
        display.clear();
        display.setColor(WHITE);
        display.drawRect(64-2*i, 32-i, 4*i, 2*i);
         display.display();
        display.fillRect(64-2*i, 32-i, 4*i, 2*i);
         display.display();
        delay(100);
    }
}//切換畫面用
void Drawball(int b_x,int b_y){
    display.drawCircle(b_x, b_y, 2);
     display.display();
    display.fillCircle(b_x, b_y, 2);
     display.display();
}//遊戲跑動球用

void Lost(){
    display.drawXbm(0,0, 128, 64, idle1[6]);
     display.display();
    delay(1000);
    //display.clear();//想測試能不能直接覆蓋畫面
    for (int i=0; i <= 32; i++) {
        display.drawXbm(128-i*4,0, 128, 64, idle1[4]);
         display.display();
        delay(100);
        display.clear();
    }
    for (int i=0; i <=3 ; i++) {
        display.drawXbm(0,0, 128, 64, idle1[4]);
         display.display();
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, idle1[5]);
         display.display();
        delay(250);
        display.clear();
    }
}//遊戲輸了用

void Win(){
    display.drawXbm(0,0, 128, 64, idle1[7]);
     display.display();
    delay(1000);
    //display.clear();//想測試能不能直接覆蓋畫面
    for (int i=0; i <= 32; i++) {
        display.drawXbm(128-i*4,0, 128, 64, idle1[2]);
         display.display();
        delay(100);
        display.clear();
    }
    for (int i=0; i <=3 ; i++) {
        display.drawXbm(0,0, 128, 64, idle1[2]);
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, idle1[3]);
        delay(250);
        display.clear();
    }
}//遊戲贏了用

void Retry(){
     display.drawXbm(0,0, 128, 64, idle1[8]);
    //可以回傳個網頁回去嗎？
}

void Close(){
    for (int i=0; i <=3 ; i++) {
        display.drawXbm(0,0, 128, 64, idle1[9]);
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, idle1[10]);
        delay(250);
        display.clear();
    }
    //想設計成漸漸消失的樣子，程式碼還沒想
}//關機用

void Start(){
    for (int i=0; i <=3 ; i++) {
        display.drawXbm(0,0, 128, 64, idle1[11]);
         display.display(); 
        delay(500);
        display.clear();
        display.drawXbm(0,0, 128, 64, idle1[12]);
        display.display(); 
        delay(500);
        display.clear();
    }
   // while(1) {
        //  /*讀狀態的程式碼要加～不會寫～*/
       for(int r=0; r<=5;r++){
        display.drawXbm(0,0, 128, 64, idle1[0]);
         display.display();
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, idle1[1]);
         display.display();
        delay(250);
        display.clear();}
       // if(/*點擊了start*/)break;
    //}
}//點start畫面使用

void Gamepic(){
    display.drawXbm(0,0, 128, 64,*(idle1+13));
     display.display(); 
    
}
void handleRoot() {
  snprintf(webSite,2000,"<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\" > <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Remote Control LED</title> <script src=\"https://code.jquery.com/jquery-3.3.1.js\"></script> <script>$(document).ready(function(){$(\"[type=range]\").change(function(){var ledvalue=$(\"#led\").val(); $(\".ledvalue\").text(ledvalue);});}); </script> <style>html{background-color: #bce6ff; font-family: Arial, Helvetica, sans-serif;}.title{text-align: center; color: #d33d3d; margin-bottom: 50px;}a{position:relative; text-decoration: none; background-color: #FFFFFF; border-radius: 4px; height:100px; width: 100px; text-align: center; margin: 0 ; top:50%; font-size: 2em; /*outline: solid red 2px;*/}.btn{color: #5e5e5e;}.toprow{display:flex; justify-content: center; /* outline: solid red 2px;*/}.secrow{justify-content: center; display:flex; /* outline: solid red 2px;*/}.speedchoose{/* outline: solid red 2px;*/ display:flex; flex-direction:column; text-align: center;}.submit{/*outline: solid red 2px;*/ text-align: center; width:100px; margin-bottom:30px;}</style> </head> <body> <h1 class=\"title\">Block controler</h1> <div class=\"speedchoose\"> <h3>Game Speed=<span class='ledvalue'>0</span></h3> <form action=\"ledDiming\" method=\"get\" id=\"form1\"> <input type=\"range\" name=\"ledval\" id=\"led\" min=\"0\" max=\"20\"> </form> <br><div> <button type=\"submit\" form=\"form1\" value=\"Submit\" class=\"submit\">Submit</button> </div></div><div class=\"toprow\"> <a class=\"btn\" href=\"/T\"><p>top</p></a> </div><div class=\"secrow\"> <a class=\"btn\" href=\"/L\"><p>left</p></a> <a class=\"btn\" href=\"/D\"><p>down</p></a> <a class=\"btn\" href=\"/R\"><p>right</p></a> </div></body> </html>");
  server.send(200, "text/html",webSite);

}

void right(){
              server.handleClient();
            server.send(200, "text/html",webSite);
             digitalWrite(led,HIGH);
             display.drawXbm(54,-10 ,64, 128,*(rock_right));
             Gamepic();
          
             display.display(); 
                    
             if(i*playSpeed<=70&&i*playSpeed>0){
               ledcWriteTone(channel, 0);
               display.clear();
              /* display.drawXbm(35, 0,64, 128,*( idle+x));*/
               Gamepic();
               Drawball(84,32);
               display.display(); 
               display.drawXbm(54, -10,64, 128,*(  rock_right));
               display.display();          
               point++;
                digitalWrite(ledp[w],HIGH);
               w++;
               
              
               delay(1000);
               
               buttonState_right=1;
              } 
                     
         

  }

void left(){
          server.handleClient();
          server.send(200, "text/html",webSite);
          digitalWrite(led,LOW);
          display.drawXbm(10,-10 ,64, 128,*(rock_left));
          Gamepic();
             display.display(); 
            
             
             if(i*playSpeed>=-70&&i*playSpeed<0){
               ledcWriteTone(channel, 0);
               display.clear();
               /*display.drawXbm(35, 0,64, 128,*( idle+x));*/
                Gamepic();
               Drawball(84,32);
               display.display(); 
              display.drawXbm(10, -10,64, 128,*(  rock_left));
               display.display();          
               point++;
             digitalWrite(ledp[w],HIGH);
               w++;
               delay(1000);
               
              buttonState_left=1;
              } 
  
  }

void top(){
               server.handleClient();
           server.send(200, "text/html",webSite);
             digitalWrite(led,HIGH);
              /*display.drawXbm(-200,7 ,64, 128,*(rock_top));*/
              display.drawXbm(54,0 ,64, 128,*(rock_top));
              Gamepic();
             display.display(); 
                    
             if(c*playSpeed>=-70&&c*playSpeed<0){
               ledcWriteTone(channel, 0);
               display.clear();
              /* display.drawXbm(35, 0,64, 128,*( idle+x));*/
               Gamepic();
               Drawball(84,32);
               display.display(); 
               display.drawXbm(54,0,64, 128,*(  rock_top));
               display.display();          
               point++;
             
              digitalWrite(ledp[w],HIGH);
               w++;
               delay(1000);
               
               buttonState_top=1;
              } 
                     
         

  }

void down(){
         server.handleClient();
         server.send(200, "text/html",webSite);
          digitalWrite(led,LOW);
          display.drawXbm(54,50 ,64, 128,*(rock_top));
          Gamepic();
         /* display.drawXbm(20,-5,64, 128,*(rock_down));*/
             display.display(); 
            
             
             if(c*playSpeed<=70&&c>0){
               ledcWriteTone(channel, 0);
               display.clear();
               /*display.drawXbm(35, 0,64, 128,*( idle+x));*/
                Gamepic();
               Drawball(84,32);
               display.display(); 
               display.drawXbm(54,50,64, 128,*(  rock_top));
               display.display();          
               point++;
             digitalWrite(ledp[w],HIGH);
               w++;
               delay(1000);
               
              buttonState_down=1;
              } 
  
  }
  
void ledDiming(){
  
  playSpeed=server.arg("ledval").toInt();
  speedconfirm=1;
  
  }

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}



void setup(void) {
  for(int u=0;u<10;u++){
    pinMode(ledp[u],OUTPUT);

    }
  pinMode(36,OUTPUT);
  for (int thisLed = 0; thisLed < 10; thisLed++) {
    pinMode(ledPins[thisLed],INPUT); 
  
  }
  ledcSetup(channel, freq, resolution);
ledcAttachPin(12, channel);
  Serial.begin(115200);
  

pinMode(36,INPUT);
display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  for(int x=0;x<3 ;x++ ){
       pinMode(ledlife[x], OUTPUT);
       
    
    }
   
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  
  server.on("/", handleRoot);
  server.on("/T", top);
 server.on("/D", down);
  server.on("/R", right);
  server.on("/L", left);
  server.onNotFound(handleNotFound);
server.on("/ledDiming",ledDiming);
 server.begin();
  Serial.println("HTTP server started");

Serial.begin(115200);
  Serial.println();
 display.init(); //初始化(init)
 
  display.setContrast(255); //數值介於0~255，調整對比
  display.clear();//清除螢幕和緩衝區(clear)
  //display.drawXbm(35, 0,64, 128, walk_0_img);
  //印出想顯示的畫面  display.drawXbm(X座標, Y座標, 圖片寬度, 圖片高度, 圖片名稱);
 // display.display(); //顯示畫面(display)
   ledcAttachPin(18, channel);
}


void loop(void) {
    
  point=0;
 wintime=0;
 playtime=0;
 losetime=0;
 
//Game initial

  w=0;

 /*for (int thisLed = 0; thisLed < 3; thisLed++) {
    digitalWrite(ledPins[thisLed], LOW); 
  }*/
display.clear();
for(int u=0;u<10;u++){
  digitalWrite(ledp[u],LOW);
}
 Start();
int pressstart=0;

while(pressstart!=HIGH||speedconfirm!=1){
  pressstart=digitalRead(36);
    delay(1);
    server.handleClient();
    server.send(200, "text/html",webSite);
 
   
}
pressstart=0;
speedconfirm=0;
for(int x=0;x<3 ;x++ ){
       pinMode(ledlife[x], OUTPUT);
        digitalWrite(ledlife[x], HIGH);
    
    }
    
     display.clear();
     display.setFont(ArialMT_Plain_24);
      display.drawString(0, 20, "Ready?");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(60, 20, "3");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(60, 20, "2");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(60, 20, "1");
      display.display(); 
      delay(1000);

      display.clear();
      display.drawString(60, 20, "Go!");
      display.display(); 
      delay(1000);

//Game Start


while(idle_time!=6){  

           server.handleClient();
         server.send(200, "text/html",webSite);
           display.clear();
          Gamepic();
          Drawball(84,32);
          display.display(); 
          
           x++;
           display.display(); 
           delay(200);
           if(x==2){
           x=0;
            }
            idle_time++;
       }
          idle_time=0;



    while(losetime<4){
    

  state=random(0,5);
  switch(state){


\
      
     //向右走
     case (1): 
      while(i!=20){
          if(m==2)m=0;
          
          ledcWriteTone(channel, mel[m]);
          m++;
         
           
          display.clear();
        
          /*display.drawXbm(35+i*playSpeed, 0,64, 128,*( idle+x));*/
           Gamepic();
           if(84+i*playSpeed<=112){
           Drawball(84+i*playSpeed,32);
           }
          display.display();
         server.handleClient();
         server.send(200, "text/html",webSite);
          x++;
          i++;
          delay(100);
          if(x==2){
             x=0;
          }
          if(i==15){
            
            losetime++;
            }
       
         if(buttonState_right==1){
          buttonState_right=0;
          break;
          }
          
      }
      i=0;


       for(int y=0;y<losetime;y++){
          
          
           digitalWrite(ledlife[y], LOW);
          }
       while(idle_time!=6){  
         ledcWriteTone(channel, 0);
         server.handleClient();
         server.send(200, "text/html",webSite);
           display.clear();
           /*display.drawXbm(35, 0,64, 128,*( idle+x));*/
            Gamepic();
           Drawball(84+i*playSpeed,32);
         
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
      while(i!=-20){
         if(m==2)m=0;
          
          ledcWriteTone(channel, mel[m]);
          m++;
          display.clear();
         /* display.drawXbm(35+i*playSpeed, 0,64, 128,*( idle+x));*/
           Gamepic();
           if(84+i*playSpeed>=56){
           Drawball(84+i*playSpeed,32);
           }
          display.display();
           server.handleClient();
           server.send(200, "text/html",webSite);
          
          x++;
          i--;
         
          delay(100);
     
          if(x==2){
             x=0;
          }
           if(i==-15){
            
            losetime++;
            }
       
          if(buttonState_left==1){
          
          buttonState_left=0;
          break;                   
            }
          
      }
     
      i=0;


       for(int y=0;y<losetime;y++){
          
          
           digitalWrite(ledlife[y], LOW);
          }

        while(idle_time!=6){  
 ledcWriteTone(channel, 0);
           server.handleClient();
         server.send(200, "text/html",webSite);
           display.clear();
           /*display.drawXbm(35, 0,64, 128,*( idle+x));*/
           Gamepic();
           Drawball(84+i*playSpeed,32);
          
           display.display(); 
           delay(200);
          
           idle_time++;
          }
          idle_time=0;
          break;
      //向左走結束




     //向上走
     case (3): 
      while(c!=-20){
      
            if(m==2)m=0;
          
          ledcWriteTone(channel, mel[m]);
          m++;
          display.clear();
        
          /*display.drawXbm(35, 0+c*playSpeed,64, 128,*( idle+x));*/
           Gamepic();
           if(32+c*playSpeed>=4){
           Drawball(84,32+c*playSpeed);
           }
          display.display();
         server.handleClient();
         server.send(200, "text/html",webSite);
          x++;
          c--;
          delay(100);
          if(x==2){
             x=0;
          }
          if(c==-15){
            
            losetime++;
            }
       
         if(buttonState_top==1){
          buttonState_top=0;
          break;
          }
          
      }
      c=0;
 for(int y=0;y<losetime;y++){
          
          
           digitalWrite(ledlife[y], LOW);
          }


      
       while(idle_time!=6){  
         ledcWriteTone(channel, 0);
         server.handleClient();
         server.send(200, "text/html",webSite);
           display.clear();
           /*display.drawXbm(35, 0,64, 128,*( idle+x));*/
          
            Gamepic();
           Drawball(84+i*playSpeed,32);
           display.display(); 
           delay(200);
           
            idle_time++;
          }
          idle_time=0;
          
         
     break;
    //向上走結束

  //向下走
 case (4): 
      while(c!=20){
         if(m==2)m=0;
          
          ledcWriteTone(channel, mel[m]);
          m++;
          display.clear();
          /*display.drawXbm(35, 0+c*playSpeed,64, 128,*( idle+x));*/
           Gamepic();
           if(32+c*playSpeed<=60){
           Drawball(84,32+c*playSpeed);
           }
          display.display();
           server.handleClient();
           server.send(200, "text/html",webSite);
          
          x++;
          c++;
         
          delay(100);
     
          if(x==2){
             x=0;
          }
           if(c==15){
            
            losetime++;
            }
       
          if(buttonState_down==1){
          
          buttonState_down=0;
          break;                   
            }
          
      }
     
      c=0;

 for(int y=0;y<losetime;y++){
          
          
           digitalWrite(ledlife[y], LOW);
          }


        while(idle_time!=6){  
         ledcWriteTone(channel, 0);
           
           display.clear();
           /*display.drawXbm(35, 0,64, 128,*( idle+x));*/
           Gamepic();
           Drawball(84+i*playSpeed,32);
           display.display(); 
           delay(200);
            idle_time++;
          }
          idle_time=0;
          break;
      //向下走結束

          
}
     
      
  
}



      display.clear();
      if(point>=8){
        
        Win();
       display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_24);

        display.drawString(0, 0, "Your Score");
        display.drawString(80, 25, String(point));
        display.display(); 
        delay(3000);
        }
        else{
      Lost();
     display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_24);
      
       display.drawString(0, 0, "Your Score");
       display.drawString(80, 25, String(point));
       display.display(); 
      delay(3000);
        }
  
   display.display(); 
    
}
  
