#include <EEPROM.h>

//Motores
const byte mot1=5;
const byte mot2=6;
const byte mot3=7;

//Boton
const byte pul=2;

//Modo de activacion
byte modoAct=0;

//Posicion en memoria
const byte pos=0;

void setup() {
  Serial.begin(9600);
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  pinMode(mot3, OUTPUT);
  pinMode(pul, INPUT_PULLUP);

  modoAct=EEPROM.read(pos);

  if(modoAct<1 || modoAct>3)
  {
    EEPROM.write(pos,1);
    modoAct=1;
  }
}

void loop() {
  //Pulso del boton
  boolean pulsado=digitalRead(pul);
  delay(200);

  if(pulsado==HIGH)
  {
    modoAct++;
    if(modoAct>3)
    {
      modoAct=1;
    }
    Serial.print("Modo activacion ");
    Serial.println(modoAct);
  }
  //Todo apagado
  digitalWrite(mot1,LOW);
  digitalWrite(mot2,LOW);
  digitalWrite(mot3,LOW);

  //Encender el motor correspondiente
  if(modoAct==1)
  {
    digitalWrite(mot1,HIGH);
    digitalWrite(mot2,LOW);
    digitalWrite(mot3,HIGH);
  }
  else if(modoAct==2)
  {
    digitalWrite(mot1,LOW);
    digitalWrite(mot2,HIGH);
    digitalWrite(mot3,HIGH);
  }
  else if(modoAct==3)
  {
    digitalWrite(mot1,HIGH);
    digitalWrite(mot2,HIGH);
    digitalWrite(mot3,LOW);
  }

  if(!pulsado)
  {
    EEPROM.write(pos,modoAct);
  }
}
