#include <iostream>
#include <string>
#include "fileio.cpp"
#include "user.cpp"

void log_transaction(std::string transaction, FileIO file_stream);
User* login(std::string username);

int* trans_size;         // The size of the transaction array
std::string* trans_log;  // The array to contain the transactions
const std::string curr_account_file = "users.ua";  // The location of the users file
const std::string avail_tickets_file = "stock.at";  // The location of the stock file
FileIO file_stream(curr_account_file, avail_tickets_file); // The backend class

int main() {
    // Init variables
    User* curr_user = NULL;
    trans_size = new int(0);
    trans_log = new std::string[*trans_size];

    bool exit = false;  // The flag to quit the program
    std::string error =
        "";  // The error to display on the next iteration of the loop
    std::string command = "";  // The user's command

    while (exit == false) {
        // Clear the screen
        system("clear");

        // Display available commands and errorss
        std::cout << error;
        error = "";

        std::cout << "The available commands are:" << std::endl;
        if (curr_user == NULL) {
            std::cout << "- login : Logs you into the system." << std::endl;
        } else {
            std::cout << "- logout : Logs you out of the system." << std::endl;
        }
        std::cout << "- exit : Quits the program.\n" << std::endl;
        std::cout << "Please enter a command:" << std::endl;

        // Wait for user response
        std::cin >> command;

        // Process the command entered
        if (command == "exit") {
            exit = true;
        } else if (command == "login" && curr_user == NULL) {
            // Clear the screen
            system("clear");

            std::cout << "Please enter a valid username:" << std::endl;
            std::cin >> command;

            if (command.size() > 15 || command.size() <= 0) {
                error = "ERR: The username entered is invalid; Try again.\n";
            } else {
                curr_user = login(command);
                if (curr_user == NULL) {
                    error = "ERR: User not found; Please try again.\n";
                } else {
                }
            }

        } else if (curr_user != NULL) {
            if (command == "logout") {
                // Write transactions

                // Remove user from variable
                curr_user = NULL;
            }
        } else {
            error = "ERR: Command not found; Please try again.\n";
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
    // Convert the string to a char array
    char entered_account[15];
    for (int i = 0; i < 15; i++) {
        if (i >= username.size()) {
            entered_account[i] = ' ';
        } else {
            entered_account[i] = username[i];
        }
    }
    // Check the username for valid characters
    // TODO

    // Return the user
    return file_stream.readAccounts(entered_account);
}
