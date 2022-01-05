#!/bin/bash

#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --exclusive
#SBATCH --partition=vl-parcio

srun --mpi=pmi2 ./partdiff_blatt8_mpi 1 2 100 2 2 100