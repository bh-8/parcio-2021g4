#!/bin/bash
echo -e '#!/bin/sh\nhyperfine -w 1 -m 10 -s basic -S dash \'
for i in clang gcc; do
	for j in 1 2 3 6 12 18 24; do
		for k in partdiff partdiff_blatt3_threaded; do
			echo -e "\t-n=\"$i $j $k\" -p=\"OPTFLAGS='-Ofast -march=native -pthread' CC=$i ./build.sh $k\" \"./$k $j 2 4096 2 2 1\" \\"
		done
	done
	for l in partdiff_orig; do
		echo -e "\t-n=\"$i 1 $l\" -p=\"OPTFLAGS='-Ofast -march=native' CC=$i ./build.sh $l\" \"./$l 1 2 4096 2 2 1\" \\"
	done
done
echo -e '\t--export-csv bench.csv --export-json bench.json --export-markdown bench.md'
