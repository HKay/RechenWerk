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
void toFpn( uint16_t pre, uint16_t post, fpn_t out ) {
	// this is only used by the testsuit -> no error handling
	// basically we count the digits in the numbers handed to us
	// and copy them into the array
	uint16_t i, digits;
	uint16_t buffer;


	// zero out the output number first
	for( i=0; i < PRECISION; i++ ) {
		out[i] = 0;
	}

	// count digits in pre and post and split them into digits for copying
	buffer  = pre;
	for( i=0; i<PRE_POINT_DIGITS; i++ ) {
		out[(POST_POINT_DIGITS) +i] = buffer%10;
		buffer /= 10;
	}

	// count number of digits;
	buffer = post;
	digits=0;
	while( buffer > 9 ) {
		buffer /= 10;
		digits++;
	}

	buffer = post;
	for( i=(POST_POINT_DIGITS-1)-digits; i<POST_POINT_DIGITS; i++ ) {
		out[i] = buffer%10;
		buffer /= 10;
	}
}
/*

// convert number to double precision fixed point number
void toDFpn( uint16_t in, dfpn_t *out ) {
	uint16_t i;

	out->num = in;

	// zero out the rest of the number
	for( i=0; i < PRECISION*2; i++ ) {
		out->frac[i] = 0;
	}
}

*/
// compare two fixed point numbers
int8_t isLarger( fpn_t a, fpn_t b ) {
	uint16_t i;

	for( i=0; i<PRECISION; i++ ) {
		if( a[(PRECISION-1) -i] > b[(PRECISION-1) -i]) {
			return 1;
		}
		else if( a[(PRECISION-1) -i] < b[(PRECISION-1) -i]) {
			return -1;
		}
	}

	return 0; // numbers are equal
}
