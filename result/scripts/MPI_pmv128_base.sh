#!/bin/bash
#MSUB -r MPI_PMV      	   # Request name
#MSUB -n 128               # Number of cores
#MSUB -c 1
#MSUB -T 600               # Elapsed time limit in seconds
#MSUB -o sortie_128_base.o # Standard output. %I is the job id
#MSUB -e sortie_128_base.e # Error output. %I is the job id
#MSUB -A ocre              # Project ID
#MSUB -q rome              # partition
set -x
cd ${BRIDGE_MSUB_PWD}

ccc_mprun ./pmv_mpi -f mm/Goodwin_040.mtx
ccc_msub MPI_pmv256_base.sh

