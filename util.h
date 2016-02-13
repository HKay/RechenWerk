#ifndef __UTIL_H__
#define __UTIL_H__

void toFpn( uint16_t in, fpn_t *out );
int8_t isLarger( fpn_t *a, fpn_t *b );

#else
	#error DOUBLE INCLUDE OF __UTIL_H__
#endif // __UTIL_H__
