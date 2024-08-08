CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic -fsanitize=address,null -fno-omit-frame-pointer $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/cord.cc ./src/cord_utilities.cc ./includes/cord.hpp ./includes/cord_utilities.hpp ./includes/shared_pointer.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/cord.cc ./src/cord_utilities.cc -o $@

bin/tests: ./tests/tests.cc ./src/cord.cc ./src/cord_utilities.cc ./includes/cord.hpp ./includes/cord_utilities.hpp ./includes/shared_pointer.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/cord.cc ./src/cord_utilities.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* 
