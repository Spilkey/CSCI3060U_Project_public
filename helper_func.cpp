/*
* The helper_func class holds functions that are necessary to run the Program
* like login() and also functions that convert integers so that they can be written
* to the log files like int_to_log()
*
* @method log_transaction takes transaction and places it into transaction array
* @method login Checks if inputted username is valid
* @method get_tickets calls function in FileIO class to read and return ticket
* @method credit_to_log Adds padding to integers so they can be added to the log strings
* @method int_to_log Takes credit of at most 8 sig digs and returns a padding string including 2 decimals
*
* @author Kevin Desousa, Samuel Pilkey, and Daniel Bullock (Team JDK)
* @version 0.1
* @since 2019-03-02
*/
#include <iostream>
#include <vector>
#include <regex>
#include <math.h>
#include "admin.h"
#include "user.h"
#include "tickets.h"
#include "fileio.h"
#include "helper_func.h"
/*
*
* Takes a transaction and places it into the transaction array (increasing its size)
* each element in the array will be written to the daily transaction file
* @param transaction The transaction to log into the transaction file
* @param trans_log a vector containing all transactions in this session
* @return Nothing
*/
void log_transaction(std::string transaction, std::vector<std::string> &trans_log) {
  trans_log.push_back(transaction);
}

/*
* Takes a username, checks if it is valid, then calls a function in the FileIO class to search for the user
* @param username The username entered
* @param file_stream A pointer to an instance of FileIO
* @return User This returns a instance of the User class
*/
User* login(std::string username, FileIO *file_stream) {
    // Create the regex pattern
    std::regex pattern("[ -~]+");

    // Check the username for valid characters
    if (username.size() > 15 || username.size() <= 0 || !regex_match(username, pattern)) {
        return NULL;
    } else if (username.size() <= 15) {
        for(int i = username.size(); i < 15; i++){
            username += ' ';
        }
    }

    // Return the user
    return file_stream->readAccounts(username);
}

/*
* Calls the function in the FileIO class to read (and return) the ticket
* @param event_title The title of the event that the user wants to purchase tickets for
* @param seller_username The username of the user wanting to buy the ticket
* @param file_stream A pointer to an instance of FileIO
* @return Tickets This returns a instance of the Tickets struct
*/
Tickets* get_tickets(std::string event_title, std::string seller_username, FileIO *file_stream){
  return file_stream->readTickets(event_title, seller_username);
}

/*
* Function is called to add padding to integers so they can be added to the log strings
* @param num The number which is going padding
* @param length The length of the string to which the amount of padding is based off of
* @return std:string The integer as a string with padding
*/
std::string int_to_log(int num, int length){
  std::string new_num = std::to_string(num);
  new_num.insert(new_num.begin(), length - new_num.length(), '0');
  return new_num;
}

/*
* Function take a credit of at most 8 significant digits and returns a padding string including 2 decimals
* @param credit which will be padded
* @return padded string with zeros
*/
std::string credit_to_log(float credit){
  
    // left side credit
    std::string left_side_credit_log = int_to_log((int)credit, 6);

    // right side of credit
    float rounded;
    int right_side_credit = (int)((modf(credit, &rounded))*100);
    std::string right_side_credit_log = int_to_log(right_side_credit, 2);

    return left_side_credit_log + "." + right_side_credit_log;
}
