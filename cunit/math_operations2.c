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


/*
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
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 1.0 * 1.0 = 1.0
	toFpn(1, &a);
	toFpn(1, &b);
	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 1);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 1);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 1);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul0_1( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 1.0 * 0.1 = 0.1
	toFpn(1, &a);

	toFpn(0, &b);
	b.frac[0] = 1;

	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 0);
	CU_ASSERT_EQUAL(result.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 1);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 0);
	CU_ASSERT_EQUAL(b.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul1_0( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 0.0 * 1.0 = 0.0
	toFpn(0, &a);
	toFpn(1, &b);
	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 0);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 0);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 1);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul1_1( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 0.0 * 0.1 = 0.0
	toFpn(0, &a);
	toFpn(0, &b);
	b.frac[0] = 1;
	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 0);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 0);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 1);
	CU_ASSERT_EQUAL(b.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul2_0( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 0.1 * 0.1 = 0.01
	toFpn(0, &a);
	a.frac[0] = 1;

	toFpn(0, &b);
	b.frac[0] = 1;

	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 0);
	CU_ASSERT_EQUAL(result.frac[0], 0);
	CU_ASSERT_EQUAL(result.frac[1], 1);
	for( i=2; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 0);
	CU_ASSERT_EQUAL(a.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 1);
	CU_ASSERT_EQUAL(b.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul2_1( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 0.1 * 0.0...01 = 0.0
	toFpn(0, &a);
	a.frac[0] = 1;

	toFpn(0, &b);
	b.frac[PRECISION-1] = 1;

	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 0);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 0);
	CU_ASSERT_EQUAL(a.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 0);
	CU_ASSERT_EQUAL(b.frac[PRECISION-1], 1);
	for( i=0; i<PRECISION-1; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul2_2( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 10.0 * 0.01 = 0.1
	toFpn(10, &a);

	toFpn(0, &b);
	b.frac[1] = 1;

	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 0);
	CU_ASSERT_EQUAL(result.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 10);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 0);
	CU_ASSERT_EQUAL(b.frac[0], 0);
	CU_ASSERT_EQUAL(b.frac[1], 1);
	for( i=2; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul3_0( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 2.0 * 0.05 = 0.1
	toFpn(2, &a);

	toFpn(0, &b);
	b.frac[1] = 5;

	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 0);
	CU_ASSERT_EQUAL(result.frac[0], 1);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 2);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 0);
	CU_ASSERT_EQUAL(b.frac[0], 0);
	CU_ASSERT_EQUAL(b.frac[1], 5);
	for( i=2; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul3_1( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 2.0 * 0.5 = 1.0
	toFpn(2, &a);

	toFpn(0, &b);
	b.frac[0] = 5;

	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, OK);

	CU_ASSERT_EQUAL(result.num, 1);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(result.frac[i], 0);
	}

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 2);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 0);
	CU_ASSERT_EQUAL(b.frac[0], 5);
	for( i=1; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



void test_mul4_0( void ) {
	error_e e;
	fpn_t a, b, result;
	uint16_t i;

	// 2.0 * 33000.0 = ERROR_OVERFLOW
	toFpn(2, &a);

	toFpn(33000, &b);

	toFpn(0, &result);

	e = longMultiply( &a, &b, &result );
	CU_ASSERT_EQUAL(e, ERROR_OVERFLOW);

	// input must be unchanged
	CU_ASSERT_EQUAL(a.num, 2);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(a.frac[i], 0);
	}

	CU_ASSERT_EQUAL(b.num, 33000);
	for( i=0; i<PRECISION; i++ ) {
		CU_ASSERT_EQUAL(b.frac[i], 0);
	}
}



//
// longDivFrom()
//
int init_longDivFrom_suite( void ) {
	return 0; // success
}



int clean_longDivFrom_suite( void ) {
	return 0; // success
}



void test_divFrom0( void ) {
	// TODO: IMPLEMENT
	CU_ASSERT_EQUAL(0,1);
}



void test_divFrom1( void ) {
	// TODO: IMPLEMENT
	CU_ASSERT_EQUAL(0,1);
}



void test_divFrom2( void ) {
	// TODO: IMPLEMENT
	CU_ASSERT_EQUAL(0,1);
}
*/
