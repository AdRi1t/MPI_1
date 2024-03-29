#!/bin/bash
#MSUB -r MPI_PMV      	   # Request name
#MSUB -n 64                # Number of cores
#MSUB -c 1
#MSUB -T 600               # Elapsed time limit in seconds
#MSUB -o sortie_64_base.o  # Standard output. %I is the job id
#MSUB -e sortie_64_base.e  # Error output. %I is the job id
#MSUB -A ocre              # Project ID
#MSUB -q rome              # partition
set -x
cd ${BRIDGE_MSUB_PWD}

ccc_mprun -x ./pmv_mpi -f mm/fidapm37.mtx
ccc_msub MPI_pmv128_base.sh
