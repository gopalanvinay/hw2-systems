flags = -Wno-c++11-extensions -std=c++17 -Wall -Werror -pedantic

all:
	test

clean:
	rm *.o

test: cache_lib.o
	clang++ ${flags} -o $@ $^ test_cache_lib.cc

%.o : %.cc %.hh
	clang++ ${flags} -c -o $@ $<
