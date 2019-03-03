# CSCI3060U_Project

# Phase 1 - Question 1 and 2 (Table containing Test cases, input/output files, and terminal output)

- A google doc is provided at this link: https://docs.google.com/document/d/1evmJC0PGOVkb_suZCgI6frQrlK8LTksdNeg_VGmjRo8/edit?usp=sharing (and on blackboard) that contains the table for question 1

# Phase 1 - Question 3 (Test Organization)

- There is a directory in the github project called "tests" which contains sub-folders that have the name of each test (sorted alphabetically, they will run alphabetically as well)
- These test names are self-explanatory, for example, "Buy_AA" tests the buy transactions as an Admin user (AA)
- In these test name sub-folders, there is a test.inp file that shows the actual input files for each test case and a test.out file that shows the expected output for that case
- The plan is to run these tests with shell scripts
- There will be a .log file that will be made in each test case folder that will store the actual outputs and that we can compare to the .out files which were anticipated
- Extra (The makeTests.py and tests.csv were made to efficiently take the .inp and .out from our table and place it into their actual files)
- The test.out files are the expected daily transaction files. We have made an expected Current User file and an expected Available Tickets file that are in the main directory.
- The test folder also contains the current user accounts (users.ua) and the available tickets (stock.at) files respectively. 
- Directory structure (minimized):
```
└───tests
    ├───Addcredit_Account_Exist_AA
    │       test.inp
    │       test.out
    │
    ├───AddCredit_Completion_AA
    │       test.inp
    │       test.out
    │
    ...
    │
    └───Sell_Ticket_Number_SS
            test.inp
            test.out
    │       
    │
    │
    └───users.ua
    └───stock.at
```	
# Phase 3 - How to run:

- To compile the program use the make command to run the makefile
```
make
```
- Then run the compiled program using ./ticket-seller tests/users.ua tests/stock.at trans.out
- Follow the instructions in the terminal to use the program (ex: login)
 	
# To run our specified tests:

- Make sure you have the updated tests.csv file, and the .sh script test-runner.sh
- Make sure the test-runner.sh has permissions with chmod
- Run the script using ./test-runner.sh (linux bash)
- The diff_log.txt shows what the difference between the test.out and trans.out files, (using the diff command)
- The test_results.txt file shows every test and whether the test was successful or not with the words (GOOD/BAD)
	
