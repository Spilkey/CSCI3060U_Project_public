#ifndef fileio_H
#define fileio_H

class FileIO {
    std::string daily_trans_file;
    std::string curr_account_file;
    std::string avail_tickets_file;

   public:
    FileIO(std::string account_file, std::string tickets_file, std::string transaction_file);
    User* readAccounts(std::string username);
    Tickets* readTickets(std::string event_title, std::string seller_username);

};

#endif
