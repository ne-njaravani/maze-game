#!/bin/bash

# remove read permissions from this file - note: put them back at the end!
chmod -r invalid-mazes/bad-permissions.txt

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
if grep -q "Usage: ./maze <mazefile path>" tmp;
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
if grep -q "Usage: ./maze <mazefile path>" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing more than 1 argument - "
# Adapted from COMP1921 Lab 2: Testing
((all_counter++))
./maze x x > tmp
if grep -q "Usage: ./maze <mazefile path>" tmp;
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
if grep -q "Error: invalid file" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing whether file exists - "
((all_counter++))
timeout 0.2s ./maze x > tmp
if grep -q "Error: invalid file" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing whether file is empty - "
((all_counter++))
timeout 0.2s ./maze empty.txt > tmp
if grep -q "Invalid maze width: no width found" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing bad permissions - "
timeout 0.2s ./maze invalid-mazes/bad-permissions.txt > tmp
if grep -q "Error: invalid file" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi



#-------Maze TESTS-------

echo -n "Testing invalid long width - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/too-wide.txt > tmp
if grep -q "Invalid maze width: too wide" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing invalid short width - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/too-narrow.txt > tmp
if grep -q "Invalid maze width: too narrow" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing invalid long height - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/too-long.txt > tmp
if grep -q "Invalid maze height: too long" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing invalid small height - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/too-short.txt > tmp
if grep -q "Invalid maze height: too short" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing missing start point - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/missing-start.txt > tmp
if grep -q "Error: No start point found" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing missing end point - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/missing-end.txt > tmp
if grep -q "Error: No end point found" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing more than 1 start point - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/more-than-1-start.txt > tmp
if grep -q "Error: More than 1 start point found" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing more than 1 end point - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/more-than-1-end.txt > tmp
if grep -q "Error: More than 1 end point found" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi


echo -n "Testing unequal rows - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/different-width.txt > tmp
if grep -q "Invalid maze width: inconsistent line length" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing unequal columns - "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/different-height.txt > tmp
if grep -q "Error: height is not the same on each column" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

echo -n "Testing Invalid characters in the maze- "
((all_counter++))
timeout 0.2s ./maze invalid-mazes/foreign-char-in-maze.txt > tmp
if grep -q "Error: Invalid character in maze" tmp;
then
    echo "PASS"
    ((pass_counter++))
else
    echo "FAIL"
fi

#-------Keypress TESTS-------
echo -e "\n~~ Keypress Tests~~"

echo -n "Testing map request - "
((all_counter++))
timeout 0.2s ./maze > tmp
if grep -q "...LOADING MAP..." tmp;
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

# adding read permissions back to this file
chmod +r invalid-mazes/bad-permissions.txt

# Tidy up and remove the tmp file at the end.
rm -f tmp