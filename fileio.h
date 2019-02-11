#ifndef fileio_H
#define fileio_H

/*
@param daily_trans_file name of daily transaction file
@param curr_account_file name of current user accounts file
@param avail_tickets_file name of available tickets file

@method readAccounts reads the current accounts file (users.ua)
@method readTickets reads the available tickets file (stock.at)
*/
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
