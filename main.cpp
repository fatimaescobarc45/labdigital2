#include <Arduino.h>
#include <stdint.h>

//declaración de pines
const int8_t led0 = 4;
const int8_t led1 = 17;
const int8_t led2 = 18;
const int8_t led3 = 21; 
const int8_t bsuma = 26;
const int8_t bresta = 25;

const int8_t ledcero = 19;
const int8_t leduno = 16;
const int8_t leddos 22;
const int8_t ledtres = 23;

const int8_t alarma = 13;

int8_t leds[9] = {led0, led1, led2, led3, ledcero, leduno, leddos, ledtres, alarma};

volatile uint32_t contadorSuma;
volatile uint32_t contadorResta;
volatile bool sumaPresionado;
volatile bool restaPresionado;
volatile uint32_t ultimoISRsuma;
volatile uint32_t ultimoISRresta;

void contBinario();

// variables antirrebote
unsigned long ultimaSuma = 0;
unsigned long ultimaResta = 0;
unsigned long ultimoCambio = 0;
const unsigned long debounceDelay = 50; // ms


int initTMR0(void);
void IRAM_ATTR bsuma_ISR(void);
void IRAM_aTTR bresta_ISR(void);


// paso 1: instanciar timer 0

hw_timer_t *Timer0_Cfg = NULL;

//ISRs (rutinas de interrupción)



void setup() {
  // put your setup code here, to run once:

  //configurar el timer 0
  initTMR0();

  for (int i = 0; i<9; i++){
    pinMode(led[i], OUTPUT);
  }
  
  pinMode(bsuma, INPUT_PULLUP);
  pinMode(bresta, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(sumaPresionado){
    sumaPresionado = false;
  }
}

void initSumayResta(){
  attachInterrupt(bsuma, &bsuma_ISR, FALLING);


}

void IRAM_ATTR bsuma_ISR(void){
  sumaPresionado = true;
  contadorSuma++;
}

void IRAM_ATTR bresta_ISR(void){
  restaPresionado = true;
  contadorResta++;
}

void initTMR0(){
  //paso 2: configurar timer 0
  Timer0_Cfg = timerBegin(0, 80, true);
  // paso 3: configuer handler ISRf

  timerAttachInterrupt(Timer0_Cfg, TMR0_ISR, true);

  //paso 4: configurar alarma
  timerAlarmWrite(Timer0_Cfg, 500000, true);

  //paso 5 : iniciar la alarma 
  timerAlarmEnable(Timer0_Cfg);


}

void IRAM_ATTR TMR0_ISR(void){

  if(digitalRead(LED)){
    digitalWrite(LED, LOW);
  }
  else{
    digitalWrite(LED, HIGH);
  }
 }

 void contBinario() {

  static bool yaSumo = HIGH;
  static bool yaResto = HIGH;

  bool sumando = digitalRead(bsuma);
  bool restando = digitalRead(bresta);

  if (yaSumo == HIGH && sumando == LOW && (millis() - ultimaSuma) > debounceDelay) {
  counter++;
  ultimaSuma = millis();
}
yaSumo = sumando;

if (yaResto == HIGH && restando == LOW && (millis() - ultimaResta) > debounceDelay) {
  counter--;
  ultimaResta = millis();
}
yaResto = restando;

  if (counter > 15) {
    counter = 0;
  } else if (counter < 0) {
    counter = 15;
  }
  
  switch (counter) {
  case 0:
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    break;
  case 1:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    break;
  case 2:
    digitalWrite(led0, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    break;
  case 3:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    break;
  case 4:
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    break;
  case 5:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    break;
  case 6:
    digitalWrite(led0, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    break;
  case 7:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    break;
  case 8:
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    break;
  case 9:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    break;
  case 10:
    digitalWrite(led0, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    break;
  case 11:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    break;
  case 12:
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    break;
  case 13:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    break;
  case 14:
    digitalWrite(led0, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    break;
  case 15:
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    break;
  default:
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    break;
}  
  delay(50);
}
