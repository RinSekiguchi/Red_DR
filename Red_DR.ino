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
    ESP.Update();
    ESP.StatePrint();

    /*Serial.print(ESP.Read_X());
    Serial.print("\t");
    Serial.print(ESP.Read_Y());
    Serial.print("\t");
    Serial.print(ESP.Read_A());
    Serial.print("\t");
    Serial.print(ESP.Read_B());
    Serial.print("\t");
    Serial.print(ESP.Read_L1());
    Serial.print("\t");
    Serial.print(ESP.Read_R1());
    Serial.print("\t");
    Serial.print(ESP.Read_L2());
    Serial.print("\t");
    Serial.print(ESP.Read_R2());
    Serial.print("\t");
    Serial.print(ESP.Read_PAD());
    Serial.print("\t");
    Serial.print(ESP.Read_PS());
    Serial.print("\t");
    Serial.print(ESP.Read_SHARE());
    Serial.print("\t");
    Serial.print(ESP.Read_OPTION());
    Serial.print("\t");
    Serial.print(ESP.Read_UP());
    Serial.print("\t");
    Serial.print(ESP.Read_RIGHT());
    Serial.print("\t");
    Serial.print(ESP.Read_DOWN());
    Serial.print("\t");
    Serial.print(ESP.Read_LEFT());
    Serial.print("\t");
    Serial.print(ESP.Read_LJoyX());
    Serial.print("\t");
    Serial.print(ESP.Read_LJoyY());
    Serial.print("\t");
    Serial.print(ESP.Read_RJoyX());
    Serial.print("\t");
    Serial.println(ESP.Read_RJoyY());*/

    flag_10ms=false;
  }
}