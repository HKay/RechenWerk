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
	fpn_t tmp;
	toFpn( 0, &tmp);

	CU_ASSERT_EQUAL( tmp.num, 0 );
	// check for uninitialised memory
	for( i=0; i < PRECISION; i++ ) {
		CU_ASSERT_EQUAL( tmp.frac[i], 0 );
	}
}



void test_fpn1( void ) {
	// convert regular number to fpn
	uint16_t i;
	fpn_t tmp;
	toFpn( 5, &tmp);

	CU_ASSERT_EQUAL( tmp.num, 5 );
	// check for uninitialised memory
	for( i=0; i < PRECISION; i++ ) {
		CU_ASSERT_EQUAL( tmp.frac[i], 0 );
	}
}



void test_fpn2( void ) {
	// convert negative(huge) number to fpn
	uint16_t i;
	fpn_t tmp;
	toFpn( -1, &tmp);

	CU_ASSERT_EQUAL( tmp.num, 65535 );
	// check for uninitialised memory
	for( i=0; i < PRECISION; i++ ) {
		CU_ASSERT_EQUAL( tmp.frac[i], 0 );
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

	// this relies on 'tofpn()' test to succeed
	toFpn(0, &zero);
	toFpn(1, &one);

	CU_ASSERT_EQUAL( isLarger(&zero, &one ), -1 );
	CU_ASSERT_EQUAL( isLarger(&one,  &zero),  1 );
	CU_ASSERT_EQUAL( isLarger(&zero, &zero),  0 );
}

void test_isLarger1( void ) {
	// compare with differences after the point
	fpn_t one;
	fpn_t zero;
	fpn_t really_small1;
	fpn_t really_small2;
	fpn_t nearly_big;

	// zero out all digits
	toFpn(0, &zero);
	toFpn(1, &one);
	toFpn(0, &really_small1);
	toFpn(0, &really_small2);
	toFpn(0, &nearly_big);

	really_small1.frac[PRECISION-1] = 1; // 0.00...01
	really_small2.frac[PRECISION-1] = 2; // 0.00...02
	nearly_big.frac[0] = 9; // 0.900...

	CU_ASSERT_EQUAL( isLarger(&really_small1, &zero),           1 );
	CU_ASSERT_EQUAL( isLarger(&really_small1, &really_small2), -1 );
}



void test_isLarger2( void ) {
	// compare with differences after the point
	fpn_t one;
	fpn_t really_small;
	fpn_t nearly_big;

	// zero out all digits
	toFpn(0, &really_small);
	toFpn(0, &nearly_big);
	toFpn(0, &one);

	// assign values
	one.num = 1;
	really_small.frac[PRECISION-1] = 1; // 0.00...01
	nearly_big.frac[0] = 9; // 0.900...

	CU_ASSERT_EQUAL( isLarger(&one,           &nearly_big),  1 );
	CU_ASSERT_EQUAL( isLarger(&really_small,  &one),        -1 );
}
