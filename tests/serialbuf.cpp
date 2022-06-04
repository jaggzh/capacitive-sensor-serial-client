#define SERMAG_DEBUG
#include "SerialMagicChunks.h"

#include <stdint.h>
#include <stdio.h>
class Serious {
    public:
		Serious();
		void write(uint8_t);
};
Serious::Serious() { }
void Serious::write(uint8_t c) {
    printf(" C: %d\n", c);
}

int main() {
	Serious dog; /* test serial class */
	SerialMagic ser(&(dog.write), 2);
	for (int i=65; i<75; i++) ser.add((uint16_t)i);
}

