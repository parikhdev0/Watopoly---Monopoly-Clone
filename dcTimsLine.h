#ifndef _DCTIMSLINE_H_
#define _DCTIMSLINE_H_

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "player.h"
#include "square.h"

class DCTimsLine : public Square {
	const int jailFee = 50;
public:
        DCTimsLine(Board * board,std::string name, int position);
        virtual void action(Player* player) override;
	void rollDice(Player* player);
	void payJailFee(Player* player);
	void useRollUp(Player* player);
};

#endif

