#include <dht.h>

#include <LiquidCrystal.h>

#define CONTRAST 80
#define INTERVAL 5000


dht DHT;
#define SOUND 9
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);   //set Uno pins that are

void setup() {
  analogWrite(6, CONTRAST);
  lcd.begin(16,2);
  pinMode(SOUND,OUTPUT);

  Serial.begin(9600);


}

void DisplayTemp(double temp, double hum){
  lcd.setCursor(4,0);
  lcd.print("Omega 3");

  lcd.setCursor(0,1);

  lcd.print("Tem:");
  lcd.print(int(temp));

  lcd.write(0xdf);
  lcd.print("C");
  lcd.setCursor(9,1);

  lcd.print("Hum:");
  lcd.print(int(hum));
  lcd.print("%");

}

void DisplayExp(){
    lcd.setCursor(4,0);
    lcd.print("Omega 3");
    lcd.setCursor(0,1);
    lcd.print("Exp: 13/02/2023");
}

void DisplayTimeLeft(double DisplayHours, double DisplayTime){
    lcd.setCursor(4,0);
    lcd.print("Omega 3");
    lcd.setCursor(0,1);
    lcd.print("Time:");
    lcd.setCursor(6,1);
    lcd.print((int)DisplayHours);
    lcd.print("hr");
    lcd.setCursor(9,1);
    lcd.print(":");
    lcd.setCursor(10,1);
    lcd.print((int)DisplayTime);
    lcd.setCursor(12,1);
    lcd.print("min");
}

double temp;
double hum;
double timeleft = 1;

int temp_limit;

unsigned long intialTime = 0;
unsigned long intialCountDown = 0;

void loop() {

  int state = 0;
  unsigned long finalTime = millis();
  unsigned long finalCountDown = millis();
  unsigned long TimeDiff = 0;
  unsigned long TimeLeft = (timeleft+1) * 60 *1000;
  double DisplayTime = 0;
  double DisplayHours = 0;

  Serial.print("finalTime: ");
  Serial.println(finalTime);

  int ReadTemp= DHT.read11(7);
  temp = DHT.temperature;
  hum = DHT.humidity;

  DisplayTemp(temp,hum);

  delay(500);


  if(finalTime - intialTime >= INTERVAL){

    lcd.clear();

    DisplayExp();

    delay(5000);
    finalTime = millis();
    lcd.clear();
    intialTime = finalTime;

    finalCountDown = millis();
    TimeDiff = finalCountDown - intialCountDown;
    TimeLeft -= TimeDiff;
    DisplayTime = TimeLeft/(60);
    DisplayTime = DisplayTime/1000;

    if (DisplayTime >= 60){
      DisplayHours = DisplayTime/60;
      DisplayTime = DisplayHours - (int)DisplayHours;
      DisplayTime = DisplayTime * 100;
      DisplayTime = map(DisplayTime, 1, 100, 0 , 60);

    }

    lcd.clear();

    DisplayTimeLeft(DisplayHours,DisplayTime);

    delay(5000);
    finalTime = millis();
    lcd.clear();
    intialTime = finalTime;
  }

  if (TimeLeft<=0){
    tone(SOUND, 10);
    digitalWrite(SOUND,HIGH);
    delay(500);
    digitalWrite(SOUND,LOW);
  }
}