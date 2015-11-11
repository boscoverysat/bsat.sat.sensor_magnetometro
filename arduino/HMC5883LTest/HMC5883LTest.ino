
/****************************
 HMC5883LTest

  Este sketch comprueba el funcionamiento basico de un sensor magnetometro 
  HMC5883L

  Author: @goyoregalado
  Esta version incluye una referencia temporal basada en el contador
  de milisegundos del propio arduino.
  No debe considerarse una referencia fiable.
  
  Los valores se devuelven en miligauss.
  
******************************/



#include <Wire.h>
#include "hmc5883l.h"

float magX, magY, magZ;
unsigned int milsec = 0;

void setup() {
  magX = 0.0;
  magY = 0.0;
  magZ = 0.0;
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Inicializando bus I2C");
  Wire.begin();
  Serial.println("Configurando magnetometro HMC5883L");
  configure_hmc5883l();
  Serial.println("Configuracion concluida");


}

void loop() {
  milsec = millis();
  

  hmc5883l_singleread();
  Serial.print(milsec);
  Serial.print("ms ;");
  Serial.print(magX * 0.73);
  Serial.print("mg ;");
  Serial.print(magY * 0.73);
  Serial.print("mg ;");
  Serial.print(magZ * 0.73);
  Serial.println("mg");
  
  delay(500);
}

void configure_hmc5883l() {
  Wire.beginTransmission(HMC5883L);
  // Se configura 0 00 001 00
  // El bit mas significativo siempre debe ser 0
  // Los siguientes dos bits se ponen a cero para que no haga
  // media de lecturas.
  // Los siguientes tres bits toman el valor 100 y eso provoca
  // que la velocidad de medida sea de 15 Hz
  // Los dos ultimos bits establecen que la medida se haga sin sesgo, por eso toman valor 00
  Wire.write(HMC5883L_CONFIG_A);
  Wire.write(0x04);
  Wire.endTransmission(true);
  
  Wire.beginTransmission(HMC5883L);
  // Se configura 000 00000
  // Los tres primeros bits configuran la ganancia de las salidas. Toman un valor 000
  // este valor implica que la ganancia sea de 1370 LSB/Gauss
  Wire.write(HMC5883L_CONFIG_B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  
  Wire.beginTransmission(HMC5883L);
  // Se configura con el valor 000000 01
  // Los seis primeros bits tienen que configurarse a cero obligatoriamente.
  // Los dos ultimos bits se configuran con el valor 01 que representa el modo de lectura unica.
  // Si queremos usar lecturas continuas entonces se programa con 00
  // Dado que en modo de lectura unica el chip permanece en reposo hasta la siguiente lectura, parece
  // el modo mas adecuado para el modelo de cubesat.
  Wire.write(HMC5883L_MODE);
  Wire.write(0x01);
  Wire.endTransmission(true);
}

void hmc5883l_singleread() {
  Wire.beginTransmission(HMC5883L);
  // Se configura con el valor 000000 01
  // Los seis primeros bits tienen que configurarse a cero obligatoriamente.
  // Los dos ultimos bits se configuran con el valor 01 que representa el modo de lectura unica.
  // Si queremos usar lecturas continuas entonces se programa con 00
  // Dado que en modo de lectura unica el chip permanece en reposo hasta la siguiente lectura, parece
  // el modo mas adecuado para el modelo de cubesat.
  Wire.write(HMC5883L_MODE);
  Wire.write(0x01);
  Wire.endTransmission(true);  
  
  Wire.beginTransmission(HMC5883L);
  Wire.write(HMC5883L_DATAX_H);
  Wire.endTransmission(false);
  Wire.requestFrom(HMC5883L, 6, true);
  magX = Wire.read() <<8| Wire.read();
  magZ = Wire.read() <<8| Wire.read();
  magY = Wire.read() <<8| Wire.read();
}
