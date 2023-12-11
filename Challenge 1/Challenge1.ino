#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32,16,2);

void setup()
{
 Serial.begin(9600);
 pinMode(9,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 lcd.init();
 lcd.setCursor(0,0);
 lcd.backlight();
 lcd.display(); 
}
void loop()
{
  
  pumpFlow();
}

void pumpFlow(){
  int moistureRead = analogRead(A0);
  int ldrRead = analogRead(A3);
  
  Serial.print("Moisture:");
  Serial.println(moistureRead);
  Serial.print("Resistor:");
  Serial.println(ldrRead);
  
 
  if(ldrRead > 250 && moistureRead <300){
    digitalWrite(9,HIGH);
    digitalWrite(4,LOW);
    noTone(5);
    lcd.setCursor(3,0);
    lcd.print("Motor: ON");
    lcd.setCursor(0,1);
    lcd.print("LED & Buzzer:OFF");
  }
  
 
  else if(ldrRead <250){
    digitalWrite(9,LOW);
    digitalWrite(4,HIGH);
    tone(5,523);
    lcd.setCursor(3,0);
    lcd.print("Motor:OFF");
    lcd.setCursor(0,1);
    lcd.print("LED & Buzzer: ON");
}
  else {
    digitalWrite(9,LOW);
    noTone(5);
    lcd.setCursor(3,0);
    lcd.print("Motor:OFF");
    lcd.setCursor(0,1);
    lcd.print("LED & Buzzer:OFF");
  }
}
