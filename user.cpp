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

void User::addCredit(int tmp_credit) {
    credit = tmp_credit;
}


std::string User::getUserName(){
    return user_name;
}

int User::getCredit() {
    return credit;
}

std::string User::getUserType(){
    return acc_type;
}
