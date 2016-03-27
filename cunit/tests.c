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
#include <CUnit/Basic.h>
#include "../math.h"
#include "../util.h"
#include "unit.h"




//
// This function replaces main() in the real program
//
int __wrap_main (void) {
	CU_pSuite pSuite = NULL;

	// initialize the CUnit test registry
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("toFpn()", init_fpn_suite, clean_fpn_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "0 to fpn          ", test_fpn0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "5.3 to fpn        ", test_fpn1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "65535.65535 to fpn", test_fpn2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}



	pSuite = CU_add_suite("toDFpn()", init_dfpn_suite, clean_dfpn_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "0 to dfpn          ", test_dfpn0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "5.3 to dfpn        ", test_dfpn1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "65535.65535 to dfpn", test_dfpn2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}



	pSuite = CU_add_suite("isLarger()", init_isLarger_suite, clean_isLarger_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "differences before the decimal point", test_isLarger0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "differences after the decimal point", test_isLarger1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "differences before and after the decimal point", test_isLarger2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}



	pSuite = CU_add_suite("longAddInto()", init_longAdd_suite, clean_longAdd_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "1+2 = 3    ", test_add0_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "1+0 = 1    ", test_add0_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "65535+65535=OVERFLOW ERROR", test_add0_2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "0.0...01 + 0.0...02 = 0.0...03", test_add1_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0.09 + 0.01 = 0.10            ", test_add1_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0.09 + 0.02 = 0.11            ", test_add1_2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "0.1 + 0.9 = 1.0          ", test_add2_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0.9...99 + 0.0...01 = 1.0", test_add2_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "1.2 + 0.9 = 2.1          ", test_add2_2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "...999.900... + 0.1 = OVERFLOW ERROR", test_add2_3) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}



	pSuite = CU_add_suite("longSubFrom()", init_longSub_suite, clean_longSub_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "1-0 = 1                    ", test_sub0_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0-0 = 0                    ", test_sub0_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "1-1 = 0                    ", test_sub0_2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0-1 = ERROR_UNDERFLOW      ", test_sub0_3) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0.1 - 0.1 = 0.0            ", test_sub1_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "0.1 - 0.0...01 = 0.099...99", test_sub1_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "1.0 - 0.1 = 0.9            ", test_sub2_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0.1 - 1.0 = ERROR_UNDERFLOW", test_sub2_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}


	pSuite = CU_add_suite("longMulInto()", init_longMul_suite, clean_longMul_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "1.0 * 1.0 = 1.0", test_mul0_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "1.0 * 0.1 = 0.1", test_mul0_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "0.0 * 1.0 = 0.0", test_mul1_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
/*
	if ( NULL == CU_add_test(pSuite, "0.0 * 0.1 = 0.0", test_mul1_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}


	if ( NULL == CU_add_test(pSuite, "0.1 * 0.1 = 0.01", test_mul2_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "0.1 * 0.0...01 = 0.0", test_mul2_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "10.0 * 0.01 = 0.1", test_mul2_2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}


	if ( NULL == CU_add_test(pSuite, "2.0 * 0.05 = 0.1", test_mul3_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "2.0 * 0.5 = 1.0", test_mul3_1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}


	if ( NULL == CU_add_test(pSuite, "2.0 * 33000.0 -> ERROR_OVERFLOW", test_mul4_0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}







	pSuite = CU_add_suite("longDivFrom()", init_longDivFrom_suite, clean_longDivFrom_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}

	if ( NULL == CU_add_test(pSuite, "divide before decimal point", test_divFrom0) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "divide after decimal point", test_divFrom1) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
	if ( NULL == CU_add_test(pSuite, "divide before and after decimal point", test_divFrom2) ) {
		CU_cleanup_registry( );
		return CU_get_error( );
	}
*/


	// Run all tests using the CUnit Basic interface
	CU_basic_set_mode( CU_BRM_VERBOSE );
	CU_basic_run_tests( );
	CU_cleanup_registry( );

	return CU_get_error( );
}
