#include <NewPing.h>
#include <LiquidCrystal.h> 
#include <Servo.h>
#include <SPI.h> 

#define trigPin A0 
#define echoPin A1 
#define MAX_DISTANCE 500

#define PU          0x01
#define STOP        0x02
#define RESET       0x03
#define CLR_INT     0x04
#define RD_STATUS   0x05
#define RD_PLAY_PTR 0x06
#define PD          0x07
#define RD_REC_PTR  0x08
#define DEVID       0x09
#define PLAY        0x40
#define REC         0x41
#define ERASE       0x42
#define G_ERASE     0x43
#define RD_APC      0x44
#define WR_APC1     0x45
#define WR_APC2     0x65
#define WR_NVCFG    0x46
#define LD_NVCFG    0x47
#define FWD         0x48
#define CHK_MEM     0x49
#define EXTCLK      0x4A
#define SET_PLAY    0x80
#define SET_REC     0x81
#define SET_ERASE   0x82 

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
Servo myservo; 

void setup() {
lcd.begin(16, 2);
Serial.begin (115200); 
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
myservo.attach(9); //Set servo pada pin PWM 9

  digitalWrite(SS, HIGH);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS, HIGH);

  digitalWrite(SS,LOW);
  SPI.transfer(PU); // power up 
  SPI.transfer(0x00); // data byte
  digitalWrite(SS,HIGH);
  delay(100);  

  digitalWrite(SS,LOW);
  SPI.transfer(CLR_INT); // clear interupt and eom bit
  SPI.transfer(0x00); // data byte
  digitalWrite(SS,HIGH);
  delay(100);
}

void loop() {     
 int duration, jarak,posisi=0,i;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 jarak = duration/58.2;
 Serial.print(jarak);
 Serial.println(" cm");
 int start = 289;
 int selesai = 328;
 

 if(jarak<=50)
 {
  myservo.write(0);  
  lcd.setCursor(3,0);
  lcd.print("TONG SAMPAH");
  lcd.setCursor(4,1);
  lcd.print("TERBUKAA");
  digitalWrite(SS,LOW);
  SPI.transfer(STOP); // clear interupt and eom bit
  SPI.transfer(0x00); // data byte
  digitalWrite(SS,HIGH);
 
  delay(5000); 
  
 }
 else 
 {
myservo.write(80);
lcd.setCursor(3,0);
lcd.print("TONG SAMPAH");
lcd.setCursor(4,1);
lcd.print("OTOMATIS");

  digitalWrite(SS,LOW);
  SPI.transfer(SET_PLAY); // clear interupt and eom bit
  SPI.transfer(0); // data byte
  SPI.transfer(start&255);
  SPI.transfer(selesai&255);
  SPI.transfer(STOP);
  SPI.transfer(0);
  digitalWrite(SS,HIGH);  
  
 }
 
}
