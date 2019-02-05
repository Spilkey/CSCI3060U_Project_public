#include <cstring>
#include <iostream>
#include <string>
#include "admin.h"
#include "user.h"
#include "fileio.h"

void log_transaction(std::string transaction, FileIO file_stream);
User* login(std::string username);

int* trans_size = new int(0);  // The array to contain the transactions
std::string* trans_log =
    new std::string[*trans_size];  // The size of the trans array

const std::string curr_trans_file =
    "trans.out";  // The location to save the transaction file
const std::string curr_account_file =
    "tests/users.ua";  // The location of the users file
const std::string avail_tickets_file =
    "tests/stock.at";  // The location of the stock file
FileIO file_stream(curr_account_file, avail_tickets_file, curr_trans_file);  // The backend class

int main() {
    // Init variables
    User* curr_user = NULL;

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
            if (acc_type == "AA") {
                std::cout << "- create : Creates a new account." << std::endl;
                std::cout << "- delete : Deletes an exisiting account."
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
        std::cin >> command;

        // Process the command entered
        if (curr_user == NULL) {
            if (command == "exit") {
                exit = true;
            } else if (command == "login") {
                // Clear the screen
                system("clear");

                std::cout << "Please enter a valid username:" << std::endl;
                std::cin >> command;

                curr_user = login(command);
                if (curr_user == NULL) {
                    error =
                        "ERR: The username entered is either invalid or does "
                        "not exist; Please try again.\n";
                }
            }
        } else {
            if (acc_type == "AA") {
                if (command == "create") {
                    // Run create
                } else if (command == "delete") {
                    // Run delete
                } else if (command == "refund") {
                    // Run refund
                } else if (command == "addcredit") {
                    // Run addcredit for admins
                }
            }

            if (acc_type != "SS" && command == "buy") {
                // Run buy
            } else if (acc_type != "BS" && command == "sell") {
                // Run sell
            } else if (acc_type != "AA" && command == "addcredit") {
                // Run addcredit for non admins
            } else if (command == "logout") {
                // Write transactions

                // Remove user from variable
                curr_user = NULL;
            } else {
                error = "ERR: Command not found; Please try again.\n";
            }
        }
    }

    return 0;
}

void log_transaction(std::string transaction) {
    (*trans_size)++;  // Increment the size
    std::string* temp_log =
        new std::string[*trans_size];  // Create a temp array with the new size

    memcpy(temp_log, trans_log,
           ((*trans_size) - 1) *
               sizeof(std::string));  // Copy the strings over to the temp array

    delete[] trans_log;    // Delete the old array
    trans_log = temp_log;  // Use the new array
    trans_log[(*trans_size) - 1] =
        transaction;  // Append the transaction to the end
}

User* login(std::string username) {
    // Check the username for valid characters
    // TODO

    if (username.size() > 15 || username.size() <= 0) {
        return NULL;
    }

    // Return the user
    return file_stream.readAccounts(username);
}
