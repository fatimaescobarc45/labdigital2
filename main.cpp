#include <Arduino.h>
#include <stdint.h>
#include <driver/ledc.h>

int8_t bSelector  = 32; 
int8_t bBrillo = 35;
int8_t bDerecha = 34; 
int8_t bIzquierda= 39;

int8_t ledR = 22; int8_t brilloLedR; 

int8_t ledG = 19; int8_t brilloLedG; 
int8_t ledB = 17; int8_t brilloLedB; 
int8_t leds[3] = {ledR, ledG, ledB};
int8_t pinServo = 4;

int8_t ledActual = 0;
int8_t posicionServo = 0;
int32_t dutyServo = 0;

#define freqPWM 50
#define resPWM 16 

// Variables para antirrebote
unsigned long ult_led = 0;
unsigned long ult_brillo = 0;
unsigned long ult_derecha = 0;
unsigned long ult_izquierda = 0;
const unsigned long t_rebote = 60; // tiempo antirrebote


// put function declarations here:
void initPWM();
void ajustarBrillo(int led);
int moverServo();



void setup() {
  // put your setup code here, to run once:
  pinMode(bSelector, INPUT_PULLUP);
  pinMode(bBrillo, INPUT_PULLUP);
  pinMode(bIzquierda, INPUT_PULLUP);
  pinMode(bDerecha, INPUT_PULLUP);

  initPWM();
}


void loop() {
  // put your main code here, to run repeatedly:
  static bool yaRugio = HIGH;
  bool seleccionando = digitalRead(bSelector);
  //antirrebote
  if (yaRugio == HIGH && seleccionando == LOW && (millis() - ult_led) > t_rebote) {
    ledActual++;
    ult_led = millis();
  }
  if (ledActual > 2) {
    ledActual = 0;
  }
  yaRugio = seleccionando;

  ajustarBrillo(ledActual);

  int32_t dutyR = brilloLedR*0.3*65535;
  int32_t dutyG = brilloLedG*0.3*65535;
  int32_t dutyB = brilloLedB*0.3*65535;

  ledcWrite(0, dutyR);
  ledcWrite(1, dutyG);
  ledcWrite(2, dutyB);

  posicionServo = moverServo();
  switch (posicionServo) {
  case 0: // 0.5 ms
      dutyServo = 1638; // reglas de 3 de ciclo de 25ms
    break;
  case 1: // 1.0 ms
    dutyServo = 3277;
    break;
  case 2: // 1.5 ms
    dutyServo = 4915;
    break;
  case 3: // 2.0 ms
    dutyServo = 6553;
    break;
  case 4: // 2.5 ms
    dutyServo = 8191;
    break;
  default:
    dutyServo = 4915; // centro (1.5 ms)
    break;
}
  ledcWrite(3, dutyServo);


}
// put function definitions here:
void initPWM(void){
  // acá configuramos el PWM de la led roja
  ledcSetup(0, freqPWM, resPWM);
  ledcAttachPin(ledR, 0);
  ledcWrite(0, 0);

   // acá configuramos el PWM de la led verde
  ledcSetup(1, freqPWM, resPWM);
  ledcAttachPin(ledG, 1);
  ledcWrite(1, 0);
   // acá configuramos el PWM de la led azul
  ledcSetup(2, freqPWM, resPWM);
  ledcAttachPin(ledB, 2);
  ledcWrite(2, 0);

   // acá configuramos el PWM del servo
  ledcSetup(3, freqPWM, resPWM);
  ledcAttachPin(pinServo, 3);
  ledcWrite(3, 0);  
}

void ajustarBrillo(int canal) {
  static bool yaBrillo = HIGH;
  bool ajuste = digitalRead(bBrillo);
  if (yaBrillo == HIGH && ajuste == LOW && (millis() - ult_brillo) > t_rebote) {
    switch (canal) {
      case 0:
        brilloLedR++;
        if (brilloLedR > 3) brilloLedR = 0;
        break;
      case 1:
        brilloLedG++;
        if (brilloLedG > 3) brilloLedG = 0;
        break;
      case 2:
        brilloLedB++;
        if (brilloLedB > 3) brilloLedB = 0;
        break;
    }
    ult_brillo = millis();
  }
  yaBrillo = ajuste;
  delay(100);
}

int moverServo(){

  static bool yaMovioIzq = HIGH;
  bool ajusteI = digitalRead(bIzquierda);
  if (yaMovioIzq == HIGH && ajusteI == LOW && (millis() - ult_izquierda) > t_rebote) {
      posicionServo++;
      if(posicionServo>4){
        posicionServo = 4;
      }
      ult_izquierda = millis();
  }
  
  yaMovioIzq = ajusteI;

  static bool yaMovioDer = HIGH;
  bool ajusteD = digitalRead(bDerecha);
  if (yaMovioDer == HIGH && ajusteD == LOW && (millis() - ult_derecha) > t_rebote) {
      posicionServo--;
      if(posicionServo<0){
        posicionServo = 0;
      }
      ult_derecha = millis();
  }
  
  yaMovioDer = ajusteD;

  delay(100);

  return posicionServo;

}