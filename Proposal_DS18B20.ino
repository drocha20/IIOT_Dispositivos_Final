#include <OneWire.h>
#include <DallasTemperature.h>

const int pinDatosDQ = 9;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
 
void setup() {
    
    Serial.begin(9600);
    sensorDS18B20.begin(); 
}
 
void loop() {

    Serial.println("Mandando comandos a los sensores");
    sensorDS18B20.requestTemperatures();
 
    Serial.print("Temperatura sensor 1: ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.println(" C");
    Serial.print("Temperatura sensor 2: ");
    Serial.print(sensorDS18B20.getTempCByIndex(1));
    Serial.println(" C");
    Serial.print("Temperatura sensor 3: ");
    Serial.print(sensorDS18B20.getTempCByIndex(2));
    Serial.println(" C");
    
    delay(1000); 
}
