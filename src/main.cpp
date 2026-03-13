#include <Arduino.h>
#include <LiquidCrystal.h>

#define LED 3
#define RPM A8
#define DRIVER_VCC 11
#define MOTOR_VCC 9

int calculateRPM(int);

int IR_FREQ = 600;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(RPM, INPUT_PULLUP);
  pinMode(DRIVER_VCC, OUTPUT);
  pinMode(MOTOR_VCC, OUTPUT);
  digitalWrite(DRIVER_VCC, LOW);



  delay(3000);

  digitalWrite(LED, HIGH);
  digitalWrite(DRIVER_VCC, HIGH);
  digitalWrite(MOTOR_VCC, HIGH);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  attachInterrupt(digitalPinToInterrupt(RPM), calculateRPM(IR_FREQ), HIGH);
}

int calculateRPM(int f)
{
  Serial.println(f);
}