/**
* The admin class implements the functions that require elevated permissions
*
* Class not included in phase 2 prototype.
* Will contain extra admin functions not accessible by the User class:
* @method createAccount()
* @method deleteAccount()
* @method refund()
* @method addCredit() // the admin version of adding credit
*
* @author Kevin Desousa, Samuel Pilkey, and Daniel Bullock (Team JDK)
* @version 0.1
* @since 2019-02-03
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include "admin.h"
#include "user.h"
#include "tickets.h"
#include "fileio.h"
#include "helper_func.h"

Admin::Admin() {}

std::string Admin::createUser(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream){
    std::string error;
    std::string new_account_name;
    std::string new_account_type;
    std::string credit;
    int initial_credit;
    system("clear");

    // prompts user to enter in the new user name of the account
    std::cout << "Please enter the Username of the account you wish to create: \n";
    std::getline(std::cin,  new_account_name);
    // prompts user to enter in the new account type
    std::cout << "Please enter the account type of the account you wish to create (AA, FS, BS, SS): \n";
    std::getline(std::cin,  new_account_type);
    // prompts user to enter in the new user name of the account
    std::cout << "Please enter the initial credit of the account you wish to create: \n";
    std::getline(std::cin, credit);

    // converts entered number from user to an integer
    initial_credit = atoi(credit.c_str());

    // regex to check for invalid characters in a new user name
    // goes from space to ~
    std::regex pattern("[ -~]+");

    User* check_user = login(new_account_name, file_stream);
    // Handling for entry errors from user
    if (initial_credit < 0) {
      error = "ERR: You cannot give a user negative credit\n";
    } else if (initial_credit > 999999) {
      error = "ERR: You cannot give a user more than $999 999 credit\n";
    } else if (new_account_name.length() > 15) {
      error = "ERR: You cannot give a user a name over 15 characters\n";
    } else if (new_account_name.length() == 0) {
      error = "ERR: You did not enter in any value for the new username\n";
    } else if (new_account_type.length() == 0) {
      error = "ERR: You did not enter in any value for the new user account type\n";
    } else if (new_account_type != "AA" &&
               new_account_type != "FS" &&
               new_account_type != "BS" &&
               new_account_type != "SS") {
      error = "ERR: New account type must be AA, FS, BS, or SS\n";

    // if not a regex match, invalid character
    } else if (!regex_match(new_account_name, pattern)) {
      error = "ERR: You entered an invalid character in your username \n";

    } else if ((new_account_name + (std::string(15 - new_account_name.length(), ' '))) == curr_user->getUserName()) {
      error = "ERR: You cannot create use your own username for a new account \n";

    } else if (check_user != NULL ) {
      error = "ERR: That username is already taken\n";

    } else {
<<<<<<< HEAD

=======
>>>>>>> 0db2861f83635715cb44ed5adfe969f890bc9c71
      new_account_name += (std::string(15 - new_account_name.length(), ' '));

      // left side of credit
      std::string credit_log = credit_to_log(std::strtof(credit.c_str(),0));

      std::stringstream ss;
      ss << "01 " << new_account_name << " "
          << new_account_type << " "
          << credit_log;
      std::string log = ss.str();

      std::cout << log << std::endl; // debug for checking log
      log_transaction(log, trans_log);
      error = "User created!\n";
  }
  delete check_user;
  return error;
}

/*
* Function runs the delete command
* @param curr_user a instance of the current user for attaining data
* @return a string containing the appropriate prompt after the command executes
*/
std::string Admin::deleteUser(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream){
  // Run delete
  std::string error;
  std::string deleted_account_name;
  system("clear");

  // prompts user to enter in the user name of the account to delete
  std::cout << "Please enter the Username of the account you wish to delete: \n";
  std::getline(std::cin,  deleted_account_name);

  User* user_to_be_deleted = login(deleted_account_name, file_stream);

  // Handling for entry errors from user
  if ((deleted_account_name + (std::string(15 - deleted_account_name.length(), ' '))) == curr_user->getUserName()) {
    error = "ERR: You cannot delete yourself \n";
  } else if (deleted_account_name.length() == 0) {
    error = "ERR: You did not enter in any value for the new username\n";
  } else if (user_to_be_deleted == NULL) {
    error = "ERR: User to be deleted does not exist in the database\n";
  } else {

    std::string credit_log = credit_to_log(user_to_be_deleted->getCredit());

    std::stringstream ss;
    ss << "02 " << user_to_be_deleted->getUserName() << " "
        << user_to_be_deleted->getUserType() << " "
        << credit_log;
    std::string log = ss.str();

    std::cout << log << std::endl; // debug for checking log
    log_transaction(log, trans_log);
    error = "User deleted!\n";
  }
  return error;
}

/*
* Function runs the refund command
* @param curr_user a instance of the current user for attaining data
* @return a string containing the appropriate prompt after the command executes
*/
std::string Admin::refundUser(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream){
  std::string error;
  std::string buyer_username;
  std::string seller_username;
  std::string credit;

  system("clear");

  std::cout << "Please enter the buyer's username" << std::endl;
  std::getline(std::cin, buyer_username);

  std::cout << "Please enter the seller's usernmae" << std::endl;
  std::getline(std::cin, seller_username);

  std::cout << "Please enter in the amount of credit to refund" << std::endl;
  std::getline(std::cin, credit);

  User* buyer = login(buyer_username, file_stream);
  User* seller = login(seller_username, file_stream);

  if(buyer == NULL){
    error = "ERR: Buyer was not found\n";

  } else if (seller == NULL){
    error = "ERR: Seller was not found\n";

  } else if (buyer->getUserType() == "SS"){
    error = "ERR: buyer is not of type BB FS or AA\n";

  } else if (seller->getUserType() == "BS"){
    error = "ERR: seller is not of type SS FS or AA\n";

  } else if (std::strtof(credit.c_str(),0) == 0){
    error = "ERR: Cannot refund 0 credit\n";

  } else if (std::strtof(credit.c_str(),0) < 0) {
    error = "ERR: You cannot refund negative credit \n";

  } else if (std::strtof(credit.c_str(),0) > 999999.99) {
    error = "ERR: Cannot not refund more than the max credit\n";

  } else if (std::strtof(credit.c_str(),0) > seller->getCredit()){
    error = "ERR: Cannot refund more than your curent balance\n";

  } else {

    std::string credit_logged = credit_to_log(std::strtof(credit.c_str(),0));

    std::stringstream ss;
    ss << "05 " << buyer->getUserName() << " "
        << seller->getUserName() << " "
        << credit_logged;
    std::string log = ss.str();

    log_transaction(log, trans_log);

    std::cout << log << std::endl;
    error = "Refund Successful!\n";
  }
return error;
}

/*
* Function runs the addcredit commands for admins
* @param curr_user a instance of the current user for attaining data
* @return a string containing the appropriate prompt after the command executes
*/
std::string Admin::addCredit_Admin(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream){
  // Run addcredit for admins
  system("clear");
  std::string user_name;
  std::string error;
  std::string credit_amount;

  std::cout << "Enter in the username you wish to add credit to" << std::endl;

  std::getline(std::cin,  user_name);

  std::cout << "Enter in the amount of credit you wish to add" << std::endl;

  std::getline(std::cin,  credit_amount);

  User* addCredit_user = login(user_name, file_stream);

  // error checking
  if(addCredit_user == NULL){
    error = "User was not found\n";

  } else if (atoi(credit_amount.c_str()) > 1000){
    error = "ERR: Max credit of $1000 per seesion to be added exceeded\n";

  } else if (atoi(credit_amount.c_str()) == 0 || atoi(credit_amount.c_str()) < 0){
    error = "ERR: Credit of $0 or below cannot be accepted\n";

  } else if (credit_amount.length() == 0){
    error = "ERR: No value entered\n";

  } else if ((std::strtof(credit_amount.c_str(),0)+addCredit_user->getCredit()) > 999999.99){
    error = "ERR: Can't exceed the max credit of $999999.99\n";

  } else {

    std::string credit_log = credit_to_log(std::strtof(credit_amount.c_str(),0)+addCredit_user->getCredit());

    std::stringstream ss;
    ss << "06 " << addCredit_user->getUserName() << " "
       << addCredit_user->getUserType() << " "
       << credit_log;
    std::string log = ss.str();

    std::cout << log << std::endl; // debug for checking log

    log_transaction(log, trans_log);
    error = "Credit added!\n";
  }
  return error;
}
