#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>

#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8); // (CE, CSN)

const byte address[6] = "1RF24";

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
    Serial.println("aaa");
    char text[2] = {0};
    radio.read(&text, sizeof(text) - 1);
    String code = String(text); // Array -> Zeichen ("code")
    if (code == "w") {
      digitalWrite(3, 1);
      digitalWrite(2, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(A3, 1);
      digitalWrite(A2, 0);
      digitalWrite(A4, 0);
      digitalWrite(A5, 1);
    }

    if (code == "s") {
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(5, 0);
      digitalWrite(4, 1);
      digitalWrite(A2, 1);
      digitalWrite(A3, 0);
      digitalWrite(A5, 0);
      digitalWrite(A4, 1);
    }

    Serial.println(code);

    if (code == "d") {
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
    }

    if (code == "a") {
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
    }
  }

  else {
    delay(30);
    if (!radio.available()) {
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
