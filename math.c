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



// In all math functions here output 'result'
// can be the same variable as used as the input



error_e longAdd( fpn_t a, fpn_t b, fpn_t result ) {
	// add fixed point numbers 'a' and 'b' into 'result'
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



error_e longMul10( fpn_t a, fpn_t result ) {
	// since this is binary coded decimals we just have to left shift all digits
	error_e e;
	uint16_t i;

	if( a[PRECISION-1] != 0 ) {
		return ERROR_OVERFLOW;
	}

	for( i=PRECISION-1; i > 0; i-- ) {
		result[i] = a[i-1];
	}
	result[0] = 0;

	return OK;
}



error_e longDiv10( fpn_t n /* numerator */, fpn_t result ) {
	// since this is binary coded decimals we just have to right shift all digits
	error_e e;
	uint16_t i;

	for( i=0; i < PRECISION-1; i++ ) {
		result[i] = n[i +1];
	}
	result[PRECISION-1] = 0;

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



error_e longDiv( fpn_t n /* numerator */, fpn_t d /* denominator */, fpn_t result ) {
	error_e e;
	uint16_t i;

	for( i=0; i < PRECISION; i++ ) {
		// numerator is supposed to be smaller than denominator by far.
		; // TODO
	}

	return OK;
}



