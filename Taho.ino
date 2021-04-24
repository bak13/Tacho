#include <LiquidCrystal_I2C.h>
#include "Tacho.h"

#define TACH_PIN 2
#define OUT_PIN 7
#define MIN_LIM 1

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 or 0x3F 
                                   // and type of screen 2004 or 1602
Tacho tacho; 


void setup() {
  //инициализируем LCD
  lcd.init();
  lcd.backlight();
  
  //настраиваем пин выхода
  pinMode(OUT_PIN,OUTPUT);
  
  // пин тахометра подтягиваем к VCC
  pinMode(TACH_PIN, INPUT);

  // настраиваем прерывание
  attachInterrupt(0, isr, FALLING);
}


// обработчик прерывания
void isr() {
  tacho.tick();   // сообщаем библиотеке об этом
}


void loop() {
  // put your main code here, to run repeatedly:
  
  
  static uint32_t tmr;
  if (millis() - tmr > 500) {
    tmr = millis();
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(tacho.getRPM());
    lcd.setCursor(0,1);
    lcd.print(tmr);
    
  }
  
    if (tacho.getRPM() < MIN_LIM){
      digitalWrite(OUT_PIN,LOW);
    }else{
      digitalWrite(OUT_PIN,HIGH);
    }
}
