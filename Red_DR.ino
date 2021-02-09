#include "define.h"     //CONTROLのために必要
#include "Controller.h"   
#include "MsTimer2.h"

bool flag_10ms =false;
Controller ESP;  // ()を付けるとうまくいかないので注意　setup()の外で宣言


void time(){
  flag_10ms = true;
}

void setup() {
  Serial.begin(115200);
  CONTROL.begin(115200);   //define.hのCONTROLをクラスの中でも使っているのでSerialを変えるときは注意が必要
                           //CONTROLが不都合ならばクラスの中のCONTROLの部分を変える必要がある
  //Serial.print("ready...\n");
  
  MsTimer2::set(10,time); 
  MsTimer2::start();
}

void loop(){
  if(flag_10ms){
    ESP.update();     //繰り返し処理の中に置いておく必要がある．これやらないとボタンの情報が更新されない
    ESP.statePrint(); //受信した(checksumを通った)値をprintするもの．多分使わない．

    delay(1);
    if(ESP.readButton(BUTTON_MARU)==2) Serial.println("open");   //押した瞬間にprintf  BUTTON_MARUは４にしても良い（define参考に）
    if(ESP.readButton(BUTTON_MARU)==-1) Serial.println("close"); //放した瞬間にprintf
    delay(1);

    flag_10ms=false;
  }

}