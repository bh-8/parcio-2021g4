#!/bin/sh
FOLDER=$1
if !(test -d "${FOLDER}"); then
	echo "Please enter a valid path to a directory"
	exit 2
fi
if !(test -f "${FOLDER}/../gruppe.txt"); then
	echo "Please create gruppe.txt"
	exit 2
fi
if test -d "${FOLDER}/_abgabe"; then
	rm -r "${FOLDER}/_abgabe"
fi
cd "${FOLDER}/.."
find "${FOLDER}" -type f -name Makefile -print0 | \
	xargs -0 -I{} sh -c 'cd $(echo "{}" | cut -d "/" -f -2); make clean > /dev/null'
NAMES="$(cat "gruppe.txt" | cut -d ' ' -f 2 | tr -d '\n')"
cp -a -R --reflink=auto "${FOLDER}" "${NAMES}"
cp -a --reflink=auto "gruppe.txt" "${NAMES}/gruppe.txt"
test -f "${NAMES}.tar.gz" && rm "${NAMES}.tar.gz"
tar -czf "${NAMES}.tar.gz" "${NAMES}"
if !(test -d "${FOLDER}/_abgabe"); then
        mkdir "${FOLDER}/_abgabe"
fi
mv "${NAMES}.tar.gz" "${FOLDER}/_abgabe/${NAMES}.tar.gz"
rm -r "${NAMES}"
