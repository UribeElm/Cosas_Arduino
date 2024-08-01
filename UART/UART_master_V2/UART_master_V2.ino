#include <LiquidCrystal.h>


float tempC, tempR;
int pinLM35 = A0;

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

byte sendData[6];

void setup() 
{   
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(pinLM35,INPUT);
}
void loop() 
{ 
  tempR = analogRead(pinLM35);
  tempC = (5.0 * tempR * 100.0)/1024.0;
  Serial.println(tempC);
  lcd.print("Temp(°C):");
  lcd.print(tempC);

  byte btemp[4];

  fromFloatToBytes(btemp,tempC);


  //////////////Trama de envio

  sendData[0]='E';
  
  sendData[1]=btemp[3];
  sendData[2]=btemp[2];
  sendData[3]=btemp[1];
  sendData[4]=btemp[0];

  sendData[5]='U';
  sendData[6]='\n';

  ////////////Fin trama

  Serial.write(sendData,6);
  delay(2000);
  
  lcd.clear();
}

void fromFloatToBytes(byte* bytes, float a)
{
  int length=sizeof(float);
  for(int i=0; i<length; i++)
  {
    bytes[i]=((byte*)&a)[i];
  }
}
