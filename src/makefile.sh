#!/usr/bin/env bash

array=`find . -name "*.c" -not -path "*output/*" -not -path "*main.c*"`
executableFiles=""

for i in $array
do
	oldFullPath=${i#"./"}
	oldFullPath="output/${oldFullPath%'.c'}"
	fileNameObject="${oldFullPath##*/}.o"
	directoryPath=${oldFullPath%/*}
	
	mkdir -pv $directoryPath
	filePath="$directoryPath.o"

	newFullPath="$directoryPath/$fileNameObject"
    gcc -c $i -o $newFullPath
    executableFiles="$executableFiles $newFullPath "
done

gcc -c main.c -o 'output/main.o'
executableFiles="$executableFiles output/main.o"
gcc -o webscrapping.exe $executableFiles