#!/bin/bash
#
# backup-diff.sh - compare all the .c files in current directory with backup
#
# usage: backup-diff.sh
# (no arguments)
#
# input: none
# output: a line of information for each file, and diffs where they differ
# exit status: zero.
#
# CS50, January 2020

for i in *.c
do
  if [ ! -r "$i.bak" ]
  then
  	echo "$i - no backup" 
  else
  	if cmp --quiet "$i.bak" "$i" 
  	then
  		echo "$i unchanged"
  	else
  		echo "$i differences:"
  		diff "$i.bak" "$i" 
  	fi
  fi
done

exit 0

