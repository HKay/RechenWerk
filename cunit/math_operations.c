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
// longAddInto()
//
int init_longAdd_suite( void ) {
	return 0; // success
}



int clean_longAdd_suite( void ) {
	return 0; // success
}



void test_add0_0( void ) {
	// adding before the decimal point
	fpn_t one;
	fpn_t two;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// 1+2=3
	toFpn( 1, 0, one );
	toFpn( 1, 0, p1 );
	toFpn( 2, 0, two );
	toFpn( 2, 0, p2 );
	toFpn( 3, 0, expect );

	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, one), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, two), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, two), 0 );
}


void test_add0_1( void ) {
	// adding zero
	fpn_t zero;
	fpn_t one;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;


	// 1+0=1
	toFpn( 1, 0, one );
	toFpn( 1, 0, p1 );
	toFpn( 0, 0, zero );
	toFpn( 0, 0, p2 );
	toFpn( 1, 0, expect );

	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, one),  0 );
	CU_ASSERT_EQUAL( isLarger(p2, zero), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, zero), 0 );
}



// This check only passes when
// PRE_POINT_DIGITS < 6
void test_add0_2( void ) {
	// pre point overflow check
	fpn_t big;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	error_e e;

	toFpn( 65535, 0, p1 );
	toFpn( 65535, 0, p2 );
	toFpn( 65535, 0, big );
	// 65535+65535=ERROR_OVERFLOW
	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, ERROR_OVERFLOW );
	CU_ASSERT_EQUAL( isLarger(p1, big), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, big), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, ERROR_OVERFLOW );
	CU_ASSERT_EQUAL( isLarger(p2, big), 0 );
}



void test_add1_0( void ) {
	// adding after the decimal point
	fpn_t p1;
	fpn_t p2;
	fpn_t small;
	fpn_t bigger;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// adding without carry
	// 0.0...01 + 0.0...02 = 0.0...03
	toFpn( 0, 0, p1 );
	toFpn( 0, 0, p2 );
	toFpn( 0, 0, small );
	toFpn( 0, 0, bigger );
	toFpn( 0, 0, expect );

	p1[0] = 1;
	p2[0] = 2;
	small[0] = 1;
	bigger[0] = 2;
	expect[0] = 3;
	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, small), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, bigger), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, bigger), 0 );
}



void test_add1_1( void ) {
	// adding after the decimal point
	fpn_t p1;
	fpn_t p2;
	fpn_t small;
	fpn_t bigger;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// adding with carry to zero
	// 0.09 + 0.01 = 0.10
	toFpn( 0, 0, p1 );
	toFpn( 0, 0, p2 );
	toFpn( 0, 0, small );
	toFpn( 0, 0, bigger );
	toFpn( 0, 0, expect );

	p1[POST_POINT_DIGITS-2] = 9;
	bigger[POST_POINT_DIGITS-2] = 9;
	p2[POST_POINT_DIGITS-2] = 1;
	small[POST_POINT_DIGITS-2] = 1;
	expect[POST_POINT_DIGITS-1] = 1;

	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, bigger), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );
}



void test_add1_2( void ) {
	fpn_t p1;
	fpn_t bigger;
	fpn_t p2;
	fpn_t small;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// adding with carry to non-zero
	// 0.09 + 0.02 = 0.11
	toFpn( 0, 0, p1 );
	toFpn( 0, 0, bigger );
	toFpn( 0, 0, p2 );
	toFpn( 0, 0, small );
	toFpn( 0, 0, expect );

	p1[POST_POINT_DIGITS-2] = 9;
	bigger[POST_POINT_DIGITS-2] = 9;
	p2[POST_POINT_DIGITS-2] = 2;
	small[POST_POINT_DIGITS-2] = 2;
	expect[POST_POINT_DIGITS-1] = 1;
	expect[POST_POINT_DIGITS-2] = 1;

	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, bigger), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );
}



void test_add2_0( void ) {
	// carry jumps the decimalpoint
	uint16_t i;
	fpn_t p1;
	fpn_t p2;
	fpn_t small;
	fpn_t bigger;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// 0.1 + 0.9 = 1.0
	toFpn( 0, 1, p1 );
	toFpn( 0, 1, small );
	toFpn( 0, 9, p2 );
	toFpn( 0, 9, bigger );
	toFpn( 1, 0, expect );

	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, small), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, bigger), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, bigger), 0 );
}



void test_add2_1( void ) {
	// adding before and after the decimal point
	uint16_t i;
	fpn_t p1;
	fpn_t p2;
	fpn_t tiny;
	fpn_t big;
	fpn_t res;
	fpn_t expect;
	error_e e;

	toFpn( 0, 0, p1 );
	toFpn( 0, 0, p2 );
	toFpn( 0, 0, tiny );
	toFpn( 0, 0, big );
	toFpn( 1, 0, expect );

	// carry jumps the decimal point after maximum shift
	// 0.9...99 + 0.0...01 = 1.0

	for( i=0; i<POST_POINT_DIGITS; i++ ) {
		p1[i] = 9;
		big[i] = 9;
	}
	p2[0] = 1;
	tiny[0] = 1;
	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, big), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, tiny), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, tiny), 0 );
}



void test_add2_2( void ) {
	fpn_t p1;
	fpn_t p2;
	fpn_t bigger;
	fpn_t small;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// carry jumps the decimal point to non-zero after point
	// 1.2 + 0.9 = 2.1
	toFpn( 1, 2, p1 );
	toFpn( 1, 2, bigger );
	toFpn( 0, 9, p2 );
	toFpn( 0, 9, small );
	toFpn( 2, 1, expect );

	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, bigger), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );
}



void test_add2_3( void ) {
	uint16_t i;
	fpn_t p1;
	fpn_t pretty_big;
	fpn_t p2;
	fpn_t small;
	fpn_t res;
	error_e e;

	// carry leads to overflow
	// ...999.900... + 0.1 = ERROR_OVERFLOW
	toFpn( 0, 9, p1 );
	toFpn( 0, 9, pretty_big );
	toFpn( 0, 1, p2 );
	toFpn( 0, 1, small );

	for( i=0; i<PRE_POINT_DIGITS; i++ ) {
		p1[POST_POINT_DIGITS+i]=9;
		pretty_big[POST_POINT_DIGITS+i]=9;
	}

	e = longAdd( p1, p2, res );
	CU_ASSERT_EQUAL( e, ERROR_OVERFLOW );
	CU_ASSERT_EQUAL( isLarger(p1, pretty_big), 0 )
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 )

	// modify one of the parameters
	e = longAdd( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, ERROR_OVERFLOW );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );
}



//
// longSub()
//
int init_longSub_suite( void ) {
	return 0; // success
}



int clean_longSub_suite( void ) {
	return 0; // success
}



void test_sub0_0( void ) {
	// subtracting before and after the decimal point
	fpn_t zero;
	fpn_t one;
	fpn_t p1;
	fpn_t p2;
	fpn_t expect;
	fpn_t res;
	error_e e;

	// 1-0 = 1
	toFpn( 1, 0, one );
	toFpn( 1, 0, p1 );

	toFpn( 0, 0, zero );
	toFpn( 0, 0, p2 );

	toFpn( 1, 0, expect );


	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, one), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, zero), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, zero), 0 );
}


void test_sub0_1( void ) {
	fpn_t zero;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// 0-0 = 0
	toFpn( 0, 0, zero );
	toFpn( 0, 0, p1 );
	toFpn( 0, 0, p2 );
	toFpn( 0, 0, expect );


	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, zero), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, zero), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, zero), 0 );
}



void test_sub0_2( void ) {
	fpn_t zero;
	fpn_t one;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// 1-1 = 0
	toFpn( 0, 0, zero );
	toFpn( 1, 0, one );
	toFpn( 1, 0, p1 );
	toFpn( 1, 0, p2 );
	toFpn( 0, 0, expect );

	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, one), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );
}



void test_sub0_3( void ) {
	fpn_t zero;
	fpn_t one;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	error_e e;

	// 0-1 = 65535
	toFpn( 0, 0, zero );
	toFpn( 0, 0, p1 );

	toFpn( 1, 0, one);
	toFpn( 1, 0, p2 );

	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, ERROR_UNDERFLOW );
	CU_ASSERT_EQUAL( isLarger(p1, zero), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, ERROR_UNDERFLOW );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );
}



void test_sub1_0( void ) {
	fpn_t zero;
	fpn_t p1;
	fpn_t p2;
	fpn_t small;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// 0.1 - 0.1 = 0.0
	toFpn( 0, 0, zero );
	toFpn( 0, 1, p1 );
	toFpn( 0, 1, p2 );
	toFpn( 0, 1, small );
	toFpn( 0, 0, expect );

	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, small), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );
}



void test_sub1_1( void ) {
	uint16_t i;
	fpn_t p1;
	fpn_t p2;
	fpn_t small;
	fpn_t tiny;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// 0.1 - 0.0...01 = 0.099...99
	toFpn( 0, 1, small );
	toFpn( 0, 1, p1 );
	toFpn( 0, 0, tiny );
	toFpn( 0, 0, p2 );
	p2[0] = 1;
	tiny[0] = 1;

	toFpn( 0, 0, expect );
	for( i=0; i< POST_POINT_DIGITS-1; i++ ) {
		expect[i] = 9;
	}


	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, small), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, tiny), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, tiny), 0 );
}



void test_sub2_0( void ) {
	fpn_t one;
	fpn_t small;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;

	// 1.0 - 0.1 = 0.9
	toFpn( 1, 0, one );
	toFpn( 1, 0, p1 );
	toFpn( 0, 1, small );
	toFpn( 0, 1, p2 );
	toFpn( 0, 9, expect );

	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, one), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, small), 0 );
}



void test_sub2_1( void ) {
	fpn_t small;
	fpn_t p1;
	fpn_t p2;
	fpn_t one;
	fpn_t res;
	error_e e;

	// 0.1 - 1.0 = ERROR_UNDERFLOW
	toFpn( 0, 1, small );
	toFpn( 0, 1, p1 );
	toFpn( 1, 0, one );
	toFpn( 1, 0, p2 );

	e = longSub( p1, p2, res );
	CU_ASSERT_EQUAL( e, ERROR_UNDERFLOW );
	CU_ASSERT_EQUAL( isLarger(p1, small), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );

	e = longSub( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, ERROR_UNDERFLOW );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );
}
