/* downlinkDemo.ino
 *
 * Copyleft Hackables 2017
 *
 * Downlink activation, and reception of a Sigfox network message
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
  Serial.begin(9600);

  // Check TD1208 communication
  if (!akeru.begin())
  {
    Serial.println("TD1208 KO");
    while(1);
  }

  //akeru.echoOn(); // uncomment this line to see AT commands

  String data = "";
  if (akeru.receive(&data))
  {
    Serial.print("Data received : 0x");
    Serial.println(data);
  }
}

void loop()
{
}
