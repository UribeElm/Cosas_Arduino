const int Trigger = 13,Echo = 12,controlPin = 8, ctrlRein=7, ctrlMenos=6; 
int dat, Verde=4, Rojo=2, pulsacion = 0, estado_boton,st_rein, estado_boton_anterior,st_r_ant, stc, st_menos, st_ant_menos, cont_menos=0;
long d;

void setup() {
  Serial.begin(9600);
  
  //Zona ultrasonico
  pinMode(Trigger, OUTPUT); 
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
  //Fin zona
  
  //Zona de LEDs
  pinMode(Rojo,OUTPUT);
  pinMode(Verde,OUTPUT);
  //Fin zona
  
  //Zona del PWM
  pinMode(11,OUTPUT);
  //Fin

  //Zona del detector de botones
  pinMode(controlPin, INPUT_PULLUP);
  estado_boton_anterior = digitalRead(controlPin);
  pinMode(ctrlRein,INPUT_PULLUP);
  st_r_ant=digitalRead(ctrlRein);
  //Fin de zona
}

void loop()
{
  medirdistancia();
  if(d>60)
  {
    digitalWrite(Verde,LOW);
    digitalWrite(Rojo,HIGH);
    Serial.println("Motor apagado");
    analogWrite(11,0);
    pulsacion=0;
  }
  else
  {
    detecta_pulsacion();
    detecta_rein();
    detecta_menos();
    digitalWrite(Rojo,LOW);
    Serial.println("Motor listo");  
    digitalWrite(Verde,HIGH);
    analogWrite(11,pulsacion*170/4);
  }
  delay(100);
}

void medirdistancia()
{
  dat=analogRead(A0); 
  int stat=1;
  long t; 

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);       
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); 
  d = t/59;        
}

void detecta_rein()
{
      st_rein=digitalRead(ctrlRein);
      if(st_rein!=st_r_ant)
      {
          if(st_rein==HIGH)
          {
            Serial.println("Aqui debe reiniciar");
            pulsacion=0;
            Serial.println(pulsacion);
          }
      }
      st_r_ant=st_rein;
}

void detecta_pulsacion() {
estado_boton = digitalRead(controlPin);
if (estado_boton != estado_boton_anterior) 
{
  if (estado_boton == HIGH) 
  {
    Serial.println("Nueva pulsacion");
    Serial.println(pulsacion++);
  }
}
  estado_boton_anterior = estado_boton;
}

void detecta_menos() {
cont_menos=pulsacion;
st_menos = digitalRead(ctrlMenos);
if (st_menos != st_ant_menos) 
{
  if (st_menos == HIGH) 
  {
    if(cont_menos!=0)
    {
      Serial.println("Nueva pulsacion");
      Serial.println(pulsacion--);
    } 
  }
}
  st_ant_menos = st_menos;
}
