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

((all_counter++))
./maze x > tmp
if grep -q "File Not Found" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi


#-------Maze TESTS-------

echo -n "Testing long width - "((all_counter++))
./maze x > tmp
if grep -q "Error: Maze width is greater than 100" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing short - "((all_counter++))
./maze x > tmp
if grep -q "Error: Maze width is less than 5" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi
 
echo -n "Testing height greater than upperbound - "((all_counter++))
./maze x > tmp
if grep -q "Error: Maze width is greater than 100" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi



#-------Keypress TESTS-------
echo -e "\n~~ Keypress Tests~~"

echo -n "Testing valid keypress - "
# Test whether the cases of the valid letters were taken into account
# Us# Test the maze width size too bige the read command to read a single character from user input (without echoing it)
# adapted from a Stack Overflow: shell-script-respond-to-keypress
# URL: https://stackoverflow.com/questions/24016046/shell-script-respond-to-keypress

((all_counter++))
./maze > tmp
if grep -q "Here is the Map and your current location (X):" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing invalid keypress - "

echo -n "Testing map requested i.e. whether m/M was pressed - "
#Test if map displayed

((all_counter++))
./maze > tmp
if grep -q "Here is the Map and your current location (X):" tmp;
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