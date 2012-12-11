/*
 *  y_pagefault.cpp
 *  
 *
 */


// C++ note: the "= 0" declares this as a "pure virtual function"


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

class BitstringFunction
{
public:
	virtual void appendTo(Bitstring * dest)  = 0;
	
	virtual unsigned int getMaxBits()  = 0;
	virtual unsigned int getMinBits()  = 0;
};


template <typename tq_result_t>
class PagefaultGeneric
{

public:

	typedef void(*pagefault_func_t)(tq_result_t ** results, byte_t * first_page);

	//typedef void(*pagefault_func_t)(byte_t * first_page);

	//typedef char foo;

	pagefault_func_t pagefault_tq;
	
	virtual void build_pagefaultBitstring_tq(unsigned int unroll_degree)
	{

		pagefaultBitstring_tq = new Bitstring(prologue->getMaxBits() + 
			timer->getMaxBits() * 2 +
			touch->getMaxBits() * unroll_degree +
			epilogue->getMaxBits());
		

		
		prologue->appendTo(pagefaultBitstring_tq);

		timer->appendTo(pagefaultBitstring_tq);
		
		for(unsigned int i = 0; i < unroll_degree; i++)
		{
			touch->appendTo(pagefaultBitstring_tq, i);
		}
		
		timer->appendTo(pagefaultBitstring_tq);
		epilogue->appendTo(pagefaultBitstring_tq);
		

		pagefault_tq = (pagefault_func_t) pagefaultBitstring_tq->bytes;
			
	}			
	
	// The result of build
	Bitstring * pagefaultBitstring_tq;
	
	BitstringFunction * timer;	

	BitstringFunction * prologue;
	
	BitstringFunction * epilogue;


	class BitstringFunctionTouch: public BitstringFunction
	{
	public:
		virtual void appendTo(Bitstring * dest, unsigned int page_index) = 0;
	protected:
		virtual void appendTo(Bitstring * dest) = 0;
	};


	BitstringFunctionTouch * touch;
		

};


// Read some gotchas
// "Why am I getting errors when my template-derived-class uses a nested type it inherits from its template-base-class?"
// "Why am I getting errors when my template-derived-class uses a member it inherits from its template-base-class?"
// http://www.parashift.com/c++-faq-lite/templates.html#faq-35.18
// C++ is such a bizarre langauge.  You have to understand the compiler
// in order to understand the language.

template <typename tq_result_t>
class Pagefault_x86_32 : public PagefaultGeneric<tq_result_t>
{
//	typedef void(*pagefault_func_t)( tq_result_t ** results, byte_t * first_page);

	//typedef void(*pagefault_func_t)(byte_t * first_page);

	//typedef char foo;

public:

	Pagefault_x86_32(unsigned int unroll_degree)
	{	
		
		this->prologue = new Prologue();
		this->epilogue = new Epilogue();
		this->timer = new Timer();
		this->touch = new Touch();
	
		this->build_pagefaultBitstring_tq(unroll_degree);

	}
	
	unsigned int getSize()
	{
		
		return this->pagefaultBitstring_tq->currentBitIndex;
	}
	
protected:
	
	class Prologue : public BitstringFunction
	{
	public:
		Prologue(){}
	
		void appendTo(Bitstring * dest)
		{
			dest->currentBitIndex += 8;
		}
		
		unsigned int getMaxBits() {return 8;}
		unsigned int getMinBits() {return 8;}
	};


	class Epilogue : public BitstringFunction
	{
	public:
		virtual void appendTo(Bitstring * dest)
		{
			dest->currentBitIndex += 12;
		}
		
		virtual unsigned int getMaxBits() {return 12;}
		virtual unsigned int getMinBits() {return 12;}
	};

	class Timer : public BitstringFunction
	{
	public:
		virtual void appendTo(Bitstring * dest)
		{
			dest->currentBitIndex += 20;
		}
		
		virtual unsigned int getMaxBits() {return 20;}
		virtual unsigned int getMinBits() {return 20;}
	};

	class Touch : public PagefaultGeneric<tq_result_t>::BitstringFunctionTouch
	{
	public:
		virtual void appendTo(Bitstring * dest, unsigned int page_index)
		{
			dest->currentBitIndex += 50;
		}
		
		virtual unsigned int getMaxBits() {return 50;}
		virtual unsigned int getMinBits() {return 50;}
		
		virtual void appendTo(Bitstring * dest)
		{
			dest->currentBitIndex += 13;
		}
		
	};

};



using namespace std;

int main()
{
	Pagefault_x86_32<double> pf(2);

	byte_t x[5];
	double a = 5;
	double * b = &a;
	
	//pf.pagefault_tq(&b, x);

	cout << "size = " << pf.getSize() << endl;
}