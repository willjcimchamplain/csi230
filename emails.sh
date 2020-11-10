#!/bin/bash

#Author: Will Im
#
#Class: CSI 230
#Assignment: Project 2
#Due Date: October 22, 2020
#
#Description:
#	This program takes emails from a text file, and automatically creates accounts with passwords
#	The program then sends emails to the users with their credentials 
#	All resources used for help are credited in the project2Notes.txt file in my github
#
#Certification of Authenticity:
#	I certify that this is entirely my own work, except where I have given fully - documented references to the work of others.
#	I understand the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
#	-Reproduce this assignment and provide a copy to another member of the adacemic staff and / or 
#	-Communicate a copy of this assignment to a plagiarism checking service (which may then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
 

# Declares variables
filename="emails.txt"
emails=`cat $filename`
groupname="csi230"

# Checks if user is logged in as root
if [ "$EUID" -ne 0 ]
	then echo "Must be logged in as root user!"
	exit
fi

# Creates a group, if the group is already created, that will be used
addgroup $groupname

# For loop runs through each email, processing all information for the current email, and generating and deleting a password within the bounds of the loop
for currentEmail in $emails; do
	# Sets the username and generates a password for the current loop
	username=$( echo "$currentEmail" | cut -f1 -d"@")
	password=$(openssl rand -base64 16 | colrm 17)

	# Adds the current user, assigns the username and password, then adds the user to the given group
	useradd -m $username
	echo -e "$password\n$password" | passwd $username
	adduser $username $groupname

	# Sends email using the mail command, first test is the body, then after the pipeline, we enter the subject, sender, and recipient (Which is the current email in the loop)
	echo -e "Username: $username \nPassword: $password" | mail -s "csi230 demo" -a From:Will\<will@aptlabs.net\> $currentEmail

	# Sets password to NULL 
	password="NULL"

	# Requires the user to change password on the first logon
	chage -d 0 $username

	# Sets the user's shell to bash
	usermod --shell /bin/bash $username
done
