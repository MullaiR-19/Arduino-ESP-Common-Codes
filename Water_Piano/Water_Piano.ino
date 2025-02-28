/*
Copyright(c)- Bhaskar Tripathi
Note - Being a part time flute player, I have tried to write the notes as close as possible but it is still not very refined. 
You may try to experiment more with the notes array to futher refine it.
*/
int speakerPin = 3;  //buzzer is connected to Pin 11 of the Board.

int tempo = 200;  //set tempo

void playTone(int tone, int duration) {  //created a square wave for given time duration
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {  //Assigning high time for the notes
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 956, 851, 758, 716, 638, 568, 1014, 478 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);  // pin 7 as an OutPut Pin
}

void loop() {  //Main function

  if (analogRead(A0) < 1000) {
    playNote('C', 500);  //play the corresponding note for the corresponding beat
    // delay(1000);
  }
  if (analogRead(A1) < 1000) {
    playNote('g', 500);  //play the corresponding note for the corresponding beat
    // delay(1000);
  }
  if (analogRead(A2) < 1000) {
    playNote('b', 500);  //play the corresponding note for the corresponding beat
    delay(1000);
  }
}