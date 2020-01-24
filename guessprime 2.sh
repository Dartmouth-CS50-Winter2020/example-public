#!/bin/bash
#
# File: guessprime.sh
# 
# Description: The user tries to guess a prime between 1-100 
# This is not a good program. There is no check on what the
# user enters; it may not be a prime, or might be outside the range.
# Heck - it might not even be a number and might be empty!
# Some defensive programming would check the input.
# 
# Input: The user enters a guess
#
# Output: Status on the guess

# Program defines a variable called prime and set it to a value.

prime=31

echo -n "Enter a prime between 1-100: "
read guess

while [ $guess != $prime ]; do
    echo "Wrong! try again"
    echo -n "Enter a prime between 1-100: "
    read guess
done
exit 0
