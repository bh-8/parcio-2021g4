#!/bin/bash
#SBATCH --partition=vl-parcio		# spezifizierte Partition
#SBATCH --time=5					# 5 Minuten bis timeout
#SBATCH --output=timescript.out		# output file
#SBATCH --nodes=4					# 4 Knoten anfordern (-N)
#SBATCH --ntasks=4					# 4 Ausführungen (-n)
#SBATCH --cpus-per-task=1			# 1 Ausführung pro Knoten
#SBATCH --wait						# auf Beendigung aller Jobs warten

srun ./timescript.sh

#Done
echo fertig>jobscript.out
#EOF