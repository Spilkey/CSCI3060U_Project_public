#!/bin/bash
#script to loop through directories to merge files


tests="tests/*"
touch test_log.txt

for t in $tests
do

    # If its a directory, go inside of it
    if [ -d "$t" ]
    then 
        # Run the script and dump the output in the folder to be compared
        ./ticket-seller users.ua stock.at $t/trans.out < $t/test.inp
        
        echo "TEST $t:" >> test_log.txt
        diff $t/trans.out $t/test.out >> test_log.txt
        echo $'\n' >> test_log.txt
    fi
 
done