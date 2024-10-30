// Definisi pin sensor
#include <Servo.h>

const int s = 8;
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

  // Inisialisasi motor mati
  Serial.begin(9600);
  STOP();
}

void loop() {
    if (Serial.available() > 0) {
    // Membaca data dari serial
      char receivedChar = Serial.read();
      Serial.println(receivedChar);
      if (receivedChar == 'F') {
        MAJU();
      }
      else if (receivedChar == 'L') { // kalau yang hitam cuma dikiri maka harus belok kiri agar sensor kanan mendeteksi hitam
        KIRI();
      }
      else if (receivedChar == 'R') {
        KANAN();
      }
      // Jika tidak ada yang terdeteksi, berhenti
      else if (receivedChar == 'B'){
        MUNDUR();
      }else {
        STOP();
        OPEN();
      } 

  }
}

void MAJU(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, HIGH);
  digitalWrite(EnR, HIGH);
  Serial.println("MAJU");
}

void MUNDUR(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, LOW);
  digitalWrite(EnR, LOW);
  Serial.println("MUNDUR");
}

void STOP(){
  analogWrite(VelL, 0);
  analogWrite(VelR, 0);
  Serial.println("STOP");
}

void KIRI(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, HIGH);
  digitalWrite(EnR, LOW);
  Serial.println("KANAN");
}

void KANAN(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, LOW);
  digitalWrite(EnR, HIGH);
  Serial.println("KIRI");
}

void OPEN(){
  servo.write(pos-90);
  delay(5000);
  servo.write(pos+90);
}
