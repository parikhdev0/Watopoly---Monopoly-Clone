#include "tuition.h"
using namespace std;

Tuition::Tuition(Board * board,string name, int position) : Square{board, name, "", position, 0, nullptr, 0, false, false} {}

void Tuition::action(Player* player){
	int tenpercent = player->getWorth() * 0.1;
	cout << "Choose between paying $300 tuition or 10\% of your total worth (including your savings, printed prices of all buildings you own, and costs of each improvement)." << endl;
	cout << "Enter '300' to pay the flat fee, or '10' to pay 10\% of your total worth." << endl;
	cout << "10\% of your worth is " << tenpercent << endl; 
	while(true){
		string command;
        	cin >> command;
	
        	if (cin.eof()) break;	
		
		int moneyOwed=300;
	        if ( command == "10" ){
			moneyOwed=tenpercent;
		}
		else if (command != "300"){
			cout << "Enter valid command" << endl;
			continue;
		}
		player->subtractMoney(moneyOwed, getBoard()->getPlayers());
		if (player->isBankrupt()){
                        if (getBoard()->getPlayers().size()<3){
				cout << "Game has ended." << endl;
				return;
			}
			cout << "You have been bankruptted, your properties will be auctionned, your other assets will return to the bank." << endl;
			vector<shared_ptr<Square>> squares = player->getSquares();
	                int numProperties = squares.size();
               	 	for (int i=0; i<numProperties; i++){
                       		shared_ptr<Square> square = squares[i];
				square->setOwner(nullptr);
		       		square->auction();
                	}
			getBoard()->setRollUpCards(getBoard()->getRollUpCards()-player->getTimCups());
		}
		break;
	}
}
