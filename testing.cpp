/*
 *  testing.c
 *	Routines for running unit tests on Yamba
 *
 *  Michael N. Gagnon, December 2009
 */

#include <stdio.h>

#include "testing.h"

int test_runs = 0;
int test_failures = 0;
bool print_all_tests = DEFAULT_PRINT_ALL_TESTS;

/*void init_testing()
{
	test_runs = 0;
	test_failures = 0;
	print_all_tests = DEFAULT_PRINT_ALL_TESTS;
}*/

void finish_testing()
{
	printf("\nTests: %d\n", test_runs);
	
	if (test_failures == 0)
		printf("All success\n");
	else
		printf("Failures: %d\n", test_failures);
}