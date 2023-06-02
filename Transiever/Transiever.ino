#include <SPI.h>
#include <RF24.h>
//TODO Sende analoge daten für joystick
RF24 radio(9, 10); // (CE, CSN)
const byte address[6] = "1RF24";
struct dataStruct {
    int Xposition;
    int Yposition;

} myData;
void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(125);
  radio.openWritingPipe(address);
  radio.stopListening();
  // Serial.begin(9600);

}

void loop() {
  //  Serial.println(radio.isChipConnected());

  myData.Xposition = analogRead(0);
  myData.Yposition = analogRead(1);
  radio.write(&myData, sizeof(myData), 1);
  delay(10);
}

