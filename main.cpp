#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

#define pinR 27
#define pinG 25
#define pinB 33
#define pinpot1 35
#define pinpot2 34

int cont;

// variables PWM

#define freqPWM 50
#define resPWM 8 
int32_t dutyR; int32_t dutyG; int32_t dutyB;


// put function declarations here:

void mostrarEnLCD(int valor1, int valor2, int valor3);
void initPWM();
void ajustarBrillo(int led);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
   lcd.begin(16, 2);
   pinMode(pinR, OUTPUT);
   pinMode(pinG, OUTPUT);
   pinMode(pinB, OUTPUT);
  initPWM();


}

void loop() {
  // put your main code here, to run repeatedly:

  while(Serial.available()){
    if((char)Serial.read()=='+'){
      cont++;
    }
    else if((char)Serial.read() == '-'){
      cont--;
    }
  }
  if(cont>255){
    cont=255;
  }
  if(cont<0){
    cont=0;
  }

  int pot1 = analogRead(pinpot1);
  int pot2 = analogRead(pinpot2);

  dutyR = map(pot1, 0, 4095, 0, 255);
  dutyG = map(pot2, 0, 4095, 0, 255);
  dutyB = cont;
  Serial.print("Rojo: ");
  Serial.print(dutyR);
  Serial.print(" Verde: ");
  Serial.print(dutyG);
  Serial.print(" Azul: ");
  Serial.println(dutyB);
  
  mostrarEnLCD(dutyR, dutyG, cont);

  ledcWrite(0, dutyR);
  ledcWrite(1, dutyG);
  ledcWrite(2, dutyB);


}

// put function definitions here:
void mostrarEnLCD(int valor1, int valor2, int valor3) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rojo:Verde:Azul:");
  lcd.setCursor(0, 1);
  lcd.print(valor1);
  lcd.setCursor(5, 1);
  lcd.print(valor2);
  lcd.setCursor(11, 1);
  lcd.print(valor3);
  delay(50);

}
void initPWM(void){
  // acá configuramos el PWM de la led roja
  ledcSetup(0, freqPWM, resPWM);
  ledcAttachPin(pinR, 0);
  ledcWrite(0, 0);

   // acá configuramos el PWM de la led verde
  ledcSetup(1, freqPWM, resPWM);
  ledcAttachPin(pinG, 1);
  ledcWrite(1, 0);

  // acá configuramos el PWM de la led azul
  ledcSetup(2, freqPWM, resPWM);
  ledcAttachPin(pinB, 2);
  ledcWrite(2, 0);

}