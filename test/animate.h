
#include <Wire.h> 
#include"images.h"
#include "SSD1306Wire.h"
void Changescene() {
    for (int i=1; i < 33; i++) {
        display.setColor(WHITE);
        display.drawRect(64-2*i, 32-i, 4*i, 2*i);
        display.fillRect(64-2*i, 32-i, 4*i, 2*i);
        delay(100);
    }
    delay(700);
    for (int i=32; i > 0; i--) {
        display.clear();
        display.setColor(WHITE);
        display.drawRect(64-2*i, 32-i, 4*i, 2*i);
        display.fillRect(64-2*i, 32-i, 4*i, 2*i);
        delay(100);
    }
}//切換畫面用

void Drawball(int b_x,int b_y){
    display.drawCircle(b_x, b_y, 2);
    display.fillCircle(b_x, b_y, 2);
}//遊戲跑動球用

void Lost(){
    display.drawXbm(0,0, 128, 64, bd_bits);
    delay(1000);
    //display.clear();//想測試能不能直接覆蓋畫面
    for (int i=0; i <= 32; i++) {
        display.drawXbm(128-i*4,0, 128, 64, lost1_bits);
        delay(300);
        display.clear();
    }
    for (int i=0; i <=3 ; i++) {
        display.drawXbm(0,0, 128, 64, lost1_bits);
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, lost2_bits);
        delay(250);
        display.clear();
    }
}//遊戲輸了用

void Win(){
    display.drawXbm(0,0, 128, 64, hd_bits);
    delay(1000);
    //display.clear();//想測試能不能直接覆蓋畫面
    for (int i=0; i <= 32; i++) {
        display.drawXbm(128-i*4,0, 128, 64, win1_bits);
        delay(300);
        display.clear();
    }
    for (int i=0; i <=3 ; i++) {
        display.drawXbm(0,0, 128, 64, win1_bits);
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, win2_bits);
        delay(250);
        display.clear();
    }
}//遊戲贏了用

void Retry(){
     display.drawXbm(0,0, 128, 64, retry_bits);
    //可以回傳個網頁回去嗎？
}

void Close(){
    for (int i=0; i <=3 ; i++) {
        display.drawXbm(0,0, 128, 64, close1_bits);
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, close2_bits);
        delay(250);
        display.clear();
    }
    //想設計成漸漸消失的樣子，程式碼還沒想
}//關機用

void Start(){
    for (int i=0; i <=5 ; i++) {
        display.drawXbm(0,0, 128, 64, saveearth1_bits);
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, saveearth2_bits);
        delay(250);
        display.clear();
    }
   // while(1) {
        //  /*讀狀態的程式碼要加～不會寫～*/
        display.drawXbm(0,0, 128, 64, start1_bits);
        delay(250);
        display.clear();
        display.drawXbm(0,0, 128, 64, start2_bits);
        delay(250);
        display.clear();
       // if(/*點擊了start*/)break;
    //}
}//點start畫面使用

void Gamepic(){
    display.drawXbm(0,0, 128, 64,gamepic_bits);
    /*display.setFont(ArialMT_Plain_16);
    for (int i=120; i>=0; i--) {
        display.drawString(12,7,i);
        deley(1000);
    }*///待解決的問題：倒數計時要怎麼做？一旦用display.clear()畫面全會消失
}
