#!/bin/bash
#script to loop through directories to merge files


tests="tests/*"

for t in $tests
do

    # If its a directory, go inside of it
    if [ -d "$t" ]
    then

        ./ticket-seller users.ua stock.at trans.out < "$t/test.inp"
        
        # for tt in $t/*
        # do
        #         echo "Processing $tt"
        #         # run_function
        # done
    
    else
                        echo "Processing $t"
    fi

done

