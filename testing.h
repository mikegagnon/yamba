/*
 *  testing.h
 *	Routines for running unit tests on Yamba
 *
 *  Michael N. Gagnon, December 2009
 *
 */

#ifndef __YAMBA_TESTING_H__
#define __YAMBA_TESTING_H__

#include "logging.h"

extern int test_runs;
extern int test_failures;

#define DEFAULT_PRINT_ALL_TESTS	  false
extern bool print_all_tests;

// Compiler portability note:
// I don't know if this stringification trick works on all C++ compilers
//	http://gcc.gnu.org/onlinedocs/cpp/Stringification.html
// It's helpful for debugging failed tests, but not crucial

#ifndef XSTR
	#define XSTR(s) STR(s)
	#define STR(s) #s
#endif
 
#define TEST(assertion, format, ...) do { \
if (!(assertion)) \
{ \
	fprintf(stderr, \
		"FAIL     " __FILE__ ", line " XSTR(__LINE__) ": " format "\n", \
		__VA_ARGS__); \
	test_failures++; \
	test_runs++; \
} \
else if (print_all_tests) \
{ \
	fprintf(stderr, \
		"SUCCESS  " __FILE__ ", line " XSTR(__LINE__) ": " format "\n", \
		__VA_ARGS__); \
	test_runs++; \
} \
else \
	test_runs++; \
} while(0) \

#define TEST_NO_LOG(file, linenumber, assertion, format, ...) do { \
		TURN_OFF_LOG(); \
		TEST(file, linenumber, assertion, format, __VA_ARGS__); \
		LOG_RETURN_TO_NORMAL(); \
	} while(0)

#define TEST_MAX_LOG(file, linenumber, assertion, format, ...) do { \
		TURN_ON_MAX_LOG(); \
		TEST(file, linenumber, assertion, format, __VA_ARGS__); \
		LOG_RETURN_TO_NORMAL(); \
	} while(0)

//void init_testing();

void finish_testing();

#endif