#ifndef fileio_H
#define fileio_H

class FileIO {
    std::string daily_trans_file;
    std::string curr_account_file;
    std::string avail_tickets_file;

   public:
    FileIO(std::string account_file, std::string tickets_file);
    User* readAccounts(char username[15]);
};

#endif