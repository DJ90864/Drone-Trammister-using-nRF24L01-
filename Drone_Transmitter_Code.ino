#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9, 10); // CE, CSN


const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; 


  struct Data_Sent{
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte pot1;
  byte pot2;
  byte toggle1;
  byte toggle2;
};


Data_Sent inputs;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   
  radio.begin();
  radio.openWritingPipe(my_radio_pipe);  
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  
  reset_data();
}



void loop() {
  // put your main code here, to run repeatedly:

  read_data();
 
  
  radio.write(&inputs, sizeof(Data_Sent));
  
}

void read_data(){

  inputs.throttle = map(analogRead(A9), 0, 1023, 0, 255);
  inputs.yaw = map(analogRead(A8), 0, 1023, 0, 255);
  inputs.pitch = map(analogRead(A7), 0, 1023, 0, 255);
  inputs.roll = map(analogRead(A6), 0, 1023, 0, 255);
  inputs.pot1 = map(analogRead(A4), 0, 1023, 0, 255);
  inputs.pot2 = map(analogRead(A2), 0, 1023, 0, 255);
  inputs.toggle1 = digitalRead(2);
  inputs.toggle2 = digitalRead(4);
  
}

void reset_data(){

  inputs.throttle = 127;
  inputs.yaw = 127;
  inputs.pitch = 127;
  inputs.roll = 127;
  inputs.pot1 = 0;
  inputs.pot2 = 0;
  inputs.toggle1 = 0;
  inputs.toggle2 = 0;
  
}
