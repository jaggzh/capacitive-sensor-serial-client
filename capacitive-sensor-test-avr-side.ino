/* by jaggz.h {who is at} gmail.com
 * 2022-06-05
 * This is Copyright GPL3.0, with the one change that I am not requiring
 * the copy of GPL3.0 to be included with it. (I think that's one of their
 * conditions).
 */

#include <Arduino.h>
#include <TXOnlySerial.h>

#include "serialmagic-defs.h"
#include "SerialMagicBuf.h"

/*
Todo:
   AVR: A0 = Transmit to ESP
 ESP32: UART RX: SD3 / gpio10 = Receive from AVR
*/

#define TXPIN A0
// #define RXPIN A1 /* Dummy pin. We're not rx'ing */

SerialMagic<TXOnlySerial> ser(TXPIN); // (RX,TX) if using SoftwareSerial

void setup() {
	Serial.begin(115200);
	ser._ser.begin(9600);
}
void loop() {
	static uint8_t i=0;
	i++;
	Serial.write("Writing\n");
	ser.add(i); // <-- Calls write()
}

