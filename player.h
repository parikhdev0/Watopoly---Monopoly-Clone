#ifndef PLAYER_H
#define PLAYER_H

#include "square.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>
class Square;

class Player{
	
	char piece;
	std::string name;
	
	bool bankrupt;
	int money;
	int position;
	int timCups;
	
	int numOfResidences;
	int numOfGyms;
	std::vector<std::shared_ptr<Square>> squaresOwned;
	
	bool inJail;
	int jailTurns;
	std::vector<int> jailLastRoll;
	
public:
	Player(char piece, std::string name, int money, int position, int timCups);
	char getPiece();
	std::string getName();
	bool isBankrupt();
	int getMoney();
	int getPosition();
	void setPosition(int pos);
	int getTimCups();
	void addTimCup();
	void useTimCup();
	int getGymNum();
	void addGym();
	int getResNum();
	void addRes();
	std::vector<std::shared_ptr<Square>> getSquares();
	bool isInJail();
	void setJail(bool jail);
	int getJailTurns();
	void setJailTurns(int jt);
	std::vector<int> getJailLastRoll();
	void setJailLastRoll(std::vector<int> roll);	
	
	int getWorth();
	void printPlayerAssets();
	void move(int position);
	void addMoney(int amount);
	void subtractMoney(int amount, std::vector<std::shared_ptr<Player>> otherPlayers);
	void addSquare(std::shared_ptr<Square> square);
	void transferMoney(Player* to, int amount, std::vector<std::shared_ptr<Player>> otherPlayers);
	void transferProperty(Player* to, std::shared_ptr<Square> square, std::vector<std::shared_ptr<Player>> players);	

};
#endif
