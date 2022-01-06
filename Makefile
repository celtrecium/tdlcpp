CC=g++
CXXFLAGS=-pedantic -Wall -Wextra -Wsign-conversion -Wconversion -Wshadow -ltdl -ltdlcpp -lu8string -lsbvector
OBJ=main.o

all: options main.o demo

options:
	@echo demo build options:
	@echo "CXX	= $(CXX)"
	@echo "CXXFLAGS	= $(CXXFLAGS)"
	@echo

clean:
	rm -rf demo

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $^

demo: ${OBJ}
	${CXX} ${CXXFLAGS} $^ -o $@
	rm -rf ${OBJ}
	@echo "Now you can run ./demo"
