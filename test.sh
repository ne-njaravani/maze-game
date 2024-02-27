#!/bin/bash

gcc maze.c -o maze

echo -e "~~ Testing Maze ~~"

# Make the test script executable
chmod+x test.sh

# Initialise counters
all_counter=0
pass_counter=0

#-------Argument Tests-------

echo -n "Testing no arguments - "
# Adapted from COMP1921 Lab 2: Testing
((all_counter++))
./maze > tmp
if grep -q "Usage: maze <filename>" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing 1 argument - "
# Adapted from COMP1921 Lab 2: Testing
((all_counter++))
./maze x > tmp
if grep -q "Usage: maze <filename>" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi


#-------FILE TESTS-------

echo -e "\n~~ File Handling Tests~~"

# Test filename
echo -n "Testing bad filename - "
# Adapted from COMP1921 Lab 2: Testing

((all_counter++))
./studentData fake.csv > tmp
if grep -q "Error: Bad filename" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing whether file exists - "
# Test whether file exists
((all_counter++))
./maze x > tmp
if grep -q "File Not Found" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi
# Test whether file is empty


# Test execution permissions

# Test whether object file is executable


#-------Maze TESTS-------

# Test the maze width size
# Test the maze height size
# Test missing start point
# Test missing end point
# Test Test more than 1 start point
# Test more than 1 end point
# Test if all rows of the maze are the same width
# Test if all columns of the maze are the same length
# Test for the presence of invalid characters present in the maze


#-------Keypress TESTS-------
echo -e "\n~~ Keypress Tests~~"

echo -n "Testing valid keypress - "
# Test whether the cases of the valid letters were taken into account
# Use the read command to read a single character from user input (without echoing it)
# adapted from a Stack Overflow: shell-script-respond-to-keypress
# URL: https://stackoverflow.com/questions/24016046/shell-script-respond-to-keypress

((all_counter++))
read -s -n 1 key
if [ "$key" == "m" ] || [ "$key" == "M" ] || [ "$key" == "w" ] || [ "$key" == "W" ] || [ "$key" == "a" ] || [ "$key" == "A" ] || [ "$key" == "s" ] || [ "$key" == "S" ] || [ "$key" == "d" ] || [ "$key" == "D" ];
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing invalid keypress - "

# Test if movement into wall happens


# Test if player out of bounds

echo -n "Testing invalid keypress - "
#Test if map displayed

((all_counter++))
./maze > tmp
if grep -q "Here is the Map:" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

# Display test counter which includes total, passed and percentage passed
echo "Total tests: $all_counter"
echo "Passed tests: $pass_counter"
echo "Percentage passed: $(echo "scale=2; $pass_counter*100 / $all_counter" | bc)%"

# Tidy up and remove the tmp file at the end.
rm -f tmp