#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "board.h"
#include "subject.h"
#include <string>
#include <vector>
#include <memory>
class Player;
class Board;
class Square: public Subject{
	Board * board;	
	std::string name;
	std::string monopolyBlock;	
	int position;
	int cost;
	Player * owner;
	int improvement_level;	
	bool ownable;
	bool improvable;
 public:
  Square(Board * board, std::string name, std::string monopolyBlock, int position, int cost, 
		  Player * owner, int improvement_level, bool ownable, bool improvable);

  Board* getBoard();
  virtual std::string getName() override;
  std::string getMonopolyBlock();
  int getPosition();
  int getCost();
  Player* getOwner();
  void setOwner(Player* player);
  int getImprovementLevel();
  void setImprovementLevel(int level);
  bool isOwnable();
  bool isImprovable();
  bool isMortgaged();  
  virtual int getValue();
  virtual bool isGym();
  virtual void action(Player * player);
  virtual void mortgage(Player * player);
  virtual void unmortgage(Player * player);
  virtual void improveBuy(Player * player);
  virtual void improveSell(Player * player);
  virtual void auction();
  virtual ~Square()=0;

};

#endif

