/*
Tank Commander v0.01
*/

#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int tempPin = 0;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup() 
{
  sensors.begin();
  lcd.begin(16, 2);
}

void loop()
{
  // Get the temp in F
  float ambientTemp = cToF(getAmbientTemp(tempPin));
  float tankTemp = cToF(getTankTemp());
  

  // Print it to the display
  lcd.setCursor(0, 0);
  lcd.print("Air Temp ");
  lcd.print(int(ambientTemp));
  lcd.print("F");  
  
  lcd.setCursor(0, 1);  
  lcd.print("H20 Temp ");
  lcd.print(int(tankTemp));
  lcd.print("F");
  // Wait
  delay(500);
}

float getTankTemp() {
  sensors.requestTemperatures();  
  return sensors.getTempCByIndex(0);
}

float getAmbientTemp(int tempPin) {
  float tempC = (5.0 * analogRead(tempPin) * 100.0)/1024.0;  //convert the analog data to temperature
  return tempC;
}

float cToF(float tempC) {
  return ((tempC*9)/5) + 32;
}
