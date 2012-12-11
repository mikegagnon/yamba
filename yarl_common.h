//
// yarl_common.h
//
//	Yamba runtime library
//	Michael N. Gagnon, December 2009

#ifndef __YAMBA_YARL_COMMON_H__
#define __YAMBA_YARL_COMMON_H__

#include <list>
#include "logging.h"

namespace Yamba
{

/*******************************************************************************
 * type definitions
 ******************************************************************************/

typedef char byte_t;


/*******************************************************************************
 * class YambaDebug
 ******************************************************************************/

// All Yamba classes inherit this to facilitate debugging

class YambaDebug
{
public:
	virtual const char * getClassName() const {return "?";}
	
	virtual const char * getObjectName() const {return getClassName();}
};


/*******************************************************************************
 * class FunkyCast
 ******************************************************************************/
// Used to cast byte pointers to function pointers
//
// There is no platform specific way to cast byte pointers to function pointers
// so we platforms must instantiate FunkyCast.  Hopefully, all function pointers
// can be cast the same way, otherwise we'll need different cast implementations
// for different function signatures.
//

template <typename func_ptr_t> 
class FunkyCast : public YambaDebug
{
	
public:
	virtual func_ptr_t cast(byte_t * bytes) const = 0;

};

// This should work on a wide variety of 32-bit platforms
// Assumes that function pointers and byte pointers are equivalent 
// to 32-bit values
// ISO C++ forbids casting between pointer-to-function and pointer-to-object
template <typename func_ptr_t> 
class FunkyCast_direct : public FunkyCast<func_ptr_t>
{
	
public:
	func_ptr_t cast(byte_t * bytes) const
	{
		LOG_ENTER("bytes=%p", bytes);
		
		uintptr_t val = reinterpret_cast<uintptr_t>(bytes);
//		LOG(FINEST, "val=%08x", val);
		
		func_ptr_t func_ptr = reinterpret_cast<func_ptr_t>(val);
//		LOG(FINEST, "func_ptr=%p", func_ptr);
		
		return func_ptr;
	}

	const char * getClassName() const {return "FunkyCast_32_bit_simple";}

};



/*******************************************************************************
 * class CpuGeneric
 ******************************************************************************/

class CpuGeneric : public YambaDebug
{

public:
	unsigned int bitsToBytes(unsigned int bits)
	{
		LOG_ENTER("bits = %d", bits);
		unsigned int bytes = bits / bits_per_byte();
		if (bits % bits_per_byte() != 0)
			bytes++;
		return bytes;
	}

	
	virtual unsigned int bits_per_byte() const = 0;

};


/*******************************************************************************
 * struct BitPointer
 ******************************************************************************/

// A reference to the bitOffset bit within the byte referenced by bytePointer
struct BitPointer
{
	byte_t * bytePointer;
	unsigned int bitOffset;
};

/*******************************************************************************
 * class BitstringElement
 ******************************************************************************/

class BitstringLinkCast;

class BitstringElement : public YambaDebug
{

public:
	BitstringElement()
	{
		bytes = NULL;
	}
	
	
	byte_t * bytes;
	
	std::list<BitstringLinkCast * > linkCasts;
};

/*******************************************************************************
 * class BitstringLinkCast
 ******************************************************************************/

// This will be the base class for each specific LinkCast
class BitstringLinkCast : public YambaDebug
{
public:	

	// During phase 1 (compile), the LinkCast initializes it's state for 
	//	this object
	// During phase 2 (link), for each LinkCast the linker calls 
	//	finalizeCast. The finalize cast uses it's state and p to 
	//	determine it's final bits, then copies them into element at the 
	//	appropriate location within element.
	//
	// Precondition: 
	//	(1) element is the the parent BitString element that 
	//	    contains this BitstringLinkCast
	//	(2) p points to the first bit where element is allcoated in 
	//	    memory
	// Postcondition: the appropriate bits have been placed in memory
	//	at the appropriate place.
	virtual void finalizeCast(BitstringElement & element, 
		const BitPointer & p)  = 0;
};


/*******************************************************************************
 * class BitstringBuilder
 ******************************************************************************/

class BitstringFunction;

class BitstringBuilder : public YambaDebug
{
public:
	BitstringBuilder()//CpuGeneric * cpu)
	{
		numBits = 0;
		bytes = NULL;
	}
	
	unsigned int getNumBits() const
	{
		return numBits;
	}
	
	unsigned int getNumBytes() const
	{
		// throw exception of cpu == NULL
		return cpu->bitsToBytes(numBits);
	}
	
	void phase2()
	{
		bytes = new byte_t[getNumBytes()];
	}
	
				
	std::list<BitstringElement> elements;

	
	byte_t * bytes;
	
	unsigned int numBits;

protected:
	CpuGeneric * cpu;
	
	virtual void setCpu() = 0;


};


/*******************************************************************************
 * class BitstringFunction
 ******************************************************************************/

class BitstringFunction : public YambaDebug
{
public:
	virtual void compile(BitstringBuilder * builder) = 0;
};



} // End namespace Yamba

#endif
