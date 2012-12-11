#
# Yamba runtime makefile
#
# Michael N. Gagnon, October 2009
#

CPP=g++
CFLAGS=-ansi -pedantic -g -Wno-variadic-macros
COMPILE=$(CPP) $(CFLAGS) -c

CLEANABLE=test_yarl_common test_yarl_common.o testing.o logging.o

all: test_yarl_common test_timers

clean:
	rm $(CLEANABLE)

memcheck: test_runtime
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./test_runtime
	
logging.o: logging.h logging.cpp
	$(COMPILE) logging.cpp
	
testing.o: testing.h testing.cpp logging.h
	$(COMPILE) testing.cpp

timers.o: timers.h timers.cpp yarl_common.h
	$(COMPILE) timers.cpp

test_timers.o: test_timers.cpp yarl_common.h timers.h testing.h logging.h x86_32.h
	$(COMPILE) test_timers.cpp
	
test_timers: test_timers.o testing.o logging.o
	$(CPP) $(CFLAGS) test_timers.o testing.o logging.o -o test_timers
	
test_yarl_common.o: test_yarl_common.cpp yarl_common.h testing.h logging.h
	$(COMPILE) test_yarl_common.cpp
	
test_yarl_common: test_yarl_common.o testing.o logging.o
	$(CPP) $(CFLAGS) test_yarl_common.o testing.o logging.o -o test_yarl_common
