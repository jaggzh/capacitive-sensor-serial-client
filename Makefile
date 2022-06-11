all:
	echo "Try make vi"

vi:
	vi \
		Makefile \
		capacitive-sensor-serial-client.ino \
		sensor.cpp \
		sensor.h \
		~/Arduino/libraries/MagicSerialChunk/src/MagicSerialChunk.c \
		~/Arduino/libraries/MagicSerialChunk/src/MagicSerialChunk.h
