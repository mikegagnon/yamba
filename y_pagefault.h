/*
 *  y_pagefault.h
 *
 */
 
// C++ note: 
//	the "= 0" declares this as a "pure virtual function"
//	the "const" declares the function as a "const function"


typedef char byte_t;

// <void c_function(void ** results, byte_t * first_page)>

//typedef (*pagefault_func_t)(tq_result_t ** results, byte_t * first_page)

//byte_t * pagefault_func_bytes;

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
	
private:
	byte_t * bytes;
	
	unsigned int currentBitIndex;
	unsigned int maxBits;
	
};


class BitstringFunction
{
public:
	virtual void appendTo(Bitstring * dest) const = 0;
	virtual unsigned int getMaxBits() const = 0;
	virtual unsigned int getMinBits() const = 0;
};



template <typename tq_result_t>
class PagefaultGeneric
{
	typedef void(*pagefault_func_t)( tq_result_t ** results, byte_t * first_page);

	//typedef void(*pagefault_func_t)(byte_t * first_page);

	//typedef char foo;

public:
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
			
	}			
	
	// The result of build_pagefaultBitstring_tq;
	Bitstring * pagefaultBitstring_tq;
	
	BitstringFunction * timer;	

	BitstringFunction * prologue;
	
	BitstringFunction * epilogue;


	class BitstringFunctionTouch: public BitstringFunction
	{
	public:
		virtual void appendTo(Bitstring * dest, unsigned int page_index) const = 0;
	protected:
		virtual void appendTo(Bitstring * dest) const = 0;
	};


	BitstringFunctionTouch * touch;
		

};

