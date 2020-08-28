#ifndef _NEEDLESHALL_H_
#define _NEEDLESHALL_H_

#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "square.h"

class NeedlesHall : public Square {

 public:
        NeedlesHall(Board * board,std::string name, int position);
        virtual void action(Player * player) override;
};

#endif

