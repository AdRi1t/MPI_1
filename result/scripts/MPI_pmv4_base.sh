#!/bin/bash
#MSUB -r MPI_PMV      	   # Request name
#MSUB -n 4                 # Number of cores
#MSUB -c 1
#MSUB -T 600               # Elapsed time limit in seconds
#MSUB -o sortie_4_base.o   # Standard output. %I is the job id
#MSUB -e sortie_4_base.e   # Error output. %I is the job id
#MSUB -A ocre              # Project ID
#MSUB -q rome              # partition
set -x
cd ${BRIDGE_MSUB_PWD}

ccc_mprun -x ./pmv_mpi -f mm/fidapm37.mtx
ccc_msub MPI_pmv8_base.sh
