#ifndef _GYM_H_
#define _GYM_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "square.h"
class Gym : public Square{
 private:
  static const int gym_price = 150;
 
  int improvementCost;
  std::vector<int> tuition;
  bool gym = true;

 public:
  Gym(Board * board,std::string name, int position);
 
  virtual void action(Player * player) override; 
  virtual bool isGym() override;
  void buy(Player * player, int price);
  void auction();
  void payFee(Player * player);
  void mortgage(Player * player);
  void unmortgage(Player * player);
};

#endif

