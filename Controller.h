#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifndef Arduino_h
#include <Arduino.h>
#include"define.h" //追加した
#endif

#define BAUD_RATE_PROMICRO 115200

class Controller
{
public:
    Controller(HardwareSerial *_Ser);

    void update();

    /**
     * コントローラのボタン入力状態を返す．
     * 
     * @param buttonNum ボタン番号 1~12
     * @return 1:押されている 0:離されている 2:押された -1:離された
     * 
     */
    int8_t readButton(int buttonNum) const;

    unsigned int getButtonState() const;

    /**
     * ジョイスティックの値を読む
     * @return -1.0 ~ 1.0
     * 
     *      X
     *      ^
     *      |
     * Y<---+----
     *      |
     *      |
     */
    double readJoyLX() const;
    double readJoyLY() const;
    double readJoyRX() const;
    double readJoyRY() const;

    unsigned int readJoyLXbyte() const;
    unsigned int readJoyLYbyte() const;
    unsigned int readJoyRXbyte() const;
    unsigned int readJoyRYbyte() const;

    bool getButtonChanged() const;

    void begin();


private:
    HardwareSerial *Ser;

    unsigned int ButtonState, preButtonState;
    unsigned int LJoyX, LJoyY, RJoyX, RJoyY;

    bool buttonChanged;
    

private:
    int recv_num;

    char recv_msgs[9];
};

#endif