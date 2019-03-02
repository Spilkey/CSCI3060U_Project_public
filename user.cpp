/**
* The User class implements functions to handle various user-related functions
* such as buy, sell, addCredit, etc.
*
* @method addCredit() adds credit to the current user
* @method getUserName() returns user name of the current user
* @method getCredit() returns credit of current user
* @method getUserType() returns the user type (permissions) of the current user
*
* @author Kevin Desousa, Samuel Pilkey, and Daniel Bullock (Team JDK)
* @version 0.1
* @since 2019-02-03
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include "admin.h"
#include "user.h"
#include "tickets.h"
#include "fileio.h"
#include "helper_func.h"

User::User(std::string temp_name, int temp_credit, std::string account) {
    user_name = temp_name;
    credit = temp_credit;
    acc_type = account;
    if (acc_type == "AA") {
        admin_commands = new Admin();
    } else {
        admin_commands = NULL;
    }
}

/*
* Adds credit to the current user
* @param tmp_credit The amount of credit to set the current user to
*/

std::string User::getUserName() {
    return user_name;
}

float User::getCredit() {
    return credit;
}

std::string User::getUserType() {
    return acc_type;
}

Admin* User::getAdmin(){
    return admin_commands;
}

/*
* Function runs the buy command
* @param curr_user a instance of the current user for attaining data
* @return a string containing the appropriate prompt after the command executes
*/
std::string User::buy(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream){

  std::string error;
  std::string event_t;
  std::string seller_username;
  std::string credit;
  int num_of_tickets;
  system("clear");

  // prompts user to enter in event title
  std::cout << "Please enter the Event title of the tickets you wish to buy: \n";
  std::getline(std::cin, event_t);

  // prompts user to enter in seller username
  std::cout << "Please enter the user name who you will buying from: " << std::endl;
  std::getline(std::cin, seller_username);

  // prompts user to enter in amount of tickets
  std::cout << "Please enter in the amount of tickets you wish to buy: " << std::endl;
  std::getline(std::cin, credit);

  // converts entered number from user to an integer
  num_of_tickets = atoi(credit.c_str());

  // setting ticket stuct equal to the information the user entered.
  // Equals Null if information is invalid
  Tickets* current_tickets = new Tickets;
  current_tickets = get_tickets(event_t, seller_username, file_stream);

  /*
  TODO
  make a normalizer function for main.cpp and fileio.cpp to use
  */
  // normalizes the user name to 15 chars
  if(seller_username.length() < 15 ){
      seller_username += (std::string(15 - seller_username.length(), ' '));
                    }
  // Handling for entry errors from user
  if(current_tickets == NULL){
    error = "ERR: The information entered was not valid \n";

  }else if(current_tickets->seller_username == curr_user->getUserName()){
    error = "ERR: You cannot buy from yourself \n";

  }else if(num_of_tickets > 4 && curr_user->getUserType() != "AA"){
    error = "ERR: You cannot purchase more than 4 tickets \n";

  }else if(num_of_tickets <= 0){
    error = "ERR: You cannot purchace 0 tickets \n";

  }else if(current_tickets->total_tickets < num_of_tickets){
    error = "ERR: You cannot purchace more than the total amount of tickets \n";

  }else{

    std::cout << "The cost per ticket is " << current_tickets->price
    << "\nThe total cost for this transaction is "<< num_of_tickets*current_tickets->price << std::endl;

    // takes in user choice
    std::string choice;
    std::cout << "Do you wish to complete this transaction yes or no " << std::endl;
    std::getline(std::cin, choice);
    if(choice == "yes"){

      // log

      // calculates the remaining number of tickerts after purchase
      int rem_tickets = current_tickets->total_tickets - num_of_tickets;

      // converts remaining numbner of tickets to string and adds padding
      std::string new_ticket_counter = int_to_log(rem_tickets, 3);

      // left side
      std::string left_side_price_log = int_to_log((int)(current_tickets->price), 3);

      // right side
      float rounded;
      int right_side_price = (int)((modf(current_tickets->price, &rounded))*100);

      std::string right_side_price_log = int_to_log(right_side_price, 2);


      //creates a string stream to create a string to be sent to the log_transaction() f, trans_logunction
      std::stringstream ss;
      ss << "04 " << current_tickets->event_title << " "
         << current_tickets->seller_username << " "
         << new_ticket_counter  << " " << left_side_price_log
         << "." << right_side_price_log;
      std::string log = ss.str();

      std::cout << log << std::endl; // debug for checking log

      // using error srting to alert user of completion
      error = "Transaction Completed!!\n";

      log_transaction(log, trans_log);

    }else{
      error = "Transaction Canceled!!\n";
    }
  }
  // handling pointers
  delete current_tickets;
  return error;
}

/*
* Function runs the sell command
* @param curr_user a instance of the current user for attaining data
* @return a string containing the appropriate prompt after the command executes
*/
std::string User::sell(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream){
  // Run sell
  system("clear");
  std::string error;
  std::string event_t;
  std::string sale_price;
  std::string num_of_tickets;

  std::cout << "Please enter the event title of the tickets you wish to sell."
                "Max length is 25 Characters."
            << std::endl;
  std::getline(std::cin,  event_t);

  std::cout << "Please enter in the sale price." << std::endl;

  std::getline(std::cin,  sale_price);

  std::cout << "Please enter in the number of tickets you wish to sell" << std::endl;

  std::getline(std::cin,  num_of_tickets);

  // error checking
  if (event_t.length() > 25){
    error = "ERR: Length of the event title is too long \n";

  } else if (event_t.length() == 0){
    error = "ERR: You did not enter in any value for the event title \n";

  } else if (atoi(sale_price.c_str()) > 999){
    error = "ERR: Price of the tickets is to expensive. Max price allowed is 999.99 \n";

  } else if (sale_price.length() == 0){
    error = "ERR: You did not enter a sale price \n";

  } else if (atoi(sale_price.c_str()) == 0){
    error = "ERR: You entered invalid input for the sale price\n";

  } else if (atoi(num_of_tickets.c_str()) > 100) {
    error = "ERR: You cannot sell more than 100 tickets \n";

  } else if (num_of_tickets.length() == 0){
    error = "ERR: You did not enter in any value for the number of tickets\n";

  } else if (atoi(num_of_tickets.c_str()) == 0){
    error = "ERR: You entered invalid input for the number of tickets\n";

  } else {

    // normalizing event title
    if (event_t.length() < 25 ){
        event_t += (std::string(25 - event_t.length(), ' '));

    }

    // converts remaining numbner of tickets to string and adds padding
    std::string num_of_tickets_to_log = int_to_log(atoi(num_of_tickets.c_str()), 3);

    // left side of price
    std::string left_side_price_log = int_to_log(atoi(sale_price.c_str()), 3);

    // right side of price
    float rounded;
    int right_side_price = (int)((modf(strtof(sale_price.c_str(),0), &rounded))*100);
    std::string right_side_price_log = int_to_log(right_side_price, 2);

    std::stringstream ss;
    ss << "03 " << event_t << " "
       << curr_user->getUserName() << " "
       << num_of_tickets_to_log << " " << left_side_price_log
       << "." << right_side_price_log;
    std::string log = ss.str();

    std::cout << log << std::endl; // debug for checking log

    log_transaction(log, trans_log);
    error = "Successfully added ticket. Ticket will be processed and will be available next seesion\n";
  }
  return error;
}

/*
* Function runs the addcredit command for standard users
* @param curr_user a instance of the current user for attaining data
* @return a string containing the appropriate prompt after the command executes
*/
std::string User::addCredit_Standard(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream){
  system("clear");
  std::string error;
  std::string credit_amount;
  std::cout << "Enter in the amount of credit you wish to add" << std::endl;

  std::getline(std::cin,  credit_amount);
  // error checking
  if (atoi(credit_amount.c_str()) > 1000){
    error = "ERR: Max credit of $1000 per seesion to be added exceeded\n";

  } else if (atoi(credit_amount.c_str()) == 0){
    error = "ERR: Credit of $0 cannot be accepted\n";

  } else if (credit_amount.length() == 0){
    error = "ERR: No value entered\n";

  } else if ((strtof(credit_amount.c_str(),0)+curr_user->getCredit()) > 999999.99){
    error = "ERR: Can't exceed the max credit of 999999.99\n";

  } else {

    std::string credit_log = credit_to_log(std::strtof(credit_amount.c_str(),0)+curr_user->getCredit());

    std::stringstream ss;
    ss << "06 " << curr_user->getUserName() << " "
       << curr_user->getUserType() << " "
       << credit_log;
    std::string log = ss.str();

    std::cout << log << std::endl; // debug for checking log

    log_transaction(log, trans_log);
    error = "Credit added\n";
  }
  return error;
}
