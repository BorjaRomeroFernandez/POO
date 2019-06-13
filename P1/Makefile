CXX = clang++
STD = c++17
CXXFLAGS = -std=c++11 -g -Wall -Wextra -pedantic
CPPFLAGS = -DP1 -I../Tests-auto -I.
VPATH = ../Tests-auto:.

all: test-P1-auto test-P1-consola

test-consola: test-P1-consola
	@./$<

test-auto: test-P1-auto
	@./$<

test-P1-consola: test-P1-consola.o fecha.o cadena.o
	@$(CXX) $(CXXFLAGS) $^ -o $@

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
   test-auto.o cadena.o fecha.o

	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

check:
	make -f Make_check.mk checks

clean:
	make -f Make_check.mk clean
	rm -f *.o
	find . -type f \( -iname "test*" ! -iname "*.cpp" \) -delete