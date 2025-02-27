int sensorVal = 0;

void setup() {
  pinMode(3, OUTPUT);

}

void loop() {

  sensorVal = analogRead(A0);
  analogWrite(3,map(sensorVal,0,1023,0,255));

}
