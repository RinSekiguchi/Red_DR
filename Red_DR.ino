//0116 四輪メカナムプログラム

#include <Arduino.h>
#include <MsTimer2.h>
#include <math.h>
#include "encCounter.h"
#include "RoboClaw.h"
#include "lpms_me1Peach.h"
#include "define.h"
#include "LCDclass.h"
#include "Controller.h" //コントローラーを使うためのライブラリ―
#include "Filter.h"

myLCDclass myLCD(&SERIAL_LCD);
RoboClaw MD(&SERIAL_ROBOCLAW, 1);
Controller CONT(&SERIAL_LEONARDO);

double INT_TIME = 0.010;           //PIDのライブラリーの中で使う時間
int MS_INT_TIME = INT_TIME * 1000; //msに変換する、MSタイマーではこの単位に変換
int A = 0;                         //ボタンの値が入る
Filter count_filx(INT_TIME);
Filter count_fily(INT_TIME);
Filter count_filz(INT_TIME);

double TRnoXziku = 0.0; //　速度計算代入
double TRnoYziku = 0.0;

int LED_count = 0;   //LEDを光らせる際に数をカウント？？
int print_count = 0; //何回割込みをしたか数えるため
double angle_rad = 0.0; //ジャイロセンサから読み取った角度
double refVx = 0.0; //コントローラーの値(-1~1までに変換)
double refVy = 0.0;
double refVz = 0.0;

int tmpJoyx; //コントローラーのクラスからの値
int tmpJoyy;
int tmpJoyz;

double TimerENC1 = 0.0; //エンコーダの差
double TimerENC2 = 0.0;
double LCL_ENC_mmps_x = 0.0; //エンコーダローカル完成
double LCL_ENC_mmps_y = 0.0;

double ENC_DIS_x = 0.0; //エンコーダのローカルからグローバルへの変換
double ENC_DIS_y = 0.0;
double pre_enc_one = 0.0; //前のエンコーダの値代入
double pre_enc_two = 0.0;

double mdCmdA; //速度、roboclowに送る前
double mdCmdB;
double mdCmdC;
double mdCmdD;
double fil_refVx; //フィルターに掛けた後のジョイスティックの値
double fil_refVy;
double fil_refVz;

double diff_vel_error_x = 0.0; //I制御
double x_cmd = 0.0;            //グローバルの速度指令X
double gain1_x = 1.0;
double gain2_x = 0.0;

double diff_vel_error_y = 0.0;
double y_cmd = 0.0; //グローバルの速度指令X
double gain1_y = 1.0;
double gain2_y = 0.0;

double gol_con_x = 0.0; //グローバルからローカル
double gol_con_y = 0.0;

//シリアル通信関係
lpms_me1 lpms(&SERIAL_LPMSME1); //ジャイロセンサーの通信？？
// 自己位置推定用のエンコーダの初期化
encCounter enc1(1);
encCounter enc2(2);
int enc_one = 0;
int enc_two = 0;

bool flag_10ms = false;

void timer_warikomi()
{
  CONT.update();    //コントローラーの値をアップデート
  flag_10ms = true; //0.1秒ごと周期割込みするため　
  print_count++;    //割込みの回数をカウント

  //エンコーダデータ取得
  enc_one = enc1.getCount(); //エンコーダーからカウント値を取得
  enc_two = enc2.getCount(); //

  //LPMS-ME1から角度を取得(ジャイロセンサー、機体の角度を検出)
  angle_rad = (double)lpms.get_z_angle();
  TimerENC1 = (enc_one - pre_enc_one); //前との差を比較
  TimerENC2 = (enc_two - pre_enc_two);

  //エンコーダー速度(m/s)変換
  TRnoYziku = -1 * (0.048 * PI * ((double)TimerENC2 / 800.0)) / INT_TIME;
  TRnoXziku = -1 * (0.048 * PI * ((double)TimerENC1 / 800.0)) / INT_TIME;

  //ローカルエンコーダ完成
  LCL_ENC_mmps_x = TRnoXziku * INT_TIME; //距離
  LCL_ENC_mmps_y = TRnoYziku * INT_TIME;

  //エンコーダーデータをローカルからグローバルへ
  ENC_DIS_x += (LCL_ENC_mmps_x * cos(angle_rad)) + (-LCL_ENC_mmps_y * sin(angle_rad));
  ENC_DIS_y += -1 * ((LCL_ENC_mmps_x * sin(angle_rad)) + (LCL_ENC_mmps_y * cos(angle_rad))); //＋＝にすることで前回の値と比較、累積させていく

  //エンコーダの前回値代入
  pre_enc_one = enc_one;
  pre_enc_two = enc_two;
}

void setup()
{
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);

  //シリアル通信関係
  Serial.begin(115200);          //PCとの通信速度
  SERIAL_ROBOCLAW.begin(115200); //Robclawとのシリアル通信のボーレート
  SERIAL_LCD.begin(115200);
  SERIAL_XBEE.begin(115200);

  enc1.init();
  enc2.init();

  if (lpms.init() != 1)
  {
  }

  MsTimer2::set((int)MS_INT_TIME, timer_warikomi); // 10ms period
  MsTimer2::start();

  count_filx.setLowPassPara(0.16, 0.0);
  count_fily.setLowPassPara(0.32, 0.0);
  count_filz.setLowPassPara(0.16, 0.0);

  　 myLCD.color_white(); //LCDの色を白に
  myLCD.clear_display();
  myLCD.color_blue(); //青色に変更
}

void loop()
{
  digitalWrite(PIN_LED_GREEN, LOW);
  if (flag_10ms)
  {
    myLCD.write_str("angle", LINE_1, 0);   //angleの文字表氏
    myLCD.write_str(angle_rad, LINE_1, 6); //実際の角度表示
    myLCD.write_str("DISx", LINE_2, 0);
    myLCD.write_double(ENC_DIS_x, LINE_2, 6); //グローバルの距離
    myLCD.write_str("DISy", LINE_3, 0);
    myLCD.write_double(ENC_DIS_y, LINE_3, 6);

    A = CONT.readButton(BUTTON_MARU);     //足回りの制御方法に応じて使うボタンを割り振る
    tmpJoyx = CONT.readJoyLXbyte();       //127
    tmpJoyy = 255 - CONT.readJoyLYbyte(); //128
    tmpJoyz = CONT.readJoyRYbyte();       //128

    if (refVx < 128 && refVx > -128 && refVy < 128 && refVy > -128 && refVz < 128 && refVz > -128)
    {
      refVx = (tmpJoyx * 0.008) - 1.02; //1m/sに直す
      refVy = (tmpJoyy * 0.008) - 1.02; //もっとスマートに計算できる??
      refVz = (tmpJoyz * 0.008) - 1.02;

      //コントローラーの値をローカルに変換
      gol_con_x = (refVx * cos(angle_rad)) + (-refVy * sin(angle_rad));
      gol_con_y = -1 * ((refVx * sin(angle_rad)) + (refVy * cos(angle_rad)));

      //コントローラーの値をフィルターにかける
      fil_refVx = count_filx.LowPassFilter(gol_con_x);
      fil_refVy = count_fily.LowPassFilter(gol_con_y);
      fil_refVz = count_filz.LowPassFilter(refVz);

      //コントローラーの速度指令値と現状の速さを速度PIDをかける
      double vel_error_x = fil_refVx - TRnoXziku;
      static double pre_vel_error_x = vel_error_x;
      diff_vel_error_x = (vel_error_x - pre_vel_error_x) / INT_TIME;
      x_cmd = vel_error_x * gain1_x + diff_vel_error_x * gain2_x;

      double vel_error_y = fil_refVy - TRnoYziku;
      static double pre_vel_error_y = vel_error_y;
      diff_vel_error_y = (vel_error_y - pre_vel_error_y) / INT_TIME;
      y_cmd = vel_error_y * gain1_y + diff_vel_error_y * gain2_y; //この辺クラス化してすっきりさせたい

      Serial.print(fil_refVx); //ジョイスティックの速度指令値を表示
      Serial.print("\t");
      Serial.print(fil_refVy);
      Serial.print("\t");
      Serial.print(fil_refVz);
      Serial.println("\t");
    }
    //roboclowに速度指令値を送る
    double refOmegaA, refOmegaB, refOmegaC, refOmegaD;
    refOmegaA = x_cmd + y_cmd + (BODY_A + BODY_B)*angle_rad;
    refOmegaB = x_cmd + -1*y_cmd + -1*(BODY_A + BODY_B)*angle_rad;
    refOmegaC = x_cmd + y_cmd + -1*(BODY_A + BODY_B)*angle_rad;
    refOmegaD = x_cmd + -1*y_cmd + (BODY_A + BODY_B)*angle_rad;
    
    //それぞれのモーターに送る速度指令値がrefOmegaA~D
    //roboclawに送るためにpps(pulse/s)に変換する
    mdCmdA = refOmegaA * _RES_PIWHEELDIM;
    mdCmdB = refOmegaB * _RES_PIWHEELDIM;
    mdCmdC = refOmegaC * _RES_PIWHEELDIM;
    mdCmdD = refOmegaD * _RES_PIWHEELDIM;

    MD.SpeedM1(ADR_MD1, (int)mdCmdA); // 左前 ①
    MD.SpeedM2(ADR_MD1, (int)mdCmdB); // 左後 ②
    MD.SpeedM1(ADR_MD2, (int)mdCmdC);  // 右後 ③
    MD.SpeedM2(ADR_MD2, (int)mdCmdD);  // 右前 ④
    flag_10ms = false;
  }
}
