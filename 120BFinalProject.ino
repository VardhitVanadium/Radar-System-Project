
#include <Servo.h>
#include "Timer.h"
const int trigPin = 10;
const int echoPin = 11;
const int redLEDPlusBuzzer = 8;
const int greenLED = 9;
long duration;
int distance;

Servo myServo;
bool objectDetected = false;
int servoPin = 12;
int x = 0;
//merely code for rotating servo and ultrasonic sensor and I will incorporate active buzzer and ultrasonic sensor readings after checkpoint 
enum ServoStates{ServoRight, ServoLeft} servoState = ServoRight;
void adjustServo(void) {
 switch(servoState) {
case ServoRight:
if(myServo.read() == 150) {// starts rotating Servo and ultrasonic sensor left when Servo is rotated all the way right(180 is maximum value)
servoState = ServoLeft;
}
break;

case ServoLeft:
if(myServo.read() == 25) {
servoState = ServoRight;
} //rotates Servo and ultrasonic sensor right when Servo is rotated all the way left(0 is minimum value)
break;
 }

 switch(servoState) {
case ServoRight:
  for(int i=25;i < 150;i++){  
  myServo.write(i);
  servoDelay();
  ultrasonic();
  }


case ServoLeft:
  for(int i=150;i>25;i--){  
  myServo.write(i);
  servoDelay();
  ultrasonic();
  }
}
}

void ultrasonic(){ 
    if (distance < 30){
    digitalWrite(greenLED, LOW);
    digitalWrite(redLEDPlusBuzzer, HIGH);
  }
  else{
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLEDPlusBuzzer, LOW);
  }
  digitalWrite(trigPin, LOW); 
  while(!TimerFlag){}
      TimerFlag=0;
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  trigPinDelay();
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
}

void servoDelay() {
  for (int i = 0; i < 15; i++) {
    while(!TimerFlag){}
      TimerFlag=0;
  }
}

void trigPinDelay() {
  for (int i = 0; i < 5; i++) {
     while(!TimerFlag){}
      TimerFlag=0;
  }
}

void setup() {
  // put your setup code here, to run once:
TimerOn();
TimerSet(2);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode (redLEDPlusBuzzer, OUTPUT);
pinMode (greenLED, OUTPUT);
Serial.begin(9600);
myServo.attach(servoPin);
}


void loop() {
  // put your main code here, to run repeatedly:
adjustServo();

}



