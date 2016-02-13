#ifndef __UNIT_H__
#define __UNIT_H__

int init_fpn_suite( void );
int clean_fpn_suite( void );
void test_fpn0( void );
void test_fpn1( void );
void test_fpn2( void );

int init_isLarger_suite( void );
int clean_isLarger_suite( void );
void test_isLarger0( void );
void test_isLarger1( void );
void test_isLarger2( void );

int init_longAddInto_suite( void );
int clean_longAddInto_suite( void );
void test_addInto0_0( void );
void test_addInto0_1( void );
void test_addInto0_2( void );
void test_addInto1_0( void );
void test_addInto1_1( void );
void test_addInto1_2( void );
void test_addInto2_0( void );
void test_addInto2_1( void );
void test_addInto2_2( void );
void test_addInto2_3( void );

int init_longSubFrom_suite( void );
int clean_longSubFrom_suite( void );
void test_subFrom0_0( void );
void test_subFrom0_1( void );
void test_subFrom0_2( void );
void test_subFrom0_3( void );
void test_subFrom1_0( void );
void test_subFrom1_1( void );
void test_subFrom2_0( void );
void test_subFrom2_1( void );

int init_longMulInto_suite( void );
int clean_longMulInto_suite( void );
void test_mulInto0( void );
void test_mulInto1( void );
void test_mulInto2( void );

int init_longDivFrom_suite( void );
int clean_longDivFrom_suite( void );
void test_divFrom0( void );
void test_divFrom1( void );
void test_divFrom2( void );

#else
	#error DOUBLE INCLUDE OF __UNIT_H__
#endif //__UNIT_H__
