#!/bin/bash
echo -e '#!/bin/sh\nhyperfine -w 1 -m 3 -s basic -S dash \'
for l in clang gcc; do
	for i in dynamic guided static; do
		for k in ELEMENT COLUMN ROW; do
			for j in {1..24}; do
				echo -e "\t-n=\"$k OMP_SCHEDULE=$i THREADS=$j CC=$l\" -p=\"OPTFLAGS='-Ofast -march=native -fopenmp -D $k' PGO=false STRIP=true CC=$l ./build.sh\" \"OMP_SCHEDULE=$i ./partdiff $j 2 4096 2 2 1\" \\"
			done
		done
	done
done
echo -e '\t--export-asciidoc bench.adoc --export-csv bench.csv --export-json bench.json --export-markdown bench.md'
