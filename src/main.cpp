#include <Arduino.h>
#include <LiquidCrystal.h>

#define LED 3
#define RPM_INT 18 
#define IR_VCC 11
#define IR_FREQ 600
#define DRIVER_EN 2

#define LCD_EN 7
#define LCD_RST 6

void calculateRPM();

int avgRPM;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(RPM_INT, INPUT_PULLUP);
  pinMode(IR_VCC, OUTPUT);
  pinMode(DRIVER_EN, OUTPUT);

  delay(3000);

  digitalWrite(LED, HIGH);
  digitalWrite(IR_VCC, HIGH);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(DRIVER_EN, HIGH);
  attachInterrupt(digitalPinToInterrupt(RPM_INT), calculateRPM, HIGH);
}

void calculateRPM()
{
  int arr[IR_FREQ] = {};
  int count = 0;

  for(int i = 0; i < IR_FREQ; i++)
  {

    arr[i] = digitalRead(RPM_INT);

    if(arr[i] == 1)
    {
      count++;
    }
  }

  int avgRPM = count / IR_FREQ;
  Serial.println(avgRPM);

}