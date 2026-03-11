#!/bin/bash

process=$1
trueprocess=$2
if [[ "$process" == "-9" && "$2" != "" ]]; then
	signal="-9"
	killprocess="$trueprocess"

elif [[ "$process" != "-9" && "$2" != "" ]]; then
	signal="-15"
	killprocess="$trueprocess"
else
	signal="-15"
	killprocess="$process"
fi

./ourpgrep.sh "$killprocess" | 
while read procid
do
	kill "$signal" "$procid"
done

# The conditionals are when process=$1 happen to contain a signal instead of the process name.

# The elif conditional is when a signal other than -9 is entered. It assumes then that you have something
# for trueprocess, which will now contain the process name.

#LIMITATION: This cannot run properly if trueprocess has a dash at the beginning.
#For example, ./ourpkill.sh nano -9 will put ourpkill.sh in a loop.
#In other words, the dash anything goes first.
