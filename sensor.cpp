#include <Arduino.h>
#include <CapacitiveSensor.h>
#include <PrintHero.h>

#define _IN_SENSOR_C
#include "sensor.h"

#define CAP_TX_PIN A7
#define CAP_RX_PIN A6
#define SMOOTH_DIV 8
#define LONG_SMOOTH_DIV 256
#define DATA_REDUCE_DIV 0

#define CAPSENSE_QUANTITY 16 // higher=more readings=slower but less noisy

// This is to establish a fixed timing for moving avgs and stuff to be consistent
#define DELAY_BETWEEN_CAP_READINGS 6

long raw_reading=0;
float vavg=0;
float longavg=0;
CapacitiveSensor sens(CAP_TX_PIN, CAP_RX_PIN);
int slowctr=0;
#ifdef DEBUG
	unsigned int debug_skipreads=0;
#endif

int loop_sensor(unsigned long now) {
	static unsigned long last_reading_ms=now;

	if (now-last_reading_ms < DELAY_BETWEEN_CAP_READINGS) {
#ifdef DEBUG
		debug_skipreads++;
#endif
		return 0;
	}
	last_reading_ms = now;

	raw_reading =  sens.capacitiveSensorRaw(CAPSENSE_QUANTITY);
	/* vavg += (tot - vavg) / SMOOTH_DIV; */
	/* longavg += (tot - longavg) / LONG_SMOOTH_DIV; */
	/* if (!slowctr) { */
	/* 	/1* sp("val:"); sp(tot); *1/ */
	/* 	dbsp(" vavg:"); dbsp(vavg); */
	/* 	dbsp(" vLavg:"); dbsp(longavg); */
	/* 	/1* sp(" v-lavg:"); sp(vavg-longavg); *1/ */
	/* 	dbspl(""); */
	/* 	/1* spl(vavg-longavg); *1/ */
	/* 	slowctr++; */
	/* } */
	/* if (slowctr >= DATA_REDUCE_DIV) { */
	/* 	slowctr=0; */
	/* } */
	return 1;
}

void setup_sensor() {
	sens.set_CS_AutocaL_Millis(0xFFFFFFFF); // disable calibration
	delay(200); // I think we got a weird first reading unless we waited.
	            // I'm not sure what needed to settle down though.
	// initialize averages storage
	raw_reading = sens.capacitiveSensorRaw(CAPSENSE_QUANTITY);
	vavg = longavg = raw_reading;
}



