#ifndef user_H
#define user_H

class User {
   protected:
    char user_name[15];
    std::string acc_type;
    int credit;

   public:
    User(char temp_name[15], int temp_credit, std::string account);
    void addCredit(int tmp_credit);

    std::string getUserName();
    int getCredit();
};


#endif
