#ifndef admin_H
#define admin_H

#include "fileio.h"
#include "user.h"
class FileIO;
class User;
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
class Admin {
  public:
   Admin();
   std::string createUser(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream);
   std::string deleteUser(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream);

   std::string refundUser(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream);
   std::string addCredit_Admin(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream);
};


#endif
