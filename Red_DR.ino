#define BUTTON_X       0x0001
#define BUTTON_Y       0x0002
#define BUTTON_A       0x0004
#define BUTTON_B       0x0008
#define BUTTON_L1      0x0010
#define BUTTON_R1      0x0020
#define BUTTON_L2      0x0040
#define BUTTON_R2      0x0080
#define BUTTON_PAD     0x0100
#define BUTTON_PS      0x0200
#define BUTTON_SHARE   0x0400
#define BUTTON_OPTION  0x0800
#define BUTTON_UP      0x1000
#define BUTTON_RIGHT   0x2000
#define BUTTON_DOWN    0x4000
#define BUTTON_LEFT    0x8000

#define CONTROLL Serial7

unsigned int ButtonState;
byte RJoyX, RJoyY, LJoyX, LJoyY;

void setup() {
  Serial.begin(115200);
  CONTROLL.begin(115200);
  Serial.print("ready...\n");
}

byte serial_recieve(){
  //byte temp;
  char temp;
  do{
    temp =CONTROLL.read();
  }
  while(temp==-1);
  CONTROLL.write(temp);
  return temp;
}

void update() {
  char checksum = 0x00,receive_data[10];
  int loop_count=0;
  while(loop_count<10){
    //if (CONTROLL.available()){    
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
      delay(1);
      }
      else loop_count++;
    delay(1);
    //} 
  }

  /*if(ButtonState==BUTTON_X) Serial.print("X");
  if(ButtonState==BUTTON_Y) Serial.print("Y");
  if(ButtonState==BUTTON_A) Serial.print("A");
  if(ButtonState==BUTTON_B) Serial.print("B");
  if(ButtonState==BUTTON_L1)Serial.print("L1");
  if(ButtonState==BUTTON_R1)Serial.print("R1");
  if(ButtonState==BUTTON_L2)Serial.print("L2");
  if(ButtonState==BUTTON_R2)Serial.print("R2");
  if(ButtonState==BUTTON_PAD)Serial.print("PAD");
  if(ButtonState==BUTTON_PS)Serial.print("PS");
  if(ButtonState==BUTTON_SHARE)Serial.print("SHAPE");
  if(ButtonState==BUTTON_OPTION)Serial.print("OPTION");
  if(ButtonState==BUTTON_UP)Serial.print("UP");
  if(ButtonState==BUTTON_RIGHT)Serial.print("RIGHT");
  if(ButtonState==BUTTON_DOWN)Serial.print("DOWN");
  if(ButtonState==BUTTON_LEFT)Serial.print("LEFT");

  float LX = LJoyX/255;  //調整必要
  float LY = LJoyY/255;
  float RX = RJoyX/255;
  float RY = RJoyY/255;
  Serial.print(LX);
  Serial.print(" | ");
  Serial.print(LY);
  Serial.print(" | ");
  Serial.print(RX);
  Serial.print(" | ");
  Seiral.println(RY);*/
  
}

void loop(){
  update();

  Serial.print(ButtonState);
  Serial.print("\t");
  Serial.print(LJoyX);
  Serial.print("\t");
  Serial.print(LJoyY);
  Serial.print("\t");
  Serial.print(RJoyX);
  Serial.print("\t");
  Serial.println(RJoyY);
  delay(5);
}