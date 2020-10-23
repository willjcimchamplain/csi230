#!/bin/bash

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
