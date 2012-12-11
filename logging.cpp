/*
 *  logging.h
 *
 *  Michael N. Gagnon, October 2009
 *
 *  Mostly C99 ANSI C
 *  GNU-C specific language features should be explicitly identified (just grep for GNU-C)
 *
 *  Best viewed wiith tab-charcter === 8 "floating" spaces
 */


#include "logging.h"

int log_level = DEFAULT_LOG_LEVEL;
int temp_log_level = DEFAULT_LOG_LEVEL;
