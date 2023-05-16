#!/bin/bash
#MSUB -r MPI_PMV      	# Request name
#MSUB -n 16
#MSUB -c 1
#MSUB -N 1				   # Number of node
#MSUB -T 180               # Elapsed time limit in seconds
#MSUB -o sortie_16.o       # Standard output. %I is the job id
#MSUB -e sortie_16.e       # Error output. %I is the job id
#MSUB -A ocre              # Project ID
#MSUB -q rome
set -x
cd ${BRIDGE_MSUB_PWD}

ccc_mprun ./pmv_mpi -f mm/fidapm37.mtx
ccc_msub MPI_job32.sh
