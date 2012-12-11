//
// timers.h
//
//	Yamba runtime library timing functions
//	Michael N. Gagnon, December 2009

#ifndef __YAMBA_x86_32_H__
#define __YAMBA_x86_32_H__

#include "yarl_common.h"
#include "timers.h"

namespace Yamba
{

class Cpu_x86_32 : public CpuGeneric
{

public:

	unsigned int bits_per_byte() const {return 8;}
	const char * getClassName() const {return "Cpu_x86_32";}	

};

template <typename func_ptr_t> 
class FunkyCast_x86_32 : public FunkyCast_direct<func_ptr_t>
{};


class BitstringBuilder_x86_32 : public BitstringBuilder
{

public:
	
	BitstringBuilder_x86_32() : BitstringBuilder()
	{
		setCpu();
	}
	
	void setCpu()
	{
		cpu = new Cpu_x86_32();
	}

};


/*******************************************************************************
 * class Timer_RDTSC_x86_32
 ******************************************************************************/

class Timer_RDTSC_x86_32 : public Timer<uint64_t>
{

public:

	Timer_RDTSC_x86_32()
	{
		this->tq_func_builder = new BitstringBuilder_x86_32();
		this->funky = new FunkyCast_x86_32<tq_func_t>();
	
		this->prologue = new Prologue();
		this->epilogue = new Epilogue();
		this->body = new Body();
		
		this->build_tq();
	}
	
	class Prologue : public BitstringFunction
	{
		const char * getClassName() const {return "Timer_RDTSC_x86_32::Prologue";}
		
		void compile(BitstringBuilder * builder)
		{
		
		}
	};
	
	class Epilogue : public BitstringFunction
	{
		const char * getClassName() const {return "Timer_RDTSC_x86_32::Epilogue";}
		
		void compile(BitstringBuilder * builder)
		{
		
		}
	};
	
	class Body : public BitstringFunction
	{
		const char * getClassName() const {return "Timer_RDTSC_x86_32::Body";}
		
		void compile(BitstringBuilder * builder)
		{
		
		}
	};
	
	const char * getClassName() const {return "Timer_RDTSC_x86_32";}

};


} // End namespace Yamba


#endif
