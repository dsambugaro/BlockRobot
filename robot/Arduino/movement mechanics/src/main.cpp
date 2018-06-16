#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04
#define NUMBER_COMMANDS 12

bool hasData = false;
bool running = false;
byte interruptPin = 2;
int commandsReceived[NUMBER_COMMANDS];
int commandsBuffer[5][NUMBER_COMMANDS] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int commandsRunning[NUMBER_COMMANDS];
int byteReading = 0;

void stopAll() {
  for (size_t i = 0; i < NUMBER_COMMANDS; i++) {
    commandsReceived[i] = 0;
    commandsRunning[i] = 0;
    for (size_t j = 0; j < 5; j++) {
      commandsBuffer[j][i] = 0;
    }
  }
}

void statusInformation() {
  if (running) {
    Wire.write(1);
  } else {
    Wire.write(0);
  }
}

void receiveData() {
  if (byteReading >= NUMBER_COMMANDS) {
    byteReading = 0;
  }
  while(Wire.available()) {
    commandsReceived[byteReading] = Wire.read();
    byteReading++;
  }
  if (byteReading == NUMBER_COMMANDS) {
    hasData = true;
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Wire.onReceive(receiveData);
  Wire.onRequest(statusInformation);
  attachInterrupt(digitalPinToInterrupt(interruptPin), stopAll, RISING);
  pinMode(interruptPin, INPUT_PULLUP);
}

void loop() {

  if (hasData && !running) {
    for (int i = 0; i < NUMBER_COMMANDS; i++) {
      Serial.print(commandsReceived[i]);
      Serial.print(" ");
      delay(500);
    }
  }

  if (hasData) {
    digitalWrite(13, HIGH);

    digitalWrite(13, LOW);
  }
  delay(100);
}
