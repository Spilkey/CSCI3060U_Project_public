#include <iostream>
#include <vector>
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
* @return Nothing
*/
void log_transaction(std::string transaction, std::vector<std::string> &trans_log) {
  trans_log.push_back(transaction);
}

/*
* Takes a username, checks if it is valid, then calls a function in the FileIO class to search for the user
* @param username The username entered
* @return User This returns a instance of the User class
*/
User* login(std::string username, FileIO *file_stream) {
    // Check the username for valid characters
    if (username.size() > 15 || username.size() <= 0) {
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
* Function take a credit of  at most 8 significant digits and returns a padding string including 2 decimals
* @param credit which will be padded
* @return padded string with zeros
*/
std::string credit_to_log(float credit){
    std::string left_side_credit_log = int_to_log((int)credit, 6);

    // right side of credit
    float rounded;
    int right_side_credit = (int)((modf(credit, &rounded))*100);
    std::string right_side_credit_log = int_to_log(right_side_credit, 2);

    return left_side_credit_log + "." + right_side_credit_log;
}
