#!/bin/bash
#MSUB -r MPI_PMV      	   # Request name
#MSUB -n 2                 # Number of cores
#MSUB -c 1
#MSUB -T 600               # Elapsed time limit in seconds
#MSUB -o sortie_2_coo.o    # Standard output. %I is the job id
#MSUB -e sortie_2_coo.e    # Error output. %I is the job id
#MSUB -A ocre              # Project ID
#MSUB -q rome              # partition
set -x
cd ${BRIDGE_MSUB_PWD}

ccc_mprun -x ./pmv_mpi -f mm/fidapm37.mtx -c
ccc_msub MPI_pmv4_coo.sh


