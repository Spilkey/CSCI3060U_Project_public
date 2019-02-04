#include <iostream>
#include <string>
#include "user.h"

User::User(char temp_name[15], int temp_credit, std::string account) {
    for(int i = 0; i < 15; i++){
        user_name[i] = temp_name[i];
    }
    credit = temp_credit;
    acc_type = account;
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
