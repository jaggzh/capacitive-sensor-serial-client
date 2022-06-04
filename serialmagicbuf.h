#ifndef _SERIALMAGIC_H
#define _SERIALMAGIC_H
#include <Arduino.h>

// Default size of chunks to send, in bytes, surrounded
// by start and end sequencs
// If not provided at object instantiation:
#define SERIAL_MAGIC_DEFAULT_CHUNKSIZE 4
#define SERIAL_MAGIC_DEFAULT_STSEQ1 0x02
#define SERIAL_MAGIC_DEFAULT_STSEQ2 0xFE
#define SERIAL_MAGIC_DEFAULT_ENSEQ1 0x03
#define SERIAL_MAGIC_DEFAULT_ENSEQ2 0xFD

template <class T>
class SerialMagic {
private:
	uint16_t _chunksize;
	uint16_t _ctr;
	T _ser;
	uint8_t _stseq1, _stseq2, _enseq1, _enseq2;

public:
	SerialMagic(T ser,
	            uint16_t chunksize=SERIAL_MAGIC_DEFAULT_CHUNKSIZE,
	            uint8_t  stseq1=SERIAL_MAGIC_DEFAULT_STSEQ1,
	            uint8_t  stseq2=SERIAL_MAGIC_DEFAULT_STSEQ2,
	            uint8_t  enseq1=SERIAL_MAGIC_DEFAULT_ENSEQ1,
	            uint8_t  enseq2=SERIAL_MAGIC_DEFAULT_ENSEQ2);
	void set_chunk_size(uint16_t newsize);
	void add(uint8_t c);
	void add(uint16_t v);
}

}; // /class SerialMagic

template <class T> SerialMagic<T>::SerialMagic(T ser,
                                               uint16_t chunksize,
                                               uint8_t  stseq1,
                                               uint8_t  stseq2,
                                               uint8_t  enseq1,
                                               uint8_t  enseq2) {
	_ser = ser; // store serial object
	_chunksize = chunksize;
	_stseq1 = stseq1;
	_stseq2 = stseq2;
	_enseq1 = enseq1;
	_enseq2 = enseq2;
}

template <class T> SerialMagic<T>::set_chunk_size(uint16_t newsize) {
	_chunksize = newsize;
	_ctr = 0;
}

template <class T> SerialMagic<T>::_send_startseq(void)
	{ _ser.write(_stseq1); _ser.write(stseq2); }
template <class T> SerialMagic<T>::_send_endseq(void)
	{ _ser.write(_enseq1); _ser.write(enseq2); }

template <class T> SerialMagic<T>::add(uint8_t c) {
	if (!_ctr) _send_startseq();
	_ctr++;
	_ser.write(v);
	if (_ctr >= _chunksize) {
		_send_endseq();
		_ctr=0;
	}
}
/* template <class T> SerialMagic<T>::add(uint16_t v) { */
/* 	uint8_t *p = (uint8_t *)v; */
/* 	add(p[0]); */
/* 	add(p[1]); */
/* } */
template <class T, class U> SerialMagic<T>::add(U v) {
	for (uint8_t i=0; i<sizeof(U); i++)
		add(*((uint8_t *)v)[i]);
}

#endif  // _SERIALMAGIC_H
