/* by jaggz.h {who is at} gmail.com
 * 2022-06-05
 * This is Copyright GPL3.0, with the one change that I am not requiring
 * the copy of GPL3.0 to be included with it. (I think that's one of their
 * conditions).
 */
#include <Arduino.h>
#include <TXOnlySerial.h>

#include "ser_send.h"
#include "serial_defs.h"

void ser_add(TXOnlySerial ser, uint8_t c);
void _ser_send_startseq(TXOnlySerial ser);
void _ser_send_endseq(TXOnlySerial ser);

/* Packages with start/end sequences can hold this many bytes.
 * Override with ser_set_chunk_size(uint16_t newsize);
 * *** Caller must handle alignment  ***
 * If the chunk size is 4 bytes, and the caller has written 1 byte,
 * then 3 are available before a send.
 * In this case, if a uint32_t is sent, there's no room, so the
 * library will send 0's to complete the current chunk,
 * then it'll add the uint32_t.
 * (I have not yet determined if the new uint32_t will trigger an
 * immediate send, since the buffer will already be full).
 */
int _ser_chunk_size=4;

void ser_set_chunk_size(uint16_t newsize) {
	_ser_chunk_size = newsize;
}

void ser_add(TXOnlySerial ser, uint8_t c) {
	if (!ser_counter) ser_send_startseq(ser);
	ser_counter++;
	ser.write(c);
}

void _ser_send_startseq(TXOnlySerial ser) {
	ser.write(SER_STSEQ1);
	ser.write(SER_STSEQ2);
}
void _ser_send_endseq(TXOnlySerial ser) {
	ser.write(SER_ENSEQ1);
	ser.write(SER_ENSEQ2);
}
