#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);


// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  
   lcd.begin(16, 2);
     lcd.print("Hola mundo i guess");
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}