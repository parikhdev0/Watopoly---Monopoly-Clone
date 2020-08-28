#ifndef _GOOSENESTING_H_
#define _GOOSENESTING_H_

#include <iostream>
#include <fstream>
#include "square.h"

class GooseNesting : public Square {
 public:
        GooseNesting(Board * board,std::string name, int position);
        virtual void action(Player * player) override;
};

#endif

