#include <Servo.h>
const int s = 9;
Servo servo;
int VelL = 5;
int VelR = 6;
int EnL = 4; //kiri
int EnR = 7; //kanan
int pos = 90;
void setup() {
  // Set sensor infrared sebagai input
  servo.attach(s);
  servo.write(pos);
  // Set motor sebagai output
  pinMode(VelL, OUTPUT);
  pinMode(VelR, OUTPUT);
  pinMode(EnL, OUTPUT);
  pinMode(EnR, OUTPUT);
 pinMode(12, OUTPUT);
  // BT.begin(9600);
  Serial.begin(9600);
  STOP();
}
int i = 10;
void loop() {
      servo.write(90-i);
///////////////////////////////////////////////////////////////////////////////////////////
  
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
     
      case 'F':
        MAJU();
        break;
      case 'B':
        MUNDUR();
        break;
      case 'L':
        KIRI();
        break;
      case 'R':
        KANAN();
        break;
      case 'S':
        STOP();
        break;
    }
  
        
  }
}

void MAJU(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, HIGH);
  digitalWrite(EnR, HIGH);
  // delay(1000);
  Serial.println("MAJU");
}

void MUNDUR(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, LOW);
  digitalWrite(EnR, LOW);
  // delay(1000);
  Serial.println("MUNDUR");
}

void STOP(){
  analogWrite(VelL, 0);
  analogWrite(VelR, 0);
  // delay(1000);
  Serial.println("STOP");
}

void KIRI(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, HIGH);
  digitalWrite(EnR, LOW);
  // delay(1000);
  Serial.println("KANAN");
}

void KANAN(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, LOW);
  digitalWrite(EnR, HIGH);
  // delay(1000);
  Serial.println("KIRI");
}