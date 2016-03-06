/*
* -------------------------------------------------------------------------------------------
* "THE MATE-WARE LICENSE" (Revision 42):
* Daniel Steuer <daniel.steuer@bingo-ev.de> schrieb diese Datei.
* Solange Sie diesen Vermerk nicht entfernen, können Sie mit dem Material machen,
* was Sie möchten. Wenn wir uns eines Tages treffen und Sie denken, das Material ist es wert,
* können Sie mir dafür eine Club-Mate ausgeben. Daniel Steuer
* -------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "math.h"
#include "util.h"



fpn_t e;
fpn_t lastTerm;

/*

void longPrint( fpn_t a ) {
	uint32_t i;

	for( i=(PRECISION-PRE_POINT_DIGITS); i<PRECISION; i++ ) {
		printf( "%i", a[i] );
	}
	printf( "." );
	for( i=0; i<(PRECISION-PRE_POINT_DIGITS); i++ ) {
		printf( "%i", a[i] );
	}
	printf( "\n" );
}
*/


int main( void ) {
	uint32_t i;

//	toFpn( 0, &e);

//	e.num = 1;
	lastTerm[PRECISION-1] = 1;



/*	for( i=0; i < 10; i++ ) {
		longDiv( lastTerm, i );
		longAdd( e, lastTerm );

		printf( "e=" );
		longPrint( e );
	}
*/

	return 0;
}



void computeE( void ) {
	// compute e:
	// this is over when the number doesn't
	// change anymore from step to step
	//
	//     --  1
	// e = \  ----
	//     /_  n!
	//

	;

}



void computePi ( void ) {
	;
}
