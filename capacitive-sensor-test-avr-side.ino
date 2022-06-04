#include <Arduino.h>
#include <TXOnlySerial.h>

#include "serial_defs.h"

/*
Todo:
   AVR: A0 = Transmit to ESP
 ESP32: UART RX: SD3 / gpio10 = Receive from AVR
*/

#define TXPIN A0
#define RXPIN A1 /* Dummy pin. We're not rx'ing */

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

void ser_add(TXOnlySerial ser, uint8_t c) {
	if (!ser_counter) ser_send_startseq(ser);
	ser_counter++;
	ser.write(c);
}

void ser_send_startseq(TXOnlySerial ser) {
	ser.write(SER_STSEQ1);
	ser.write(SER_STSEQ2);
}
void ser_send_endseq(TXOnlySerial ser) {
	ser.write(SER_ENSEQ1);
	ser.write(SER_ENSEQ2);
}
