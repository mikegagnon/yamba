/*
 *  y_smc.cpp
 *  
 *
 */


// C++ note: the "= 0" declares this as a "pure virtual function"

#include <list>

#include <iostream>


using namespace std;

typedef char byte_t;

unsigned int bits_to_bytes(unsigned int bits)
{
	unsigned bytes =  bits / 8;
	if (bits % 8 != 0)
		bytes++;
	return bytes;
}

class Bitstring
{
public:
	Bitstring(unsigned int maxBits)
	{
		this->maxBits = maxBits;
		currentBitIndex = 0;
		bytes = new byte_t[bits_to_bytes(maxBits)];
	}
	
	~Bitstring()
	{
		delete bytes;
	}
	
//private:
	byte_t * bytes;
	
	unsigned int currentBitIndex;
	unsigned int maxBits;
};

struct BitPointer
{
	byte_t * bytePointer;
	unsigned int bitOffset;
};

class BitstringElement;

// This will be the base class for each specific LinkCast
class BitstringLinkCast
{
public:	

	// During phase 1 (compile), the LinkCast initializes it's state for this object
	// During phase 2 (link), for each LinkCast the linker calls finalize_cast.
	//	The finalize cast uses it's state and p to determine
	//	it's final bits, then copies them into element at the appropriate
	//	location within element.
	//
	// Precondition: 
	//	(1) element is the the parent BitString element that 
	//	    contains this BitstringLinkCast
	//	(2) p points to the first bit where element is allcoated in 
	//	    memory
	// Postcondition: the appropriate bits have been placed in memory
	//	at the appropriate place.
	virtual void finalizeCast(BitstringElement & element, const BitPointer & p)  = 0;
};

class BitstringElement
{

public:
	BitstringElement()
	{
		bytes = NULL;
	}
	
	
	byte_t * bytes;
	
	list<BitstringLinkCast * > linkCasts;
	
	
};

class BitstringBuilder;


class BitstringFunction
{
public:
	virtual void compile(BitstringBuilder * builder) = 0;
	//virtual void appendTo(Bitstring * dest)  = 0;
	
	virtual unsigned int getMaxBits()  = 0;
	virtual unsigned int getMinBits()  = 0;
};

class BitstringBuilder
{
public:
	BitstringBuilder()
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
		return bits_to_bytes(numBits);
	}
	
	void phase2()
	{
		bytes = new byte_t[getNumBytes()];
		
	}

		
	list<BitstringElement> elements;

	
	byte_t * bytes;
	
	unsigned int numBits;

};




template <typename tq_result_t>
class FooGeneric
{

public:

	typedef void(*foo_func_t)( tq_result_t ** results);

	foo_func_t foo_tq;
	
	BitstringBuilder foo_tq_builder;
	
	virtual void build_foo_tq()
	{
		// assert foo_tq_builder.elements == empty
		
		// Phase 1: Compile
		
		prologue->compile(&foo_tq_builder);
		timer->compile(&foo_tq_builder);
		timer->compile(&foo_tq_builder);
		epilogue->compile(&foo_tq_builder);

			
		// Phase 2: Allocate, flatten, and link
		
		foo_tq_builder.phase2();
		
	}			
		
	BitstringFunction * timer;	

	BitstringFunction * prologue;
	
	BitstringFunction * epilogue;		

};


// Read some gotchas
// "Why am I getting errors when my template-derived-class uses a nested type it inherits from its template-base-class?"
// "Why am I getting errors when my template-derived-class uses a member it inherits from its template-base-class?"
// http://www.parashift.com/c++-faq-lite/templates.html#faq-35.18
// C++ is such a bizarre langauge.  You have to understand the compiler
// in order to understand the language.

template <typename tq_result_t>
class Foo_x86_32 : public FooGeneric<tq_result_t>
{

public:

	Foo_x86_32()
	{	
		
		this->prologue = new Prologue();
		this->epilogue = new Epilogue();
		this->timer = new Timer();
	
		this->build_foo_tq();

	}
	
	unsigned int getNumBits()
	{
		
		return this->foo_tq_builder.getNumBits();
	}
	
protected:
	
	class Prologue : public BitstringFunction
	{
	public:
		Prologue(){}
	
		void compile(BitstringBuilder * builder)
		{
			builder->numBits += 8;
		}
		
		unsigned int getMaxBits() {return 8;}
		unsigned int getMinBits() {return 8;}
	};


	class Epilogue : public BitstringFunction
	{
	public:
		void compile(BitstringBuilder * builder)
		{
			builder->numBits += 12;
		}
		
		unsigned int getMaxBits() {return 12;}
		unsigned int getMinBits() {return 12;}
	};

	class Timer : public BitstringFunction
	{
	public:
		void compile(BitstringBuilder * builder)
		{
			builder->numBits += 20;
		}
		
		unsigned int getMaxBits() {return 20;}
		unsigned int getMinBits() {return 20;}
	};



};


using namespace std;

int main()
{
	Foo_x86_32<int> foo;
	
	cout << "foo " << foo.getNumBits() <<  endl;
}
