#!/bin/bash

#Author: Will Im
#
#Class: CSI 230
#Assignment: 6.2 - converter.sh
#Due Date: October 15, 2020
#
#Description:
#	This program recieves an input file from the user, and then outputs that file in either all upper case or lower case numbers
#	The program demonstrates my ability to recieve a file, and check if the file exists as the program will output an error if an invalid file name in given
#
#Certification of Authenticity:
#	I certify that this is entirely my own work, except where I have given fully - documented references to the work of others.
#	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
#	-Reproduce this assignment and provide a copy to another member of the adacemic staff and / or 
#	-Communicate a copy of this assignment to a plagiarism checking service (which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)

#To run this correctly, run "./converter.sh -f homer.txt -c U > upperfile.txt" for uppercase conversion
#Run "./converter.sh -f homer.txt -c L > upperfile.txt" for lowercase conversion
#The correct format or any errors will be placed in "upperfile.txt" to avoid clogging the console

usage()
{
	echo "$0 usage: [-f input filed] [-c U(upper) or L(lower)"
	exit 1
}

fileError()
{
	echo "Error: file does not exist"
	exit 1
}

while getopts ":f:c:" options;
do
	case "${options}" in
		f)
			f=${OPTARG}
			#TO DO IF FILE IS HERE, IF NOT USAGE
			if [ -e $f ]; then
				echo "${f} - found"
			else
				fileError
			fi
		;;
		c)
			c=${OPTARG}
			if [[ ${c} == "U" || ${c} == "L" ]]; then 
				echo "${f} - ${c}"
			else
				usage
			fi
		;;
		*)
			usage
		;;
	esac
done
#conversion logic here

while read line
do
	if [ ${c} == "U" ]; then
		echo $line | tr [:lower:] [:upper:]
	else
		echo $line | tr [:upper:] [:lower:]
	fi
done < $f


exit 0
