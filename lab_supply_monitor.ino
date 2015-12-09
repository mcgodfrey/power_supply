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
 * D5 = 19
 * D6 = 11
 * D7 = 12
 * RW to gnd
 *
 *
*/

#include <LiquidCrystal.h>

int Vset = A0;
int Vmeas = A1;
int Iset = A2;
int Imeas = A3;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup() {
  //lcd setup
  lcd.begin(16, 2);
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
  float set_voltage = (57.0/10.0)*5.0/1024.0*analogRead(Vset);
  float meas_voltage = (57.0/10.0)*5.0/1024.0*analogRead(Vmeas);
  float set_current = analogRead(Iset)*(5.0/1024.0)/(0.004*0.2*2200.0);
  float meas_current = analogRead(Imeas)*(5.0/1024.0)/(0.004*0.2*2200.0);

  //update the lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V = ");
  lcd.setCursor(4, 0);
  lcd.print(meas_voltage);
  lcd.setCursor(9,0);
  lcd.print("(");
  lcd.print(set_voltage);
  lcd.print(")");
  lcd.setCursor(0, 1);
  lcd.print("I = ");
  lcd.setCursor(4, 1);
  lcd.print(meas_current,3);
  lcd.setCursor(9,1);
  lcd.print("(");
  lcd.print(set_current,3);
  lcd.print(")");

  delay(100);  
}
