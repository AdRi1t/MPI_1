CCPP=mpic++
CPPFLAGS= -Wall -g
all: main.o

main.o : main.cpp func.cpp
	${CCPP} $^ -o $@  ${CPPFLAGS}

clean:
	rm -rf *.o