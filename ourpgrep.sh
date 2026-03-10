#!/bin/bash

username=$(whoami)
process=$1

if [ "$process" != "" ]; then
	ps aux > processes.txt
	grep "$username" processes.txt > procuser.txt
	grep "$process" procuser.txt > procuserproc.txt
	grep -v "$0" procuserproc.txt | tr -s " " | cut -d " " -f 2 > procuserproc2.txt
	cat procuserproc2.txt

	rm procuserproc.txt | rm procuser.txt | rm processes.txt | rm procuserproc2.txt
else
	echo "ourpgrep: no matching criteria specified"
fi

# grep -v "$0" here just removes the instance of this script running. This is for bash, since without it,
# it lists down this script alongside the true instances of bash.

# tr here is used for deletion. In this case, since it has the -s tag, it combines all that are double-spaced
# into one space.

# cut here is for extraction of specific parts. -d is used as a delimiter; in this instance, it\'s the space we tr\'d.
# -f here indicates the field of each line. So -f 2 means the second field.

# Not yet tested for other test cases.
