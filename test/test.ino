#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <Wire.h> 
#include "animation.h"
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#define Logo_width 128
#define Logo_height 64
SSD1306Wire  display(0x3c, 21, 22);
const int buttonPin_right = 19; 
int freq = 5000;
int ledchannel = 0;
int resolution = 8;

const char* ssid = "iPhone";
const char* password = "maggie9907";
int buttonState_right=0;
int buttonState_left=0;
int buttonState_top=0;
int buttonState_down=0;
int i=0;
int c=0;
char webSite[1000];
const int buttonPin_left = 32;
int ledlife[3]={32,33,25};
int speedtime=0;
int x=0;

int idle_time=0;
int state=-1;
int playSpeed=15;
int point=0;
int wintime=0;
int playtime=0;
int losetime=0;
WebServer server(80);

int val = 0;

const int led = 23;

void handleRoot() {
  snprintf(webSite,1000,"<html> <head> <meta charset='UTF-8'/> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Remote Control LED</title> <style>html{background-color:#cbef99;}.title{text-align:right;color:#ffaad6;text-shadow:0px 3px 5px #000; margin-bottom: 50px;}a{display:inline-block;text-decoration:none;background-color:#FFFFFF;radius:3px; width:150px;text-align:center;margin:0 auto;margin-bottom:30px;font-size:2em;box-shadow: 0px 3px 6px #000;}.btn1{color:#659700;}.btn2{color:#A8A8A8;}</style> </head> <body> <h1 class=\"title\">Remote LED Control</h1> <a class=\"btn2\" href=\"/T\">上</a> <a class=\"btn2\" href=\"/L\">左</a> <a class=\"btn1\" href=\"/D\">下</a> <a class=\"btn1\" href=\"/R\">右</a> </body></html>\";");
  server.send(200, "text/html",webSite);

}

void right(){
               server.handleClient();
            server.send(200, "text/html",webSite);
             digitalWrite(led,HIGH);
              display.drawXbm(100,7 ,64, 128,*(rock_right));
             display.display(); 
                    
             if(i<=7&&i>0){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(100, 7,64, 128,*(  rock_right));
               display.display();          
               point++;
               delay(1000);
               
               buttonState_right=1;
              } 
                     
         

  }

void left(){
          server.handleClient();
         server.send(200, "text/html",webSite);
          digitalWrite(led,LOW);
          display.drawXbm(-35,7 ,64, 128,*(rock_left));
             display.display(); 
            
             
             if(i>=-8&&i<0){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(-35, 7,64, 128,*(  rock_left));
               display.display();          
               point++;
               delay(1000);
               
              buttonState_left=1;
              } 
  
  }

void top(){
               server.handleClient();
           server.send(200, "text/html",webSite);
             digitalWrite(led,HIGH);
              display.drawXbm(-200,7 ,64, 128,*(rock_top));
             display.display(); 
                    
             if(c>=-8&&c<0){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(-200,7,64, 128,*(  rock_top));
               display.display();          
               point++;
               delay(1000);
               
               buttonState_top=1;
              } 
                     
         

  }

void down(){
          server.handleClient();
         server.send(200, "text/html",webSite);
          digitalWrite(led,LOW);
          display.drawXbm(20,-5,64, 128,*(rock_down));
             display.display(); 
            
             
             if(c<=7&&c>0){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(20, -5,64, 128,*(  rock_down));
               display.display();          
               point++;
               delay(1000);
               
              buttonState_down=1;
              } 
  
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
  Serial.begin(115200);

pinMode(27,INPUT);
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

  server.begin();
  Serial.println("HTTP server started");

Serial.begin(115200);
  Serial.println();
 display.init(); //初始化(init)
  display.flipScreenVertically();
  display.setContrast(255); //數值介於0~255，調整對比
  display.clear();//清除螢幕和緩衝區(clear)
  display.drawXbm(35, 0,64, 128, walk_0_img);
  //印出想顯示的畫面  display.drawXbm(X座標, Y座標, 圖片寬度, 圖片高度, 圖片名稱);
  display.display(); //顯示畫面(display)
  
}







void loop(void) {
    
  point=0;
 wintime=0;
 playtime=0;
 losetime=0;
//Game initial

int rd;
    rd=analogRead(27);
    Serial.println(rd);
    rd=map(rd,0,4100,0,20);
    delay(7);
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Read Value is");
    display.drawString(0,20, String(rd));
    display.display();

 
/*if(){
/*for(int x=0;x<3 ;x++ ){
       pinMode(ledlife[x], OUTPUT);
        digitalWrite(ledlife[x], HIGH);
    
    }
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

//Game Start


while(idle_time!=6){  

           server.handleClient();
         server.send(200, "text/html",webSite);
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



    while(losetime<4){
    

  state=random(0,5);
  switch(state){

      
     //向右走
     case (1): 
      while(i!=20){
          
           
          display.clear();
        
          display.drawXbm(35+i*playSpeed, 0,64, 128,*( idle+x));
         
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
         server.handleClient();
         server.send(200, "text/html",webSite);
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
      while(i!=-20){
        
          display.clear();
          display.drawXbm(35+i*playSpeed, 0,64, 128,*( idle+x));
         
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

           server.handleClient();
         server.send(200, "text/html",webSite);
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
      while(c!=-20){
      
           
          display.clear();
        
          display.drawXbm(35, 0+c*playSpeed,64, 128,*( idle+x));
         
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
         server.handleClient();
         server.send(200, "text/html",webSite);
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
      while(c!=20){
        
          display.clear();
          display.drawXbm(35, 0+c*playSpeed,64, 128,*( idle+x));
         
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



      display.clear();
      display.drawString(0, 0, "You Lose");
      display.display(); 
      delay(1000);
      display.clear();
      display.drawString(0, 0, "Your Score");
      display.display(); 
      display.drawString(80, 25, String(point));
      display.display(); 
      delay(5000);
    */
  
  
}
  
