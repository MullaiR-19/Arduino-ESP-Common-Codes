const int trigPin1 = 12;//front
const int echoPin1 = 11;
const int trigPin2 = 10; //left
const int echoPin2 = 9;
const int trigPin3 = 8;//right
const int echoPin3 = 7;
const int in1 = 2;
const int in2 = 4;
const int in3 = 6;
const int in4 = 13;
const int en1 = 3;
const int en2 = 5;

#define DIS 10

//#define SPEED 100

void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode (en1, OUTPUT);
  pinMode (en2, OUTPUT);
  Serial.begin(9600);

  analogWrite(en1, 80);
  analogWrite(en2, 100);

}
void loop() {

  if (FrontSensor() > DIS && RightSensor() > DIS && LeftSensor() > DIS) {
    analogWrite(en1, 80);
    analogWrite(en2, 100);
    forward();
  }
  else if (FrontSensor() < DIS && RightSensor() > DIS && LeftSensor() > DIS) {
    stop();
    analogWrite(en1, 80);
    analogWrite(en2, 100);
    if (RightSensor() > LeftSensor()) {
      turn_right();
      delay(500);
    }
    if (RightSensor() < LeftSensor()) {
      turn_left();
      delay(500);
    }
  }
  else if (FrontSensor() > DIS && RightSensor() > DIS && LeftSensor() < DIS) {
//    stop();
    analogWrite(en1, 70);
    analogWrite(en2, 70);
  }
  else if (FrontSensor() > DIS && RightSensor() < DIS && LeftSensor() > DIS) {
//    stop();
    analogWrite(en1, 60);
    analogWrite(en2, 100);
  }

  else if (FrontSensor() == 0 || RightSensor() == 0 || LeftSensor() == 0) {
    stop();
  }

}
void forward () {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void turn_left () {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}
void turn_right () {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}
void reverse () {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

long FrontSensor () {
  long dur;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin1, LOW);
  dur = pulseIn(echoPin1, HIGH);
  Serial.print("Front: ");
  Serial.println(dur / 58);
  return (dur / 58); // convert the distance to centimeters.
}
long RightSensor () {
  long dur;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin2, LOW);
  dur = pulseIn(echoPin2, HIGH);
  Serial.print("RIGHT: ");
  Serial.println(dur / 58);
  return (dur / 58); // convert the distance to centimeters.
}
long LeftSensor () {
  long dur;
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin3, LOW);
  dur = pulseIn(echoPin3, HIGH);
  Serial.print("Left: ");
  Serial.println(dur / 58);
  return (dur / 58); // convert the distance to centimeters.
}
