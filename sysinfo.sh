#!/bin/bash

# sysinfo_page - A script to produce a system information HTML file

##### Constants

TITLE="System Information for $HOSTNAME"
RIGHT_NOW="$(date +"%x %r %Z")"
TIME_STAMP="Updated on $RIGHT_NOW by $USER"
PROGNAME="$(basename $0)"

##### Functions
system_info()
{
    echo "<h2>System release info</h2>"
    echo "<pre>"
    lsb_release -a
    lscpu | grep Architecture:
    echo "</pre>"

}   # end of system_info - Will Im

free_memory()
{
    echo "<h2>Free system memory</h2>"
    echo "<pre>"
    free -h
    echo "</pre>"
}   # end of free_memory - Will Im

cpu_info()
{
    echo "<h2>Processor Info</h2>"
    echo "<pre>"
    inxi -C
    echo "</pre>"
}   #end of cpu_info - Will Im

speedtest()
{
    echo "<h2>System Bandwidth</h2>"
    echo "<pre>"
    speedtest-cli | grep Download: 
    echo "</pre>"
}   #end of speedtest - Will Im

report_title(){
    echo "<h1>$TITLE</h1>"
    echo "<p>$TIME_STAMP</p>"
}   # end of report_title - Will Im

list_users(){
    echo "<h2>System Users and their groups</h2>"
    echo "<pre>"
    for user in $(awk -F: '$3 >= 1000 {print $1}' /etc/passwd); do groups $user; done
    echo "</pre>"
}   # end of list_users - Will Im

get_ip()
{
    echo "<h2>System IP Address</h2>"
    echo "<pre>"
    ip route get 1.2.3.4 | awk '{print $7}'
    echo "</pre>"
}   # end of get_ip - Will Im

show_uptime()
{
    echo "<h2>System uptime</h2>"
    echo "<pre>"
    uptime
    echo "</pre>"

}   # end of show_uptime

drive_space()
{
    echo "<h2>Filesystem space</h2>"
    echo "<pre>"
    df
    echo "</pre>"

}   # end of drive_space

home_space() {
    echo "<h2>Home directory space by user</h2>"
    echo "<pre>"
    format="%8s%10s%10s   %-s\n"
    printf "$format" "Dirs" "Files" "Blocks" "Directory"
    printf "$format" "----" "-----" "------" "---------"
    if [ $(id -u) = "0" ]; then
        dir_list="/home/*"
    else
        dir_list=$HOME
    fi
    for home_dir in $dir_list; do
        total_dirs=$(find $home_dir -type d | wc -l)
        total_files=$(find $home_dir -type f | wc -l)
        total_blocks=$(du -s $home_dir)
        printf "$format" "$total_dirs" "$total_files" "$total_blocks"
    done
    echo "</pre>"

}   # end of home_space


write_page()
{
    cat <<- _EOF_
    <html>
        <head>
        <title>$TITLE</title>
        </head>
        <body>
        $(report_title)
        $(system_info)
	$(free_memory)
	$(cpu_info)
	$(speedtest)
	$(get_ip)
        $(show_uptime)
	$(list_users)
        $(drive_space)
        $(home_space)
        </body>
    </html>
_EOF_

}

usage()
{
    echo "usage: sysinfo_page [[[-f file ] [-i]] | [-h]]"
}


##### Main

interactive=1
filename=~/sysinfo_page.html

if [ "$(id -u)" != "0" ]; then
    echo "You must be logged in as root to access this script" >&2
    exit 1
fi

while [ "$1" != "" ]; do
    case $1 in
        -f | --file )           shift
                                filename=$1
                                ;;
        -i | --interactive )    interactive=1
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done

# Test code to verify command line processing

if [ "$interactive" = "1" ]; then

    response=

    read -p "Enter name of output file [$filename] > " response
    if [ -n "$response" ]; then
        filename="$response"
    fi

    if [ -f $filename ]; then
        echo -n "Output file exists. Overwrite? (y/n) > "
        read response
        if [ "$response" != "y" ]; then
            echo "Exiting program."
            exit 1
        fi
    fi
fi
echo "output file = $filename"


# Write page (comment out until testing is complete)

write_page > $filename
