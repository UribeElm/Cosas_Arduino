//Motores
int s1=2, s2=3, s3=4, s4=5, sa=6;

//Ultrasónico
int eco= 8, trig=7, ult_detec; 
long d, t;

//LED
int led=9;

void setup() {
  Serial.begin(9600);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(s4,OUTPUT);
  pinMode(eco,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(trig,LOW);
  digitalWrite(sa,HIGH);
}

void loop() {

  ultrasonic();
  
  //Ataque
  while(ult_detec==1)
  {
      Serial.println("Enemigo detectado a ");
      Serial.println(d);
      adelante();
      ultrasonic();
      digitalWrite(led,HIGH);
  }
        
  //Cuando no detecta enemigo ni fuera de la arena
      Serial.println("Buscando...");
      izquierda();
      ultrasonic();
      digitalWrite(led,LOW);
}

void adelante()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, LOW);
}

void izquierda()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, HIGH);
}

void ultrasonic()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);         
  digitalWrite(trig, LOW);
  
  t = pulseIn(eco, HIGH); 
  d = t/59;
  if(d<30)
  {
    ult_detec=1;
  }
  else
  {
    ult_detec=0;
  }
}
