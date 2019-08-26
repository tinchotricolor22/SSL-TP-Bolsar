#!/usr/bin/env bash

array=`find src/. -name "*.c" -not -path "*main.c*"`
executableFiles=""

for i in $array
do
	oldFullPath=${i#"src/"}
	oldFullPath="custom_build/${oldFullPath%'.c'}"
	fileNameObject="${oldFullPath##*/}.o"
	directoryPath=${oldFullPath%/*}
	
	mkdir -pv $directoryPath
	filePath="$directoryPath.o"

	newFullPath="$directoryPath/$fileNameObject"
    gcc -c $i -o $newFullPath
    executableFiles="$executableFiles $newFullPath "
done

gcc -c src/main.c -o 'custom_build/main.o'
executableFiles="$executableFiles custom_build/main.o"
gcc -o SS_TP_BOLSAR $executableFiles