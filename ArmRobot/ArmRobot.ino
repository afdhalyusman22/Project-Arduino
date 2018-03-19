#include <Wire.h>
#include "HX711.h"
#include <Servo.h>

Servo myservo;

float berat;

HX711 scale(A2, A1);
int pos = 5;
int adc_kunci_val[3] = {750, 820, 900 };
int jumlah_kunci = 3;
int adc_kunci_in;
int tombol = A4;
int kunci = -1;
int old_kunci = -1;//
int kiriState, kananState, jalanState = 1;
int timbang = 0;
int servoBState = 0;
int servoAState = 1;
int servoTurunState = 1;
int servoNaikState = 0;
int relayAdaptor = 8;

void setup() {
  Serial.begin(9600);
  
  pinMode(A0, OUTPUT); analogWrite(A0, 255);
  pinMode(A3, OUTPUT); analogWrite(A3, 0);

  pinMode(6, OUTPUT); digitalWrite(6, HIGH);
  pinMode(7, OUTPUT); digitalWrite(7, HIGH);

  pinMode(8, OUTPUT); digitalWrite(relayAdaptor, LOW);
  
  myservo.attach(4);
  myservo.write(5);
  scale.set_scale();

  kalibrasi();
  mundur();
}

void loop() {
  int a, b;
  berat = scale.get_units();
  if (berat < 0) berat = berat * -1;

  a = berat / 115;
  Serial.println(a);
  berat = 0;
  
  scale.power_down();
  analogRead(tombol);
  
  bacaKunci ();
  if (a >= 100) { 
    naik();          
    maju();
    timbang = 1;
    servoAState = 0;
  }
  if ((timbang == 1) and ( a <= 5)) {
    mundur();
    turun ();
  }
  
  delay(500);
  scale.power_up();
}

void turun() {
  if (kananState != 0) {
  if (servoTurunState != 1) servoTurun();
  }
  delay(3000);
  digitalWrite(relayAdaptor, LOW);
}

void naik() { 
  if (kananState != 0) { 
     if (servoNaikState != 1) servoNaik();
     }
}


void maju() {//dcmaju
    if (kiriState != 1) {
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    delay(100);
  } 
  if (kiriState != 0){
  if (servoBState != 1) servoB();
  }  
}

void mundur() {
if (servoAState != 1) servoA();
  //delay(100);
  if (kananState != 1){
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }  
}

void servoTurun() {  
  for (pos = 5; pos <= 175; pos += 5) { 
    myservo.write(pos);             
    delay(25);
    if (pos <= 10) servoTurunState = 1;
  }
}

void servoNaik() {
  for (pos = 175; pos >= 0; pos -= 5) { 
    myservo.write(pos);             
    delay(25);    
    if (pos >= 175) servoNaikState = 1;
  }
}

void servoA() {
  for (pos = 175; pos >= 0; pos -= 5) { 
    myservo.write(pos);           
    delay(25);    
    if (pos >= 175) servoAState = 1;
    servoBState = 0;    
    servoTurunState = 0;
    servoNaikState = 0;
  }
}

void servoB() {  
  for (pos = 5; pos <= 175; pos += 5) { 
    myservo.write(pos);              
    delay(25);
    if (pos <= 10) servoBState = 1;
  }
  delay(500);
  digitalWrite(relayAdaptor, HIGH); 
}

void posisiAwal() {
  
}

void servo() {
  for (pos = 5; pos <= 175; pos += 5) { 
    // in steps of 1 degree
    myservo.write(pos);             
    delay(25);                       
  }
  for (pos = 175; pos >= 0; pos -= 5) { 
    myservo.write(pos);             
    delay(25);                      
  }
}

void kiri() {
  digitalWrite(7, HIGH);
  kiriState = 1;
  kananState = 0;
}

void kanan () {
  //digitalWrite(6, HIGH);
  kananState = 1;  
  kiriState = 0;
}

void jalan() {
}

void bacaKunci () {//4
  adc_kunci_in = analogRead(tombol);
  kunci = ambil_kunci(adc_kunci_in);
  if (kunci != old_kunci)
  {
    delay(50);
    adc_kunci_in = analogRead(tombol);
    kunci = ambil_kunci(adc_kunci_in);
    if (kunci != old_kunci)
    {
      old_kunci = kunci;
      if (kunci >= 0)
      {
        if (kunci == 0) kiri();
        if (kunci == 1) {digitalWrite(6, HIGH); kanan();};
        if (kunci == 2) jalan();

      }
    }
  }
}


int ambil_kunci(unsigned int input)
{
  int k;
  for (k = 0; k < jumlah_kunci; k++)
  {
    if (input < adc_kunci_val[k])
    {
      return k;
    }
  }
  if (k >= jumlah_kunci)k = -1;
  return k;
}

void kalibrasi() {
  
  scale.set_scale(); //
  scale.set_scale(-19.f);
  scale.tare();
  
}

