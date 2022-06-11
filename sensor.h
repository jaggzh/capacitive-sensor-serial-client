#ifndef _IN_SENSOR_H
#define _IN_SENSOR_H

/* #define DEBUG */

#ifndef _IN_SENSOR_C
extern float vavg;
extern float longavg;
extern long raw_reading;
#ifdef DEBUG
	extern unsigned int debug_skipreads;
#endif
#endif

int loop_sensor(unsigned long now); // sets vavg and longavg
void setup_sensor();

#endif

