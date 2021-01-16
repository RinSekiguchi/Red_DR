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
    if(serial_recieve()=='~'){

      byte checksum = 0,receive_data[9];

      for (int i=0;i<9;i++) receive_data[i]= serial_recieve();

      for(int i=0;i<9;i++)checksum ^=receive_data[i];
      if(checksum=='~') checksum='}';

      if((checksum==serial_recieve())&&('\n' == serial_recieve())){
        for (int i=0;i<9;i++){
         Serial.print(receive_data[i]);
         Serial.print("\t");
         } 
         Serial.print("\t\t");
         Serial.println(checksum); 
        //Serial.println((int)checksum);
        delay(4);
      }
    }
  }
}

