/* sendSingleValues.ino
 *
 * Copyright Hackables 2017
 *
 * How to send a single analog value on the Sigfox network
 */

#include <Arduino.h>
#include <Akeru.h>

// TD1208 Sigfox module IO definition
/*   Hackables device | TX | RX
          SigFox Hack | D4 | D3
             Breakout | your pick */
#define TX 4
#define RX 3

// Sigfox instance management
Akeru akeru(RX, TX);

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
}

void loop()
{
  int sensorValue = analogRead(A0);

  // Trace on serial console
  Serial.println(sensorValue);

  // convert to hexadecimal before sending
  String data = akeru.toHex(sensorValue);

  // Send in the mighty internet!
  // akeru.sendPayload() returns 0 if message failed.
  if (akeru.sendPayload(data))
  {
    Serial.println("Message sent !");
  }

  // Wait for 10 minutes.
  // Note that delay(600000) will block the Arduino (bug in delay()?)
  for (int second = 0; second < 600; second++)
  {
    delay(1000);
  }
}
