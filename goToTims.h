#ifndef _GOTOTIMS_H_  
#define _GOTOTIMS_H_ 

#include <iostream>
#include "player.h"
#include "square.h"

class GoToTims : public Square {  
public:    
	GoToTims(Board * board,std::string name, int position);  
	virtual void action(Player * player) override;
};

#endif

