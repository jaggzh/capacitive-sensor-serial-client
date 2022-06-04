tests: serialbuf_run

serialbuf_run: serialbuf
	./serialbuf

serialbuf: serialbuf.cpp
	g++ --std=c++11 -o $@ $^

vi:
	vi \
		Makefile \
		serialbuf.cpp \
		../SerialMagicChunks.h
