//
// logging.h
//
// Michael N. Gagnon, December 2009
//
// Compiler portability:
// (1) This works fine on my version of g++
// 
// (2) Variadic macros are useful for logging, but are not a standardized C++
// feature.  If your compiler doesn't support this feature then
// you'll need to re-define these variadic macros as variadic functions
// (you'll have to pass __FILE__ and __func__ on your own--my main reason
// to not using variadic functions)
//
// (3) __func__ is also not a standardized feature.  If your compiler doesn't
// support __func__ see if it is available by a different name.  If not,
// just change references to __func__ to "[unknown]"
//

#ifndef __YAMBA_LOGGING_H__
#define __YAMBA_LOGGING_H__

#include <stdio.h>

#define LOGGING_OFF	-1
#define SEVERE		 0
#define WARNING		 1
#define INFO		 2
#define CONFIG		 3
#define FINE		 4	// entrances and normal-exits to/from functions
#define FINER		 5	
#define FINEST		 6

#define DEFAULT_LOG_LEVEL	FINEST

extern int log_level;
extern int temp_log_level;

#define BOOLSTR(boolval) ((boolval) ? "true" : "false")

#ifndef XSTR
	#define XSTR(s) STR(s)
	#define STR(s) #s
#endif

/* Logs a message to stderr
 * Example: LOG(WARNING, "one + one = %d", 2); 
 *
 * MVC++ note uses __FUNCTION__ instead of __func__
 */
#define LOG(level, format, ...) do { \
		if (level <= log_level) \
			fprintf(stderr, \
				"%s, line %s, %.%s(...): " format "\n", \
				__FILE__, XSTR(__LINE__), this->getObjectName(), __func__, __VA_ARGS__); \
	} while(0)

#define IF_LOG(level) if (level <= log_level)


/* Logs the entrance into a function. Make sure to specify all function 
 * arguments. 
 * Example: LOG_ENTER("*object=%p, num_bits=%d", (void *) object, num_bits);
 */
#define LOG_ENTER(format, ...) do { \
		if (FINE <= log_level) \
			fprintf(stderr, \
				"%s, line %s, %s.%s(" format "): entering function\n", \
				__FILE__, XSTR(__LINE__), this->getObjectName(), __func__, __VA_ARGS__); \
	} while(0)

#define LOG_ENTER_VOID() LOG_ENTER("%s", "")

/* Temporarily turn off logging. (Don't forget to LOG_RETURN_TO_NORMAL();)
 * This is mostly useful for testing correct handling of failures modes.  
 * I.e. we test that a function properly handles bad input.  This would 
 * normally generate error messages, but since we are expecting these errors,
 * we don't want them output to stderr.
 *
 * Don't nest these macros---they use globals
 */
#define TURN_OFF_LOG() do {			\
		temp_log_level = log_level;	\
		log_level = LOGGING_OFF;			\
	} while(0)

/* Temporarily turn on MAXIMUM logging. (Don't forget to 
 * LOG_RETURN_TO_NORMAL();) This is mostly useful for when you want to turn on 
 * logging for a single errant function.
 */
#define TURN_ON_MAX_LOG() do {			\
		temp_log_level = log_level;	\
		log_level = FINEST;		\
	} while(0) 

/* Return logging to previous level (after turning off with TURN_OFF_LOG();) */
#define LOG_RETURN_TO_NORMAL() (log_level = temp_log_level)



#endif
