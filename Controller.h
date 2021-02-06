#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller{
    public:
        Controller(int SerialSpeed);
        void update();
        void statePrint();
        bool readButton_bin(unsigned int ButtonNum);
        int  readButton(unsigned int ButtonNum);

        unsigned int getButtonState();
    
        double readJoyLX();
        double readJoyLY();
        double readJoyRX();
        double readJoyRY();   

        uint8_t readJoyLXbyte();
        uint8_t readJoyLYbyte();
        uint8_t readJoyRXbyte();
        uint8_t readJoyRYbyte(); 
        
    private:
        
        unsigned int ButtonState;
        unsigned int preButtonState;
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