#include<LiquidCrystal_I2C.h>
#include<Servo.h>
LiquidCrystal_I2C lcd(32,16,2);
Servo door;

int trigPin = 4;
int echoPin = 5;
int pos;

void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  door.write(0);
  door.attach(3);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  
  
 lcd.init();
 lcd.setCursor(0,0);
 lcd.backlight();
 lcd.display(); 
}

void loop()
{
  SmartDoor();
  PIR();
  GasDetection();
  Irrigation();
  LDR();
}

void PIR(){
 
  int pirValue = analogRead(A0);
  //Serial.println(pirValue);
  if(pirValue >1000){
    digitalWrite(13,HIGH);
    delay(5000);
    digitalWrite(13,LOW);
  }
  else{
    digitalWrite(13,LOW);
}
} 
void GasDetection(){
  int gasValue = analogRead(A1);
  //Serial.println(gasValue);
  if(gasValue > 220){
     tone(12,523);
     digitalWrite(11,HIGH);
   }
  else{
     noTone(12);
     digitalWrite(11,LOW);
    }
  }

void Irrigation(){
  int moisture = analogRead(A2);
  //Serial.println(moisture);
  if(moisture < 300){
    digitalWrite(10,HIGH);
  }
  else{
    digitalWrite(10,LOW);
  }
}

void LDR(){
  int ldrValue = analogRead(A3);
  //Serial.println(ldrValue);
  
  if(ldrValue < 500){
    digitalWrite(9,HIGH);
    lcd.setCursor(3,0);
    lcd.print("Night Time!");
    door.write(0);
    delay(1000);
  }
  else{
    digitalWrite(9,LOW);
    lcd.setCursor(3,0);
    lcd.print(" Welcome!   ");
    

  }
}

void SmartDoor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin,HIGH);
  int distance = duration *0.034 /2;
  //Serial.println(distance);
  
  if(distance <= 330){
    door.write(90);
   
  }
  if(distance >=330){
    door.write(0);
}
}
