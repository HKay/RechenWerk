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



// add fixed point numbers 'a' and 'b' into 'result'
error_e longAdd( fpn_t a, fpn_t b, fpn_t result ) {
	int16_t i;
	int16_t index;
	uint8_t carry=0;

	if((a != result) && (b!=result)) {
		// the result is not to be stored in either a or b
		toFpn( 0, 0, result );
	}

	// add digit by digit from least to most significant
	for( i=0; i < PRECISION; i++ ) {
		result[i] = a[i] + b[i];
		if( carry ) {
			result[i] += 1;
			carry = 0;
		}

		// carry
		if( result[i] > 9 ) {
			result[i] -= 10;
			carry = 1;
		}
	}
	if( carry ) {
		// still one carry left over that doesn't fit into the memory
		return ERROR_OVERFLOW;
	}
	return OK;
}



error_e longSub( fpn_t m /* minuend */, fpn_t s /* subtrahend */, fpn_t r /* result */ ) {
	uint16_t i, index;
	uint8_t carry = 0; // subtract '-1' from the next digit

	// this function does not support negative values
	// 'm' must be larger than 's' to avoid just that
	if( isLarger( m, s) == -1 ) {
		return ERROR_UNDERFLOW;
	}

	if((m != r) && (s!=r)) {
		// the result is not to be stored in either a or b
		toFpn( 0, 0, r );
	}

	// subtract back to front
	for( i=0; i < PRECISION; i++ ) {
		if( carry ) {
			if( m[i]-carry < s[i]) {
				carry = 1;
				r[i] = m[i]+10 -s[i] -1;
			}
			else {
				carry = 0;
				r[i] = m[i] -s[i] -1;
			}
		}
		else {
			if( m[i] < s[i] ) {
				carry = 1;
				r[i] = m[i]+10 - s[i];
			}
			else {
				carry = 0;
				r[i] = m[i] - s[i];
			}
		} // carry
	} // for

	if( carry ) {
		// one carry is left over
		// should never happen, due to check at the beginning
		return ERROR_UNDERFLOW;
	}

	return OK;
}



error_e longMul( fpn_t a, fpn_t b, fpn_t result ) {
	// We need double precision to account for all the possible carries
	uint16_t i, j;
	uint8_t digit_buf, carry;
	dfpn_t buf;

	toDFpn( 0, 0, buf );

	for( i=0; i<PRECISION; i++ ) {
		for( j=0,carry=0; j<PRECISION; j++ ) {
			digit_buf = (a[i] * b[j]) + carry;
			carry = 0;
			while( digit_buf > 9 ) {
				carry += 1;
				digit_buf -= 10;
			}
			buf[j+i] += digit_buf;
		}

		if( carry ) {
			// we are at the highest digit
			// but still have a carry left over
			return ERROR_OVERFLOW;
		}
	}


	for( i=0; i<PRECISION; i++ ) {
		result[i] = buf[i+(DOUBLE_PRECISION-PRECISION)];
	}
	return OK;
}



/*


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

