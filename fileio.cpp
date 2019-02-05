#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "admin.h"
#include "user.h"
#include "fileio.h"

FileIO::FileIO(std::string account_file, std::string tickets_file, std::string transaction_file) {
    // TODO - load the transaction file
    daily_trans_file = transaction_file;
    curr_account_file = account_file;
    avail_tickets_file = tickets_file;
}

User* FileIO::readAccounts(std::string username) {
    std::string line;
    std::ifstream file;
    file.open(curr_account_file);

    if (file.is_open()) {
        bool found = false;
        std::string buff[3];

        while (std::getline(file, line) && found == false) {
            std::stringstream ss(line);

            // Load the line's information into the buffer
            int i = 0;
            while (ss >> buff[i]) {
                i++;
            }

            // Check if it matches the string
            if(buff[0] == username){
                found = true;
            } else {
                found = false;
            }
        }

        file.close();
        if (found == true) {
          return new User(buff[0], atoi(buff[2].c_str()), buff[1] );
        }
    }
    return NULL;
}
