#include <Servo.h>

#define MQ_PIN A0
#define RED_LED 11
#define GREEN_LED 12
#define CONTROLLER_SERVO 3

int GAS_VAL = 0;

Servo controllerServo;

void setup() {
  pinMode(MQ_PIN, INPUT);  // MQ-6 A0 Pin
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  controllerServo.attach(CONTROLLER_SERVO);
  controllerServo.write(10);

  Serial.print("   GAS SENSOR   ");
}

void loop() {
  GAS_VAL = analogRead(MQ_PIN);
  Serial.println(GAS_VAL);

  if (GAS_VAL > 600) {
    Serial.print("   LPG Detected   ");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    controllerServo.wirte(65);
  }

  else {
    Serial.print("   LPG Not Detected   ");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    controllerServo.wirte(10);
  }

  delay(10);
}

