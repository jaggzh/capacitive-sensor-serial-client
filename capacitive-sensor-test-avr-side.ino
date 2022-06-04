/* by jaggz.h {who is at} gmail.com
 * 2022-06-05
 * This is Copyright GPL3.0, with the one change that I am not requiring
 * the copy of GPL3.0 to be included with it. (I think that's one of their
 * conditions).
 */

#include <Arduino.h>
#include <TXOnlySerial.h>

#include <.h>
#include "defs.h"

/*
Todo:
   AVR: A0 = Transmit to ESP
 ESP32: UART RX: SD3 / gpio10 = Receive from AVR
*/

#define TXPIN A0
// #define RXPIN A1 /* Dummy pin. We're not rx'ing */

TXOnlySerial ser(TXPIN); // RX, TX

uint16_t ser_counter=0;

void setup() {
	Serial.begin(115200);
	ser.begin(9600);
}
void loop() {
	static uint8_t i=0;
	i++;
	/* if (ser.available()) { */
		Serial.write("Writing\n");
		ser.write(i);
	/* } else { */
	/* 	Serial.write("No ser.available()\n"); */
	/* } */
}

