#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller{
    public:
        Controller();           
        void update();          //受信の処理＋ボタンの情報の更新．　繰り返し処理の中に置いておく必要がある．
        void statePrint();      //受信した情報をprint．基本受信の確認用．
        bool readButton_bin(unsigned int ButtonNum); //押していない時はfalse(0),押してるときはtrue(1)を返す．　ButtonNumはデータの欲しいボタンの名前を
        int  readButton(unsigned int ButtonNum);     //上にプラスして 押した瞬間は2，放した瞬間は-1を返す．    define.hを参考に数字を入力しても良い

        unsigned int getButtonState();  //分解する前のButtonStateの情報をprint 0~65535の値をとる
    
                                //       X
        double readJoyLX();     //       ^ 
        double readJoyLY();     //       | 
        double readJoyRX();     //  Y<---+----
        double readJoyRY();     //       | 
                                //       | 
                                //  1.0  ~   -1.0

                                //       X
        uint8_t readJoyLXbyte();//       ^ 
        uint8_t readJoyLYbyte();//       |
        uint8_t readJoyRXbyte();//  Y<---+----
        uint8_t readJoyRYbyte();//       | 
                                //       |
                                //  255  ~    0

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