 #include <LiquidCrystal.h> 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(8, 9); // RX, TX
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float persenGaram, kadar;
int putarState = 0;
int dMillis = 1000;
int oldDataMenu;
int waktutunda;
int jedaMenu = 5  ;
float kalibrasi = 0.57 ;
int buzzerState = 0;
void setup() {
  lcd.begin(8, 2);
  pinMode(A0, INPUT);

  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial); //set softwareSerial for DFPlayer
  delay(10);
  //mp3_reset();  //soft-Reset module DFPlayer
  delay(1000);   //wait 1ms for respon command
  mp3_set_volume (25); //set Volume module DFPlayer
}

void loop() {
  if (putarState == 0) proses();
  // proses();// keperluan kalibrasi
}
void proses() {
  int a = analogRead(A0);
  //persenGaram = a; // keperluan kalibrasi
  persenGaram = ((a - 151.7)  / 129.5) * kalibrasi;
  if (persenGaram <= 0) persenGaram = 0;
  if ((persenGaram >= 0.3) and (persenGaram < 0.6)) persenGaram = 0.3;
  if ((persenGaram >= 0.6) and (persenGaram < 0.8)) persenGaram = 0.6;
  if ((persenGaram >= 0.8) and (persenGaram < 1.0)) persenGaram = 0.8;
  if ((persenGaram >= 1.0) and (persenGaram < 1.3)) persenGaram = 1.0;
  if ((persenGaram >= 1.3) and (persenGaram < 1.7)) persenGaram = 1.3;
  if ((persenGaram >= 1.7) and (persenGaram < 2.0)) persenGaram = 1.7;
  if (persenGaram >= 2.0) persenGaram = 2.0;
 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(persenGaram);
  lcd.print("%");

  if ((int(persenGaram * 100)) < 30) lcd.print("  R");
  if ((int(persenGaram * 100)) < 80) lcd.print("  N");
  if ((int(persenGaram * 100)) < 130) lcd.print("  T");
  if ((int(persenGaram * 100)) >= 130) lcd.print(" ST");

  kadar = persenGaram * 2.50;
 

  if (kadar <= 0) kadar = 0;
  lcd.setCursor(0, 1);
  lcd.print(kadar);
  lcd.print("g ");
  delay(500);
tunda();
  // if (putarState == 0) putar(kadar * 100);
}
void putar0(int a) {
  mp3_play (100);
  delay(2600);
  mp3_play (a);
  delay(2600);
  mp3_play (500);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar(int a) {
  mp3_play (100);
  delay(2600);
  mp3_play (a);
  delay(2600);
  mp3_play (200);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar1(int a) {
  mp3_play (101);
  delay(2600);
  mp3_play (a);
  delay(2600);
  mp3_play (200);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar2(int a) {
  mp3_play (102);
  delay(2600);
  mp3_play (a);
  delay(2600);
  mp3_play (300);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar3(int a) {
  mp3_play (103);
  delay(2600);
  mp3_play (a);
  delay(2600);
  mp3_play (400);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar4(int a) {
  mp3_play (104);
  delay(2600);
  mp3_play (a);
  delay(2600);
  mp3_play (400);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar5(int a) {
  mp3_play (105);
  delay(2600);
  mp3_play (a);
  delay(2600);
  mp3_play (400);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar6(int a) {
  mp3_play (106);
  delay(2600);
  mp3_play (a);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar7(int a) {
  mp3_play (107);
  delay(2600);
  mp3_play (a);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar8(int a) {
  mp3_play (108);
  delay(2600);
  mp3_play (a);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar9(int a) {
  mp3_play (109);
  delay(2600);
  mp3_play (a);
  delay (3000);
  mp3_stop();
  putarState = 1;
}
void putar10(int a) {
  mp3_play (110);
  delay(2600);
  mp3_play (a);
  delay (3000);
  mp3_stop();
  putarState = 1;
}

void buzzer(){
  tone(7, 1000, 800);
  delay(600);
  buzzerState = 1;
}

void tunda () {
  unsigned long waktutunda = millis();
  if (waktutunda - oldDataMenu > 1000) {
    oldDataMenu = waktutunda;
    jedaMenu -= 1;
    if (jedaMenu <= 0) {
    buzzer();
      if (putarState == 0) {
        if (kadar < 0.70 ) putar0 ((kadar * 100));
        if ((kadar >= 0.75) and (kadar < 1 )) putar ((kadar * 100));
        if ((kadar >= 1) and (kadar < 2)) putar1 (((kadar - 1)*100));
        if ((kadar >= 2) and (kadar < 3)) putar2 (((kadar - 2)*100));
        if ((kadar >= 3) and (kadar < 4)) putar3 (((kadar - 3)*100));
        if ((kadar >= 4) and (kadar < 5)) putar4 (((kadar - 4)*100));
        if ((kadar >= 5) and (kadar < 6)) putar5 (((kadar - 5)*100)); 
        if ((kadar >= 6) and (kadar < 7)) putar6 (((kadar - 6)*100));
        if ((kadar >= 7) and (kadar < 8)) putar7 (((kadar - 7)*100));
        if ((kadar >= 8) and (kadar < 9)) putar8 (((kadar - 8)*100));
        if ((kadar >= 9) and (kadar < 10)) putar9 (((kadar - 9)*100));
        if ((kadar >= 10)and (kadar < 11)) putar10 (((kadar - 10 )*100));                   
      }    
    }
  }
}

void identitas() {
  lcd.setCursor(0, 0);
  lcd.print("SENSOR");
  lcd.setCursor(0, 1);
  lcd.print("GARAM");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("AFDHAL");
  lcd.setCursor(0, 1);
  lcd.print("YUSMAN");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("UPI-YPTK");
  lcd.setCursor(0, 1);
  lcd.print(" PADANG");
  delay(1000);
}
