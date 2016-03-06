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



//static fpn_t temp1;
//static fpn_t temp2;



// add fixed point numbers 'a' and 'b' into 'result'
error_e longAdd( fpn_t a, fpn_t b, fpn_t result ) {
	int16_t i;
	int16_t index;

	// add digit by digit from least to most significant
	for( i=0; i < PRECISION; i++ ) {
		result[i] = a[i] + b[i];

		// carry
		if( result[i] > 9 ) {
			result[i] -= 10;

			if( i < PRECISION ) {
				result[i+1] += 1;
			}
			else {
				return ERROR_OVERFLOW;
			}
		}
	}
	return OK;
}


// subtract 'b' from 'a'
//void longSubFrom( fpn_t *m /* minuend */, fpn_t *s /* subtrahend */ ) {
/*	uint16_t i, index;
	uint8_t carry = 0; // subtract '-1' from the next digit

	// 'm' must be larger than 's' to avoid negative values
	if( isLarger( m, s) == -1 ) {
		toFpn(65535, m); // signal error
		return;
	}

	// subtract back to front
	for( i=0; i < PRECISION; i++ ) {
		index = (PRECISION-1) -i;

		if( carry ) {
			// we have a carry so the minuend must be larger by 1
			if( m->frac[index] >= (s->frac[index] +1) ) {
				carry = 0;
				m->frac[index] -= (s->frac[index] +1);
			}
			else {
				carry = 1;
				m->frac[index] += 10;
				m->frac[index] -= (s->frac[index] +1);
			}
		}
		else {
			if( m->frac[index] >= s->frac[index] ) {
				carry = 0;
				m->frac[index] -= s->frac[index];
			}
			else {
				carry = 1;
				m->frac[index] += 10;
				m->frac[index] -= s->frac[index];
			}
		} // carry
	} // for

	// last digit subtracts from integer part
	if( carry ) {
		m->num -= (s->num +1);
	}
	else {
		m->num -= s->num; // positive by definition
	}
	return;
}



error_e longMultiply( fpn_t *a, fpn_t *b, fpn_t *result ) {
	// We need double precision to account for all the possible carries
	uint16_t i, j;
	uint8_t digit_buf;
	dfpn_t fpn_buf;

	toDFpn( 0, &fpn_buf );

	for( i=0; i<PRECISION; i++ ) {
		for( j=0; i<PRECISION; i++ ) {
			// start from the very back and multiply to the front
			// a bit further every time
			digit_buf = a->frac[PRECISION-1 -j] * b->frac[PRECISION-1 -j];
			fpn_buf.frac[DOUBLE_PRECISION-1 -i -j] = fpn_buf.frac[DOUBLE_PRECISION-1 -i -j] + digit_buf;
			while( fpn_buf.frac[DOUBLE_PRECISION-1 -i -j] > 9) {
				if( (i+j) > DOUBLE_PRECISION ) { // TODO: CHECK LIMITS
					fpn_buf.num += 1; // move carry over decimal point
				}
				else {
					fpn_buf.frac[DOUBLE_PRECISION-1 -i -j -1] += 1; // move carry
				}
				fpn_buf.frac[DOUBLE_PRECISION-1 -i -j] -= 10;
			}
		}
	}

	result->num = a->num * b->num;

	return OK;
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






*/

