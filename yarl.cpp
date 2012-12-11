/*
 *  runtime.c
 *  
 *  Michael N. Gagnon, October 2009
 *
 *  Mostly C99 ANSI C
 *  GNU-C specific language features should be explicitly identified (just grep for GNU-C)
 *
 *  Best viewed wiith tab-charcter === 8 "floating" spaces
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "runtime.h"


unsigned int BITS_PER_BYTE = CHAR_BIT;


/************************************************************************************************************
 * Constructors / destructors
 ************************************************************************************************************/

y_error_t new_element_simple(struct bitstring_element_simple_struct ** object, unsigned int num_bits)
{
	unsigned int num_bytes;

	LOG_ENTER("*object=%p, num_bits=%d", (void *) *object, num_bits);
	
	num_bytes = get_numbytes(num_bits);

	if (*object != NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NON_NULL_POINTER, "*object == %p, I refuse to overwrite a non-null pointer", (void *) *object);
	
	*object = (struct bitstring_element_simple_struct *) malloc(sizeof(struct bitstring_element_simple_struct));
	if (*object == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_OUT_OF_MEMORY, "%s",  "out of memory");
	LOG(FINER, "new *object at %p", (void *) *object);	
	
	LOG(FINER, "allocating (*object)->bits with %d bytes", num_bytes);	
	(*object)->bits = malloc(num_bytes * sizeof(byte_t));
	if ((*object)->bits == NULL)
	{
		free (*object);
		*object = NULL;
		RET_ERR(SEVERE, Y_RUNTIME_OUT_OF_MEMORY, "%s",  "out of memory");
	}
	
	(*object)->num_bits = num_bits;
	
	RET_GOOD();
}

y_error_t free_element_simple(struct bitstring_element_simple_struct ** object)
{
	LOG_ENTER("*object=%p", (void *) *object);
	
	if (*object == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NULL_POINTER, "%s",  "*object == NULL, I cannot free a NULL pointer");
	
	free((*object)->bits);
	free(*object);
	*object = NULL;
	
	RET_GOOD();
}

y_error_t new_element_ref(struct bitstring_element_reference_struct ** object, immut_str_t * identifier, struct bitstring_struct * bitstring)
{
	LOG_ENTER("*object=%p, identifier='%s', bistring=%p", (void *) *object, identifier, (void *) bitstring);
	
	if (*object != NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NON_NULL_POINTER, "*object == %p, I refuse to overwrite a non-null pointer", (void *) *object);
	if (identifier == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NULL_POINTER, "%s",  "identifier == NULL, but it should point to an immutable string");

	*object = (struct bitstring_element_reference_struct *) malloc(sizeof(struct bitstring_element_reference_struct));
	if (*object == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_OUT_OF_MEMORY, "%s",  "out of memory");
	LOG(FINER, "new *object at %p", (void *) *object);
	
	(*object)->identifier = identifier;
	(*object)->bitstring = bitstring;

	RET_GOOD();
}

y_error_t free_element_ref(struct bitstring_element_reference_struct ** object)
{
	LOG_ENTER("*object=%p", (void *) *object);
	
	if (*object == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NULL_POINTER, "%s",  "*object == NULL, I cannot free a NULL pointer");
	
	free(*object);
	*object = NULL;
	
	RET_GOOD();
}

y_error_t new_element_func(struct bitstring_element_func_struct ** object, struct yamaba_function_struct * yfunc)
{
	LOG_ENTER("*object=%p, yfunc='%s'", (void *) *object, yfunc == NULL ? "NULL" : yfunc->func_identifier);

	if (*object != NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NON_NULL_POINTER, "*object == %p, I refuse to overwrite a non-null pointer", (void *) *object);
	if (yfunc == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NULL_POINTER, "%s",  "yfunc == NULL, but it should point to a valid yamaba_function_struct object");
	
	*object = (struct bitstring_element_func_struct *) malloc(sizeof(struct bitstring_element_func_struct));
	if (*object == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_OUT_OF_MEMORY, "%s",  "out of memory");
	LOG(FINER, "new *object at %p", (void *) *object);

	(*object)->yfunc = yfunc;
	(*object)->params = NULL;
	
	if (yfunc->num_parameters > 0)
	{	
		LOG(FINEST, "creating an array of %d func_parameter_struct objects", yfunc->num_parameters);
		(*object)->params = (struct func_parameter_struct *) malloc(sizeof(struct func_parameter_struct) * yfunc->num_parameters);
		if ((*object)->params == NULL)
		{
			free(*object);
			*object = NULL;
			RET_ERR(SEVERE, Y_RUNTIME_OUT_OF_MEMORY, "%s",  "out of memory");
		}
		
		for (int i = 0; i < yfunc->num_parameters; i++)
		{
			(*object)->params[i].identifier = yfunc->formal_params[i];
			(*object)->params[i].value = 0;
			(*object)->params[i].bound = false;
			LOG(FINEST, "param #%d = '%s'", i + 1, (*object)->params[i].identifier);
		}
	}
	else
		LOG(FINEST, "%s", "no parameters for this object");

	
	RET_GOOD();
}

y_error_t free_element_func(struct bitstring_element_func_struct ** object)
{
	LOG_ENTER("*object=%p", (void *) *object);
	
	if (*object == NULL)
		RET_ERR(SEVERE, Y_RUNTIME_NULL_POINTER, "%s",  "*object == NULL, I cannot free a NULL pointer");
	
	if ((*object)->params != NULL)
		free((*object)->params);
	free(*object);
	*object = NULL;
	
	RET_GOOD();
}

/************************************************************************************************************
 * Helpers
 ************************************************************************************************************/


unsigned int get_numbytes(unsigned int numbits)
{
	if (numbits % BITS_PER_BYTE == 0)
		return  numbits / BITS_PER_BYTE;
	else
		return numbits / BITS_PER_BYTE + 1;
}

char * err_to_str(y_error_t err)
{
	switch (err) {
		case Y_RUNTIME_UNDEF:
			return stringify(Y_RUNTIME_UNDEF);
		case Y_RUNTIME_GOOD:
			return stringify(Y_RUNTIME_GOOD);
		case Y_RUNTIME_UNEXPECETED_ELEMENT_TYPE:
			return stringify(Y_RUNTIME_UNEXPECETED_ELEMENT_TYPE);
		case Y_RUNTIME_MISSING_IDENTIFIER:
			return stringify(Y_RUNTIME_MISSING_IDENTIFIER);
		case Y_RUNTIME_OUT_OF_MEMORY:
			return stringify(Y_RUNTIME_OUT_OF_MEMORY);
		case Y_RUNTIME_NULL_POINTER:
			return stringify(Y_RUNTIME_NULL_POINTER);
		case Y_RUNTIME_UNDEFINED_FUNCTION_BODY:
			return stringify(Y_RUNTIME_UNDEFINED_FUNCTION_BODY);
		case Y_RUNTIME_NON_NULL_POINTER:
			return stringify(Y_RUNTIME_NON_NULL_POINTER);	
		default:
			return "[Unknown error code]";
	}
}

/************************************************************************************************************
 * Data structure validators
 ************************************************************************************************************/

bool valid_bitstring_element_func_struct(struct bitstring_element_func_struct * element)
{
	LOG_ENTER("*element=%p=", (void *) element);
	
	if (element == NULL)
		RET_INVALID("%s", "element == NULL");
	
	if (element->yfunc == NULL)
		RET_INVALID("%s", "element->yfunc == NULL");
	
	for (int i = 0; i < element->yfunc->num_parameters; i++)
	{
		if (!ident_equal(element->params[i].identifier, element->yfunc->formal_params[i]))
			RET_INVALID("parameter #%d does not match: '%s' != '%s'", i, element->params[i].identifier, element->yfunc->formal_params[i]);
	}
		
	RET_VALID();
}

bool valid_and_bound_bitstring_element_func_struct(struct bitstring_element_func_struct * element, bool desired_bound)
{
	LOG_ENTER("*element=%p, desired_bound=%s", (void *) element, (desired_bound ? "true" : "false"));
	
	if (!valid_bitstring_element_func_struct(element))
		RET_INVALID("%s", "element is invalid (not even considering bindings)");
	
	for (int i = 0; i < element->yfunc->num_parameters; i++)
	{	
		if (element->params[i].bound != desired_bound)
		{
			if (desired_bound)
				RET_INVALID("parameter #%d is not bound, but it should be", i);
			else
				RET_INVALID("parameter #%d is bound, but it should NOT be bound", i);
		}
	}
	
	RET_VALID();
}