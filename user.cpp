#include <iostream>
#include "user.h"

User::User(char temp_name[15], int temp_credit) {
    for(int i = 0; i < 15; i++){
        user_name[i] = temp_name[i];
    }
    credit = temp_credit;
}

std::string User::getUserName(){
    return user_name;
}

int User::getCredit() {
    return credit;
}


Standard::Standard(char temp_name[15], int temp_credit, char account[2]) : User(temp_name, temp_credit) {
    acc_type[0] = account[0];
    acc_type[1] = account[1];
}


void Standard::addCredit(int tmp_credit) {
    credit = tmp_credit;
}