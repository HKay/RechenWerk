#ifndef __MATH_H__
#define __MATH_H__

#ifndef PRE_POINT_DIGITS
	#define PRE_POINT_DIGITS  2
#endif
#ifndef POST_POINT_DIGITS
	#define POST_POINT_DIGITS 200
#endif

#define DOUBLE_POST_POINT_DIGITS (POST_POINT_DIGITS*2)

#define PRECISION (PRE_POINT_DIGITS + POST_POINT_DIGITS)
#define DOUBLE_PRECISION (PRE_POINT_DIGITS + DOUBLE_POST_POINT_DIGITS)



typedef uint8_t fpn_t[PRECISION]; // little endian
typedef uint8_t dfpn_t[DOUBLE_PRECISION]; // little endian

typedef enum {
	OK=1,
	ERROR_OVERFLOW=2,
	ERROR_UNDERFLOW=3
} error_e;



error_e longAdd( fpn_t a, fpn_t b, fpn_t result );
error_e longSub( fpn_t minuend, fpn_t subtrahend, fpn_t result );
error_e longMul( fpn_t a, fpn_t b, fpn_t result );
void longDivFrom( fpn_t *numerator, fpn_t *denominator );

#else
	#error DOUBLE INCLUDE OF __MATH_H__
#endif // __MATH_H__
