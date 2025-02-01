// Definisi pin sensor
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1); // Gunakan pin 0 (RX) dan 1 (TX) untuk modul Bluetooth
const int s = 9;
Servo servo;

int VelL = 5;
int VelR = 6;
int EnL = 4; // Kiri
int EnR = 7; // Kanan
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

    BT.begin(9600);
    STOP();
}
void loop() {
    char receivedChar = BT.read();
    
    if (serial.available()) {
        receivedChar = serial.read();
    }

    if (receivedChar == 'F') {
        MAJU();
    } else if (receivedChar == 'L') {
        KIRI();
    } else if (receivedChar == 'R') {
        KANAN();
    } else if (receivedChar == 'S') {
        STOP();
        OPEN();
    } else if (receivedChar == 'B') {
        MUNDUR();
    } else {
        // Tidak ada aksi
    }
}

void MAJU() {
    analogWrite(VelL, 250);
    analogWrite(VelR, 250);
    digitalWrite(EnL, HIGH);
    digitalWrite(EnR, HIGH);
    Serial.println("MAJU");
}

void MUNDUR() {
    analogWrite(VelL, 250);
    analogWrite(VelR, 250);
    digitalWrite(EnL, LOW);
    digitalWrite(EnR, LOW);
    Serial.println("MUNDUR");
}

void STOP() {
    analogWrite(VelL, 0);
    analogWrite(VelR, 0);
    Serial.println("STOP");
}

void KIRI() {
    analogWrite(VelL, 250);
    analogWrite(VelR, 250);
    digitalWrite(EnL, HIGH);
    digitalWrite(EnR, LOW);
    Serial.println("KIRI");
}
void KANAN() {
    analogWrite(VelL, 250);
    analogWrite(VelR, 250);
    digitalWrite(EnL, LOW);
    digitalWrite(EnR, HIGH);
    Serial.println("KANAN");
}
void OPEN() {
    servo.write(pos-90);
    delay(5000);
    servo.write(pos+90);
}
