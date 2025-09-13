#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

#define bsuma 34
#define bresta 36
#define pot1 12
#define pot2 14

// Variables para antirrebote
unsigned long lastSuma = 0;
unsigned long lastResta = 0;
const unsigned long debounceDelay = 50; // milisegundos

// Estado anterior de los botones
bool prevSuma = HIGH;
bool prevResta = HIGH;

// Variable de contador
int contador = 0;


// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  pinMode(bsuma, INPUT_PULLUP);
  pinMode(bresta, INPUT_PULLUP);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
   lcd.begin(16, 2);

    
}

void loop() {
  // put your main code here, to run repeatedly:
    // Antirrebote para bsuma
  bool lecturaSuma = digitalRead(bsuma);
  if (prevSuma == HIGH && lecturaSuma == LOW && (millis() - lastSuma) > debounceDelay) {
    contador++;
    lastSuma = millis();
  }
  prevSuma = lecturaSuma;

  // Antirrebote para bresta
  bool lecturaResta = digitalRead(bresta);
  if (prevResta == HIGH && lecturaResta == LOW && (millis() - lastResta) > debounceDelay) {
    contador--;
    lastResta = millis();
    

  }
 if(contador > 255){
      contador = 0;
    }

  if(contador<0){
      contador = 255;
    }


  int8_t lectura1 = analogRead(pot1);
  int8_t lectura2 = analogRead(pot2) * 5 / 4095;

  prevResta = lecturaResta;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pot1:Pot2:Cont:");
  lcd.setCursor(0,1);
  lcd.print(lectura1);
  lcd.setCursor(6,1);
  lcd.print(lectura2);
  lcd.setCursor(12,1);
  lcd.print(contador);

  delay(150);





}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
