/* 
 *  Convertiremos el arduino en un instrumento que mida la temperatura y humedad
 *  La señal de datos del DHT11 se conectará al pin 8
 *  *IDN? --> DevolveRa ARDUINO INSTRUMENT , MODEL HMSR-LACH, Jun 20 2022 10:30:00
 *  
 *  SYSTem:INST:TEMPerature? -->Devolvera la temperatura
 *  SYSTem:INST:HUMedity? --> Devolvera la humedad
 *  SYSTem:INST:VOLTage? --> Devolvera el voltaje 
*/
#include <dht.h>
dht DHT;
#include "Arduino.h"
#include "Vrekrer_scpi_parser.h"

SCPI_Parser instrumento;
const int dataPin = 8;

void setup(){
  instrumento.RegisterCommand(F("*IDN?"), &Identify);
  instrumento.SetCommandTreeBase(F("SYSTem:INST"));
  instrumento.RegisterCommand(F(":TEMPerature?"), &GetTemperature);
  instrumento.RegisterCommand(F(":HUMidity?"), &GetHumidity);
  instrumento.RegisterCommand(F(":VOLTage?"), &GetVoltage);
  Serial.begin(9600);
  pinMode(dataPin,INPUT);
  pinMode(A0, INPUT);
}

void loop(){
  instrumento.ProcessInput(Serial, "\n");
}

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface){
  interface.println(F("ARDUINO INSTRUMENT, MODEL HMSR-LACH, Jun 20 2022 10:30:00"));  
}

void GetTemperature(SCPI_C commands, SCPI_P parameters, Stream& interface){
  DHT.read11(dataPin);
  interface.println(String(DHT.temperature));
}

void GetHumidity(SCPI_C commands, SCPI_P parameters, Stream& interface){
  DHT.read11(dataPin);
  interface.println(String(DHT.humidity));
}

void GetVoltage(SCPI_C commands, SCPI_P parameters, Stream& interface){
  interface.println(String((float)analogRead(A0)*5.0/1023));
}
