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
#ifndef helper_func_H
#define helper_func_H

#include "user.h"
#include "tickets.h"
class User; // forward delcaration
class Tickets;

// I/O
void log_transaction(std::string transaction, std::vector<std::string> &trans_log);
User* login(std::string username, FileIO *file_stream);
Tickets* get_tickets(std::string event_title, std::string seller_username, FileIO *file_stream);

// helper functions
std::string int_to_log(int num, int length);
std::string credit_to_log(float credit);

#endif
