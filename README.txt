
Yamba runtime library (Yarl)

Michael N. Gagnon, December 2009

Yarl is written in C++ and uses non-standardized C++ features, such as:
	1. The <stdint.h> library to get uint64_t (ISO C++ doesn't even allow
       64-bit integers via long long). 
	2. Variadic macros

It's difficult to precisely identify the non-standardized features since g++
-ansi -pedantic doesn't seem to rule them out.  Plus the C++ standard is not
freely available.  But these C++ features are a part of C99 so will hopefully
be in future C++ standards and are hopefully compiler extensions on your
compiler.

At this time I've only tested this code with g++ but I plan to get it working
for Microsoft Visual C++.

Source code best viewed with 80-charcter gutter and 8-character floating tabs.
