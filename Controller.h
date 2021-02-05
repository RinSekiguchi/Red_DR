#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller{
    public:
        Controller(int SerialSpeed);
        void Update();
        void StatePrint();
    
        bool Read_X();
        bool Read_Y();
        bool Read_A();
        bool Read_B();
        bool Read_L1();    
        bool Read_R1();
        bool Read_L2();
        bool Read_R2();
        bool Read_PAD();
        bool Read_PS();
        bool Read_SHARE();
        bool Read_OPTION();
        bool Read_UP();
        bool Read_RIGHT();
        bool Read_DOWN();
        bool Read_LEFT();
    
        double Read_LJoyX();
        double Read_LJoyY();
        double Read_RJoyX();
        double Read_RJoyY();    
        
    private:
        
        unsigned int ButtonState;
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