#ifndef user_H
#define user_H

class User {
   protected:
    char user_name[15];
    int credit;

   public:
    User(char temp_name[15], int temp_credit);
    std::string getUserName();
    int getCredit();
};

class Standard : public User {
    char acc_type[2];

   public:
    Standard(char temp_name[15], int temp_credit, char account[2]);
    void addCredit(int tmp_credit);
};

#endif