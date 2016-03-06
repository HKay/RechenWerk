#ifndef __UNIT_H__
#define __UNIT_H__



void longPrint( fpn_t a );
void longPrint2( fpn_t a );
void statusPrint( error_e e );

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

int init_longAdd_suite( void );
int clean_longAdd_suite( void );
void test_add0_0( void );
void test_add0_1( void );
void test_add0_2( void );
void test_add1_0( void );
void test_add1_1( void );
void test_add1_2( void );
void test_add2_0( void );
void test_add2_1( void );
void test_add2_2( void );
void test_add2_3( void );

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

int init_longMul_suite( void );
int clean_longMul_suite( void );
void test_mul0_0( void );
void test_mul0_1( void );
void test_mul1_0( void );
void test_mul1_1( void );
void test_mul2_0( void );
void test_mul2_1( void );
void test_mul2_2( void );
void test_mul3_0( void );
void test_mul3_1( void );
void test_mul4_0( void );
void test_mul4_1( void );

int init_longDivFrom_suite( void );
int clean_longDivFrom_suite( void );
void test_divFrom0( void );
void test_divFrom1( void );
void test_divFrom2( void );

#else
	#error DOUBLE INCLUDE OF __UNIT_H__
#endif //__UNIT_H__
