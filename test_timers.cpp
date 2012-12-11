//
// test_timers.cpp
//





#include <iostream>

#include "yarl_common.h"
#include "x86_32.h"
#include "timers.h"
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


void test_Timer_RDTSC_x86_32();


int main()
{
	log_level = WARNING;

	print_all_tests = false;
	//TURN_ON_MAX_LOG();
	//LOG_RETURN_TO_NORMAL(); 

	test_Timer_RDTSC_x86_32();

	finish_testing();

}

void test_Timer_RDTSC_x86_32()
{
	Cpu_8bit cpu8;
	Timer_RDTSC_x86_32 timer; 
	
	unsigned int actual, expected, bits;

	// 8-bit CPU
	//TEST((actual = cpu8.bitsToBytes(bits=0)) == (expected = 0), "cpu8.bitsToBytes(%d) --> %d but should be %d", bits, actual, expected);
	
}