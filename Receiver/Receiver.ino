#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>

#include <SPI.h>
#include <RF24.h>
//TODO Füge alle möglichen bewegungen hinzu
//TODO Mache es möglich Motoren geschwindigkeit mit analog zu kontolieren
RF24 radio(7, 8); // (CE, CSN)
int pwmx;
int pwmy;
const byte address[6] = "1RF24";
struct dataStruct {
    int Xposition;
    int Yposition;
} myData;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(50);
  radio.openReadingPipe(0, address);
  radio.startListening();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

}
int pwm(int x) {
  int out;
  if (x < 512) { //Check if joystick is above, below, or at the middle and calculate the unmapped output
    x = 512 - x;
  }
  if (x > 512) {
    x = x - 512;
  }
  if (x == 512) {
    x = 0;
  }
  out = map(x, 0, 1023, 100, 255); //Map the output to a PWM value
  Serial.println(x);
  return out; //Return the value
}
void loop() {

  if (radio.available()) {
    radio.read( &myData, sizeof(myData) );
    //Serial.print("Y Pos");
    //Serial.println(myData.Yposition);
    //Serial.print("X Pos");
    //Serial.println(myData.Xposition);
    pwmx=pwm(myData.Xposition);
    pwmy=pwm(myData.Yposition);
    if (myData.Yposition >= 700) {

      digitalWrite(3, 1);
      digitalWrite(2, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(A3, 1);
      digitalWrite(A2, 0);
      digitalWrite(A4, 0);
      digitalWrite(A5, 1);

      analogWrite(10,pwmy);
      analogWrite(11,pwmy);
    }

    if (myData.Yposition <= 200) {
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(5, 0);
      digitalWrite(4, 1);
      digitalWrite(A2, 1);
      digitalWrite(A3, 0);
      digitalWrite(A5, 0);
      digitalWrite(A4, 1);
      //Serial.println(pwmy);
      //analogWrite(10,pwmy);
      //analogWrite(11,pwmy);
    }
    if (myData.Xposition >= 700){
      digitalWrite(3, 1);
      digitalWrite(2, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(A3, 1);
      digitalWrite(A2, 0);
      digitalWrite(A4, 1);
      digitalWrite(A5, 0);
      analogWrite(10,pwmx);
      analogWrite(11,pwmx);
    }
    if (myData.Xposition <= 200){
      digitalWrite(3, 0);
      digitalWrite(2, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(A3, 0);
      digitalWrite(A2, 1);
      digitalWrite(A4, 0);
      digitalWrite(A5, 1);
      analogWrite(10,pwmx);
      analogWrite(11,pwmx);
    }

    if (myData.Yposition>200 && myData.Yposition<700 && myData.Xposition>200 && myData.Xposition<700) {
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

