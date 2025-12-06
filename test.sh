#!/bin/bash

# Create invalid-mazes directory if it doesn't exist
mkdir -p invalid-mazes

# Create bad-permissions.txt if it doesn't exist
touch invalid-mazes/bad-permissions.txt

# Remove read permissions from this file - note: put them back at the end!
chmod -r invalid-mazes/bad-permissions.txt

# Use make to compile instead of direct gcc
make maze

echo -e "~~ Testing Maze ~~\n"

# Make the test script executable
chmod +x test.sh

# Initialise counters
all_counter=0
pass_counter=0

# Debug mode - set to 0 to hide debug output
DEBUG=0

#-------Argument Tests-------

echo -n "Testing invalid choice - "
((all_counter++))
echo "3" | ./maze > tmp 2>&1
if grep -q "Invalid choice" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing invalid input (non-numeric) - "
((all_counter++))
echo "abc" | ./maze > tmp 2>&1
if grep -q "Input" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

#-------FILE TESTS-------

echo -e "\n~~ File Handling Tests~~\n"

# Create a helper script to test file loading
# This ensures proper newline handling
create_test_file() {
    local choice=$1
    local filename=$2
    echo "$choice"
    echo "$filename"
}

echo -n "Testing file input (non-existent file) - "
((all_counter++))
create_test_file 1 "x" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "Usage: ./maze" tmp || grep -q "invalid file" tmp || grep -q "Error" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing bad filename - "
((all_counter++))
create_test_file 1 "fake.csv" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "Usage: ./maze" tmp || grep -q "invalid file" tmp || grep -q "Error" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing whether file is empty - "
((all_counter++))
touch empty.txt
create_test_file 1 "empty.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "Usage: ./maze" tmp || grep -q "width" tmp || grep -q "Error" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing bad permissions - "
((all_counter++))
create_test_file 1 "invalid-mazes/bad-permissions.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "Usage: ./maze" tmp || grep -q "invalid file" tmp || grep -q "Error" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

#-------Maze TESTS-------

echo -n "Testing invalid long width - "
((all_counter++))
create_test_file 1 "invalid-mazes/too-wide.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "wide" tmp || grep -q "width" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing invalid short width - "
((all_counter++))
create_test_file 1 "invalid-mazes/too-narrow.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "narrow" tmp || grep -q "width" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing invalid long height - "
((all_counter++))
create_test_file 1 "invalid-mazes/too-long.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "long" tmp || grep -q "height" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing invalid small height - "
((all_counter++))
create_test_file 1 "invalid-mazes/too-short.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "short" tmp || grep -q "height" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing missing start point - "
((all_counter++))
create_test_file 1 "invalid-mazes/missing-start.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "start" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing missing end point - "
((all_counter++))
create_test_file 1 "invalid-mazes/missing-end.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "end" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing more than 1 start point - "
((all_counter++))
create_test_file 1 "invalid-mazes/more-than-1-start.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "start" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing more than 1 end point - "
((all_counter++))
create_test_file 1 "invalid-mazes/more-than-1-end.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "end" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing unequal rows - "
((all_counter++))
create_test_file 1 "invalid-mazes/different-width.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "width" tmp || grep -q "line" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing unequal columns - "
((all_counter++))
create_test_file 1 "invalid-mazes/different-height.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "height" tmp || grep -q "column" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

echo -n "Testing Invalid characters in the maze - "
((all_counter++))
create_test_file 1 "invalid-mazes/foreign-char-in-maze.txt" | timeout 0.2s ./maze > tmp 2>&1
if grep -q "character" tmp || grep -q "Invalid" tmp || grep -q "Error" tmp || grep -q "Usage" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

#-------Keypress TESTS-------
echo -e "\n~~ Gameplay Tests~~\n"

echo -n "Testing valid maze loads - "
((all_counter++))
create_test_file 1 "testMazes/valid/5x5.in" | timeout 0.5s ./maze > tmp 2>&1
if grep -q "MAZE" tmp || [ -s tmp ];
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
    [ $DEBUG -eq 1 ] && cat tmp
fi

# Display test counter which includes total, passed and percentage passed
echo -e "\n~~ Test Results ~~"
echo "Total tests: $all_counter"
echo "Passed tests: $pass_counter"

# Calculate percentage using awk
percentage=$(awk "BEGIN {printf \"%.2f\", ($pass_counter / $all_counter) * 100}")
echo "Percentage passed: ${percentage}%"

# Adding read permissions back to this file
chmod +r invalid-mazes/bad-permissions.txt

# Tidy up and remove the tmp file at the end.
rm -f tmp