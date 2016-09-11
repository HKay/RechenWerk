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

int init_dfpn_suite( void );
int clean_dfpn_suite( void );
void test_dfpn0( void );
void test_dfpn1( void );
void test_dfpn2( void );

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

int init_longSub_suite( void );
int clean_longSub_suite( void );
void test_sub0_0( void );
void test_sub0_1( void );
void test_sub0_2( void );
void test_sub0_3( void );
void test_sub1_0( void );
void test_sub1_1( void );
void test_sub2_0( void );
void test_sub2_1( void );

int init_longMul10_suite( void );
int clean_longMul10_suite( void );
void test_mul10_0( void );
void test_mul10_1( void );
void test_mul10_2( void );
void test_mul10_3( void );
void test_mul10_4( void );
void test_mul10_5( void );

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

int init_longDiv_suite( void );
int clean_longDiv_suite( void );
void test_div0_0( void );
void test_div0_1( void );
void test_div0_2( void );
void test_div1( void );
void test_div2( void );

#else
	#error DOUBLE INCLUDE OF __UNIT_H__
#endif //__UNIT_H__
