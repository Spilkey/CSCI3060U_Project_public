#!/bin/bash
#script to loop through directories to merge files


tests="tests/*"

rm test_log.txt
touch test_log.txt

rm test_verif.txt
touch test_verif.txt

for t in $tests
do

    # If its a directory, go inside of it
    if [ -d "$t" ]
    then 

        # Run the script and dump the output in the folder to be compared
        ./ticket-seller tests/users.ua tests/stock.at $t/trans.out < $t/test.inp
        
        echo "TEST $t:" >> test_log.txt
        diff $t/trans.out $t/test.out >> test_log.txt
        echo $'\n' >> test_log.txt

        # Write a file documenting if the file is ok or not
        if [ "diff $t/trans.out $t/test.out" == "" ]
        then
            echo "TEST $t: GOOD" >> test_verif.txt
        else
            echo "TEST $t: BAD" >> test_verif.txt
        fi



        rm $t/trans.out
    fi
 
done