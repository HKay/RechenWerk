#ifndef __MATH_H__
#define __MATH_H__

#define PRECISION 99
#define DOUBLE_PRECISION (PRECISION*2)

typedef struct fpn_s {
	uint16_t num; // before decimal point
	uint8_t frac[PRECISION]; // after decimal point
} fpn_t;


typedef struct dfpn_s {
	uint16_t num; // before decimal point
	uint8_t frac[DOUBLE_PRECISION]; // after decimal point
} dfpn_t;

typedef enum {
	OK=1,
	ERROR_OVERFLOW=2,
	ERROR_UNDERFLOW=3
} error_e;



void longAddInto( fpn_t *a, fpn_t *b );
void longSubFrom( fpn_t *a, fpn_t *b );

error_e longMultiply( fpn_t *a, fpn_t *b, fpn_t *result );
void longDivFrom( fpn_t *numerator, fpn_t *denominator );

#else
	#error DOUBLE INCLUDE OF __MATH_H__
#endif // __MATH_H__
