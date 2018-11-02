#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "animation.h"
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#define Logo_width 128
#define Logo_height 64
SSD1306Wire  display(0x3c, 21, 22);
const int buttonPin_right = 19; 
String website;
const char* ssid = "iPhone";
const char* password = "maggie9907";
int buttonState_right=0;
int i=0;

const int buttonPin_left = 32;

int buttonState_left=0;
int x=0;

int idle_time=0;
int state=-1;
int playSpeed=20;
int point=0;
int wintime=0;
int playtime=0;
WebServer server(80);

const int led = 23;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", website);
  digitalWrite(led, 0);
}

void right(){
            server.handleClient();
             digitalWrite(led,HIGH);
              display.drawXbm(100,7 ,64, 128,*(rock_right));
             display.display(); 
                    
             if(i<=6&&i>0){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(100, 7,64, 128,*(  rock_right));
               display.display();          
               point++;
               delay(1000);
               wintime++;
               buttonState_right=1;
              } 
                    
  server.send(200, "text/html", website);
  }

void left(){
          server.handleClient();
  digitalWrite(led,HIGH);
   display.drawXbm(-35,7 ,64, 128,*(rock_left));
             display.display(); 
            
             
             if(i>=-6&&i<0){
               display.clear();
               display.drawXbm(35, 0,64, 128,*( idle+x));
               display.display(); 
               display.drawXbm(-35, 7,64, 128,*(  rock_left));
               display.display();          
               point++;
               delay(1000);
               wintime++;
              buttonState_left=1;
              } 
  server.send(200, "text/html", website);
  }


void buildWeb(){
  website += "<html>";
  website += "<head>\n";
  website += "<meta charset='UTF-8'/>\n";
  website += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  website += "<title>Remote Control LED</title>\n";
  website += "<style>";
  website += "html{background-color:#cbef99;}";
  website += ".title{text-align:right;color:#ffaad6;text-shadow:0px 3px 5px #000; margin-bottom: 50px;}";
  website += "a{display:flex;text-decoration:none;background-color:#FFFFFF;radius:3px; ";
  website += "width:150px;text-align:center;margin:0 auto;margin-bottom:30px;font-size:2em;box-shadow: 0px 3px 6px #000;}";
  website += ".btn1{color:#659700;}";
  website += ".btn2{color:#A8A8A8;}";
  website += "</style>";
  website += "</head>\n";
  website += "<body>";
  website += "<h1 class=\"title\">Remote LED Control</h1>";
  website += "<a class=\"btn1\" href=\"/R\">右</a>";
  website += "<a class=\"btn2\" href=\"/L\">左</a>";
  website += "</body></html>";
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
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 buildWeb();
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
  
  server.on("/R", right);
  server.on("/L", left);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");


 display.init(); //初始化(init)
  display.setContrast(255); //數值介於0~255，調整對比
  display.clear();//清除螢幕和緩衝區(clear)
  display.drawXbm(35, 0,64, 128, walk_0_img);
  //印出想顯示的畫面  display.drawXbm(X座標, Y座標, 圖片寬度, 圖片高度, 圖片名稱);
  display.display(); //顯示畫面(display)
  
}







void loop(void) {
  server.handleClient();



    while(/*playtime-wintime<=4*/1){
   playtime++;
  buttonState_right = digitalRead(buttonPin_right);
   server.handleClient();

  state=random(0,3);
  switch(state){

     
     //向右走
     case (1): 
      while(i!=20){
      
        server.handleClient();
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
         if(buttonState_right==1){
          buttonState_right=0;
          break;
          }
          
      }
      i=0;
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
    //向右走結束

  //向左走
 case (2): 
      while(i!=-20){
        server.handleClient();
      display.clear();
          display.drawXbm(35+i*playSpeed, 0,64, 128,*( idle+x));
          x++;
          i--;
          display.display(); 
          delay(100);
     
          if(x==2){
             x=0;
          }
          
          if(buttonState_right==HIGH){
             display.drawXbm(100, 7,64, 128,*(  rock_right));
             display.display();          
            
            }
          if(buttonState_left==1){
          
          buttonState_left=0;
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
      //向左走結束

    

          
}
     
      
  
}



 display.clear();
      display.drawString(0, 0, "You Lose");
      display.display(); 
      delay(1000);
    
}
  
