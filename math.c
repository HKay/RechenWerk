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



static fpn_t temp1;
static fpn_t temp2;



// add fixed point number 'b' to 'a'
void longAddInto( fpn_t *a, fpn_t *b ) {
	int16_t i;
	int16_t index;

	a->num += b->num;

	// add digit by digit from back to front
	for( i=0; i < PRECISION; i++ ) {
		index = PRECISION -i -1;
		a->frac[index] += b->frac[index];

		// carry
		if( a->frac[index] > 9 ) {
			a->frac[index] -= 10;

			if( index > 0 ) {
				a->frac[index -1] += 1;
			}
			else {
				a->num += 1;
			}
		}
	}
}



// subtract 'b' from 'a'
void longSubFrom( fpn_t *m /* minuend */, fpn_t *s /* subtrahend */ ) {
	uint16_t i, index;
	uint8_t carry = 0;

	// 'm' must be larger than 's' to avoid negative values
	if( isLarger( m, s) == -1 ) {
		toFpn(65535, m);
		return;
	}

	// subtract back to front
	for( i=0; i < PRECISION; i++ ) {
		index = (PRECISION-1) -i;

		if( !carry ) {
			if( m->frac[index] >= s->frac[index] ) {
				carry = 0;
				m->frac[index] -= s->frac[index];
			}
			else {
				carry = 1;
				m->frac[index] += 10;
				m->frac[index] -= s->frac[index];
			}
		}
		else {
			if( m->frac[index] >= (s->frac[index]+1) ) {
				carry = 0;
				m->frac[index] -= (s->frac[index] +1);
			}
			else {
				carry = 1;
				m->frac[index] += 10;
				m->frac[index] -= (s->frac[index] +1);
			}
		} // carry
	} // for

	// last digit subtracts from integer part
	if( !carry ) {
		m->num -= s->num; // positive by definition
	}
	else {
		m->num -= (s->num +1);
	}
	return;
}



void longDivFrom( fpn_t *numerator, fpn_t *denominator ) {
	uint16_t i;
	uint16_t temp1_index;
	uint16_t temp2_index;

	for( i=0; i < PRECISION; i++ ) {
		// numerator is supposed to be smaller than denominator by far.
		; // TODO
	}
}



// shift digits right once
void _longDivBy10( fpn_t *a ) {
	uint16_t i;

	for( i=0; i < PRECISION; i++ ) {
		a->frac[PRECISION -i] = a->frac[PRECISION -i -1];
	}
	// shift last digit into byte array
	a->frac[0] = a->num % 10;
	a->num /= 10;
}






