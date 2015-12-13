/*
 * Voltage and current monitor for lab supply
 *
 * Vset to A0
 * Vmeas to A1
 * Iset to A2
 * Imeas to A3
 *
 * 
 * Rs = 7
 * Enable = 8
 * D4 = 9
 * D5 = 10
 * D6 = 11
 * D7 = 12
 * RW to gnd
 *
 *
*/

#include <LiquidCrystal.h>

int Vset = A7;
int Iset = A6;
int Vmeas = A5;
int Imeas = A4;

//               (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup() {
  //lcd setup
  lcd.begin(20, 4);
  lcd.clear();
  
  //ADC pin setup
  pinMode(Vset, INPUT);  
  pinMode(Vmeas, INPUT);  
  pinMode(Iset, INPUT);  
  pinMode(Imeas, INPUT);  
  analogReference(DEFAULT);
}


void loop() {
  //meaure values
  float set_voltage = 5.64*5.0/1024.0*analogRead(Vset);
  //float set_voltage = 5.0/1024.0*analogRead(Vset);
  float meas_voltage = 5.64*5.0/1024.0*analogRead(Vmeas);
  //float meas_voltage = 5.0/1024.0*analogRead(Vmeas);
  //float set_current = analogRead(Iset)*(5.0/1024.0)/(0.004*0.2*2200.0);
  float set_current = analogRead(Iset)*(5.0/1024.0);
  //float meas_current = analogRead(Imeas)*(5.0/1024.0)/(0.004*0.2*2200.0); 
  float meas_current = analogRead(Imeas)*(5.0/1024.0);

  //update the lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vmeas = ");
  lcd.setCursor(8, 0);
  lcd.print(meas_voltage);
  lcd.setCursor(0, 1);
  lcd.print("Vset = ");
  lcd.setCursor(8, 1);
  lcd.print(set_voltage);
  lcd.setCursor(0, 2);
  lcd.print("Imeas = ");
  lcd.setCursor(8, 2);
  lcd.print(meas_current);
  lcd.setCursor(0, 3);
  lcd.print("Iset = ");
  lcd.setCursor(8, 3);
  lcd.print(set_current);
  
  delay(50);  
}
