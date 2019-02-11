#ifndef tickets_H
#define tickets_H

/*
@return event title
@return seller username
@return total number of tickets for sale
@return ticket price
*/
struct Tickets{
  std::string   event_title;
  std::string   seller_username;
  int           total_tickets;
  float         price;
};

#endif
