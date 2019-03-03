/*
* Program intention/purpose: Ticket buying/selling service for logged-in users.
*
* How to compile: In the CSCI3060U_Project directory run the makefile by
* using the "make" command in a terminal.
*
* To run the actual program in your terminal use the command:
* ./ticket-seller tests/users.ua tests/stock.at trans.out
*
* Users can complete eight different transactions and use also the exit command:
* login, logout, create, delete, sell, buy, refund, addcredit,
* and type "exit" to end the program.
* Simply type these tranaction codes in the program to initiate each transaction's sequence.
* Once in the transaction sequence, just follow the instructions the program outputs to you.
*
* Input files:
* tests/users.ua (the current users file)
* tests/stock.at (the available tickets file)
* Output files:
* trans.out (the daily transaction file)
*
* @author Kevin Desousa, Samuel Pilkey, and Daniel Bullock (Team JDK)
* @version 0.1
* @since 2019-02-03
*/

#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <regex>
#include <vector>
#include "admin.h"
#include "user.h"
#include "tickets.h"
#include "fileio.h"
#include "helper_func.h"

std::string buy(User* curr_user);
std::string sell(User* curr_user);
std::string addCredit_Standard(User* curr_user);

std::vector<std::string> trans_log;

std::string curr_account_file =
    "";  // The location of the users file
std::string avail_tickets_file =
    "";  // The location of the stock file
std::string curr_trans_file =
    "";  // The location to save the transaction file
FileIO* file_stream; // The backend class

/*
* This is the main method which handles the user input and calls the functions
* @param args Unused (to be replaced with files)
* @return Nothing (technically an int since c++ requires the main to return something)
*/

int main(int argc, char** argv) {
    // Init variables
    User* curr_user = NULL;

    // Checking for correct command line arguments
    if (argc == 4) {
      curr_account_file += argv[1];
      avail_tickets_file += argv[2];
      curr_trans_file = argv[3];
    } else {
      std::cout << "Incorrect filename arguments, please run the program as follows:\n"
                << "./ticket-seller tests/users.ua tests/stock.at trans.out" << std::endl;
      return 0;
    }

    file_stream = new FileIO(curr_account_file, avail_tickets_file, curr_trans_file);

    bool exit = false;  // The flag to quit the program
    std::string error =
        "";  // The error to display on the next iteration of the loop
    std::string command = "";  // The user's command

    while (exit == false) {
        // Clear the screen
        system("clear");

        // Display available commands and errors
        std::cout << error;
        error = "";

        // Get the current user's account type
        std::string acc_type;
        if (curr_user != NULL) {
            acc_type = curr_user->getUserType();
        }
        std::cout << "The available commands are:" << std::endl;
        if (curr_user == NULL) {
            std::cout << "- login : Logs you into the system." << std::endl;
            std::cout << "- exit : Quits the program." << std::endl;
        } else {
            if (!acc_type.compare("AA")) {
                std::cout << "- create : Creates a new account." << std::endl;
                std::cout << "- delete : Deletes an existing account."
                          << std::endl;
                std::cout << "- refund : Reimburse a ticket sale." << std::endl;
                std::cout << "- addcredit : Add credit to a user." << std::endl;
            } else {
                std::cout << "- addcredit : Add credit to your account."
                          << std::endl;
            }

            if (acc_type != "SS") {
                std::cout << "- buy : Purchase a ticket." << std::endl;
            }
            if (acc_type != "BS") {
                std::cout << "- sell : Sell a ticket." << std::endl;
            }
            std::cout << "- logout : Logs you out of the system." << std::endl;
        }
        std::cout << "\nPlease enter a command:" << std::endl;

        // Wait for user response
        std::getline(std::cin, command);

        // Process the command entered
        if (curr_user == NULL) {
            if (command == "exit") {
                exit = true;

            } else if (command == "login") {
                // Clear the screen
                system("clear");

                std::cout << "Please enter a valid username:" << std::endl;
                std::getline(std::cin, command);

                curr_user = login(command, file_stream);
                if (curr_user == NULL) {
                    error =
                        "ERR: The username entered is either invalid or does "
                        "not exist; Please try again.\n";
                }
            }
        } else {
            if (acc_type == "AA" && command == "create") {
              // calling getAdmin() to obtain admin commands
                error = curr_user->getAdmin()->createUser(curr_user, trans_log, file_stream);

            } else if (acc_type == "AA" && command == "delete") {
                error = curr_user->getAdmin()->deleteUser(curr_user, trans_log, file_stream);

            } else if (acc_type == "AA" && command == "refund") {
                error = curr_user->getAdmin()->refundUser(curr_user, trans_log, file_stream);

            } else if (acc_type == "AA" && command == "addcredit") {
                error = curr_user->getAdmin()->addCredit_Admin(curr_user, trans_log, file_stream);

            } else if (acc_type != "SS" && command == "buy") {
              // calling commands from user class
                error = curr_user->buy(curr_user, trans_log, file_stream);

            } else if (acc_type != "BS" && command == "sell") {
                error = curr_user->sell(curr_user, trans_log, file_stream);

            } else if (acc_type != "AA" && command == "addcredit") {
                error = curr_user->addCredit_Standard(curr_user, trans_log, file_stream);

            } else if (command == "logout") {
                // Write transactions
                curr_user = NULL;

                // Log the logout
                log_transaction("00", trans_log);

                // Write the transactions to the external file
                file_stream->writeTransactions(trans_log);

                // Clear the log
                trans_log.clear();
            } else {
                error = "ERR: Command not found; Please try again.\n";
            }
        }
    }
    delete curr_user;
    return 0;
}
