#ifndef _COOP_H_
#define _COOP_H_

#include <iostream>
#include "square.h"

class Coop : public Square {
  const static int payMoney = 150;

 public:
        Coop(Board * board,std::string name, int position);
        virtual void action(Player* player) override;
};

#endif

