/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

/* ## personal changes by sycramore denoted by ##
*/

/*
## general : Datei ist deutlich weniger ausfuehrlich kommentiert als die Bosch-Library
  */

// ## Seengreat benutzt die Adafruit-Library. Potentiell gute Wahl, Adafruit bietet guten ausfuehrlichen Kundensupport fuer Anfaengersoftware und
// ## Projekte und holt meines Wissens nach die somit entstehenden Kosten ueber den deutlich hoeheren Preis der verkauften Hardware wieder rein.
// ## Heisst aber auch, dass eine Adafruit-Library wahrscheinlich gut getestet ist und sauber geschrieben/dokumentiert?

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


// ## Seengreat bietet anscheinend Support fuer die beiden gaengigen Protokolle I2C und SPI.
// ## I2C - seriell (eine Datenleitung, Daten werden Zeichen fuer Zeichen gesendet - einfach, aber langsam)
// ## I2C - meistens - ein Master, mehrere Slaves, also eine zentrale Kontrollstelle mit vielen empfangenden Empfaengern
// ## I2C - benoetigt 2 Leitungen, SDA (Datenleitung, serial data) und SCL (Zeitsignal, seria clock)
// ## Master gibt Taktrate vor
// ## SPI - drei Leitungen, serielle Uebertragung, aber parallele Kommunikation moeglich durch die beiden Datenleitungen zwischen Master und Slave

// ## SPI - 

// ## Spannend, SPI scheint Standard zu sein, I2C als Zusatz ueber die externe Adafruit Library integriert
// ## Warum? Ich haette gedacht, dass I2C als Protokoll deutlich einfacher sein sollte als SPI. Ist SPI vielseitiger und daher Standard?

//If USEIIC is 1 means use I2C interface, If it is 0,use SPI interface
#define USE_IIC 1
//
#if USE_IIC
Adafruit_BME280 bme; // I2C
#else

// ## Definition der I/O-Ports fuer Kommunikation, die Zahlen sind typischerweise die Portnummern, die im Datenblatt des Arduino stehen
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
#endif


// ## Die Zahl sieht bekannt aus. HPA koennten Hektopascal sein. Ich kenne die 1013 als Druck aus Standardbedingungen und Normalbedingungen in der physikalischen
// ## Chemie. Sea level, also Meeresspiegel ist bei Hoehenmessungen der Nullwert. Da die Hoehe des Luftdrucks abhaengig ist von der Hoehe relativ zum Meeresspiegel,
// ## ergibt es Sinn, diesen Nullwert einmal festzulegen fuer Messungen von Luftdruck. Die Temperaturabhaengigkeit koennte man dann ueber den Sensor mit integrieren,
// ## bzw der Sensor misst ja die Temperatur auch mit. Die Hoehenabhaengigkeit des Luftdrucks koennte man aber extra in eventuelle Rechnungen bzw
// ## Ausgaben mit einbeziehen
#define SEALEVELPRESSURE_HPA (1013.25)

unsigned long delayTime;

void setup() {
    Serial.begin(115200); //## 115200 Baud ist die hoechste serielle Uebertragungsrate bei Arduino
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin();  
    // You can also pass in a Wire library object like &Wire2
    //status = bme.begin(0x76, &Wire2); //## wieso die 0x76? Was macht der Wert?
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();
}


void loop() { 
    printValues();
    delay(delayTime);
}

// ## gut, Seengreat ruft also nur die Adafruit-Library auf als Demobeispiel und demonstriert ein paar essentielle Funktionen der Library
// ## Wenn ich mehr wissen will, sollte ich also die Adafruit Library sezieren, falls diese Open Source ist.
void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}
