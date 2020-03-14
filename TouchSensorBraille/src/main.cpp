#include <Arduino.h>

static volatile uint64_t timeSeconds = 4;
String letter;

const int touch_pin_13 = 13;
const int touch_pin_12 = 12;
const int touch_pin_14 = 14;
const int touch_pin_27 = 27;
String finger1, finger2, finger3;
static volatile uint8_t touch_count1, touch_count2, touch_count3; 
static volatile uint64_t limit = 500;
int reading1, reading2, reading3, reading4;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
static volatile bool startTimer = false;
//static volatile bool limit_consecutive_trigger = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(touch_pin_13, INPUT);
  pinMode(touch_pin_12, INPUT);
  pinMode(touch_pin_14, INPUT);
  pinMode(touch_pin_27, INPUT);
  Serial.begin(9600);
}

void IRAM_ATTR detect_touch() {
  Serial.println("TOUCH DETECTED!!!");
  startTimer = true;
  lastTrigger = millis();
  touch_count1 = 0;
  touch_count2 = 0;
  touch_count3 = 0;
  //limit_consecutive_trigger = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  reading4 = touchRead(touch_pin_27);
  Serial.println(reading4);
  touchAttachInterrupt(touch_pin_27,detect_touch, 20);
  // Current time
  now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("Touch stopped...");
    startTimer = false;
    //limit_consecutive_trigger = false;
  }
  if(startTimer && (now - lastTrigger < (timeSeconds*1000))){
    reading1 = touchRead(touch_pin_13);
    reading2 = touchRead(touch_pin_12);
    reading3 = touchRead(touch_pin_14);
    Serial.print("Reading1 : ");
    Serial.println(reading1);
    Serial.print("Reading2 : ");
    Serial.println(reading2);
    Serial.print("Reading3 : ");
    Serial.println(reading3);
    if(reading1 < 30){
      touch_count1 = touch_count1 + 1;
      Serial.print("touch_count1: ");
      Serial.println(touch_count1);
    }
    if(reading2 < 30){
      touch_count2 = touch_count2 + 1;
    }
    if(reading3 < 30){
      touch_count3 = touch_count3 + 1;
    }
    if(touch_count1 > 0){
      finger1 = "1";
    }
    else{
      finger1 = "0";
    }
    if(touch_count2 > 0){
      finger2 = "1";
    }
    else{
      finger2 = "0";
    }
    if(touch_count3 > 0){
      finger3 = "1";
    }
    else{
      finger3 = "0";
    }
    letter = finger1 + finger2 + finger3;
  }
  Serial.print("Letter is: ");
  Serial.println(letter);
  delay(1000);
}