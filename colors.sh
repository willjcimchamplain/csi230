#!/bin/bash

#Author: Will Im
#
#Class: CSI 230
#Assignment: 6.1
#Due Date: October 12, 2020
#
#Description:
#	This program takes a user input of a color and then outputs a line in the selected color
#
#Certification of Authenticity:
#	I certify that this is entirely my own work, except where I have given fully - documented references to the work of others.
#	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
#	-Reproduce this assignment and provide a copy to another member of the adacemic staff and / or 
#	-Communicate a copy of this assignment to a plagiarism checking service (which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
 
red='\033[0;31m'
green='\033[0;32m'
yellow='\033[0;33m'
blue='\033[0;34m'
magenta='\033[0;35m'
cyan='\033[0;36m'
default='\033[0m'

declare -a allColors=("red" "green" "yellow" "blue" "magenta" "cyan")

printf "Please enter your favorite color of the following:\n"
for i in "${allColors[@]}"
do
	printf "$i"
	printf "\n"
done

read -p "Your choice: " color
color=${color^^}

case $color in

	RED)
		selectedColor=$red
		;;

	GREEN)
		selectedColor=$green
		;;

	YELLOW)
		selectedColor=$yellow
		;;

	BLUE)
		selectedColor=$blue
		;;

	MAGENTA)
		selectedColor=$magenta
		;;

	CYAN)
		selectedColor=$cyan
		;;
	*)
		printf "Invalid entry\n"
		exit 1
		;;

esac

echo -e "${selectedColor}Your favorite color is ${color}${default}"

