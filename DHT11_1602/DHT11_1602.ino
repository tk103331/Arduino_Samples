#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>

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
#define DHT11_PIN 4
LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
dht DHT;  
void setup()
{
  Serial.begin(9600);
  lcd.begin (16,2); //  <<----- My LCD was 16x2

  
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home

  //lcd.print("SainSmartI2C16x2");
  lcd.setBacklight(HIGH);
}

void loop()
{
 int chk = DHT.read11(DHT11_PIN);
 lcd.home();
  lcd.clear();
switch (chk)  
  {  
    case 0:  lcd.print("OK,\t"); break;  
    case -1: lcd.print("Checksum error,\t"); break;  
    case -2: lcd.print("Time out error,\t"); break;  
    default: lcd.print("Unknown error,\t"); break;  
  }  
 // DISPLAT DATA
 if(chk==0){
  lcd.setCursor (0,0);
  lcd.print(DHT.humidity);  
  lcd.setCursor (0,1);
  lcd.print(DHT.temperature);  
 }
  //lcd.setBacklight(LOW);      // Backlight off
  delay(200);
  //lcd.setBacklight(HIGH);     // Backlight on
  //delay(1000);
}
