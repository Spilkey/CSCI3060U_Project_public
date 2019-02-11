#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "admin.h"
#include "user.h"
#include "tickets.h"
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
Tickets* FileIO::readTickets(std::string event_title, std::string seller_username){
    std::string line;
    std::ifstream file;
    file.open(avail_tickets_file);

    if(event_title.length() < 25 ){
        event_title += (std::string(25 - event_title.length(), ' ')); // in theory this should normalize the string to 15 characters
    }
    if(seller_username.length() < 14 ){
        seller_username += (std::string(14 - seller_username.length(), ' ')); // in theory this should normalize the string to 15 characters
    }
    // std::cout << seller_username << std::endl;
    // std::cout << event_title << std::endl;
    if (file.is_open()) {
        bool found = false;
        std::string buff[4];

        while (std::getline(file, line) && found == false) {

            std::string file_event (line.begin(), line.begin()+25);
            std::string file_seller (line.begin()+26, line.begin()+40);
            //
            // std::cout << file_event << std::endl;
            // std::cout << file_seller << std::endl;

            //if the seller username and event title is found
            if((seller_username == file_seller) && (event_title == file_event)){
                found = true;
                buff[0] = file_event;
                buff[1] = file_seller;
                buff[2] = std::string (line.begin()+41, line.begin()+44);
                buff[3] = std::string (line.begin()+45, line.begin()+51);
            }
        }

        file.close();
        if (found == true) {
          //creating new stuct to hold the tickets information
          //and pass the stuct back to main.cpp
          Tickets *t =  new Tickets;
          t->event_title = buff[0];
          t->seller_username = buff[1];
          t->total_tickets = std::stoi(buff[2]);
          t->price = std::stoi(buff[3]);
          return t;
        }
    }
    return NULL;
}
