#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>

#include <SPI.h>
#include <RF24.h>
//TODO Füge alle möglichen bewegungen hinzu
//TODO Mache es möglich Motoren geschwindigkeit mit analog zu kontolieren
RF24 radio(7, 8); // (CE, CSN)

const byte address[6] = "1RF24";
struct dataStruct {
    int Xposition;
    int Yposition;
} myData;
void setup() {
  // Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(125);
  radio.openReadingPipe(0, address);
  radio.startListening();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

}

void loop() {

  if (radio.available()) {
    radio.read( &myData, sizeof(myData) );
    if (myData.Yposition >= 500) {
      digitalWrite(3, 1);
      digitalWrite(2, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(A3, 1);
      digitalWrite(A2, 0);
      digitalWrite(A4, 0);
      digitalWrite(A5, 1);
    }

    if (myData.Yposition <= 100) {
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(5, 0);
      digitalWrite(4, 1);
      digitalWrite(A2, 1);
      digitalWrite(A3, 0);
      digitalWrite(A5, 0);
      digitalWrite(A4, 1);
    }
  else {
    delay(30);
    if (myData.Yposition>100 && myData.Yposition<500) {
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(A3, 0);
      digitalWrite(A2, 0);
      digitalWrite(A4, 0);
      digitalWrite(A5, 0);
    }
  }
  delay(10);
}
}
