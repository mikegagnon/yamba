/*
 *  test_runtime.c
 *
 *  Michael N. Gagnon, October 2009
 *
 *  Mostly C99 ANSI C
 *  GNU-C specific language features should be explicitly identified (just grep for GNU-C)
 *
 *  Best viewed wiith tab-charcter === 8 "floating" spaces 
 */

#include <stdio.h>
#include "testing.h"
#include "runtime.h"

void init_test_structs();

void test_ident_equal();
void test_get_numbytes();
void test_new_free_element_simple();
void test_new_free_element_ref();
void test_new_free_element_func();
void test_valid_bitstring_element_func_struct();

int main(int argc, char *argv[])
{
	LOG_LEVEL = WARNING;

	init_test_structs();

	init_testing();
	
	test_ident_equal();
	test_get_numbytes();
	test_new_free_element_simple();
	test_new_free_element_ref();
	test_valid_bitstring_element_func_struct();
	test_new_free_element_func();	
	
	
	finish_testing();
	
	return test_failures;
}

void test_ident_equal()
{
	bool actual, expected;

	char * a, * b;
	
	char str1[] = "abc";
	char str2[] = "abcd";
	
	char str3[] = "xxxx";
	
	strcpy(str3, str2);
	
	//print_all_tests = true;
	TEST(__FILE__, __LINE__, (actual=ident_equal((a=str1), (b=str1))) == (expected=true), "ident_equal('%s', '%s') --> %s, but should be %s\n", a, b, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual=ident_equal((a=str1), (b=str2))) == (expected=false), "ident_equal('%s', '%s') --> %s, but should be %s\n", a, b, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual=ident_equal((a=str2), (b=str1))) == (expected=false), "ident_equal('%s', '%s') --> %s, but should be %s\n", a, b, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual=ident_equal((a=str2), (b=str3))) == (expected=true), "ident_equal('%s', '%s') --> %s, but should be %s\n", a, b, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual=ident_equal((a=str3), (b=str2))) == (expected=true), "ident_equal('%s', '%s') --> %s, but should be %s\n", a, b, boolstr(actual), boolstr(expected));
	//print_all_tests = false;

}
void test_get_numbytes()
{
	unsigned int a,b,c;
	
	unsigned int actual_bits_per_byte = BITS_PER_BYTE;
	
	BITS_PER_BYTE = 8;	
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=0)) == (b=0), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=1)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=2)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=3)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=4)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=5)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=6)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=7)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=8)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=9)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=10)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=11)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=12)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=13)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=14)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=15)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=16)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=17)) == (b=3), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	
	BITS_PER_BYTE = 16;
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=0)) == (b=0), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=1)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=16)) == (b=1), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=17)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=32)) == (b=2), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	TEST(__FILE__, __LINE__, (a=get_numbytes(c=33)) == (b=3), "get_numbytes(%d) --> %d, but should be %d (BITS_PER_BYTE = %d)\n", c, a, b, BITS_PER_BYTE);
	
	BITS_PER_BYTE = actual_bits_per_byte;
	
	return;
}

void test_new_free_element_simple()
{
	unsigned int a, b;
	unsigned int bits_expected, bits_actual;
	y_error_t err_actual, err_expected;

	struct bitstring_element_simple_struct * element;
	
	element = NULL;
	
	for (int i = 0; i < 2; i++)
	{
		TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = new_element_simple(&element, (bits_actual=35))), "new_element_simple(&element, numbits=%d) --> %s, but should be %s\n", bits_actual, err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NON_NULL_POINTER) == (err_actual = new_element_simple(&element, (bits_actual=35))), "new_element_simple(&element, numbits=%d) --> %s, but should be %s\n", bits_actual, err_to_str(err_actual), err_to_str(err_expected));
		TEST(__FILE__, __LINE__, (bits_expected = 35) == (bits_actual = element->num_bits), "element->num_bits --> %d, but should be %d", bits_actual, bits_expected); 
		
		TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = free_element_simple(&element)), "free_element_simple(&element) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = free_element_simple(&element)), "free_element_simple(&element) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
	}
	
}

void test_new_free_element_ref()
{
	y_error_t err_actual, err_expected;
	
	immut_str_t * temp_id;
	immut_str_t * id = "foo";
	immut_str_t * id_null = NULL;
	
	struct bitstring_struct bs_non_null_object;
	struct bitstring_struct * temp_bs;
	struct bitstring_struct * bs_null = NULL;
	struct bitstring_struct * bs_non_null = &bs_non_null_object;
	
	struct bitstring_element_reference_struct * element1 = NULL;
	struct bitstring_element_reference_struct * element2 = NULL;
	struct bitstring_element_reference_struct * element3 = NULL;
	struct bitstring_element_reference_struct * element4 = NULL;

	for (int i = 0; i < 2; i++)
	{
		TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = new_element_ref(&element1, (temp_id=id), (temp_bs=bs_non_null))), "new_element_ref(&element1, id='%s', %p) --> %s, but should be %s\n", temp_id, (void *) temp_bs, err_to_str(err_actual), err_to_str(err_expected));
		TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = new_element_ref(&element2, (temp_id=id), (temp_bs=bs_null))), "new_element_ref(&element2, id='%s', %p) --> %s, but should be %s\n", temp_id, (void *) temp_bs, err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = new_element_ref(&element3, (temp_id=id_null), (temp_bs=bs_non_null))), "new_element_ref(&element3, id='%s', %p) --> %s, but should be %s\n", temp_id, (void *) temp_bs, err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = new_element_ref(&element4, (temp_id=id_null), (temp_bs=bs_null))), "new_element_ref(&element4, id='%s', %p) --> %s, but should be %s\n", temp_id, (void *) temp_bs, err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NON_NULL_POINTER) == (err_actual = new_element_ref(&element1, (temp_id=id), (temp_bs=bs_non_null))), "new_element_ref(&element1, id='%s', %p) --> %s, but should be %s\n", temp_id, (void *) temp_bs, err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NON_NULL_POINTER) == (err_actual = new_element_ref(&element2, (temp_id=id), (temp_bs=bs_null))), "new_element_ref(&element2, id='%s', %p) --> %s, but should be %s\n", temp_id, (void *) temp_bs, err_to_str(err_actual), err_to_str(err_expected));
		
		TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = free_element_ref(&element1)), "free_element_ref(&element1) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
		TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = free_element_ref(&element2)), "free_element_ref(&element2) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = free_element_ref(&element3)), "free_element_ref(&element3) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
		TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = free_element_ref(&element4)), "free_element_ref(&element4) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
	}
	
}




/* func_pointer_t is a typedef for a function pointer
 *	func_pointer_t takes a variable number of arguments
 *	preconditions:
 *		1. *object == NULL
 *			Else, return Y_RUNTIME_NON_NULL_POINTER
 *		2. func points to a fully bound function-bitstring element
 *			(a) func must be valid in the usual sense.  Additionally,
 *			(b) func->yfunc must point to this function
 *			(c) func->list must be fully bound
 *	postconditions:
 *		If all goes well, then (*object) points to a new simple bistring element, and returns Y_RUNTIME_GOOD
 *		Else, *object == NULL and returns an error condition
 * Yamba better do it's own type checking for these functions
 */
y_error_t yamba_function_0(struct bitstring_element_simple_struct ** object, struct bitstring_element_func_struct * func)
{
	return Y_RUNTIME_UNDEFINED_FUNCTION_BODY;
}

y_error_t yamba_function_1(struct bitstring_element_simple_struct ** object, struct bitstring_element_func_struct * func)
{
	return Y_RUNTIME_UNDEFINED_FUNCTION_BODY;
}

y_error_t yamba_function_3(struct bitstring_element_simple_struct ** object, struct bitstring_element_func_struct * func)
{
	return Y_RUNTIME_UNDEFINED_FUNCTION_BODY;
}


#define TEST_NUM_FUNC_OBJECTS 5
#define TEST_NUM_PARAMS 3


struct  yamaba_function_struct yamba_function_0_object = {
	.func_identifier = "yamba_function_0",
	.func = yamba_function_0,
	.num_parameters = 0,
	.formal_params = NULL
};

struct  yamaba_function_struct yamba_function_1_object = {
	.func_identifier = "yamba_function_1",
	.func = yamba_function_1,
	.num_parameters = 1,
	.formal_params = NULL /* defined in init_test_structs() */
};

immut_str_t * yamba_function_3_object_params[3];
struct  yamaba_function_struct yamba_function_3_object = {
	.func_identifier = "yamba_function_3",
	.func = yamba_function_3,
	.num_parameters = 3,
	.formal_params = NULL /* defined in init_test_structs() */
};

#define NUM_YAMBA_FUNCTION_STRUCT_OBJECTS 3
immut_str_t * yamba_function_object_params[NUM_YAMBA_FUNCTION_STRUCT_OBJECTS][TEST_NUM_PARAMS];

struct yamaba_function_struct * yamba_function_objects[NUM_YAMBA_FUNCTION_STRUCT_OBJECTS];

struct func_parameter_struct fp_objects[TEST_NUM_FUNC_OBJECTS][TEST_NUM_PARAMS];
struct bitstring_element_func_struct element_func_objects[TEST_NUM_FUNC_OBJECTS];

void init_test_structs()
{
	yamba_function_object_params[1][0] = "a";
	yamba_function_object_params[2][0] = "a";
	yamba_function_object_params[2][1] = "b";
	yamba_function_object_params[2][2] = "c";
	
	yamba_function_objects[0] = &yamba_function_0_object;
	yamba_function_objects[0]->formal_params = NULL;
	yamba_function_objects[1] = &yamba_function_1_object;
	yamba_function_objects[1]->formal_params = yamba_function_object_params[1];
	yamba_function_objects[2] = &yamba_function_3_object;
	yamba_function_objects[2]->formal_params = yamba_function_object_params[2];
	
	for (int i = 0; i < TEST_NUM_FUNC_OBJECTS; i++)
	{
		element_func_objects[i].yfunc = &yamba_function_3_object;
		element_func_objects[i].params = fp_objects[i];
		
		fp_objects[i][2].identifier = "c";
		fp_objects[i][1].identifier = "b";
		fp_objects[i][0].identifier = "a";
		
		fp_objects[i][2].bound = true;
		fp_objects[i][1].bound = true;
		fp_objects[i][0].bound = true;
		
		fp_objects[i][2].value = 0;
		fp_objects[i][1].value = 0;
		fp_objects[i][0].value = 0;
	}
	
	/* List summary
	 *		Valid	P1	P2	P3
	 *	0	y	u	u	u		fully un-bound
	 *	1	.	b	b	b		fully bound
	 *	2	.	b	b	u		partially bound
	 *	3	.	b	u	b		partially bound
	 *	4	.	u	b	b		partially bound
	 *
	 ************************************************************************/
	
	/*** (0) ***/
	fp_objects[0][0].bound = fp_objects[0][1].bound = fp_objects[0][2].bound = false;
		
	/*** (2) ***/
	fp_objects[2][2].bound = false;
	
	/*** (3) ***/
	fp_objects[3][1].bound = false;
	
	/*** (4) ***/
	fp_objects[4][0].bound = false;
	

}

void test_valid_bitstring_element_func_struct()
{
	int i;
	bool actual, expected;
	bool desired_bound;
	
	TEST(__FILE__, __LINE__, (actual = valid_bitstring_element_func_struct(&element_func_objects[i=0])) == (expected = true), "valid_bitstring_element_func_struct(element_func_objects[%d]) --> %s, but should be %s\n", i, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual = valid_bitstring_element_func_struct(&element_func_objects[i=1])) == (expected = true), "valid_bitstring_element_func_struct(element_func_objects[%d]) --> %s, but should be %s\n", i, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual = valid_bitstring_element_func_struct(&element_func_objects[i=2])) == (expected = true), "valid_bitstring_element_func_struct(element_func_objects[%d]) --> %s, but should be %s\n", i, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual = valid_bitstring_element_func_struct(&element_func_objects[i=3])) == (expected = true), "valid_bitstring_element_func_struct(element_func_objects[%d]) --> %s, but should be %s\n", i, boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual = valid_bitstring_element_func_struct(&element_func_objects[i=4])) == (expected = true), "valid_bitstring_element_func_struct(element_func_objects[%d]) --> %s, but should be %s\n", i, boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_bitstring_element_func_struct(NULL)) == (expected = false), "valid_bitstring_element_func_struct(NULL) --> %s, but should be %s\n", boolstr(actual), boolstr(expected));
	
	desired_bound = true;
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=0], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=1], desired_bound)) == (expected = true), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=2], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=3], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=4], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(NULL, desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(NULL, desired_bound=%s) --> %s, but should be %s\n", boolstr(desired_bound), boolstr(actual), boolstr(expected));

	desired_bound = false;
	TEST(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=0], desired_bound)) == (expected = true), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=1], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=2], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=3], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(&element_func_objects[i=4], desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element_func_objects[%d], desired_bound=%s) --> %s, but should be %s\n", i, boolstr(desired_bound), boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(NULL, desired_bound)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(NULL, desired_bound=%s) --> %s, but should be %s\n", boolstr(desired_bound), boolstr(actual), boolstr(expected));


}

void test_new_free_element_func()
{	
	y_error_t err_actual, err_expected;
	bool actual, expected;

	struct bitstring_element_func_struct * element1 = NULL, * element2 = NULL, * element3 = NULL, * element4 = NULL; 

	struct yamaba_function_struct * temp_yfunc;
		
	//TURN_ON_MAX_LOG();	
	TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = new_element_func(&element1, (temp_yfunc=yamba_function_objects[0]))), "new_element_func(&element1, yfunc='%s') --> %s, but should be %s\n", temp_yfunc == NULL ? "null" : temp_yfunc->func_identifier, err_to_str(err_actual), err_to_str(err_expected));
	TEST(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(element1, false)) == (expected = true), "valid_and_bound_bitstring_element_func_struct(element1, desired_bound=false) --> %s, but should be %s\n", boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = new_element_func(&element2, (temp_yfunc=yamba_function_objects[1]))), "new_element_func(&element2, yfunc='%s') --> %s, but should be %s\n", temp_yfunc == NULL ? "null" : temp_yfunc->func_identifier, err_to_str(err_actual), err_to_str(err_expected));
	TEST(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(element2, false)) == (expected = true), "valid_and_bound_bitstring_element_func_struct(element2, desired_bound=false) --> %s, but should be %s\n", boolstr(actual), boolstr(expected));
	TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = new_element_func(&element3, (temp_yfunc=yamba_function_objects[2]))), "new_element_func(&element3, yfunc='%s') --> %s, but should be %s\n", temp_yfunc == NULL ? "null" : temp_yfunc->func_identifier, err_to_str(err_actual), err_to_str(err_expected));
	TEST(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(element3, false)) == (expected = true), "valid_and_bound_bitstring_element_func_struct(element3, desired_bound=false) --> %s, but should be %s\n", boolstr(actual), boolstr(expected));
	TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = new_element_func(&element4, (temp_yfunc=NULL))), "new_element_func(&element4, yfunc='%s') --> %s, but should be %s\n", temp_yfunc == NULL ? "null" : temp_yfunc->func_identifier, err_to_str(err_actual), err_to_str(err_expected));
	TEST_NO_LOG(__FILE__, __LINE__, (actual = valid_and_bound_bitstring_element_func_struct(element4, false)) == (expected = false), "valid_and_bound_bitstring_element_func_struct(element4, desired_bound=false) --> %s, but should be %s\n", boolstr(actual), boolstr(expected));

	//print_all_tests = true;

	TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = free_element_func(&element1)), "free_element_func(&element1) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
	TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = free_element_func(&element1)), "free_element_func(&element1) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));	
	TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = free_element_func(&element2)), "free_element_func(&element2) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
	TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = free_element_func(&element2)), "free_element_func(&element2) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));	
	TEST(__FILE__, __LINE__, (err_expected = Y_RUNTIME_GOOD) == (err_actual = free_element_func(&element3)), "free_element_func(&element3) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
	TEST_NO_LOG(__FILE__, __LINE__, (err_expected = Y_RUNTIME_NULL_POINTER) == (err_actual = free_element_func(&element3)), "free_element_func(&element3) --> %s, but should be %s\n", err_to_str(err_actual), err_to_str(err_expected));
	

	
	//LOG_RETURN_TO_NORMAL();

	
	//print_all_tests = false;
		
}
