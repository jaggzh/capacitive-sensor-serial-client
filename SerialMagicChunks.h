#ifndef _SERIALMAGIC_H
#define _SERIALMAGIC_H

#define SERMAG_DEBUG

#ifdef SERMAG_DEBUG
	#include <stdint.h>
	#include <stdio.h>
	#define MDPRINTF(...) printf(__VA_ARGS__)
#else
	#define MDPRINTF(...)
#endif

/* #include <Arduino.h> */

// Default size of chunks to send, in bytes, surrounded
// by start and end sequencs
// If not provided at object instantiation:
#define SERIAL_MAGIC_DEFAULT_CHUNKSIZE 4
#define SERIAL_MAGIC_DEFAULT_STSEQ1 (0x00+2)
#define SERIAL_MAGIC_DEFAULT_STSEQ2 (0xFF-2)
#define SERIAL_MAGIC_DEFAULT_ENSEQ1 (0x00+3)
#define SERIAL_MAGIC_DEFAULT_ENSEQ2 (0xFF-3)

class SerialMagic {
private:
	void (*_write_cb)(uint8_t);
	uint16_t _chunksize;
	uint16_t _ctr;
	uint8_t _stseq1, _stseq2, _enseq1, _enseq2;
	void _send_startseq(void);
	void _send_endseq(void);

public:
	// DEL T _ser; // They can access their own object for other calls
	SerialMagic(void (*write_cb)(uint8_t),
	            uint16_t chunksize=SERIAL_MAGIC_DEFAULT_CHUNKSIZE,
	            uint8_t  stseq1=SERIAL_MAGIC_DEFAULT_STSEQ1,
	            uint8_t  stseq2=SERIAL_MAGIC_DEFAULT_STSEQ2,
	            uint8_t  enseq1=SERIAL_MAGIC_DEFAULT_ENSEQ1,
	            uint8_t  enseq2=SERIAL_MAGIC_DEFAULT_ENSEQ2);
	void set_chunk_size(uint16_t newsize);
	void add(uint8_t v);
	void add(int8_t v);
	void add(uint8_t *b, uint16_t len);
}; // /class SerialMagic

SerialMagic::SerialMagic(void (*write_cb)(uint8_t),
                         uint16_t chunksize,
                         uint8_t  stseq1,
                         uint8_t  stseq2,
                         uint8_t  enseq1,
                         uint8_t  enseq2) {
	_ctr = 0;
	//DEL _ser = ser; // store serial object
	_chunksize = chunksize;
	_stseq1 = stseq1;
	_stseq2 = stseq2;
	_enseq1 = enseq1;
	_enseq2 = enseq2;
}

void SerialMagic::set_chunk_size(uint16_t newsize) {
	_chunksize = newsize;
	_ctr = 0;
}

void SerialMagic::_send_startseq(void) {
	MDPRINTF("Sending Start Sequence:\n");
	(*_write_cb)(_stseq1);
	(*_write_cb)(_stseq2);
}
void SerialMagic::_send_endseq(void) {
	MDPRINTF("Sending End Sequence:\n");
	(*_write_cb)(_enseq1);
	(*_write_cb)(_enseq2);
}


void SerialMagic::add(uint8_t c) {
	if (!_ctr) _send_startseq();
	_ctr++;
	MDPRINTF("Sending a char (%d/%d):\n", _ctr, _chunksize);
	(*_write_cb)(c);
	if (_ctr >= _chunksize) {
		_send_endseq();
		_ctr=0;
	}
}
void SerialMagic::add(int8_t v) { add((uint8_t)v); }
void SerialMagic::add(uint8_t *b, uint16_t len) {
	for (uint16_t i=0; i<len; i++) add(b[i]);
}

/* template <class U> */
/* void SerialMagic::add(U v) { */
/* 	for (uint8_t i=0; i<sizeof(v); i++) */
/* 		add(((uint8_t *)(&v))[i]); */
/* } */

#endif  // _SERIALMAGIC_H
