//
// test_yarl_common.cpp
//	Yamba runtime library
//

#include <iostream>

#include "yarl_common.h"
#include "testing.h"
#include "logging.h"

using namespace Yamba;

using namespace std;

// Do not want to use limits.h because then we couldn't cross compile, right?  
// But at the very least we should put in a check in the final code that 
// verifies bits_per_byte() == CHAR_BIT
class Cpu_8bit : public Yamba::CpuGeneric
{
	unsigned int bits_per_byte() const {return 8;}
	const char * getClassName() const {return "Cpu_8bit";}	
};

class Cpu_16bit : public Yamba::CpuGeneric
{
	unsigned int bits_per_byte() const {return 16;}
	const char * getClassName() const {return "Cpu_16bit";}
};


void test_bitsToBytes();


int main()
{
	log_level = WARNING;

	print_all_tests = false;
	//TURN_ON_MAX_LOG();
	//LOG_RETURN_TO_NORMAL(); 

	test_bitsToBytes();

	finish_testing();

}

void test_bitsToBytes()
{
	Cpu_8bit cpu8;
	Cpu_16bit cpu16;
	
	unsigned int actual, expected, bits;

	// 8-bit CPU
	TEST((actual = cpu8.bitsToBytes(bits=0)) == (expected = 0), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=1)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=2)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=3)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=4)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=5)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=6)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=7)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=8)) == (expected = 1), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=9)) == (expected = 2), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=10)) == (expected = 2), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=16)) == (expected = 2), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=17)) == (expected = 3), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu8.bitsToBytes(bits=18)) == (expected = 3), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	

	
	// 16-bit CPU
	TEST((actual = cpu16.bitsToBytes(bits=0)) == (expected = 0), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=1)) == (expected = 1), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=2)) == (expected = 1), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=15)) == (expected = 1), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=16)) == (expected = 1), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=17)) == (expected = 2), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=18)) == (expected = 2), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=31)) == (expected = 2), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=32)) == (expected = 2), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=33)) == (expected = 3), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	TEST((actual = cpu16.bitsToBytes(bits=34)) == (expected = 3), "cpu16.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);

}