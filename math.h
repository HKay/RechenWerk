#ifndef __MATH_H__
#define __MATH_H__

#define PRECISION 99

typedef struct fpn_s {
	uint16_t num; // before decimal point
	uint8_t frac[PRECISION]; // after decimal point
} fpn_t;



void longAddInto( fpn_t *a, fpn_t *b );
void longSubFrom( fpn_t *a, fpn_t *b );

void longMulInto( fpn_t *a, fpn_t *b );
void longDivFrom( fpn_t *numerator, fpn_t *denominator );

#else
	#error DOUBLE INCLUDE OF __MATH_H__
#endif // __MATH_H__
