# Sensor Magnetómetro
Análisis, pruebas y documentación del sensor magnetómetro empleado en el proyecto.
En esta ocasión utilizaremos un sensor HMC5883L.
La resolución máxima de medida es de +-8 Gauss. Esta unidad no es propia del
sistema internacional. La unidad para el campo magnético en SI es el Tesla T.
Un Tesla equivale a a 10000 G.

1 T = 10000 G

Como referencia, según la wikipedia en https://es.wikipedia.org/wiki/Gauss_(unidad),
el campo magnético terrestre es de unos 0,5 Gauss.

En el artículo de la wikipedia sobre el campo magnético terrestre en: https://es.wikipedia.org/wiki/Campo_magn%C3%A9tico_terrestre, se considera que
en la superficie terrestre su magnitud puede variar entre los 0,25 y los 0,65G

Este dato determinará la configuración del sensor de a bordo.

El módulo del que disponemos, junto con la cirtuitería de soporte se denomina
GY-273.

## Modos de operación del sensor
El módulo dispone de tres módulos de operación:

### Modo de operación de medida continua:
El dispositivo toma medidas continuamente a un ritmo establecido por el usuario.


### Modo de operación de medida simple:
Es el modo de operación por defecto cuando arranca el chip. El dispositivo toma
una única medida y la coloca en los registros de salida.
Una vez que la información está almacenada en los registros de salida,
el magnetómetro pasa a estado de reposo.

### Modo de reposo:
En este modo de operación se desactivan la mayoría de subsistemas para garantizar
un consumo energético menor.

## Registros del sensor:

| Dirección | Nombre                        | Tipo acceso |
|-----------|-------------------------------|-------------|
| 00        | Registro de configuración A   | Lect/Esc    |
| 01        | Registro de configuración B   | Lect/Esc    |
| 02        | Registro de modo              | Lect/Esc    |
| 03        | Registro salida X MSB         | Lect        |
| 04        | Registro salida X LSB         | Lect        |
| 05        | Registro salida Z MSB         | Lect        |
| 06        | Registro salida Z LSB         | Lect        |
| 07        | Registro salida Y MSB         | Lect        |
| 08        | Registro salida Y LSB         | Lect        |
| 09        | Registro de estado            | Lect        |
| 10        | Registro de identificación A  | Lect        |
| 11        | Registro de identificación B  | Lect        |
| 12        | Registro de identificación C  | Lect        |

## Salidas del magnetómetro.

La salida del magnetómetro depende de dos registros, concretamente, del registro
de configuración A y del registro de configuración B.

El registro de configuración A permite configurar si deseamos hacer una media sobre
las lecturas, por defecto se toma una única lectura.

También permite indicar con qué frecuencia se actualizan los registros de salida.
Por defecto, se actualizan con una frecuencia de 15 Hz.

Por último se puede configurar la posibilidad de añadir un cierto sesgo a las
lecturas, pero esta característica viene deshabilitada por defecto.

En el registro de configuración B se controla la resolución de las lecturas. Los
tres bits más significativos controlan este parámetro. Los valores posibles son:

|   GN2  |  GN1  |  GN0  | Rango de lectura recomendado | Ganancia LSB/Gauss  |  Resolución digital mG/LSB | Rango de salida |
|--------|-------|-------|------------------------------|---------------------|----------------------------|-----------------|
|  0     |    0  |   0   | +- 0.88 Ga                   | 1370                | 0.73                       | -2048 - 2047    |
|  0     |    0  |   1   | +- 1.33 Ga                   | 1090 (Val por def)  | 0.92                       | -2048 - 2047    |


El resto de valores no se documentan porque no son necesarios. El valor por defecto reduciría la resolución
de las lecturas, así que nos interesaría pasar al rango de resolución digital de 0.73 mG/LSB

Para hacer esto habría que escribir un 0 en el registro B.

## Modos del magnetómetro.
La mayoría de sensores que hemos probado utilizan un enfoque de medida contínua,
esto es, están tomando valores contínuamente y cuando lees, lo que obtienes son
los últimos valores adquiridos.
Sin embargo, este sensor permite hacer lecturas simples. Las lecturas simples,
se producen justo a continuación de la configuración del registro en este modo y
acto seguido ponen el chip en modo reposo, con lo cual el ahorro energético es mayor.

Este va a ser el enfoque que sigamos en el modelo de cubesat.

Para poder poner el sensor en esta configuración hay que escribir en el registro
de modo el valor hexadecimal 0x01.

## Páginas web de interés:
http://www.magnetic-declination.com/
