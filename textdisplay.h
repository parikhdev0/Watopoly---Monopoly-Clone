#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <cstddef> 
#include <iostream>
#include <vector>
#include <fstream>
#include "observer.h"
#include "square.h"
class Board;

class TextDisplay: public Observer {
	    const char SPACE = 32;
	    const char O = 79;
	    const char COLON = 58;
	    const char I = 73;
	    const char V = 86;
	    const char M = 77;
	    Board * game;
	    std::vector<std::shared_ptr<Player>> players;
	    std::vector<std::vector<char>> board;
    	    void updateSquare(std::shared_ptr<Square>, int row, int col);
 public:
    TextDisplay(Board * game);
    virtual void notify(std::shared_ptr<Subject>  whoNotified ) override;
    virtual void notify() override;
    void print();
};


#endif
