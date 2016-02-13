/*
* -------------------------------------------------------------------------------------------
* "THE MATE-WARE LICENSE" (Revision 42):
* Daniel Steuer <daniel.steuer@bingo-ev.de> schrieb diese Datei.
* Solange Sie diesen Vermerk nicht entfernen, können Sie mit dem Material machen,
* was Sie möchten. Wenn wir uns eines Tages treffen und Sie denken, das Material ist es wert,
* können Sie mir dafür eine Club-Mate ausgeben. Daniel Steuer
* -------------------------------------------------------------------------------------------
*/
#include <stdint.h>
#include "math.h"
#include "util.h"

// convert number to fixed point number
void toFpn( uint16_t in, fpn_t *out ) {
	uint16_t i;

	out->num = in;

	// zero out the rest of the number
	for( i=0; i < PRECISION; i++ ) {
		out->frac[i] = 0;
	}
}



// compare two fixed point numbers
int8_t isLarger( fpn_t *a, fpn_t *b ) {
	uint16_t i;

	if( a->num != b->num ) {
		if( a->num > b->num )
			return 1;
		else
			return -1;
	}

	for( i=0; i < PRECISION; i++ ) {
		if( a->frac[i] > b->frac[i] ) {
			return 1;
		}
		else if ( a->frac[i] < b->frac[i] ) {
			return -1;
		}
	}

	return 0; // numbers are equal
}
