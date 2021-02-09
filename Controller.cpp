#include <Arduino.h>
#include "define.h"
#include "Controller.h"

Controller::Controller(){
    ButtonState=0;
    RJoyX=127, RJoyY=127, LJoyX=127, LJoyY=127;
}

void Controller::update(){
  char checksum = 0x00,receive_data[9];
  int loop_count=0;
  
    while(loop_count<10 && CONTROL.available()){    
            if(serial_recieve()==10){

                for (int i=0;i<9;i++) receive_data[i]= serial_recieve();
                for (int i=0;i<9;i++) receive_data[i] -= 0x20;
                for(int i=0;i<8;i++)checksum ^=receive_data[i];

                if(receive_data[8]==checksum){
                
                    preButtonState = ButtonState;
                    ButtonState = (receive_data[0] & 0x3f) | ((receive_data[1] & 0x3f) << 6) | ((receive_data[2] &0x0f) << 12);

                    LJoyX = receive_data[3] | (receive_data[4]<<6) ;
                    LJoyY = (receive_data[4]>>2) | (receive_data[5]<<4);
                    RJoyX = (receive_data[5]>>4) | (receive_data[6]<<2);
                    RJoyY = receive_data[7] | ((receive_data[2] & 0x30)<<2);
                    
                    break;
                }
            }
     loop_count++;
    }

}

void Controller::statePrint()
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

bool Controller::readButton_bin(unsigned int ButtonNum){//放しているときは０，押しているときは１
    return ((ButtonState & (0x0001 << (ButtonNum - 1))) == (0x0001 << (ButtonNum - 1)))? true:false;
    }
    
int Controller::readButton(unsigned int ButtonNum){//放しているときは０，押しているときは１，押した瞬間は２，放した瞬間は－１
    int result = 0;
    if((ButtonState & (0x0001 << (ButtonNum - 1))) == (0x0001 << (ButtonNum - 1))) result += 2;
    if((preButtonState & (0x0001 << (ButtonNum - 1))) == (0x0001 << (ButtonNum - 1)))result -= 1;
    return result;
    }

unsigned int Controller::getButtonState(){
    return ButtonState;
    }

double Controller::readJoyLX()
{
    if(LJoyY==127)return 0;
    return ((double)LJoyY-127.5)/127.5;
}

double Controller::readJoyLY()
{
    if(LJoyX==127)return 0;
    return -((double)LJoyX-127.5)/127.5;
}

double Controller::readJoyRX()
{   
    if(RJoyY==127)return 0;
    return ((double)RJoyY-127.5)/127.5;
}

double Controller::readJoyRY()
{
    if(RJoyX==127)return 0;
    return -((double)RJoyX-127.5)/127.5;
}

uint8_t Controller::readJoyLXbyte()
{
    return LJoyY;
}
    
uint8_t Controller::readJoyLYbyte()
{
    return LJoyX;
}
    
uint8_t Controller::readJoyRXbyte()
{
    return RJoyY;
}
    
uint8_t Controller::readJoyRYbyte()
{
    return RJoyX;
}