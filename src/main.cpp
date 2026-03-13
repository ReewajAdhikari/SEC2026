#include <Arduino.h>
#include <LiquidCrystal.h>

#define LED 3
#define FAIL_LED 4
#define RPM_INT 18 
#define IR_VCC 11
#define IR_FREQ 600
#define DRIVER_EN 2

#define LCD_EN 7
#define LCD_RST 6
#define D4 36
#define D5 37
#define D6 38
#define D7 39

void calculateRPM();

LiquidCrystal lcd(LCD_RST, LCD_EN, D4, D5, D6, D7);

volatile double avgRPM;
volatile unsigned int count = 0;
volatile unsigned int lastCount = 0;
volatile unsigned long lastMillis; 

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
  lcd.begin(16, 2);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(DRIVER_EN, HIGH);
  lastMillis = millis();
  attachInterrupt(digitalPinToInterrupt(RPM_INT), calculateRPM, CHANGE);

  if(avgRPM < (0.75 * 200))
  {
    digitalWrite(FAIL_LED, HIGH);
  }

  lcd.print(avgRPM);
  delay(500);
}

void calculateRPM()
{
  
  int arr[40] = {};

  lastCount = count;

  for(int i = 0; i < 40; i++)
  {

    arr[i] = digitalRead(RPM_INT);

    if(arr[i] == 1)
    {
      count++;
    }
  }

  unsigned long currentMillis = millis();
  unsigned long dt = currentMillis - lastMillis;


  int dCount = count - lastCount;
  avgRPM = 60 * (double) dCount / (double) dt; // this math makes no sense
}