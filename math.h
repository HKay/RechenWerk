#ifndef __MATH_H__
#define __MATH_H__

#ifndef PRE_POINT_DIGITS
	#define PRE_POINT_DIGITS  2
	#warning "hit!"
#endif
#ifndef POST_POINT_DIGITS
	#define POST_POINT_DIGITS 200
#endif

#define PRECISION (PRE_POINT_DIGITS + POST_POINT_DIGITS)
#define DOUBLE_PRECISION (PRECISION*2)



typedef uint8_t fpn_t[PRECISION]; // little endian
typedef uint8_t dfpn_t[DOUBLE_PRECISION]; // little endian

typedef enum {
	OK=1,
	ERROR_OVERFLOW=2,
	ERROR_UNDERFLOW=3
} error_e;



error_e longAdd( fpn_t a, fpn_t b, fpn_t result );
void longSubFrom( fpn_t *a, fpn_t *b );

error_e longMultiply( fpn_t *a, fpn_t *b, fpn_t *result );
void longDivFrom( fpn_t *numerator, fpn_t *denominator );

#else
	#error DOUBLE INCLUDE OF __MATH_H__
#endif // __MATH_H__
