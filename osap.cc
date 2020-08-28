#include "osap.h"
using namespace std;


Osap::Osap(Board * board,string name, int position) : Square{board, name, "", position, 0, nullptr, 0, false, false} {}
void Osap::action(Player * player){
	collectMoney(player);
}
void Osap::collectMoney(Player * player){
	cout << "Collected Money from OSAP!!!" << endl;
	player->addMoney(money);
}


