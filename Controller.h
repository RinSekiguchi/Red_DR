#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller{
    public:
        Controller(int SerialSpeed);
        void Update();
        void StatePrint();
        bool ReadButton_bin(int ButtonNum);
        int  ReadButton_four(int ButtonNum);
    
        double Read_LJoyX();
        double Read_LJoyY();
        double Read_RJoyX();
        double Read_RJoyY();    
        
    private:
        
        unsigned int ButtonState;
        unsigned int PreButtonState;
        uint8_t RJoyX, RJoyY, LJoyX, LJoyY;

        byte serial_recieve(){
        char temp;
        do{
            temp =CONTROL.read();
        }
        while(temp==-1);
        CONTROL.write(temp);
        return temp;
        }
};

#endif