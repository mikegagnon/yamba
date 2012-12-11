/*
 *  runtime.h
 *  
 *  Michael N. Gagnon, October 2009
 *
 *  Mostly C99 ANSI C
 *  GNU-C specific language features should be explicitly identified (just grep for GNU-C)
 *
 *  Best viewed wiith tab-charcter === 8 "floating" spaces 
 */

#ifndef __YAMBA_RUNTIME_H__
#define __YAMBA_RUNTIME_H__

#include <stdbool.h>
#include <string.h>

#include "logging.h"

#define list_for_each(pos, head) \
	for (pos = (head); pos != NULL; pos = pos->next)

#define MAX_IDENTIFIER_LEN 256
							  
#define ident_equal(ident1, ident2) (strncmp((ident1), (ident2), MAX_IDENTIFIER_LEN) == 0)
//#define ident_equal(ident1, ident2) (strncmp(ident1, ident2, MAX_IDENTIFIER_LEN) == 0)

/************************************************************************************************************
 * Structs and typedefs (and some defines)
 ************************************************************************************************************/

/* A byte is the smallest addressable unit in memory.  It is not necessarily an octet */
typedef char byte_t;

typedef int y_error_t;

// Defined to be BITS_PER_BYTE = CHAR_BIT
// This could very well be defined using a macro, but defining it this way
//		allows me to vary BITS_PER_BYTE in test routines
extern unsigned int BITS_PER_BYTE; 

/* immut_str_t *'s should be treated like immutable strings  */
typedef char immut_str_t;

/* func_pointer_t is a typedef for a function pointer
 *	func_pointer_t takes a variable number of arguments
 *	preconditions:
 *		1. *object == NULL
 *			Else, return Y_RUNTIME_NON_NULL_POINTER
 *		2. func points to a fully bound function-bitstring element
 *			(a) func must be valid in the usual sense.  Additionally,
 *			(b) func->yfunc must point to this function
 *			(c) func->list must be fully bound
 *	postconditions:
 *		If all goes well, then (*object) points to a new simple bistring element, and returns Y_RUNTIME_GOOD
 *		Else, *object == NULL and returns an error condition
 * Yamba better do it's own type checking for these functions
 */
struct bitstring_element_simple_struct;
struct bitstring_element_func_struct;
typedef int param_t;
typedef y_error_t (*func_pointer_t)(struct bitstring_element_simple_struct ** object, struct bitstring_element_func_struct * func);



/* There three types of bitstring_elements
 *		1. simple: a string of fully defined bits
 *		2. reference: a reference to another bitstring
 *		3. function: a referencce to a function which takes parameters of type param_t and returns simple bitstring element
 */

/*  1. Simple bitstring element */
struct bitstring_element_simple_struct
{
	// Array of bytes
	// When the last byte isn't full, the bits are flushed left (to the most significant portion of the byte)
	byte_t * bits;
	unsigned int num_bits;
};

/* 2. Reference bitstring element */
struct bitstring_element_reference_struct
{
	immut_str_t * identifier;
	struct bitstring_struct * bitstring;
};

/* 3. Function bitstring element */
struct bitstring_element_func_struct
{
	struct yamaba_function_struct * yfunc;
	
	/* array of "actual" parameters
	 * length of params == yfunc->num_parameters;
	 * before func may be called, all parameters must be bound.
	 * list must have exactly yfunc->num_parameters elements, corresponding to the parameters of yfunc
	 */
	struct func_parameter_struct * params;
};

struct yamaba_function_struct
{
	immut_str_t * func_identifier;
	func_pointer_t func;
	
	int num_parameters;
	
	/* array of "formal" parameters. 
	 * Since all parameters have same type, formal paramter is composed of just a string identifier.
	 * Hence, formal_params is an array of pointers to strings
	 */
	immut_str_t ** formal_params;
};

/* represents "actual" parameters */
struct func_parameter_struct
{
	immut_str_t * identifier;
	param_t value; 	
	
	/* parameters may be bound or unbound
	 * if bound, then value is defined
	 * if not bound, then value is not defined
	 */
	bool bound;
};


/* When binding a bitstring, the caller passes the bs_bind function
 * a list of bindings.  Each binding in the list is represented
 * by an instance of this struct
 */
typedef int bs_bind_lval_type_t;
#define Y_BIND_LVAL_TYPE_UNDEFINED 0
#define Y_BIND_LVAL_TYPE_PARAM 1
#define Y_BIND_LVAL_TYPE_BITSTRING_ELEMENT 2

/* A bitstring binding may be one of two things
 *	(1) a binding to a parameter 
 *	(2) a binding to bistring-element
 * If (1) then the type of left-hand value (lval_type) better be Y_BIND_LVAL_TYPE_PARAM
 * If (2) then lval_type better be Y_BIND_LVAL_TYPE_BITSTRING_ELEMENT
 */
struct bs_bindings_struct
{
	bs_bind_lval_type_t lval_type;
	
	/* the identifier of the l-value */
	immut_str_t * left_identifier;

	/* if lval_type == Y_BIND_LVAL_TYPE_PARAM, then the value of the parameter binding
	 */
	param_t value; 	
	
	/* if lval_type == Y_BIND_LVAL_TYPE_BITSTRING_ELEMENT
	 */
	struct bitstring_struct * bitstring_element_struct; 
	 	
	struct bs_bindings_struct * next;
};

typedef int element_type_t;
#define Y_ELEMENT_UNDEFINED_TYPE 0
#define Y_ELEMENT_SIMPLE_TYPE 1
#define Y_ELEMENT_REF_TYPE 2
#define Y_ELEMENT_FUNC_TYPE 3


struct bitstring_element_struct
{
	/* Specifies which type of element this is
	 * The valye of element_type
	 */
	element_type_t element_type;
	
	/* Yes, this could be a union.  But it's easier 
	 * to debug type errors when it's not.
	 * Only the specified element_type pointer may be defined as non-null
	 * all others must be null
	 */
	struct bitstring_element_simple_struct * simple;
	struct bitstring_element_reference_struct * ref;
	struct bitstring_element_func_struct * func;
	
	/* next in the list */
	struct bitstring_element_struct * next;
};

/* a bitstring is just a list of bitstring elements*/
struct bitstring_struct
{
	struct bitstring_element_struct * list;
	immut_str_t * identifier;
};


/************************************************************************************************************
 * Public function headers (and some defines and typedefs)
 ************************************************************************************************************/

#define stringify(macro) #macro

#define Y_RUNTIME_UNDEF	-1
#define Y_RUNTIME_GOOD 0
#define Y_RUNTIME_UNEXPECETED_ELEMENT_TYPE 1
#define Y_RUNTIME_MISSING_IDENTIFIER 2
#define Y_RUNTIME_OUT_OF_MEMORY 3
#define Y_RUNTIME_NULL_POINTER 4
#define Y_RUNTIME_UNDEFINED_FUNCTION_BODY 5
#define Y_RUNTIME_NON_NULL_POINTER 6
char * err_to_str(y_error_t err);

y_error_t bs_bind(struct bitstring_struct * bs, struct bs_bindings_struct * bindings);
y_error_t bs_repeat(struct bitstring_struct * bs, int n);

/* Concatenates all bitstring elements in bs
 * precondition: 
 *		1. Every element in bs is a simple-bitstring element.
 *		   Else, (a) return Y_RUNTIME_UNEXPECETED_ELEMENT_TYPE and (b) bs is unchanged
 * postcondition: 
 *		1. bs contains a single simple-bistring element
 *		2. discarded elements are freed from memory
 *		3. returns Y_RUNTIME_GOOD
 */
y_error_t bs_concat(struct bitstring_struct * bs);

/* Creates a new bitstring and creates a deep copy of bs_old
 * precondition:
 */		
y_error_t bs_deepcopy(struct bitstring_struct * bs_old, struct bitstring_struct ** bs_new);

/**** Constructors / destructors ****************************************************************************/

/* Commonalities:
 *
 * For all "free_xxx" functions:
 *		Deallocates an object
 *		preconditions:
 *			1. *object points to an allocated object (non-null)
 *				Else, return Y_RUNTIME_NULL_POINTER
 *		postconditions:
 *			2. *object == NULL
 *		returns:
 *			Y_RUNTIME_NULL_POINTER
 *			Y_RUNTIME_GOOD
 *
 * For all "new_xxx" functions:
 *		Allocates (and sometimes initializes) an object
 *		preconditions:
 *			1. *object == NULL
 *				Else, return Y_RUNTIME_NON_NULL_POINTER
 *		postconditions:
 *			1. *object points to the newly allocated object
 *			2. This procedure makes shallow copies of immut_str_t pointers
 *				This is OK because immut_str_t strings are treated like immutable (don't modify them).
 *		returns:
 *			Y_RUNTIME_GOOD
 *			Y_RUNTIME_OUT_OF_MEMORY
 *			Y_RUNTIME_NON_NULL_POINTER
 */

/* new_element_simple: Creates a new simple element
 * postconditions (additional):
 *		1. (*element)->bits has been allocated to hold the minimum number of bytes necessary to hold numbits bits
 */
y_error_t new_element_simple(struct bitstring_element_simple_struct ** object, unsigned int numbits);
y_error_t free_element_simple(struct bitstring_element_simple_struct ** object);

/* new_element_ref: Creates a new reference element
 * preconditions  (additional):
 *		1. bitstring is either null or points to bitstring object
 * postconditions (additional):
 *		1. Shallow copy of bitstring
 * returns (additional):
 *		Y_RUNTIME_NULL_POINTER (if identifier == NULL)
 */
y_error_t new_element_ref(struct bitstring_element_reference_struct ** object, immut_str_t * identifier, struct bitstring_struct * bitstring);
y_error_t free_element_ref(struct bitstring_element_reference_struct ** object);

/* new_element_func: Creates a new function-reference element
 * preconditions  (additional):
 *		1. yfunc points to a yamba function object
 * postconditions (additional):
 *		1. Shallow copy of yfunc
 *		2. (*object)->list points to the (new) list of parameter bindings for yfunc
 *			list has exactly yfunc->num_parameters elements
 *			each parameter of list is appropriately defined w.r.t. the appropriate yfunc parameter
 *			each parameter is unbound
 * returns (additional):
 *		Y_RUNTIME_NULL_POINTER (if yfunc == NULL)
 */
y_error_t new_element_func(struct bitstring_element_func_struct ** object, struct yamaba_function_struct * yfunc);

/* free_element_func:
 * postconditions (additional):
 *		1. (*object)->params has been freed (if not NULL)
 */
y_error_t free_element_func(struct bitstring_element_func_struct ** object);

/************************************************************************************************************
 * Helper function headers (and some defines and typedefs)
 ************************************************************************************************************/

/* returns the minimum number of bytes necessary to hold numbits bits 
 * Note: numbytes(0) = 0
 */
unsigned int get_numbytes(unsigned int numbits);

/************************************************************************************************************
 * Data structure validators
 ************************************************************************************************************/

/* Definition of valid:
 *	1. element is non-NULL
 *	2. element->yfunc is non-NULL
 *	3. element->list has exactly yfunc->num_parameters items
 *	4. For each item in element->list:
 *		(a) identifer is equivalent to the appropriate yfunc identifier
 */
bool valid_bitstring_element_func_struct(struct bitstring_element_func_struct * element);

/* Definition of valid:
 *	1. valid according to valid_bitstring_element_func_struct(...)
 *	2. For each item in element->list:
 *		(a) bound == desired_bound
 */	
bool valid_and_bound_bitstring_element_func_struct(struct bitstring_element_func_struct * element, bool desired_bound);

#endif