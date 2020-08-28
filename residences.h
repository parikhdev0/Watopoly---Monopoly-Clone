#ifndef _RESIDENCES_H_
#define _RESIDENCES_H_

#include <iostream>
#include "player.h"
#include "square.h"


class Residences : public Square{
 private:
  static const int res_price = 200;
  bool gym=false;
 public:
  Residences(Board * board,std::string name, int position);
  virtual void action(Player* player) override;
  virtual bool isGym() override;
  void buy(Player * player, int price);
  void auction();
  void payRent(Player* player);
  void mortgage(Player* player);
  void unmortgage(Player* player);
};

#endif
