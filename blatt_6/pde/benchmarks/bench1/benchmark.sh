#!/bin/sh
hyperfine -w 1 -m 10 -s basic -S dash \
	-n="1" -p="OPTFLAGS='-Ofast -march=native -pthread' CC=gcc ./build.sh partdiff_blatt3_threaded" "./partdiff_blatt3_threaded 1 2 4096 2 2 109" \
	-n="2" -p="OPTFLAGS='-Ofast -march=native -pthread' CC=gcc ./build.sh partdiff_blatt3_threaded" "./partdiff_blatt3_threaded 2 2 4096 2 2 109" \
	-n="3" -p="OPTFLAGS='-Ofast -march=native -pthread' CC=gcc ./build.sh partdiff_blatt3_threaded" "./partdiff_blatt3_threaded 3 2 4096 2 2 109" \
	-n="6" -p="OPTFLAGS='-Ofast -march=native -pthread' CC=gcc ./build.sh partdiff_blatt3_threaded" "./partdiff_blatt3_threaded 6 2 4096 2 2 109" \
	-n="12" -p="OPTFLAGS='-Ofast -march=native -pthread' CC=gcc ./build.sh partdiff_blatt3_threaded" "./partdiff_blatt3_threaded 12 2 4096 2 2 109" \
	-n="18" -p="OPTFLAGS='-Ofast -march=native -pthread' CC=gcc ./build.sh partdiff_blatt3_threaded" "./partdiff_blatt3_threaded 18 2 4096 2 2 109" \
	-n="24" -p="OPTFLAGS='-Ofast -march=native -pthread' CC=gcc ./build.sh partdiff_blatt3_threaded" "./partdiff_blatt3_threaded 24 2 4096 2 2 109" \
	--export-csv bench.csv --export-json bench.json --export-markdown bench.md
