/* by jaggz.h {who is at} gmail.com
 * 2022-06-05
 * This is Copyright GPL3.0, with the one change that I am not requiring
 * the copy of GPL3.0 to be included with it. (I think that's one of their
 * conditions).
 */

#include <Arduino.h>
#include <TXOnlySerial.h>
#include <PrintHero.h>

#define MAGICCHUNK_DEBUG
#include <MagicSerialChunk.h>

#include "sensor.h"


/*
Todo:
   AVR: A0 = Transmit to ESP
 ESP32: UART RX: SD3 / gpio10 = Receive from AVR
*/

#define TXPIN A0
#define RXPIN A2 /* We might not be RX'ing */
#define CHUNKSIZE 4
#define DELAY_SERIAL_OUTPUT_MS 1
#define SENSOR_BAUD 57600


TXOnlySerial ser(TXPIN); // (RX,TX) if using RX+TX, or SoftwareSerial
struct SerialChunk chunker_real;
struct SerialChunk *chunker = &chunker_real;

void write_cb(struct SerialChunk *sp, uint8_t c) {
	static char wrap=0;
	/* Serial.write("Writing "); */
	/* if (wrap < 16) { */
	/* 	spl((uint16_t) c); */
	/* 	/1* sp(' '); *1/ */
	/* 	wrap++; */
	/* } else { */
	/* 	spl((uint16_t) c); */
	/* 	wrap=0; */
	/* } */
	ser.write(c);
}

void setup() {
	Serial.begin(115200);
	ser.begin(SENSOR_BAUD);
	// `serial_chunk_init(SerialChunk*, unsigned int, void (*)(SerialChunk*, unsigned char))'
	serial_chunk_init(chunker, CHUNKSIZE, &write_cb);
	// serial_chunk_init(SerialChunk*, unsigned int, void (*)(SerialChunk*, unsigned char))'
}
void loop() {
	unsigned long now=millis();
	static long last_ser_output=now;
	/* static uint8_t i=0; */
	/* i++; */
	static unsigned long ctr=0;
	int updated_flag = loop_sensor(now);
	if (now - last_ser_output > DELAY_SERIAL_OUTPUT_MS) {
		if (updated_flag) { // did anything new happen anyway?
			/* chunker->add(chunker, (uint8_t) now); // <-- Calls write_cb() */
			/* chunker->add(chunker, longavg); // <-- Calls write_cb() */
			/* chunker->add(chunker, vavg); // <-- Calls write_cb() */

			// Add bytes of uint16_t
			chunker->add(chunker,  raw_reading & 0xff); // <-- Calls write_cb() */
			chunker->add(chunker, (raw_reading >> 8) && 0xff); // <-- Calls write_cb() */
			DSPL(raw_reading);

			/* chunker->add(chunker, ctr & 0xff); */
			/* ctr++; */
			/* chunker->add(chunker, debug_skipreads & 0xff); */
			/* chunker->add(chunker, (debug_skipreads>>8) & 0xff); */
		}
	}
}

