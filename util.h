#ifndef __UTIL_H__
#define __UTIL_H__

void copyFpn( fpn_t src, fpn_t dest );
error_e toFpn( uint16_t pre, uint16_t post, fpn_t out );
error_e toDFpn( uint16_t pre, uint16_t post, fpn_t out );
int8_t isLarger( fpn_t a, fpn_t b );

#else
	#error DOUBLE INCLUDE OF __UTIL_H__
#endif // __UTIL_H__
