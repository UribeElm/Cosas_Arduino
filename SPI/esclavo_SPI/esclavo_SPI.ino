/*
 * Arduino bus SPI en modo esclavo
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

char datosRecibidos [100];
volatile byte indice;
volatile bool recepcionTerminada;

void setup (void)
{
  // Inicia puerto serial para visualizar
  // los datos de llegada
  Serial.begin (115200); 

  // Habilita el bus SPI en modo esclavo
  // usando el registro SPCR del microcontrolador
  SPCR |= bit (SPE);

  // Configura el pin MISO como salida (slave out)
  pinMode (MISO, OUTPUT);

  // Control de datos recibidos en el buffer
  
  // Buffer vacio
  indice = 0;

  // Indicador de final de recepcion
  recepcionTerminada = false;

  // Habilita las interrupciones del bus SPI
  SPI.attachInterrupt();

}

// Rutina de interrupcion del bus SPI
ISR (SPI_STC_vect)
{
  // Lee el rado recibido desde el registro SPDR del bus SPI
  byte datoRecibido = SPDR;

  // Si hay espacio, inserta el dato recibido en el buffer
  if (indice < sizeof datosRecibidos)
  {
    datosRecibidos[indice++] = datoRecibido;

    // Si se ha recibido final de linea
    // se procesa el buffer para su salida por el puerto serie
    if (datoRecibido == '\n')
      recepcionTerminada = true;
  }
}

void loop (void)
{
  if (recepcionTerminada)
  {
    datosRecibidos[indice] = 0;
    Serial.println (datosRecibidos);
    indice = 0;
    recepcionTerminada = false;
  }
}
