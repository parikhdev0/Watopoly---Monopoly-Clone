#include "slc.h"
using namespace std;

SLC::SLC(Board * board,string name, int position) : Square{board, name, "", position, 0, nullptr, 0, false, false} {}

void SLC::action(Player* player){
	srand (time(NULL)); 
	int val = rand() % 100 + 1;
	int oldpos = player->getPosition();
	if(val == 100 && getBoard()->getRollUpCards()!= 4){
		player->addTimCup();
		getBoard()->setRollUpCards(getBoard()->getRollUpCards()+1);
		cout << "You recieved a roll up the rims tims card from landing on SLC!" << endl;
	}
	else{
		val = rand() % 1000 + 1;	
		if(val >= 1 && val < 126){
			cout << "You moved back 3 spaces from landing on SLC." << endl;
			player->move(-3);	
		}
		else if(val >= 126 && val < 292){
			cout << "You moved back 2 spaces from landing on SLC." << endl;
			player->move(-2);
		}
		else if(val >= 292 && val < 459){
			cout << "You moved back 1 space from landing on SLC." << endl;
			player->move(-1);
		}
		else if(val >= 459 && val < 584){
			cout << "You moved up 1 space from landing on SLC." << endl;
			player->move(1);
		}
		else if(val >= 584 && val < 752){ 
			cout << "You moved up 2 spaces from landing on SLC." << endl;
			player->move(2);  
		} 
		else if(val >= 752 && val < 918){   
			cout << "You moved up 3 spaces from landing on SLC." << endl;
			player->move(3);
		} 
		else if(val >= 918 && val < 960){  
			cout << "You moved to Jail from landing on SLC." << endl;
			int oldpos = player->getPosition();
			player->setPosition(10);	
			player->setJail(true);
			player->setJailTurns(0);
			getBoard()->getSquares()[oldpos]->notifyObservers();
			getBoard()->getSquares()[10]->notifyObservers();
		}
		else{
			cout << "You moved to OSAP from landing on SLC." << endl;
			int oldpos = player->getPosition();
			player->setPosition(0);	
			getBoard()->getSquares()[oldpos]->notifyObservers();
			getBoard()->getSquares()[10]->notifyObservers();
		}
	}
	if (player->getPosition()<0){
		player->move(40);
	}
	if (player->getPosition()!=oldpos && player->getPosition()!=10){
		getBoard()->getSquares()[player->getPosition()]->action(player);
	}
	getBoard()->getSquares()[oldpos]->notifyObservers();
	getBoard()->getSquares()[player->getPosition()]->notifyObservers();
}

