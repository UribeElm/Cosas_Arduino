#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

byte trama[6];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
    if(Serial.available())
    {
      float temp=Serial.parseFloat();
      Serial.readBytes(trama,6);
      Serial.println(trama,6);
    }
    delay(2000);
    lcd.clear();    
}
