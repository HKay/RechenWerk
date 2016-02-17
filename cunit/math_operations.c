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
int init_longAddInto_suite( void ) {
	return 0; // success
}



int clean_longAddInto_suite( void ) {
	return 0; // success
}



void test_addInto0_0( void ) {
	// adding before the decimal point
	fpn_t zero;
	fpn_t one;
	fpn_t tmp;
	fpn_t res;

	toFpn( 0, &zero );
	toFpn( 1, &one );

	// 1+2=3
	toFpn( 2, &tmp );
	toFpn( 3, &res );
	longAddInto( &tmp, &one );
	CU_ASSERT_EQUAL( isLarger(&tmp, &res), 0 );
}



void test_addInto0_1( void ) {
	fpn_t zero;
	fpn_t one;
	fpn_t tmp;
	fpn_t res;

	toFpn( 0, &zero );
	toFpn( 1, &one );

	// 0+0=0
	toFpn( 0, &tmp );
	toFpn( 0, &res );
	longAddInto( &tmp, &zero );
	CU_ASSERT_EQUAL( isLarger(&tmp, &res), 0 );
}



void test_addInto0_2( void ) {
	fpn_t zero;
	fpn_t one;
	fpn_t tmp;
	fpn_t res;

	toFpn( 0, &zero );
	toFpn( 1, &one );

	// 65535+1=0
	toFpn( 65535, &tmp );
	toFpn( 0, &res );
	longAddInto( &tmp, &one );
	CU_ASSERT_EQUAL( isLarger(&tmp, &res), 0 );
}



void test_addInto1_0( void ) {
	// adding after the decimal point
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	// adding without carry
	// 0.0...01 + 0.0...02 = 0.0...03
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );

	tmp1.frac[PRECISION-1] = 1;
	tmp2.frac[PRECISION-1] = 2;
	res.frac[PRECISION-1] = 3;
	longAddInto( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 );
}



void test_addInto1_1( void ) {
	// adding after the decimal point
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	// adding with carry to zero
	// 0.09 + 0.01 = 0.10
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );

	tmp1.frac[1] = 9;
	tmp2.frac[1] = 1;
	res.frac[0] = 1;
	longAddInto( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 );
}



void test_addInto1_2( void ) {
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	// adding with carry to non-zero
	// 0.09 + 0.02 = 0.11
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );

	tmp1.frac[1] = 9;
	tmp2.frac[1] = 2;
	res.frac[0] = 1;
	res.frac[1] = 1;
	longAddInto( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 );
}



void test_addInto2_0( void ) {
	// adding before and after the decimal point
	uint16_t i;
	fpn_t zero;
	fpn_t one;
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	toFpn( 0, &zero );
	toFpn( 1, &one );


	// carry jumps the decimal point to zero after point
	// 0.1 + 0.9 = 1.0
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );

	tmp1.frac[0] = 1;
	tmp2.frac[0] = 9;
	res.num = 1;
	longAddInto( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 )
}


void test_addInto2_1( void ) {
	// adding before and after the decimal point
	uint16_t i;
	fpn_t zero;
	fpn_t one;
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	toFpn( 0, &zero );
	toFpn( 1, &one );

	// carry jumps the decimal point after maximum shift
	// 0.9...99 + 0.0...01 = 1.0
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );

	for( i=0; i<PRECISION; i++ ) {
		tmp1.frac[i] = 9;
	}
	tmp2.frac[PRECISION-1] = 1;
	res.num = 1;
	longAddInto( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 )
}



void test_addInto2_2( void ) {
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	// carry jumps the decimal point to non-zero after point
	// 1.2 + 0.9 = 2.1
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );

	tmp1.frac[0] = 2;
	tmp1.num = 1;
	tmp2.frac[0] = 9;
	res.num = 2;
	res.frac[0] = 1;
	longAddInto( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 )
}



void test_addInto2_3( void ) {
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	// carry jumps integer(uint16_t) boundaries
	// 65535.9 + 0.2 = 0.0
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );

	tmp1.frac[0] = 9;
	tmp1.num = 65535;
	tmp2.frac[0] = 2;
	res.frac[0] = 1;
	longAddInto( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 )
}



//
// longSubFrom()
//
int init_longSubFrom_suite( void ) {
	return 0; // success
}



int clean_longSubFrom_suite( void ) {
	return 0; // success
}



void test_subFrom0_0( void ) {
	// subtracting before and after the decimal point
	fpn_t zero;
	fpn_t one;
	fpn_t tmp;

	toFpn( 0, &zero );
	toFpn( 1, &one );

	// 1-0 = 1
	toFpn( 1, &tmp );

	longSubFrom( &tmp, &zero );
	CU_ASSERT_EQUAL( isLarger(&tmp, &one), 0 )
}



void test_subFrom0_1( void ) {
	fpn_t zero;
	fpn_t tmp;

	toFpn( 0, &zero );

	// 0-0 = 0
	toFpn( 0, &tmp );

	longSubFrom( &tmp, &zero );
	CU_ASSERT_EQUAL( isLarger(&tmp, &zero), 0 )
}



void test_subFrom0_2( void ) {
	fpn_t zero;
	fpn_t one;
	fpn_t tmp;

	toFpn( 0, &zero );
	toFpn( 1, &one );

	// 1-1 = 0
	toFpn( 1, &tmp );

	longSubFrom( &tmp, &one );
	CU_ASSERT_EQUAL( isLarger(&tmp, &zero), 0 )
}



void test_subFrom0_3( void ) {
	fpn_t zero;
	fpn_t one;
	fpn_t tmp;
	fpn_t res;

	toFpn( 0, &zero );
	toFpn( 1, &one );

	// 0-1 = 65535
	toFpn( 0, &tmp );
	toFpn( 65535, &res );

	longSubFrom( &tmp, &one );
	CU_ASSERT_EQUAL( isLarger(&tmp, &res), 0 )
}



void test_subFrom1_0( void ) {
	fpn_t zero;
	fpn_t tmp1;
	fpn_t tmp2;

	toFpn( 0, &zero );

	// 0.1 - 0.1 = 0.0
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	tmp1.frac[0] = 1;
	tmp2.frac[0] = 1;

	longSubFrom( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &zero), 0 )
}



void test_subFrom1_1( void ) {
	uint16_t i;
	fpn_t zero;
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	toFpn( 0, &zero );

	// 0.1 - 0.0...01 = 0.099...99
	toFpn( 0, &tmp1 );
	toFpn( 0, &tmp2 );
	toFpn( 0, &res );
	tmp1.frac[0] = 1; // 0.1
	tmp2.frac[PRECISION-1] = 1; // 0.0...01
	for( i=1; i< PRECISION; i++ ) {
		res.frac[i] = 9; // 0.099...99
	}

	longSubFrom( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 )
}



void test_subFrom2_0( void ) {
	fpn_t tmp1;
	fpn_t tmp2;
	fpn_t res;

	// 1.0 - 0.1 = 0.9
	toFpn( 1, &tmp1 ); // 1.0

	toFpn( 0, &tmp2 );
	tmp2.frac[0] = 1; // 0.1

	toFpn( 0, &res );
	res.frac[0] = 9; // 0.9

	longSubFrom( &tmp1, &tmp2 );
	CU_ASSERT_EQUAL( isLarger(&tmp1, &res), 0 )
}



void test_subFrom2_1( void ) {
	fpn_t one;
	fpn_t tmp;
	fpn_t res;

	toFpn( 1, &one );

	// 0.1 - 1.0 = 65535.9
	// but correct is 65535.0 (error constant)
	toFpn( 0, &tmp );
	tmp.frac[0] = 1; // 0.1

	toFpn( 0, &res );
	res.num = 65535; // 65535.0

	longSubFrom( &tmp, &one );
	CU_ASSERT_EQUAL( isLarger(&tmp, &res), 0 )
}
