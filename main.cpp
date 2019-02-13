/**
* Program intention/purpose: Ticket buying/selling service for logged-in users.
*
* How to compile: In the CSCI3060U_Project directory run the makefile by
* using the "make" command in a terminal.
*
* To run the actual program in your terminal use the command:
* ./ticket-seller
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
#include "admin.h"
#include "user.h"
#include "tickets.h"
#include "fileio.h"

void log_transaction(std::string transaction, FileIO file_stream);
User* login(std::string username);
Tickets* buy(std::string event_title, std::string seller_username);

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



/*
* This is the main method which handles the user input and calls the functions
* @param args Unused (to be replaced with files)
* @return Nothing
*/
// The filenames will be passed as command line arguments in the phase #3
//int main(int argc, char** argv) {
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
        std::getline (std::cin,command);

        // Process the command entered
        if (curr_user == NULL) {
            if (command == "exit") {
                exit = true;

            } else if (command == "login") {
                // Clear the screen
                system("clear");

                std::cout << "Please enter a valid username:" << std::endl;
                std::getline (std::cin,command);

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

                std::string event_t;
                std::string seller_username;
                int num_of_tickets;
                system("clear");

                //promtps user to enter in event title
                std::cout << "Please enter the Event title of the tickets you wish to buy: \n";
                std::getline (std::cin,event_t);

                //prompts user to enter in seller username
                std::cout << "Please enter the user name who you will buying from: " << std::endl;
                std::getline (std::cin,seller_username);

                //prompts user to enter in amount of tickets
                std::cout << "Please enter in the amount of tickets you wish to buy" << std::endl;
                std::getline (std::cin,command);

                //converts entered number from user to an integer
                num_of_tickets = atoi(command.c_str());

                //setting ticket stuct equal to the information the user entered.
                //Equals Null if information is invalid
                Tickets* current = new Tickets;
                current = buy(event_t, seller_username);

                /*
                TODO
                make a normalizer function for main.cpp and fileio.cpp to use
                */
                //normalizes the user name to 15 chars
                if(seller_username.length() < 15 ){
                    seller_username += (std::string(15 - seller_username.length(), ' '));
                                  }
                //Handling for entry errors from user
                if(current == NULL){
                  error = "ERR: the information entered was not valid \n";

                }else if(current->seller_username == curr_user->getUserName()){
                  error = "ERR: you cannot buy from youself \n";

                }else if(num_of_tickets > 4 && acc_type != "AA"){
                  error = "ERR: you cannot purchase more than 4 tickets \n";

                }else if(num_of_tickets <= 0){
                  error = "ERR: You cannot purchace 0 tickets \n";

                }else if(current->total_tickets < num_of_tickets){
                  error = "ERR: you cannot purchace more than the total amount of tickets \n";

                }else{

                  std::cout << "The cost per ticket is " << current->price
                  << "\nThe total cost for this transaction is "<< num_of_tickets*current->price << std::endl;

                  //takes in user choice
                  std::string choice;
                  std::cout << "Do you wish to complete this transaction yes or no " << std::endl;
                  std::getline (std::cin,choice);
                  if(choice == "yes"){

                    //log

                    // calculates the remaining number of tickerts after purchase
                    int rem_tickets = current->total_tickets - num_of_tickets;

                    //converts remaining numbner of tickets to string and adds padding
                    std::string new_ticket_counter = std::to_string(rem_tickets);
                    new_ticket_counter.insert(new_ticket_counter.begin(), 3 - new_ticket_counter.length(), '0');

                    //TODO: Convert padding method to string same as remaining tickets
                    //converts price per ticket to char arrays and pres for wrting to log string
                    //left side
                    char log_price[6] = {'0','0','0','.','0','0'};
                    log_price[0] = (current->price / 100) + 48;
                    log_price[1] = ((current->price - ((log_price[0] - 48)*100)) / 10) + 48;
                    log_price[2] = ((current->price - ((log_price[0] - 48)*100)) -
                                                      ((log_price[1] - 48)*10)) + 48;
                    //right side
                    float rounded;
                    int right_side_price_log = (int)((modf(current->price, &rounded))*100);
                    log_price[4]= (right_side_price_log / 10) + 48;
                    log_price[5] = (right_side_price_log- (log_price[4] - 48)*10) + 48;

                    //creates a string stream to create a string to be sent to the log_transaction() function
                    std::stringstream ss;
                    ss << "04 " << current->event_title << " "
                       << current->seller_username << " "
                       << new_ticket_counter  << " " << log_price;
                    std::string log = ss.str();

                    //std::cout << log << std::endl; debug for checking log

                    //using error srting to alert user of completion
                    error = "Transaction Completed!!\n";

                    //log_transaction(+current->price);


                  }else{
                    error = "Transaction Canceled!!\n";
                  }
                }
                //handling pointers
                delete current;
                //command = "";

            } else if (acc_type != "BS" && command == "sell") {
                // Run sell
            } else if (acc_type != "AA" && command == "addcredit") {
                // Run addcredit for non admins
            } else if (command == "logout") {
                // Write transactions

                curr_user = NULL;
            } else {
                error = "ERR: Command not found; Please try again.\n";
            }
        }
    }
    delete curr_user;
    return 0;
}

/*
* Takes a transaction and places it into the transaction array (increasing its size)
* each element in the array will be written to the daily transaction file
* @param transaction The transaction to log into the transaction file
* @return Nothing
*/
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

/*
* Takes a username, checks if it is valid, then calls a function in the FileIO class to search for the user
* @param username The username entered
* @return User This returns a instance of the User class
*/
User* login(std::string username) {
    // Check the username for valid characters
    // TODO
    if (username.size() > 15 || username.size() <= 0) {
        return NULL;
    } else if (username.size() <= 15) {
        for(int i = username.size(); i < 15; i++){
            username += ' ';
        }
    }

    // Return the user
    return file_stream.readAccounts(username);
}

/*
* Calls the function in the FileIO class to read (and return) the ticket
* @param event_title The title of the event that the user wants to purchase tickets for
* @param seller_username The username of the user wanting to buy the ticket
* @return Tickets This returns a instance of the Tickets class
*/
Tickets* buy(std::string event_title, std::string seller_username){
  return file_stream.readTickets(event_title, seller_username);
}
