CCPP=mpic++
CPPFLAGS= -g
all: pmv_mpi

pmv_mpi: main.o matrix.o MPI_function.o sparse_matrix.o mmio.o
	${CCPP} -o $@ $^ ${CPPFLAGS}

main.o : main.cpp
	${CCPP} -c $^ -o $@  ${CPPFLAGS}
matrix.o : matrix.cpp 
	${CCPP} -c $^ -o $@  ${CPPFLAGS}
MPI_function.o: MPI_function.cpp 
	${CCPP} -c $^ -o $@  ${CPPFLAGS}
sparse_matrix.o : sparse_matrix.cpp
	${CCPP} -c $^ -o $@  ${CPPFLAGS}
mmio.o : mmio.c
	mpicc -c $^ -o $@

clean:
	rm -rf *.o pmv_mpi
	
clear_output:
	rm -rf *.txt
