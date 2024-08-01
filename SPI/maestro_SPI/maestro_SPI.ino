/*
 * Arduino bus SPI en modo maestro
 * 
 * https://www.proyectoarduino.com
 *
 */
 
#include <SPI.h>
 
/*
 * La libreria SPI pre-define las siguientes constantes 
 * para poder usar as lineas del bus SPI para las placas
 * Arduino UNO (AU) o Arduino MEGA (AM):
 *
 * SS   - Slave Select en en pin 10 (AU) o pin 53 (AM)
 * MOSI - Master Out, Slave In en el pin 11 (AU) o pin 51 (AM)
 * MISO - Master In, Slave Out en el pin 12 (AU) o pin 50 (AM)
 * SCLK - Serial Clock en el pin 13 (AU) o pin 52 (AM)
 * 
 */
 
void setup(void)
{
  // SS en nivel alto, garantiza que el esclavo esta inactivo
  digitalWrite(SS, HIGH);  
 
  // Inicializacion en modo maestro, coloca SCK, MOSI, SS en modo salida
  // SCK y MOSI a nivel bajo (LOW), y SS en nivel alto (HIGH)
  SPI.begin();
 
  // Ajusta la velocidad de comunicaciones a 2MHz
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}
 
 
void loop(void)
{
  char enviarByte;
 
  // Habilita el dispositivo esclavo
  digitalWrite(SS, LOW);
 
  // Envia el mensaje de prueba
  for (const char *msg = "Hola mundo!\n" ; enviarByte = *msg; msg++)
    SPI.transfer(enviarByte);
 
  // Deshabilita el dispositivo esclavo
  digitalWrite(SS, HIGH);
 
  // Espera aprox. un segundo y vuelta a empezar
  delay(1000);
}
