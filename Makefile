all:
	cache test

test: cache_lib.o
	clang++ -O3 -std=c++17 -Wall -Werror -pedantic -o $@ $^ test_cache_lib.cc

%.o : %.cc %.hh
	clang++ -O3 -std=c++17 -Wall -Werror -pedantic -c -o $@ $<
