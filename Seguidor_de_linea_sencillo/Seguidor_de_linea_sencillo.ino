//Sensores
int s1=A0, s2=A1, s3=A2, s4=A3, s5=A4, es1, es2, es3,es4, es5;

//Salida a motores
int e1=2, e2=3, e3=4, e4=5, a1=6, a2=7;

//Lecturas
int ld, li, lc, lii, ldd;

void setup() {
  // put your setup code here, to run once:
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  pinMode(e1,OUTPUT);
  pinMode(e2,OUTPUT);
  pinMode(e3,OUTPUT);
  pinMode(e4,OUTPUT);
  pinMode(a1,OUTPUT);
  pinMode(a2,OUTPUT);
  Serial.begin(9600);
}

void lecturas()
{
  ld=analogRead(A0);
  lc=analogRead(A1);
  li=analogRead(A2);
  ldd=analogRead(A3);
  lii=analogRead(A4);
  if(ld>400&&lc>400%%)
  {
    
  }
}

void derecha()
{
  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(e3, LOW);
  digitalWrite(e4, HIGH);
}

void izquierda()
{
  digitalWrite(e1, HIGH);
  digitalWrite(e2, LOW);
  digitalWrite(e3, HIGH);
  digitalWrite(e4, LOW);
}

void delante()
{
  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(e3, HIGH);
  digitalWrite(e4, LOW);
}


void loop() 
{
  lecturas();
  delay(50);
  /*Serial.print("|  SD  |  ");
  Serial.print(ld);
  Serial.print("  |  SC  |  ");
  Serial.print(lc);
  Serial.print("  |  SI  |  ");
  Serial.print(li);
  Serial.println("  |  ");
  */
 while(lc>400)
  {
    Serial.println("Adelante");
    analogWrite(a1,255);
    analogWrite(a2,255);
    delante();
    lecturas();
  }
  while(ld>400)
  {
    Serial.println("Derecha");
    analogWrite(a1,128);
    analogWrite(a2,128);
    derecha();
    lecturas();
  }
  while(li>400)
  {
    Serial.println("Izquierda");
    analogWrite(a1,128);
    analogWrite(a2,128);
    izquierda();
    lecturas();
  }
  while(lii>400)
  {
    Serial.println("Derecha");
    analogWrite(a1,64);
    analogWrite(a2,64);
    derecha();
    lecturas();
  }
  while(ldd>400)
  {
    Serial.println("Izquierda");
    analogWrite(a1,64);
    analogWrite(a2,64);
    izquierda();
    lecturas();
  }
}
