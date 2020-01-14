#!/bin/bash
#
# test_guessprime.sh: test executable guessprime, which prompts
# user to input a prime number and keeps asking for input until 
# user guesses the number correctly.
#
# Input: none
# Output: result of four testing cases
#
# by CS50, January 2020

answer=31  # make sure no white spaces before and after =

# TEST 1: correct guess
echo "TEST 1: test with correct answer"
if echo $answer | ./guessprime 
then
	echo "TEST 1: Success" 
else
	echo "TEST 1: Failed"
fi

# TEST 2: non-prime number
echo "TEST 2: test with non-prime number"
if echo 100 $answer | ./guessprime
then
	echo "TEST 2: Success"
else
	echo "TEST 2: Failed"
fi

# TEST 3: incorrect prime guess 
echo "TEST 3: test with incorrect prime number"
if echo 17 19 $answer | ./guessprime
then
	echo "TEST 3: Success"
else
	echo "TEST 3: Failed"
fi

# TEST 4: number out of range
echo "TEST 4: test with number out of range"
if echo 200 $answer | ./guessprime
then
	echo "TEST 4: Success"
else
	echo "TEST 4: Failed"
fi

exit 0;
