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
#include "admin.h"
#include "user.h"

User::User(std::string temp_name, int temp_credit, std::string account) {
    user_name = temp_name;
    credit = temp_credit;
    acc_type = account;
    if(acc_type == "AA"){
        admin_commands = new Admin();
    } else {
        admin_commands = NULL;
    }
}

/*
* Adds credit to the current user
* @param tmp_credit The amount of credit to set the current user to
*/
void User::addCredit(int tmp_credit) {
    credit = tmp_credit;
}

std::string User::getUserName(){
    return user_name;
}

float User::getCredit() {
    return credit;
}

std::string User::getUserType(){
    return acc_type;
}
