/*
 * Voltage and current monitor for lab supply
 * Connects to 20x4 character LCD
 * Very simple. It just loops every 50ms (plus processing/measurement time)
 *   performs 4 measurments (current + voltage measure + set) and updates the display.
 * 
 * Current and voltage measurements must be calibrated
 * This should be a simple multiplicative adjustment which can be 
 *   calibrated with a single measurement
 * Set CALIBRATE below == 1 and measure a voltage/current at ~mid-scale
 * Measure the voltage and current with a multimeter and divide by the values displayed on the LCD
 * These are the multiplcative factors V_CAL_FACTOR and I_CAL_FACTOR
 *
 *
 * Analog voltage signal inputs
 * Vset to A5
 * Vmeas to A7
 * Iset to A6
 * Imeas to A4
 * 
 * LCD connections
 * [LCD_pin = Arduino_pin]
 * Rs = D7
 * Enable = D8
 * D4 = D9
 * D5 = D10
 * D6 = D11
 * D7 = D12
 * RW to gnd
 *
*/

#include <LiquidCrystal.h>

//set CALIBRATE == 1 to move into calibration mode.
//This will display the raw voltage measured on each pin
#define CALIBRATE 0
//Calibration multiplicative factors for current and voltage
//Varduino = 2.60V, Vmeas = 14.40V -> 
//Iarduino = 0.30, Imeas = 161.4mA
#define V_CAL_FACTOR (14.4/2.6)
#define I_CAL_FACTOR (0.1614/0.30)

byte Vset = A5;
byte Iset = A6;
byte Vmeas = A7;
byte Imeas = A4;

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
  analogReference(DEFAULT); //use the 5V power rail as refernce
}


void loop() {

  #if CALIBRATE
  //display raw voltage
  float set_voltage = 5.0/1024.0*analogRead(Vset);
  float meas_voltage = 5.0/1024.0*analogRead(Vmeas);
  float set_current = analogRead(Iset)*(5.0/1024.0);
  float meas_current = analogRead(Imeas)*(5.0/1024.0);
  #else
  //measure actual current/voltages (with calibration factors)
  float set_voltage = V_CAL_FACTOR*5.0/1024.0*analogRead(Vset);
  float meas_voltage = V_CAL_FACTOR*5.0/1024.0*analogRead(Vmeas);
  float set_current = I_CAL_FACTOR*analogRead(Iset)*(5.0/1024.0);
  float meas_current = I_CAL_FACTOR*analogRead(Imeas)*(5.0/1024.0);
  #endif

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
