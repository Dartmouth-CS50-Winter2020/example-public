#!/bin/bash
#
# backup.sh - make a backup copy of all the .c files in current directory
#
# usage: backup.sh
# (no arguments)
#
# input: none
# output: a line of confirmation for each file backed up
#
# CS50, January 2020

for i in *.c
do
  echo "back up $i"
  cp "$i" "$i.bak"
done

exit 0
