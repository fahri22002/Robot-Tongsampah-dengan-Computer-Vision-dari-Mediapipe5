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
  pinMode(IF_kiri, INPUT);
  pinMode(IF_kanan, INPUT);
  servo.attach(s);
  servo.write(pos);
  // Set motor sebagai output
  pinMode(VelL, OUTPUT);
  pinMode(VelR, OUTPUT);
  pinMode(EnL, OUTPUT);
  pinMode(EnR, OUTPUT);

  // Inisialisasi motor mati
  STOP();
}

void loop() {
    // Membaca nilai dari sensor infrared
    if (Serial.available() > 0) {
    // Membaca data dari serial
    receivedChar = Serial.read();
    }

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
  digitalWrite(EnL, LOW);
  digitalWrite(EnR, LOW);
  delay(0);
  digitalWrite(EnL, HIGH);
  digitalWrite(EnR, HIGH);
  Serial.println("STOP");
}

void KANAN(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, HIGH);
  digitalWrite(EnR, LOW);
  Serial.println("KANAN");
}

void KIRI(){
  analogWrite(VelL, 250);
  analogWrite(VelR, 250);
  digitalWrite(EnL, LOW);
  digitalWrite(EnR, HIGH);
  Serial.println("KIRI");
}

void OPEN(){
  servo.write(pos-90);
  delay(3000);
  servo.write(pos+90);
}
