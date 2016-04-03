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
// longMul()
//
int init_longMul_suite( void ) {
	return 0; // success
}



int clean_longMul_suite( void ) {
	return 0; // success
}



void test_mul0_0( void ) {
	fpn_t one;
	fpn_t p1;
	fpn_t p2;
	fpn_t expect;
	fpn_t res;
	error_e e;

	// 1.0 * 1.0 = 1.0
	toFpn(1, 0, one);
	toFpn(1, 0, p1);
	toFpn(1, 0, p2);
	toFpn(1, 0, expect);

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(res, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p1, one), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );

	// modify one of the parameters
	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL( e, OK );
	CU_ASSERT_EQUAL( isLarger(p1, expect), 0 );
	CU_ASSERT_EQUAL( isLarger(p2, one), 0 );
}



void test_mul0_1( void ) {
	fpn_t one;
	fpn_t p1;
	fpn_t small;
	fpn_t p2;
	fpn_t res;
	error_e e;

	fpn_t a, b, result;
	uint16_t i;

	// 1.0 * 0.1 = 0.1
	toFpn(1, 0, one);
	toFpn(1, 0, p1);
	toFpn(0, 1, small);
	toFpn(0, 1, p2);
	toFpn(0, 1, res);

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, one), 0);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(res, small), 0);

	e = longMul( p1, p2, p2 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(p1, one), 0);
}



void test_mul1_0( void ) {
	fpn_t zero;
	fpn_t p1;
	fpn_t one;
	fpn_t p2;
	fpn_t res;
	error_e e;
	uint16_t i;

	// 0.0 * 1.0 = 0.0
	toFpn(0, 0, zero);
	toFpn(0, 0, p1);
	toFpn(1, 0, one);
	toFpn(1, 0, p2);
	toFpn(0, 0, res);

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, zero), 0);
	CU_ASSERT_EQUAL(isLarger(p2, one), 0);
	CU_ASSERT_EQUAL(isLarger(res, zero), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, one), 0);
	CU_ASSERT_EQUAL(isLarger(p1, zero), 0);
}



void test_mul1_1( void ) {
	fpn_t zero;
	fpn_t p1;
	fpn_t small;
	fpn_t p2;
	fpn_t res;
	error_e e;
	uint16_t i;

	// 0.0 * 0.1 = 0.0
	toFpn(0, 0, zero);
	toFpn(0, 0, p1);
	toFpn(0, 1, small);
	toFpn(0, 1, p2);
	toFpn(0, 0, res);

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, zero), 0);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(res, zero), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(p1, zero), 0);
}


void test_mul2_0( void ) {
	fpn_t small;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;
	uint16_t i;

	// 0.1 * 0.1 = 0.01
	toFpn(0, 1, small);
	toFpn(0, 1, p1);
	toFpn(0, 1, p2);
	toFpn(0, 0, expect);
	expect[POST_POINT_DIGITS-2] = 1;

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, small), 0);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(res, expect), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(p1, expect), 0);
}



void test_mul2_1( void ) {
	fpn_t small;
	fpn_t tiny;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	error_e e;
	uint16_t i;

	// 0.1 * 0.0...01 = 0.0
	toFpn(0, 1, small);
	toFpn(0, 1, p1);
	toFpn(0, 0, p2);
	toFpn(0, 0, tiny);
	p2[0] = 1;
	tiny[0] = 1;

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, small), 0);
	CU_ASSERT_EQUAL(isLarger(p2, tiny), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, tiny), 0);
}



void test_mul2_2( void ) {
	fpn_t big;
	fpn_t small;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;
	uint16_t i;

	// 10.0 * 0.01 = 0.1
	toFpn(10, 0, big);
	toFpn(10, 0, p1);
	toFpn(0, 0, small);
	toFpn(0, 0, p2);
	toFpn(0, 1, expect);
	small[POST_POINT_DIGITS-2] = 1;
	p2[POST_POINT_DIGITS-2] = 1;

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, big), 0);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(res, expect), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(p1, expect), 0);
}



void test_mul3_0( void ) {
	fpn_t big;
	fpn_t small;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;
	uint16_t i;

	// 2.0 * 0.05 = 0.1
	toFpn(2, 0, big);
	toFpn(2, 0, p1);
	toFpn(0, 0, small);
	toFpn(0, 0, p2);
	toFpn(0, 1, expect);
	small[POST_POINT_DIGITS-2] = 5;
	p2[POST_POINT_DIGITS-2] = 5;

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, big), 0);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(res, expect), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(p1, expect), 0);
}

void test_mul3_1( void ) {
	fpn_t big;
	fpn_t small;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;
	uint16_t i;

	// 2.0 * 0.5 = 1.0
	toFpn(2, 0, big);
	toFpn(2, 0, p1);
	toFpn(0, 5, small);
	toFpn(0, 5, p2);
	toFpn(1, 0, expect);

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p1, big), 0);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(res, expect), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, OK);
	CU_ASSERT_EQUAL(isLarger(p2, small), 0);
	CU_ASSERT_EQUAL(isLarger(p1, expect), 0);
}




void test_mul4_0( void ) {
	fpn_t big;
	fpn_t small;
	fpn_t p1;
	fpn_t p2;
	fpn_t res;
	fpn_t expect;
	error_e e;
	uint16_t i;

	// 2.0 * 50000.0 = ERROR_OVERFLOW
	toFpn(2, 0, small);
	toFpn(2, 0, p1);
	toFpn(50000, 0, big);
	toFpn(50000, 0, p2);

	e = longMul( p1, p2, res );
	CU_ASSERT_EQUAL(e, ERROR_OVERFLOW);
	CU_ASSERT_EQUAL(isLarger(p1, small), 0);
	CU_ASSERT_EQUAL(isLarger(p2, big), 0);

	e = longMul( p1, p2, p1 );
	CU_ASSERT_EQUAL(e, ERROR_OVERFLOW);
	CU_ASSERT_EQUAL(isLarger(p2, big), 0);
}



//
// longDivFrom()
//
int init_longDiv_suite( void ) {
	return 0; // success
}



int clean_longDiv_suite( void ) {
	return 0; // success
}



void test_div0( void ) {
	// TODO: IMPLEMENT
	CU_ASSERT_EQUAL(0,1);
}



void test_div1( void ) {
	// TODO: IMPLEMENT
	CU_ASSERT_EQUAL(0,1);
}



void test_div2( void ) {
	// TODO: IMPLEMENT
	CU_ASSERT_EQUAL(0,1);
}
