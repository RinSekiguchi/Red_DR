#include <Arduino.h>
#include "define.h"
#include "Controller.h"

Controller::Controller(int SerialSpeed){
    ButtonState=0;
    RJoyX=127, RJoyY=127, LJoyX=127, LJoyY=127;
}

void Controller::Update(){
  char checksum = 0x00,receive_data[10];
  int loop_count=0;
  
    while(loop_count<10){
      
        if (CONTROL.available()){    
            if(serial_recieve()==10){

                for (int i=0;i<10;i++) receive_data[i]= serial_recieve();

                for(int i=0;i<9;i++)checksum ^=receive_data[i];

                if(receive_data[9]==checksum){
                    for (int i=0;i<9;i++) receive_data[i] -= 0x20;
                    PreButtonState = ButtonState;
                    ButtonState = (receive_data[0] & 0x3f)| ((receive_data[1] & 0x3f) << 6) | ((receive_data[2] &0x0f) << 12); 
        
                    LJoyX = receive_data[3] | (receive_data[4]<<6) ;
                    LJoyY = (receive_data[4]>>2) | (receive_data[5]<<4);
                    RJoyX = (receive_data[5]>>4) | (receive_data[6]<<2);
                    RJoyY = receive_data[7] | (receive_data[8]<<6);
                }
            }      
        } 
    loop_count++; 
    }
}

void Controller::StatePrint()
{
    Serial.print(ButtonState);
    Serial.print("\t");
    Serial.print(LJoyX);
    Serial.print("\t");
    Serial.print(LJoyY);
    Serial.print("\t");
    Serial.print(RJoyX);
    Serial.print("\t");
    Serial.println(RJoyY);
}

bool Controller::ReadButton_bin(int ButtonNum){//放しているときは０，押しているときは１
    return ((ButtonState & (0x0001 << ButtonNum - 1)) == (0x0001 << ButtonNum - 1))? true:false;
    }
    
int Controller::ReadButton_four(int ButtonNum){//放しているときは０，押しているときは１，押した瞬間は２，放した瞬間は－１
    int result = 0;
    if((ButtonState & (0x0001 << ButtonNum - 1)) == (0x0001 << ButtonNum - 1)) result += 2;
    if((PreButtonState & (0x0001 << ButtonNum - 1)) == (0x0001 << ButtonNum - 1))result -= 1;
    return result;
    }

double Controller::Read_LJoyX()
{
    if(LJoyY==127)return 0;
    return ((double)LJoyY-127.5)/127.5;
}

double Controller::Read_LJoyY()
{
    if(LJoyX==127)return 0;
    return -((double)LJoyX-127.5)/127.5;
}

double Controller::Read_RJoyX()
{   
    if(RJoyY==127)return 0;
    return ((double)RJoyY-127.5)/127.5;
}

double Controller::Read_RJoyY()
{
    if(RJoyX==127)return 0;
    return -((double)RJoyX-127.5)/127.5;
}
