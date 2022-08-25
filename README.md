# Capacitive Sensor Serial Client

I'm using this in a two-MCU system.
One device is a control box using an ESP32.
A separate "button" is a capacitive sensor that's AVR-based
(a Pro Micro 16 / atmega32u4 board).

This is the code that runs on the capacitive sensor/button.  It sends data using one of its pins back to the ESP32 where processing is done, and the control box does its stuff.

The AVR side relies on a couple of my libs:
* MagicSerialChunk: https://github.com/jaggzh/MagicSerialChunk -- Takes -&gt;add() calls and sends them over serial, with leading and trailing magic sequences for some simple (but not 100% reliable) data integrity checking.  (The magic sequences have to be correct on the client and the server, as does the bundle/chunk length or that chunk is ignored).
* PrintHero: https://github.com/jaggzh/PrintHero -- Some convenience defines for printing/serial printing with less typing.  (like sp()  dbsp() (for debug), etc.)
* TXOnlySerial: https://github.com/jaggzh/TXOnlySerial (fork from original https://github.com/felias-fogg/TXOnlySerial) -- This just has the RX code stripped from the Arduino software serial lib, so you don't need both pins. Since we're only sending from our AVR to the ESP32, this allows that.  (Normal serial is fine, just give a dummy/unused pin for RX.)


