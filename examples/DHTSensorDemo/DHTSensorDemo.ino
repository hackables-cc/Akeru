/* DHTSensorDemo.ino
 *
 * Copyright Hackables 2017
 *
 * Read the temperature and humidity values from the
 * DHt sensor and send them to the sigfox network.
 */

#include <Arduino.h>
#include <Akeru.h>
#include <DHT.h>

// TD1208 Sigfox module IO definition
/*   Hackables device | TX | RX
          SigFox Hack | D4 | D3
             Breakout | your pick */
#define TX 4
#define RX 3

// DHT11 Sensor definitions
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define DHT_POWER_PIN 6
#define DHT_COMMS_PIN 7

// LED Pin definitions
#define LED_RED     8
#define LED_YELLOW  9

// Sigfox instance management
Akeru akeru(RX, TX);

// Initialize DHT sensor.
DHT dht(DHT_COMMS_PIN, DHTTYPE);

void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    Serial.println("Starting...");

    // Check TD1208 communication
    if (!akeru.begin())
    {
        Serial.println("TD1208 KO");
        while(1);
    }

    //akeru.echoOn(); // uncomment this line to see AT commands

    // Initilize the DHT
    pinMode(DHT_POWER_PIN, OUTPUT);
    dht.begin();

    // Init DHT
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);

}


void loop()
{
    // Apply power to the DHT pin
    digitalWrite(DHT_POWER_PIN, HIGH);
    // Give time for the senso to settle
    delay(2000);

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    uint8_t h = (uint8_t) dht.readHumidity();
    // Read temperature as Celsius (the default)
    uint8_t t = (uint8_t) dht.readTemperature();


    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.print(" *C\n ");

        // Convert to hexadecimal before sending
        String temp = akeru.toHex(t);
        String humi = akeru.toHex(h);

        String msg = temp + humi; // Put everything together

        if (akeru.sendPayload(msg))
        {
          Serial.println("Message sent !\n");
        }
        else
        {
          Serial.println("Message not sent !\n");
        }

    }


    // Remove power from the DHT sensor
    digitalWrite(DHT_POWER_PIN, LOW);

    // Makes a delay of aprox 15minutes
    unsigned char half_min;
    for(half_min = 0; half_min < 30; half_min++)
    {
        delay(29950);
        digitalWrite(LED_YELLOW, HIGH);
        delay(50);
        digitalWrite(LED_YELLOW, LOW);
    }
}
