#include "BluetoothSerial.h" 
//Install Library Bluetooth di Arduino IDE => BluetoothSerial by Henry Abrahamsen

// init Class:
BluetoothSerial ESP_BT;
unsigned long previousMillis = 0; // Waktu terakhir LED diperbarui
const long interval = 1000;       // Interval untuk berkedip (ms)
int pinPos1 = 17; // Hubungkan posisi 1 ke pin 5
int pinPos2 = 5; // Hubungkan posisi 2 ke pin 34
int pinPos3 = 19; // Hubungkan posisi 3 ke pin 19
int pinPos4 = 21; // Hubungkan posisi 4 ke pin 21
int pinPos5 = 4; // Hubungkan posisi 5 ke pin 4
int pinPos6 = 16; // Hubungkan posisi 6 ke pin 17
int pinMotor1 = 12;
int pinMotor2 = 13;
int pwm = 0;
int incoming;
int rotary;
bool isBluetoothConnected = false; // Status koneksi Bluetooth

void setup() {
  ESP_BT.begin("ESP32_Control");
  Serial.begin(115200);

  // Inisialisasi pin
  pinMode(pinPos1, INPUT_PULLUP);
  pinMode(pinPos2, INPUT_PULLUP);
  pinMode(pinPos3, INPUT_PULLUP);
  pinMode(pinPos4, INPUT_PULLUP);
  pinMode(pinPos5, INPUT_PULLUP);
  pinMode(pinPos6, INPUT_PULLUP);
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
}

void loop() {
  // Periksa status koneksi Bluetooth
  bool currentConnectionStatus = ESP_BT.connected();
  if (currentConnectionStatus != isBluetoothConnected) {
    isBluetoothConnected = currentConnectionStatus;

    if (isBluetoothConnected) {
      Serial.println("Bluetooth connected!");
      // Tambahkan aksi saat Bluetooth terhubung
    } else {
      Serial.println("Bluetooth disconnected!");
      // Reset PWM jika Bluetooth terputus
      pwm = 0;
      analogWrite(pinMotor1, pwm);
      analogWrite(pinMotor2, pwm);
    }
  }

  // Jika Bluetooth terhubung, baca input dari Bluetooth
  if (isBluetoothConnected) {
    if (ESP_BT.available()){
    incoming = ESP_BT.read();
    switch (incoming) {
      case 3: pwm = 60; break;
      case 4: pwm = 100; break;
      case 5: pwm = 150; break;
      case 6: pwm = 200; break;
      case 7: pwm = 250; break;
      case 2: pwm = 0; break;
    }
    analogWrite(pinMotor1, pwm);
    analogWrite(pinMotor2, pwm);
    Serial.print("Bluetooth input: ");
    Serial.println(pwm);}
  }

  // Jika Bluetooth tidak terhubung, baca input dari rotary switch
  if (!isBluetoothConnected) {
    if (digitalRead(pinPos1) == LOW){ rotary = 1;}
    else if (digitalRead(pinPos2) == LOW) { rotary = 2;}
    else if (digitalRead(pinPos3) == LOW) { rotary = 3;}
    else if (digitalRead(pinPos4) == LOW) { rotary = 4;}
    else if (digitalRead(pinPos5) == LOW) { rotary = 5;}
    else if (digitalRead(pinPos6) == LOW) { rotary = 6;}

    switch (rotary) {
      case 1: pwm = 0; break;
      case 2: pwm = 60; break;
      case 3: pwm = 100; break;
      case 4: pwm = 150; break;
      case 5: pwm = 200; break;
      case 6: pwm = 250; break;
    }    
    //Serial.print("\t");
    Serial.print(digitalRead(pinPos1));
    Serial.print("\t");
    Serial.print(digitalRead(pinPos2));
    Serial.print("\t");
    Serial.print(digitalRead(pinPos3));
    Serial.print("\t");
    Serial.print(digitalRead(pinPos4));
    Serial.print("\t");
    Serial.print(digitalRead(pinPos5));
    Serial.print("\t");
    Serial.print(digitalRead(pinPos6));
    analogWrite(pinMotor1, pwm);
    analogWrite(pinMotor2, pwm);
    Serial.print("\tRotary input: ");
    Serial.println(rotary);
  }
}
