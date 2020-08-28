#include "goToTims.h"
using namespace std;


GoToTims::GoToTims(Board * board,string name, int position) : Square{board, name, "", position, 0, nullptr, 0, false, false} {}

void GoToTims::action(Player * player){
	cout << "You are going to jail." << endl;
	int oldpos = player->getPosition();
	player->setPosition(10);
	player->setJail(true);
	player->setJailTurns(0);
	getBoard()->getSquares()[oldpos]->notifyObservers();	
	getBoard()->getSquares()[10]->notifyObservers();

}


