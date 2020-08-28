#ifndef _SLC_H_
#define _SLC_H_

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "square.h"

class SLC : public Square {

 public:
        SLC(Board * board,std::string name, int position);
        virtual void action(Player* player) override;
};

#endif

