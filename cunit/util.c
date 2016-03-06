#include <stdio.h>
#include <stdint.h>
#include "../math.h"
#include "../util.h"
#include "unit.h"



// number: 12.345678
// memory: 87654321
void longPrint( fpn_t a ) {
	uint32_t i;

	for( i=PRECISION-1; i>=POST_POINT_DIGITS; i-- ) {
		printf( "%i", a[i] );
	}
	printf( "." );
	for( i=POST_POINT_DIGITS-1; i>0; i-- ) {
		printf( "%i", a[i] );
	}
	printf( "%i", a[i] );
	printf( "\n" );
}

void longPrint2( fpn_t a ) {
	uint32_t i;

	printf( "\n" );
	printf( "\n" );
	for( i=0; i<PRECISION; i++ ) {
		printf( "%i", a[i] );
	}
	printf( "\n" );
}
