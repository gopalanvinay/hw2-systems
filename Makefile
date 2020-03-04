flags = -std=c++17 -Wall -Werror -pedantic -O3
CXX = clang++

all:
	test

clean:
	rm -rf *.o test

test: cache_lib.o
	${CXX} ${flags} -o $@ $^ test_cache_lib.cc

%.o : %.cc %.hh
	${CXX} ${flags} -c -o $@ $<
