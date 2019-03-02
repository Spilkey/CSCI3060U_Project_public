#ifndef user_H
#define user_H

#include "admin.h"
#include "fileio.h"

class Admin; //forward delcaration
struct FileIO;
/**
* @param user_name the users username
* @param acc_type the type of account (AA, FS, BS, SS)
* @param credit the accounts amount of credit
* @param admin_commands the array of commands that admins can use from admin class
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
class User {
   protected:
    std::string user_name;
    std::string acc_type;
    float credit;
    Admin* admin_commands;

   public:
    User(std::string temp_name, int temp_credit, std::string account);

    std::string getUserName();
    float getCredit();
    std::string getUserType();
    Admin* getAdmin();

    std::string buy(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream);
    std::string sell(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream);
    std::string addCredit_Standard(User* curr_user, std::vector<std::string> &trans_log, FileIO* file_stream);
};

#endif
