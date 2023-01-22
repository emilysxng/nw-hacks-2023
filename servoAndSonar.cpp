#include <Servo.h>

const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 11; // Echo Pin of Ultrasonic Sensor
const int Time = 1;

Servo wiggly;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
  wiggly.attach(9);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

unsigned long previousTime = 0;
int state = 0;
unsigned long long INTERVAL = (long) Time*60*1000;


void loop() {

   long duration, inches, cm;
   unsigned long currentTime = millis();

   while(state == 0){
     digitalWrite(pingPin, LOW);
     delayMicroseconds(2);
     digitalWrite(pingPin, HIGH);
     delayMicroseconds(2);
     digitalWrite(pingPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     inches = (double)microsecondsToInches(duration);
     cm = (double)microsecondsToCentimeters(duration);
     Serial.print(inches);
     Serial.print("in, ");
     Serial.print(cm);
     Serial.print("cm");
     Serial.println();
     delay(100);

     if((double)cm>3.5){
      wiggly.write(300);
      delay(80);
      wiggly.write(900);
      delay(50);
     }
     if((double)cm<=3.5){
       state = 1;
       currentTime = millis();
       previousTime = currentTime;
     }
   }

  currentTime = millis();


  if(currentTime - previousTime >= INTERVAL){
    state = 1;
  }

}

double microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

double microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
