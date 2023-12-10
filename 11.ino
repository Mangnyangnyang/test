#include <Servo.h>

const int lightSensorPin = A0; // 조도 센서가 연결된 아날로그 핀 (예: A0)
const int servoPin = 9; // 서보모터가 연결된 디지털 핀 (예: 9)

Servo myServo;
bool isServoActive = false; 
unsigned long servoStartTime = 0; 
const int servoDuration = 1000; 

void setup() {
  pinMode(lightSensorPin, INPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(lightSensorPin);

  if (lightValue < 200) {
    if (!isServoActive) {
      rotateServo();
    }
  } else {
    if (isServoActive) {
      stopServo();
    }
  }

  if (Serial.available() > 0) {
    int command = Serial.parseInt();
    if (command == 1) {
      rotateServo();
    } else if (command == 2) {
      stopServo();
    }
  }

  Serial.print("Light Value: ");
  Serial.println(lightValue);

  delay(1000);
}

void rotateServo() {
  myServo.write(1800);
  isServoActive = true;
  servoStartTime = millis(); 
  Serial.println("Servo rotated!");
}

void stopServo() {
  myServo.write(1500);
  isServoActive = false;
  Serial.println("Servo stopped!");
}
