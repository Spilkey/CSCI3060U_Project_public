#ifndef tickets_H
#define tickets_H

/**
* @return event title
* @return seller username
* @return total number of tickets for sale
* @return ticket price
*
* @author Kevin Desousa, Samuel Pilkey, and Daniel Bullock (Team JDK)
* @version 0.1
* @since 2019-02-03
*/
struct Tickets{
  std::string   event_title;
  std::string   seller_username;
  int           total_tickets;
  float         price;
};

#endif
