#!/bin/bash
#MSUB -r MPI_PMV      	# Request name
#MSUB -n 2
#MSUB -c 1
#MSUB -N 1				   # Number of node
#MSUB -T 180               # Elapsed time limit in seconds
#MSUB -o sortie_2.o       # Standard output. %I is the job id
#MSUB -e sortie_2.e       # Error output. %I is the job id
#MSUB -A ocre              # Project ID
#MSUB -q rome
set -x
cd ${BRIDGE_MSUB_PWD}

ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx
ccc_msub MPI_job4.sh


