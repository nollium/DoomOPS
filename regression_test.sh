#!/bin/bash

if [[ -z "$1" ]]
	then arg="all"
	else arg="bonus"
fi

make debug $arg --quiet

paths=$(find maps/mandatory/valid -name "*.cub")

for path in $paths ; do
	error=$(./cub3D $path --save 2>&1)
	if [ ! $? -eq 0 ]; then
		echo $error > log
		printf "\e[31mERROR ON $path\n$(cat $path)\n" >> log
		printf "\n$error\n" >> log
		cat log
		printf "\e[32mDebug with lldb?"
		read -p " [y/n] " -n 1 -r
		printf "\e[0m\n"
		if [[ $REPLY =~ ^[Yy]$ ]]
		then
			lldb -o run ./cub3D -- $path --save
		fi
		exit
	fi
done

paths=$(find maps/mandatory/invalid -name "*.cub")

for path in $paths ; do
	error=$(./cub3D $path --save 2>&1)
	if [ ! $? -eq 0 ] && [ ! "$error" = "MAP ERROR" ] && [ ! "$error" = "FILE INVALID ERROR" ];
	then
		echo $error > log
		printf "\e[31mERROR ON $path\n$(cat $path)\n" >> log
		printf "\n$error\n" >> log
		cat log
		printf "\e[32mDebug with lldb?"
		read -p " [y/n] " -n 1 -r
		printf "\e[0m\n"
		if 	[[ $REPLY =~ ^[Yy]$ ]]
		then
			lldb -o run ./cub3D -- $path --save
		fi
		exit
	fi
done

printf "\e[32mSUCCESS\n"
