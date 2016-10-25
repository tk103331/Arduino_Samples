#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

int n = 1;
const int TrigPin = 2; 
const int EchoPin = 3; 
float cm; 
LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  Serial.begin(9600);
  lcd.begin (16,2); //  <<----- My LCD was 16x2
pinMode(TrigPin, OUTPUT); 
pinMode(EchoPin, INPUT); 
  
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home
 
  //lcd.print("SainSmartI2C16x2");
  lcd.setBacklight(HIGH);
}

void loop()
{
digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
delayMicroseconds(2); 
digitalWrite(TrigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigPin, LOW); 

cm = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
cm = (int(cm * 100.0)) / 100.0; //保留两位小数 
  
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("distance:");   
  lcd.setCursor (0,1);
  lcd.print(cm);  
  delay(500);
}


