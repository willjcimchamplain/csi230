#!/bin/bash

#Author: Will Im
#
#Class: CSI 230
#Assignment: 6.2 - hostLookup.sh
#Due Date: October 15, 2020
#
#Description:
#	This program recieves a file of domain addresses from the user, then outputs the public ip addressed linked with those domains
#	The program demonstrates my ability to recieve, validate, and parse user input
#
#Certification of Authenticity:
#	I certify that this is entirely my own work, except where I have given fully - documented references to the work of others.
#	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
#	-Reproduce this assignment and provide a copy to another member of the adacemic staff and / or 
#	-Communicate a copy of this assignment to a plagiarism checking service (which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)

#To run this correctly, run "./hostLookup.sh", and then input the text filename when prompted

fileError()
{
	echo "Error: file does not exist"
	exit 1
}

echo "Please enter the file name: "

read filename

if [ -e $filename ]; then
	echo "${filename} - found"
else
	fileError
fi

while read h; do
	out=$(host -W1 -t A $h)
	if [ $? -eq 0  ]; then
		ip=$(echo $out | cut -d " " -f 4)
		echo $h - $ip
	else
		echo "${h} - not found"
	fi
done < $filename

