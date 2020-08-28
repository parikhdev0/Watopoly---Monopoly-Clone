#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.h"
class Square;
class Player;
class TextDisplay;
class Board{
	
	const int maxNumOfPlayers = 8;
	const int numOfSquares = 40;
	const int jailSpace = 10;
	const int goToJailSpace = 30;
	const int osapSpace = 0;
	const int playerStartingMoney = 1500;

	int numOfPlayers;
	int rollUpCards=0;
	
	std::vector<std::shared_ptr<Player>> playerList;
	std::vector<std::shared_ptr<Square>> squares;
	
	const std::vector<std::string> pieces = {"G: Goose", "B: GRT Bus ", "D: Tim Hortons Doughnut", "P: Professor", "S: Student", "$: Money", "L: Laptop", "T: Pink Tie"};
	const std::vector<int> ownableIndex = {1,3,5,6,8,9,11,12,13,14,15,16,18,19,21,23,24,25,26,27,28,29,31,32,34,35,37,39};
	
	bool testMode = false;
	std::shared_ptr<TextDisplay> td;
	
	const std::vector<int> AL = {2, 10, 30, 90, 160, 250};
	const std::vector<int> ML = {4, 20, 60, 180, 320, 450};
	const std::vector<int> ECH = {6, 30, 90, 270, 400, 550};
	const std::vector<int> PAS = {6, 30, 90, 270, 400, 550};
	const std::vector<int> HH = {8, 40, 100, 300, 450, 600};
	const std::vector<int> RCH = {10, 50, 150, 450, 625, 750};
	const std::vector<int> DWE = {10, 50, 150, 450, 625, 750};
	const std::vector<int> CPH = {12, 60, 180, 500, 700, 900};
	const std::vector<int> LHI = {14, 70, 200, 550, 750, 950};
	const std::vector<int> BMH = {14, 70, 200, 550, 750, 950};
	const std::vector<int> OPT = {16, 80, 220, 600, 800, 1000};
	const std::vector<int> EV1 = {18, 90, 250, 700, 875, 1050};
    	const std::vector<int> EV2 = {18, 90, 250, 700, 875, 1050};
	const std::vector<int> EV3 = {20, 100, 300, 750, 925, 1100};
	const std::vector<int> PHYS = {22, 110, 330, 800, 975, 1150};
	const std::vector<int> B1 = {22, 110, 330, 800, 975, 1150};
	const std::vector<int> B2 = {24, 120, 360, 850, 1025, 1200};
	const std::vector<int> EIT = {26, 130, 390, 900, 1100, 1275};
	const std::vector<int> ESC = {26, 130, 390, 900, 1100, 1275};
	const std::vector<int> C2 = {28, 150, 450, 1000, 1200, 1400};
	const std::vector<int> MC = {35, 175, 500, 1100, 1300, 1500};
	const std::vector<int> DC = {50, 200, 600, 1400, 1700, 2000};
	
	void trade(std::vector<std::string> command, int currPlayer);
	void displayOption(std::shared_ptr<Player> player);
	void initSquares();
  
  public:
	std::vector<std::shared_ptr<Player>> getPlayers();
	std::vector<std::shared_ptr<Square>> getSquares();
	int getRollUpCards();
	void setRollUpCards(int cards);
	bool isInTestMode();
	void setTesting();
	
	void initialize(int numOfPlayers);
	void loadGame(std::string file);
	void saveGame(std::string file, int index);
	std::vector<int> rollDice(int d1, int d2);
	void play();
	
};
#endif

