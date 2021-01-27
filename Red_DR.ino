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

unsigned int ButtonState;
byte RJoyX, RJoyY, LJoyX, LJoyY;

void setup() {
  Serial.begin(115200);
  Serial4.begin(115200);
  Serial.print("ready...\n");
}

byte serial_recieve(){
  int temp;
  do{
    temp =Serial4.read();
  }
  while(temp==-1);
  //Serial.write(temp);
  return temp;
}

void loop() {
  if (Serial4.available()){
    if(serial_recieve()=='\n'){

      byte checksum = 0,receive_data[8];

      for (int i=0;i<8;i++) receive_data[i]= serial_recieve();

      //for(int i=0;i<9;i++)checksum ^=receive_data[i];
      for (int i = 0; i < 9; i++) checksum += receive_data[i];
      checksum = checksum & 0x3F + 0x20;
        

      if(checksum==(serial_recieve())/*&&('\n' == serial_recieve())*/){

        for (int i=0;i<9;i++) receive_data[i]-0x20;

        ButtonState = receive_data[0] | (receive_data[1]<<6) | (receive_data[2]<<12); 
        
        LJoyX = receive_data[3] | (receive_data[4]<<6) ;
        LJoyY = (receive_data[4]>>2) | (receive_data[5]<<4);
        RJoyX = (receive_data[5]>>4) | (receive_data[6]<<2);
        RJoyY = receive_data[7] | (receive_data[8]<<6);

        /*for (int i=0;i<9;i++){
         Serial.print(receive_data[i]);
         Serial.print("\t");
         } 
         Serial.print("\t\t");
         Serial.println(checksum); */
        //Serial.println((int)checksum);

        Serial.print(ButtonState);
        Serial.print("\t");
        Serial.print(LJoyX);
        Serial.print("\t");
        Serial.print(LJoyY);
        Serial.print("\t");
        Serial.print(RJoyX);
        Serial.print("\t");
        Serial.println(RJoyY);

        delay(4);
      }
    }
  }
}

