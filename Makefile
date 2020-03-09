flags = -std=c++17 -Wall -Werror -pedantic -O3
CXX = clang++

test: cache_lib.o fifo_evictor.o
	${CXX} ${flags} -o $@ $^ test_cache_lib.cc

clean:
	rm -rf *.o test

%.o : %.cc %.hh
	${CXX} ${flags} -c -o $@ $<
