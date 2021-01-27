#ifndef DEFINE_h
#define DEFINE_h
#include "Arduino.h"

/*struct coords //足回り
{
double x;
double y;
double z;
}*/
#define PI 3.1415926535
#define SERIAL_LPMSME1 Serial1
#define SERIAL_ROBOCLAW Serial4
#define SERIAL_LCD Serial6
#define SERIAL_LEONARDO Serial5//コントローラーのシリアル通信
#define SERIAL_XBEE Serial7

#define DIST4WHEEL (0.421185)
#define _RES_PIWHEELDIM (4 * 1024 / (3.141592 * 0.1)) //カウント値を円周で割ってrev/sに直す　Robclowに送るために変換する

#define ADR_MD1 (131) //RoboClawのアドレス
#define ADR_MD2 (130)

#define BUTTON_SIKAKU 1//コントローラーのボタン設定
#define BUTTON_SANKAKU 2
#define BUTTON_BATU 3
#define BUTTON_MARU 4

#define BUTTON_L1 5
#define BUTTON_R1 6
#define BUTTON_L2 7
#define BUTTON_R2 8

#define BUTTON_PAD 9
#define BUTTON_PS 10
#define BUTTON_SHARE 11
#define BUTTON_OPTION 12

#define BUTTON_UP 13
#define BUTTON_RIGHT 14
#define BUTTON_DOWN 15
#define BUTTON_LEFT 16

#define PIN_LED_1 20
#define PIN_LED_2 36
#define PIN_LED_3 37

#define LIMIT_1 47
#define LIMIT_2 48
#define LIMIT_3 46
#define LIMIT_4 49

#define SOLENOID_1 45
#define SOLENOID_2 44

#define BODY_A 0.4
#define BODY_B 0.55

#endif 　 //最後にこれを入れる
