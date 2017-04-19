Akeru - TD1208 library for Arduino
=========

Requirements
------------

[Sigfox-Hack](http://www.hackables.cc/en/sigfox/11-sigfox-hack.html)


Examples
--------

...

Installation
------------

Like any other library, see [tutorial](http://arduino.cc/en/Hacking/Libraries)

Use
--------------------------------------

####Sigfox module initialization

Starting with version 4 of the library, RX/TX definition is directly in the sketch. There's a single library file to include and a simple line of code to map the signals according to your device :

```
#include <Akeru.h>

/*  Hackables device | TX | RX
         Sigfoc Hack | D4 | D3
            Breakout | your pick */
#define TX 4
#define RX 3

Akeru akeru(RX, TX);
```

####Powering up

A single line to add in your `void setup()` :

```
akeru.begin(); // returns 1 when everything went ok
```

####Enabling/Disabling echo

To see AT commands and their answers : `akeru.echoOn();`

To hide AT commands and their answers : `akeru.echoOff();`

####Sending data

Data is sent to the Sigfox network in hexadecimal format, and the payload has to be a String of all elements you want to send. To ensure proper conversion of your variables, you can use `akeru.toHex()` method :

```
int val = analogRead(0);
String valString = akeru.toHex(val);
akeru.sendPayload(varString);
```
Note that if you send a array of `char` you need to provide its size in order to convert it :
```
char array[] = "Hello world";
String arrayString= akeru.toHex(array, sizeof(array));
akeru.sendPayload(arrayString);
```




