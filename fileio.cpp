/*
* The FileIO class implements functions to read/write various files 
*
* @param daily_trans_file name of daily transaction file
* @param curr_account_file name of current user accounts file
* @param avail_tickets_file name of available tickets file
*
* @method readAccounts reads the current accounts file (users.ua)
* @method readTickets reads the available tickets file (stock.at)
*
* @author Kevin Desousa, Samuel Pilkey, and Daniel Bullock (Team JDK)
* @version 0.1
* @since 2019-02-12
*/

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

/*
* Reads the current accounts file (users.ua) and returns a instance of the user class
* @param username The username entered 
* @return User This returns a instance of the User class
*/
User* FileIO::readAccounts(std::string username) {
    std::string line;
    std::ifstream file;
    file.open(curr_account_file);

    if (file.is_open()) {
        bool found = false;
        std::string buff[3];

        while (std::getline(file, line) && found == false) {
            buff[0] = "";
            for (int i = 0; i < 15; i++) {
                buff[0] += line[i];
                line[i] = 0;
            }
            line[15] = 0;

            std::cout << line << std::endl;

            std::stringstream ss(line);

            // Load the line's information into the buffer
            int i = 1;
            while (ss >> buff[i]) {
                i++;
            }

            // Check if it matches the string
            if (buff[0] == username) {
                found = true;
            } else {
                found = false;
            }
        }

        file.close();
        if (found == true) {
            return new User(buff[0], atoi(buff[2].c_str()), buff[1]);
        }
    }
    return NULL;
}

/*
* Reads the available tickets file (stock.at) and returns a instance of the ticket class
* @param event_title The title of the event that the user wants to purchase tickets for
* @param seller_username The username of the user wanting to buy the ticket
* @return Tickets This returns a instance of the Tickets class
*/
Tickets* FileIO::readTickets(std::string event_title, std::string seller_username){
    std::string line;
    std::ifstream file;
    file.open(avail_tickets_file);

    if(event_title.length() < 25 ){
        event_title += (std::string(25 - event_title.length(), ' ')); // in theory this should normalize the string to 25 characters
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
            // std::cout << file_event << std::endl;
            // std::cout << file_seller << std::endl;
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
          // creating new struct to hold the tickets information
          // and pass the struct back to main.cpp
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
