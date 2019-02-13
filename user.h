#ifndef user_H
#define user_H

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
    int credit;
    Admin* admin_commands;

   public:
    User(std::string temp_name, int temp_credit, std::string account);
    void addCredit(int tmp_credit);

    std::string getUserName();
    int getCredit();
    std::string getUserType();
};

#endif
