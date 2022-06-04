#ifndef _SERIALMAGIC_H
#define _SERIALMAGIC_H

#define SERMAG_DEBUG

#ifdef SERMAG_DEBUG
	#define MDPRINTF(...) printf(__VA_ARGS__)
#else
	#define MDPRINTF(...)
#endif

#include <stdint.h>
#include <stdio.h>
/* #include <Arduino.h> */

// Default size of chunks to send, in bytes, surrounded
// by start and end sequencs
// If not provided at object instantiation:
#define SERIAL_MAGIC_DEFAULT_CHUNKSIZE 4
#define SERIAL_MAGIC_DEFAULT_STSEQ1 (0x00+2)
#define SERIAL_MAGIC_DEFAULT_STSEQ2 (0xFF-2)
#define SERIAL_MAGIC_DEFAULT_ENSEQ1 (0x00+3)
#define SERIAL_MAGIC_DEFAULT_ENSEQ2 (0xFF-3)

template <class T>
class SerialMagic {
private:
	uint16_t _chunksize;
	uint16_t _ctr;
	uint8_t _stseq1, _stseq2, _enseq1, _enseq2;

public:
	T _ser; // They can access their own object for other calls
	SerialMagic(T ser,
	            uint16_t chunksize=SERIAL_MAGIC_DEFAULT_CHUNKSIZE,
	            uint8_t  stseq1=SERIAL_MAGIC_DEFAULT_STSEQ1,
	            uint8_t  stseq2=SERIAL_MAGIC_DEFAULT_STSEQ2,
	            uint8_t  enseq1=SERIAL_MAGIC_DEFAULT_ENSEQ1,
	            uint8_t  enseq2=SERIAL_MAGIC_DEFAULT_ENSEQ2);
	void set_chunk_size(uint16_t newsize);
	void _send_startseq(void);
	void _send_endseq(void);
	void add(uint8_t);
	void add(int8_t);
	/* void add(uint16_t); */
	/* void add(int16_t); */
	/* void add(uint32_t); */
	/* void add(int32_t); */
	/* void add(float); */
	/* void add(double); */
    template <class U> void add(U);
}; // /class SerialMagic

template <class T> SerialMagic<T>::SerialMagic(T ser,
                                               uint16_t chunksize,
                                               uint8_t  stseq1,
                                               uint8_t  stseq2,
                                               uint8_t  enseq1,
                                               uint8_t  enseq2) {
	_ctr = 0;
	_ser = ser; // store serial object
	_chunksize = chunksize;
	_stseq1 = stseq1;
	_stseq2 = stseq2;
	_enseq1 = enseq1;
	_enseq2 = enseq2;
}

template <class T> void SerialMagic<T>::set_chunk_size(uint16_t newsize) {
	_chunksize = newsize;
	_ctr = 0;
}

template <class T> void SerialMagic<T>::_send_startseq(void)
	{ MDPRINTF("Sending Start Sequence:\n");  _ser.write(_stseq1); _ser.write(_stseq2); }
template <class T> void SerialMagic<T>::_send_endseq(void)
	{ MDPRINTF("Sending End Sequence:\n"); _ser.write(_enseq1); _ser.write(_enseq2); }


template <class T> void SerialMagic<T>::add(uint8_t c) {
	if (!_ctr) _send_startseq();
	_ctr++;
	MDPRINTF("Sending a char (%d/%d):\n", _ctr, _chunksize);
	_ser.write(c);
	if (_ctr >= _chunksize) {
		_send_endseq();
		_ctr=0;
	}
}
template <class T> void SerialMagic<T>::add(int8_t v) { add((uint8_t)v); }

/*
template <class T> void SerialMagic<T>::add(uint16_t v) {
	uint8_t *p = (uint8_t *)&v; add(p[0]); add(p[1]);
}
template <class T> void SerialMagic<T>::add(int16_t v) { add((uint16_t)v); }


template <class T> void SerialMagic<T>::add(uint32_t v) {
	uint8_t *p = (uint8_t *)&v; add(p[0]); add(p[1]); add(p[2]); add(p[3]);
}
template <class T> void SerialMagic<T>::add(int32_t v) { add((uint32_t)v); }

template <class T> void SerialMagic<T>::add(float v) {
	for (uint8_t i=0; i<sizeof(v); i++)
		add(((uint8_t *)(&v))[i]);
}
template <class T> void SerialMagic<T>::add(double v) {
	for (uint8_t i=0; i<sizeof(v); i++)
		add(((uint8_t *)(&v))[i]);
}
*/
template <class T>
template <class U>
void SerialMagic<T>::add(U v) {
	for (uint8_t i=0; i<sizeof(v); i++)
		add(((uint8_t *)(&v))[i]);
}



#endif  // _SERIALMAGIC_H

class Serious {
    public:
		Serious();
		void write(uint8_t);
};
Serious::Serious() { }
void Serious::write(uint8_t c) {
    printf("C: %d\n", c);
}

int main() {
	Serious dog;
	SerialMagic<Serious> ser(dog, 4);
	for (int i=65; i<75; i++) ser.add((uint16_t)i);
}

