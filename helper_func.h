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
