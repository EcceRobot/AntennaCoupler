#include <Servo.h>

Servo SRV1;  // create servo object to control a servo
Servo SRV2;  // create servo object to control a servo
const int SensorPin = A0;
const int LEDPin = 0;
int Data = 0;
int bestData = 0;
int SRV1_pos = 0;
int best_SRV1_pos = 0;
int SRV2_pos = 0;
int best_SRV2_pos = 0;
//int SRV1_delay_1 = ;
//int SRV1_delay_1 = 100;


void setup() {
  SRV1.attach(10);
  SRV2.attach(11);
  pinMode (SensorPin, INPUT);
  pinMode (LEDPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(LEDPin, HIGH);

  //*******************prima scansione grossolana

  for (SRV2_pos = 30; SRV2_pos <= 180; SRV2_pos += 10) {
    SRV2.write(SRV2_pos);


    for (SRV1_pos = 30; SRV1_pos <= 180; SRV1_pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      SRV1.write(SRV1_pos);              // tell servo to go to position in variable 'pos'
      delay(5);
      Data = 1023 - analogRead(SensorPin);
      if (Data > bestData) {
        bestData = Data;
        best_SRV1_pos = SRV1_pos;
        best_SRV2_pos = SRV2_pos;
      }
    }
    for (SRV1_pos = 180; SRV1_pos >= 30; SRV1_pos -= 1) { // goes from 180 degrees to 0 degrees
      SRV1.write(SRV1_pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
      Data = 1023 - analogRead(SensorPin);
      if (Data > bestData) {
        bestData = Data;
        best_SRV1_pos = SRV1_pos;
      }
    }

  }

  ////*******************seconda scansione, più fine

  int temp_best_SRV1_pos = best_SRV1_pos;
  int temp_best_SRV2_pos = best_SRV2_pos;
  

  for (SRV2_pos = temp_best_SRV2_pos-5; SRV2_pos <= temp_best_SRV2_pos+5; SRV2_pos += 1) {
    SRV2.write(SRV2_pos);


    for (SRV1_pos = temp_best_SRV1_pos-10; SRV1_pos <= temp_best_SRV1_pos+10; SRV1_pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      SRV1.write(SRV1_pos);              // tell servo to go to position in variable 'pos'
      delay(20);
      Data = 1023 - analogRead(SensorPin);
      if (Data > bestData) {
        bestData = Data;
        best_SRV1_pos = SRV1_pos;
        best_SRV2_pos = SRV2_pos;
      }
    }
    for (SRV1_pos = temp_best_SRV1_pos+5; SRV1_pos >= temp_best_SRV1_pos-5; SRV1_pos -= 1) { // goes from 180 degrees to 0 degrees
      SRV1.write(SRV1_pos);              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 15ms for the servo to reach the position
      Data = 1023 - analogRead(SensorPin);
      if (Data > bestData) {
        bestData = Data;
        best_SRV1_pos = SRV1_pos;
      }
    }

  }


    SRV1.write(best_SRV1_pos);
    SRV2.write(best_SRV2_pos);
    delay(4000);
    best_SRV1_pos = 0;
    best_SRV2_pos = 0;
    bestData = 0;

  }
