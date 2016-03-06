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
#include <CUnit/Basic.h>
#include "../math.h"
#include "../util.h"
#include "unit.h"

//
// fpn()
//
int init_fpn_suite( void ) {
	return 0; // success
}



int clean_fpn_suite( void ) {
	return 0; // success
}



void test_fpn0( void ) {
	// convert 0 to fpn
	uint16_t i;
	error_e e;
	fpn_t tmp;
	e = toFpn(0, 0, tmp);

	CU_ASSERT_EQUAL( e, OK );
	// 'check' for uninitialised memory
	for( i=0; i < PRECISION; i++ ) {
		CU_ASSERT_EQUAL( tmp[i], 0 );
	}
}



void test_fpn1( void ) {
	// convert regular number to fpn
	uint16_t i;
	error_e e;
	fpn_t tmp;
	e = toFpn( 5, 3, tmp );

	CU_ASSERT_EQUAL( e, OK );
	// check for uninitialised memory
	for( i=0; i < POST_POINT_DIGITS-2; i++ ) {
		CU_ASSERT_EQUAL( tmp[i], 0 );
	}

	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS-1], 3 ); // most significant post point digit
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS], 5 ); // first post point digit

	// all digits after that
	for( i=POST_POINT_DIGITS+1; i < PRECISION; i++ ) {
		CU_ASSERT_EQUAL( tmp[i], 0 );
	}
}


void test_fpn2( void ) {
	// convert maximum number the function supports to fpn
	uint16_t i;
	fpn_t tmp;
	error_e e;
	e = toFpn( 0xffff, 0xffff, tmp); // 65535.65535
	CU_ASSERT_EQUAL( e, OK );

	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS-5], 5);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS-4], 3);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS-3], 5);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS-2], 5);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS-1], 6);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS], 5);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS+1], 3);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS+2], 5);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS+3], 5);
	CU_ASSERT_EQUAL( tmp[POST_POINT_DIGITS+4], 6);
	// check for uninitialised memory
	for( i=0; i < POST_POINT_DIGITS-6; i++ ) {
		CU_ASSERT_EQUAL( tmp[i], 0 );
	}
	for( i=POST_POINT_DIGITS+5; i < PRECISION; i++ ) {
		CU_ASSERT_EQUAL( tmp[i], 0 );
	}
}



//
// isLarger( )
//
int init_isLarger_suite( void ) {
	return 0; // success
}



int clean_isLarger_suite( void ) {
	return 0; // success
}



void test_isLarger0( void ) {
	// compare with differences before the point
	fpn_t zero;
	fpn_t one;
	fpn_t two;
	fpn_t pretty_big;

	// this relies on 'tofpn()' test to succeed
	toFpn(0, 0, zero);
	toFpn(1, 0, one);
	toFpn(0, 0, pretty_big);
	pretty_big[PRECISION-1] = 1; // 100000.000000..

	CU_ASSERT_EQUAL( isLarger(zero, one),  -1 );
	CU_ASSERT_EQUAL( isLarger(one,  zero),  1 );
	CU_ASSERT_EQUAL( isLarger(zero, zero),  0 );
	CU_ASSERT_EQUAL( isLarger(one,  one),   0 );
	CU_ASSERT_EQUAL( isLarger(one,  two),  -1 );
	CU_ASSERT_EQUAL( isLarger(two,  one),   1 );
}



void test_isLarger1( void ) {
	// compare with differences after the point
	fpn_t one;
	fpn_t zero;
	fpn_t really_small1;
	fpn_t really_small2;
	fpn_t nearly_big;

	// zero out all digits
	toFpn(0, 0, zero);
	toFpn(1, 0, one);
	toFpn(0, 0, really_small1);
	toFpn(0, 0, really_small2);
	toFpn(0, 0, nearly_big);

	really_small1[0] = 1; // 0.00...01
	really_small2[0] = 2; // 0.00...02
	nearly_big[POST_POINT_DIGITS-1] = 9; // 0.900...

	CU_ASSERT_EQUAL( isLarger(really_small2, really_small1),  1 );
	CU_ASSERT_EQUAL( isLarger(really_small1, really_small2), -1 );
	CU_ASSERT_EQUAL( isLarger(really_small1, nearly_big),    -1 );
	CU_ASSERT_EQUAL( isLarger(nearly_big,    nearly_big),     0 );
	CU_ASSERT_EQUAL( isLarger(really_small1, really_small1),  0 );
}



void test_isLarger2( void ) {
	// compare with differences before and after the point
	fpn_t one;
	fpn_t really_small;
	fpn_t nearly_big;
	fpn_t pretty_big;

	// zero out all digits
	toFpn(0, 0, really_small);
	toFpn(0, 0, nearly_big);
	toFpn(1, 0, one);
	toFpn(0, 0, pretty_big);

	// assign values
	really_small[0] = 1; // 0.00...01
	nearly_big[POST_POINT_DIGITS-1] = 9; // 0.900...
	pretty_big[PRECISION-1] = 1; // 100000.000000...

	CU_ASSERT_EQUAL( isLarger(one,          nearly_big),   1 );
	CU_ASSERT_EQUAL( isLarger(really_small, one       ),  -1 );
	CU_ASSERT_EQUAL( isLarger(pretty_big,   nearly_big),   1 );
	CU_ASSERT_EQUAL( isLarger(pretty_big,   really_small), 1 );
}
