/**
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
* @since 2019-02-03
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
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
            }
            line = line.substr(16, line.length() - 15);

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

          // this is to combat a small rounding error with strtof
            float to_user_credit = strtof(buff[2].c_str(),0);
            if(to_user_credit >= 1000000){
              to_user_credit = 999999.00;
            }
            return new User(buff[0], to_user_credit, buff[1]);
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

    // normalizing event title and user name to correct lengths
    if(event_title.length() < 25 ){
        event_title += (std::string(25 - event_title.length(), ' '));
    }
    if(seller_username.length() < 15 ){
        seller_username += (std::string(15 - seller_username.length(), ' '));
    }
    if (file.is_open()) {
        bool found = false;
        std::string ticket_info[4];

        while (std::getline(file, line) && found == false) {

            // will create a substring from int to int using .begin() as a starting point
            std::string file_event (line.begin(), line.begin()+25);
            std::string file_seller (line.begin()+26, line.begin()+41);


            // if the seller username and event title is found
            if((seller_username == file_seller) && (event_title == file_event)){
                found = true;
                ticket_info[0] = file_event;
                ticket_info[1] = file_seller;
                ticket_info[2] = std::string (line.begin()+42, line.begin()+45);
                ticket_info[3] = std::string (line.begin()+46, line.begin()+52);
            }
        }

        file.close();
        if (found == true) {
          // creating new struct to hold the tickets information
          // and pass the struct back to main.cpp
          Tickets *t =  new Tickets;
          t->event_title = ticket_info[0];
          t->seller_username = ticket_info[1];
          t->total_tickets = std::stoi(ticket_info[2]);
          //this is an integer
          //TODO: make this read a float
          t->price = std::stoi(ticket_info[3]);
          return t;
        }
    }
    return NULL;
}

void FileIO::writeTransactions(std::vector<std::string> transactions){
    std::ofstream file; // The file to write to
    file.open(this->daily_trans_file, std::ios_base::app); // Open the file


    // Check if the file has contents, if so append a new line
    std::ifstream file_check;
    file_check.open(this->daily_trans_file);
    if(file_check.peek() == std::ifstream::traits_type::eof() == false){
        file << std::endl;
    }
    file_check.close();


    // Print the elements in the array to the file
    for(int i = 0; i < transactions.size(); i++){
        if(i != 0){
             file << std::endl;
        }
        file << transactions[i];
    }

    // Close the file
    file.close();
}
