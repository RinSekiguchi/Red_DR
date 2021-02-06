#include "define.h"
#include "Controller.h"
#include "MsTimer2.h"

bool flag_10ms =false;
Controller ESP(115200);

void time(){
  flag_10ms = true;
}

void setup() {
  Serial.begin(115200);
  CONTROL.begin(115200);
  Controller ESP(115200);
  Serial.print("ready...\n");
  
  MsTimer2::set(10,time); 
  MsTimer2::start();
}

void loop(){
  if(flag_10ms){
    ESP.update();
    ESP.statePrint();

    /*Serial.print(ESP.readButton_bin(1));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(2));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(3));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(4));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(5));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(6));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(7));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(8));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(9));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(10));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(11));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(12));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(13));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(14));
    Serial.print("\t");
    Serial.print(ESP.readButton_bin(15));
    Serial.print("\t");
    Serial.println(ESP.readButton_bin(16));*/
    delay(1);
    if(ESP.readButton(BUTTON_MARU)==2) Serial.println("open");
    if(ESP.readButton(BUTTON_MARU)==-1) Serial.println("close");
    delay(1);

    flag_10ms=false;
  }


  
  
}