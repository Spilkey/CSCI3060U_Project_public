#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "user.h"
#include "fileio.h"

FileIO::FileIO(std::string account_file, std::string tickets_file) {
    // TODO - load the transaction file
    curr_account_file = account_file;
    avail_tickets_file = tickets_file;
}

User* FileIO::readAccounts(char username[15]) {
    std::string line;
    std::ifstream file;
    file.open(curr_account_file);

    if (file.is_open()) {
        bool found = false;
        std::string buff[3];
        char temp_username[15];

        while (std::getline(file, line) && found == false) {
            std::stringstream ss(line);

            // Load the line's information into the buffer
            int i = 0;
            while (ss >> buff[i]) {
                i++;
            }

            // Check if it matches the entered char array
            found = true;
            for (int i = 0; i < buff[0].size(); i++) {
                if (buff[0][i] != username[i]) {
                    found = false;
                } else {
                    temp_username[i] = buff[0][i];
                }
            }
        }

        file.close();
        if (found == true) {
            if (buff[1] == "AA") {
                return new User(temp_username, atoi(buff[2].c_str()));
            } else {
                char acc_type[2];
                acc_type[0] = buff[1][0];
                acc_type[1] = buff[1][1];

                return new Standard(temp_username, atoi(buff[2].c_str()), acc_type);
            }
        }
    }
    return NULL;
}