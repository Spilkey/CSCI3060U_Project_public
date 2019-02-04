#ifndef user_H
#define user_H

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
