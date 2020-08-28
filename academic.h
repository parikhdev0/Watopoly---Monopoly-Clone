#ifndef _ACADEMICPROPERTY_H_
#define _ACADEMICPROPERTY_H_


#include <iostream>              
#include "player.h"
#include "square.h"

class AcademicProperty: public Square {
	int improvementCost;
	std::vector<int> tuition;
	
public:
  AcademicProperty(Board * board, std::string name, std::string monopolyBlock, int position, int cost, int improvementCost, std::vector<int> tuition);

  virtual void action(Player* player);
  void buy(Player *, int price);
  void auction();
  void payTuition(Player* tenant);
  virtual void improveBuy(Player* player);
  virtual void improveSell(Player* player);
  virtual void mortgage(Player* player) override;
  virtual void unmortgage(Player* player);

  virtual int getValue() override; 
  int getImprovementCost(); 
  std::vector<int> getTuition(); 
  bool hasMonopoly();

};

#endif

