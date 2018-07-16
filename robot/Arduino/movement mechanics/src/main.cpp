#include <Arduino.h>
#include <Wire.h>
#include<AFMotor.h>

#define SLAVE_ADDRESS 0x04
#define NUMBER_COMMANDS 4
#define A_IA 11
#define A_IB 10
#define B_IA 5
#define B_IB 6

bool hasData = false;
bool running = false;
byte interruptPin = 2;
int commandsReceived[NUMBER_COMMANDS];
int commandsRunning[NUMBER_COMMANDS] = {0,0,0,0};
int byteReading = 0;

AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);

void stopAll() {
  analogWrite(A_IA, 0);
  analogWrite(A_IB, 0);

  analogWrite(B_IA, 0);
  analogWrite(B_IB, 0);

  for (size_t i = 0; i < NUMBER_COMMANDS; i++) {
    commandsReceived[i] = 0;
    commandsRunning[i] = 0;
  }
  running = false;
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
  Wire.onReceive(receiveData);
  Wire.onRequest(statusInformation);
  // attachInterrupt(digitalPinToInterrupt(interruptPin), stopAll, RISING);
  // pinMode(interruptPin, INPUT_PULLUP);
  // pinMode(A_IA, OUTPUT);
  // pinMode(A_IB, OUTPUT);
  // pinMode(B_IA, OUTPUT);
  // pinMode(B_IB, OUTPUT);
  motor2.setSpeed(255);
  motor4.setSpeed(255);
}

void loop() {

  if (hasData && !running) {
    for (int i = 0; i < NUMBER_COMMANDS; i++) {
      commandsRunning[i] = commandsReceived[i];
      Serial.print(commandsReceived[i]);
      Serial.print(" ");
      commandsReceived[i] = 0;
    }
    hasData = false;
  }

  for (int i = 0; i < NUMBER_COMMANDS; i++) {
    running = true;
    if (commandsRunning[i] == 1) {
      // Esquerda
      // analogWrite(A_IA, 0);
      // analogWrite(A_IB, 0);

      // analogWrite(B_IA, 250);
      // analogWrite(B_IB, 0);
      motor2.run(FORWARD);
      motor4.run(BACKWARD);
      delay(2000);
    }
    if (commandsRunning[i] == 2) {
      // Direita
      // analogWrite(A_IA, 250);
      // analogWrite(A_IB, 0);
      //
      // analogWrite(B_IA, 0);
      // analogWrite(B_IB, 0);
      motor4.run(FORWARD);
      motor2.run(BACKWARD);
      delay(2000);
    }
    if (commandsRunning[i] == 3) {
      // Frente
      // analogWrite(A_IA, 250);
      // analogWrite(A_IB, 0);
      //
      // analogWrite(B_IA, 250);
      // analogWrite(B_IB, 0);
      motor2.run(FORWARD);
      motor4.run(FORWARD);
      delay(2000);
    }
    if (commandsRunning[i] == 4) {
      // Trás
      // analogWrite(A_IA, 0);
      // analogWrite(A_IB, 250);
      //
      // analogWrite(B_IA, 0);
      // analogWrite(B_IB, 250);
      motor4.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(2800);
    }

    commandsRunning[i] = 0;
    // analogWrite(A_IA, 0);
    // analogWrite(A_IB, 0);
    //
    // analogWrite(B_IA, 0);
    // analogWrite(B_IB, 0);
    // delay(2000);
    motor2.run(RELEASE);
    motor4.run(RELEASE);
    delay(1000);
  }
  running = false;
  // motor2.run(FORWARD);
  // motor4.run(FORWARD);
  // delay(500000);
}
