//
// timers.h
//
//	Yamba runtime library timing functions
//	Michael N. Gagnon, December 2009

#ifndef __YAMBA_TIMERS_H__
#define __YAMBA_TIMERS_H__

#include "yarl_common.h"
//#include "x86_32.h"

#include <stdint.h>
//#include <sys/time.h>

#define USEC_IN_SEC    1000000UL
#define HZ_IN_GHZ   1000000000UL

namespace Yamba
{

// cast a byte_t pointer to a function pointer
// this necessitates platform-specific code since
// function-pointers and byte_t pointers might be 
// fundamentally  different
template <typename func_ptr_t> func_ptr_t funky_cast(byte_t * bytes);


template <typename tq_result_t>
class Timer : public YambaDebug
{

public:

	typedef void(*tq_func_t)(tq_result_t ** results);

	BitstringFunction * prologue;
	
	BitstringFunction * epilogue;

	BitstringFunction * body;	
	
	tq_func_t tq_func;
	
	BitstringBuilder * tq_func_builder;
	
	virtual void build_tq()
	{
		LOG_ENTER_VOID();

		// assert foo_tq_builder.elements == empty
		
		// Phase 1: Compile
		
		prologue->compile(tq_func_builder);
		body->compile(tq_func_builder);
		epilogue->compile(tq_func_builder);

			
		// Phase 2: Allocate, flatten, and link
		
		tq_func_builder->phase2();
		
		tq_func = funky->cast(tq_func_builder->bytes);
		
	}	
	
	const char * getClassName() const {return "Timer";}

protected:
	
	FunkyCast<tq_func_t> * funky;
		
};



} // End namespace Yamba


/*
// typdef for a function pointer to the rdtsc function
//typedef void (*rdtsc_func_t)(void ** results);

typedef void (*timer_func_t)(void ** results);


double gtd_to_usec(struct timeval * tv);
double tick_to_usec(uint64_t tick, double ghz);


void yamba_gettimeofday(void ** results);


// global pointer to the rdtsc function
// usage:
// 	uint64_t results [] = {1,2};
//	uint64_t * result_ptr = results;
//	rdtsc_func(&result_ptr);

// creates the rdtsc function on the heap and initializes rdtsc_func
timer_func_t make_rdtsc_func();
*/

#endif
