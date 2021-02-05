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

bool Controller::Read_X()
{
    return ((ButtonState & BUTTON_X) == BUTTON_X)? true:false;
}

bool Controller::Read_Y()
{
    return ((ButtonState & BUTTON_Y) == BUTTON_Y)? true:false;
}

bool Controller::Read_A()
{
    return ((ButtonState & BUTTON_A) == BUTTON_A)? true:false;
}

bool Controller::Read_B()
{
    return ((ButtonState & BUTTON_B) == BUTTON_B)? true:false;
}

bool Controller::Read_L1()
{
    return ((ButtonState & BUTTON_L1)== BUTTON_L1)? true:false;
}

bool Controller::Read_R1()
{
    return ((ButtonState & BUTTON_R1) == BUTTON_R1)? true:false;
}

bool Controller::Read_L2()
{
    return ((ButtonState & BUTTON_L2) == BUTTON_L2)? true:false;
}

bool Controller::Read_R2()
{
    return ((ButtonState & BUTTON_R2) == BUTTON_R2)? true:false;
}

bool Controller::Read_PAD()
{
    return ((ButtonState & BUTTON_PAD) == BUTTON_PAD)? true:false;
}

bool Controller::Read_PS()
{
    return ((ButtonState & BUTTON_PS) == BUTTON_PS)? true:false;
}

bool Controller::Read_SHARE()
{
    return ((ButtonState & BUTTON_SHARE) == BUTTON_SHARE)? true:false;
}

bool Controller::Read_OPTION()
{
    return ((ButtonState & BUTTON_OPTION) == BUTTON_OPTION)? true:false;
}

bool Controller::Read_UP()
{
    return ((ButtonState & BUTTON_UP) == BUTTON_UP)? true:false;
}

bool Controller::Read_RIGHT()
{
    return ((ButtonState & BUTTON_RIGHT) == BUTTON_RIGHT)? true:false;
}

bool Controller::Read_DOWN()
{
    return ((ButtonState & BUTTON_DOWN) == BUTTON_DOWN)? true:false;
}

bool Controller::Read_LEFT()
{
    return ((ButtonState & BUTTON_LEFT) == BUTTON_LEFT)? true:false;
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
