#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define micIn A0
#define touchIn 2
#define TIMER_DURATION 10000  // Set timer to 10 seconds (10000 ms)


unsigned long startTime = 0;
bool timerRunning = false;

unsigned long previousMillis = 0;
int countBlink = 0;

long micVal = 0;
int touchVal = 0;
int touchCount = 0;
int searchCount = 6;

long sum = 0 ; // Store the total value of n measurements
long level = 0 ; // Store the average value
int soundlow = 40;
int soundmedium = 500;
int num_Measure = 128 ; // Set the number of measurements


// Adjustable
int ref_eye_height = 40;
int ref_eye_width = 40;
int ref_space_between_eye = 10;
int ref_corner_radius = 10;

//current state of the eyes
int left_eye_height = ref_eye_height;
int left_eye_width = ref_eye_width;
int left_eye_x = 32;
int left_eye_y = 32;
int right_eye_x = 32 + ref_eye_width + ref_space_between_eye;
int right_eye_y = 32;
int right_eye_height = ref_eye_height;
int right_eye_width = ref_eye_width;

int dir_x = 0;
int dir_y = 0;
int count = 0;

void draw_eyes(bool update = true);
void center_eyes(bool update = true);
void blink(int speed = 12);
void sleep();
void wakeup();
void happy_eye();
void tinkle_eye();
void pat_eye();
void saccade(int direction_x, int direction_y);
void move_right_big_eye();
void move_left_big_eye();
void move_big_eye(int direction);

int timeD = 1000;


void draw_eyes(bool update = true) {
  display.clearDisplay();
  //draw from center
  int x = int(left_eye_x - left_eye_width / 2);
  int y = int(left_eye_y - left_eye_height / 2);
  display.fillRoundRect(x, y, left_eye_width, left_eye_height, ref_corner_radius, SSD1306_WHITE);
  x = int(right_eye_x - right_eye_width / 2);
  y = int(right_eye_y - right_eye_height / 2);
  display.fillRoundRect(x, y, right_eye_width, right_eye_height, ref_corner_radius, SSD1306_WHITE);
  if (update) {
    display.display();
  }
}


void center_eyes(bool update = true) {
  //move eyes to the center of the display, defined by SCREEN_WIDTH, SCREEN_HEIGHT
  left_eye_height = ref_eye_height;
  left_eye_width = ref_eye_width;
  right_eye_height = ref_eye_height;
  right_eye_width = ref_eye_width;

  left_eye_x = SCREEN_WIDTH / 2 - ref_eye_width / 2 - ref_space_between_eye / 2;
  left_eye_y = SCREEN_HEIGHT / 2;
  right_eye_x = SCREEN_WIDTH / 2 + ref_eye_width / 2 + ref_space_between_eye / 2;
  right_eye_y = SCREEN_HEIGHT / 2;

  draw_eyes(update);
}

void blink(int speed = 12) {
  draw_eyes();


  for (int i = 0; i < 3; i++) {
    left_eye_height = left_eye_height - speed;
    right_eye_height = right_eye_height - speed;
    draw_eyes();
    delay(1);
  }
  for (int i = 0; i < 3; i++) {
    left_eye_height = left_eye_height + speed;
    right_eye_height = right_eye_height + speed;

    draw_eyes();
    delay(1);
  }
}

void sleep() {  // DRAWS A LINE TO LOOK LIKE SLEEPING
  left_eye_height = 2;
  right_eye_height = 2;
  draw_eyes(true);
}

void wakeup() {  // WAKE UP THE EYES FROM AN LINE TO ROUND CORNERED SQUARE

  sleep();

  for (int h = 0; h <= ref_eye_height; h += 2) {
    left_eye_height = h;
    right_eye_height = h;
    draw_eyes(true);
  }
}

void happy_eye() {
  center_eyes(false);
  //draw inverted triangle over eye lower part
  int offset = ref_eye_height / 2;
  for (int i = 0; i < 10; i++) {
    display.fillTriangle(left_eye_x - left_eye_width / 2 - 1, left_eye_y + offset, left_eye_x + left_eye_width / 2 + 1, left_eye_y + 5 + offset, left_eye_x - left_eye_width / 2 - 1, left_eye_y + left_eye_height + offset, SSD1306_BLACK);
    // display.fillRect(left_eye_x-left_eye_width/2-1, left_eye_y+5, left_eye_width+1, 20,SSD1306_BLACK);

    display.fillTriangle(right_eye_x + right_eye_width / 2 + 1, right_eye_y + offset, right_eye_x - left_eye_width / 2 - 1, right_eye_y + 5 + offset, right_eye_x + right_eye_width / 2 + 1, right_eye_y + right_eye_height + offset, SSD1306_BLACK);
    // display.fillRect(right_eye_x-right_eye_width/2-1, right_eye_y+5, right_eye_width+1, 20,SSD1306_BLACK);
    offset -= 2;
    display.display();
    delay(1);
  }


  display.display();
  delay(1000);
}


void tinkle_eye() {
  center_eyes(false);
  //draw inverted triangle over eye lower part
  int offset = ref_eye_height / 2;
  for (int i = 0; i < 10; i++) {
    //    display.fillTriangle(left_eye_x - left_eye_width / 2 - 1, left_eye_y + offset, left_eye_x + left_eye_width / 2 + 1, left_eye_y + 5 + offset, left_eye_x - left_eye_width / 2 - 1, left_eye_y + left_eye_height + offset, SSD1306_BLACK);
    //     display.fillRect(left_eye_x-left_eye_width/2-1, left_eye_y+5, left_eye_width+1, 20,SSD1306_BLACK);

    //    display.fillTriangle(right_eye_x + right_eye_width / 2 + 1, right_eye_y + offset, right_eye_x - left_eye_width / 2 - 1, right_eye_y + 5 + offset, right_eye_x + right_eye_width / 2 + 1, right_eye_y + right_eye_height + offset, SSD1306_BLACK);
    display.fillRect(right_eye_x - right_eye_width / 2 - 1, right_eye_y + 5, right_eye_width + 1, 20, SSD1306_BLACK);
    offset -= 2;
    display.display();
//    delay(1);
  }


  display.display();
  delay(1000);
}

void saccade(int direction_x, int direction_y) {
  //quick movement of the eye, no size change. stay at position after movement, will not move back,  call again with opposite direction
  //direction == -1 :  move left
  //direction == 1 :  move right

  int direction_x_movement_amplitude = 8;
  int direction_y_movement_amplitude = 6;
  int blink_amplitude = 8;

  for (int i = 0; i < 1; i++) {
    left_eye_x += direction_x_movement_amplitude * direction_x;
    right_eye_x += direction_x_movement_amplitude * direction_x;
    left_eye_y += direction_y_movement_amplitude * direction_y;
    right_eye_y += direction_y_movement_amplitude * direction_y;

    right_eye_height -= blink_amplitude;
    left_eye_height -= blink_amplitude;
    draw_eyes();
    delay(1);
  }

  for (int i = 0; i < 1; i++) {
    left_eye_x += direction_x_movement_amplitude * direction_x;
    right_eye_x += direction_x_movement_amplitude * direction_x;
    left_eye_y += direction_y_movement_amplitude * direction_y;
    right_eye_y += direction_y_movement_amplitude * direction_y;

    right_eye_height += blink_amplitude;
    left_eye_height += blink_amplitude;

    draw_eyes();
    delay(1);
  }
}

void move_right_big_eye() {
  move_big_eye(1);
}

void move_left_big_eye() {
  move_big_eye(-1);
}

void move_big_eye(int direction) {  // MOVES TO RIGHT OR LEFT DEPENDING ON 1 OR -1 INPUT.
  //direction == -1 :  move left
  //direction == 1 :  move right

  int direction_oversize = 1;
  int direction_movement_amplitude = 2;
  int blink_amplitude = 5;

  for (int i = 0; i < 3; i++) {
    left_eye_x += direction_movement_amplitude * direction;
    right_eye_x += direction_movement_amplitude * direction;
    right_eye_height -= blink_amplitude;
    left_eye_height -= blink_amplitude;
    if (direction > 0) {
      right_eye_height += direction_oversize;
      right_eye_width += direction_oversize;
    } else {
      left_eye_height += direction_oversize;
      left_eye_width += direction_oversize;
    }

    draw_eyes();
    delay(1);
  }
  for (int i = 0; i < 3; i++) {
    left_eye_x += direction_movement_amplitude * direction;
    right_eye_x += direction_movement_amplitude * direction;
    right_eye_height += blink_amplitude;
    left_eye_height += blink_amplitude;
    if (direction > 0) {
      right_eye_height += direction_oversize;
      right_eye_width += direction_oversize;
    } else {
      left_eye_height += direction_oversize;
      left_eye_width += direction_oversize;
    }
    draw_eyes();
    delay(1);
  }

  delay(1000);

  for (int i = 0; i < 3; i++) {
    left_eye_x -= direction_movement_amplitude * direction;
    right_eye_x -= direction_movement_amplitude * direction;
    right_eye_height -= blink_amplitude;
    left_eye_height -= blink_amplitude;
    if (direction > 0) {
      right_eye_height -= direction_oversize;
      right_eye_width -= direction_oversize;
    } else {
      left_eye_height -= direction_oversize;
      left_eye_width -= direction_oversize;
    }
    draw_eyes();
    delay(1);
  }
  for (int i = 0; i < 3; i++) {
    left_eye_x -= direction_movement_amplitude * direction;
    right_eye_x -= direction_movement_amplitude * direction;
    right_eye_height += blink_amplitude;
    left_eye_height += blink_amplitude;
    if (direction > 0) {
      right_eye_height -= direction_oversize;
      right_eye_width -= direction_oversize;
    } else {
      left_eye_height -= direction_oversize;
      left_eye_width -= direction_oversize;
    }
    draw_eyes();
    delay(1);
  }


  center_eyes();
}

void pat_eye() {
  left_eye_height = 2;
//  right_eye_height = 2;
  draw_eyes(true);
}

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }


  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner

  display.println(F("Git: MullaiR-19"));
  display.println(F("  "));
  display.println(F("MullaiDIYprojects"));
  display.println(F("  "));
  display.setCursor(40, 40);
  display.setTextSize(2);
  display.println(F("HIB"));
  display.display();
  delay(3000);
  display.clearDisplay();

  sleep();
  display.display();
  delay(1000);
  wakeup();


  pinMode(micIn, INPUT);
  pinMode(touchIn, INPUT);

  startTime = millis();
  timerRunning = true;

  blink(10);
}

void allMotion(){
   Serial.println("All Motion!");
    // BOTTOM LEFT
    dir_x = -1;
    dir_y = 1;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);

    // BOTTOM
    dir_x = 0;
    dir_y = 1;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);

    // BOTTOM RIGHT
    dir_x = 1;
    dir_y = 1;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);

    // RIGHT
    dir_x = 1;
    dir_y = 0;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);

    // TOP RIGHT
    dir_x = 1;
    dir_y = -1;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);

    // TOP
    dir_x = 0;
    dir_y = -1;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);

    // TOP LEFT
    dir_x = -1;
    dir_y = -1;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);

    // LEFT
    dir_x = -1;
    dir_y = 0;
    saccade(dir_x, dir_y);
    delay(300);
    saccade(-dir_x, -dir_y);
    delay(300);
}

void loop() {

  micVal  = analogRead(micIn);
  touchVal = digitalRead(touchIn);
  //  Serial.print("Mic Value: ");
  //  Serial.println(micVal);
  //  Serial.print("Touch Value: ");
  //  Serial.println(touchVal);
  //  Serial.println("");
  delay(100);

  if (micVal > 1000) {
   allMotion();
  }

  if (touchVal == 1) {
    touchCount += 1;
    
    if (touchCount == 7) {
      happy_eye();
      Serial.println("Happy Eye!");
      delay(1000);
      center_eyes(true);
      touchCount = 0;
      startTime = millis();
      timerRunning = true;
    }

  }

  int BLINK_DURATION = random(2500, 3500); // Set timer to 2-3 seconds
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= BLINK_DURATION) {
    previousMillis = currentMillis; // Update time
    blink(10);
    countBlink+=1;
    if(countBlink == searchCount){
      searchCount = random(5,11);
      move_right_big_eye();
      delay(50);
      move_left_big_eye();
      delay(50);
      countBlink=0;
    }
  }

  sum = 0 ; // Reset the sum of the measurement values
}
