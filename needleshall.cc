#include "needleshall.h"
using namespace std;

NeedlesHall::NeedlesHall(Board * board, string name, int position) : Square{board,name, "", position, 0, nullptr, 0, false, false} {}

void NeedlesHall::action(Player* player){
        srand (time(NULL));
        int val = rand() % 100 + 1;
        if(val == 100 && getBoard()->getRollUpCards() != 4){
                player->addTimCup();
		getBoard()->setRollUpCards(getBoard()->getRollUpCards()+1);
		cout << "You got a roll up the rims card from landing on NeedlesHall" << endl;
        }
        else{
                val = rand() % 1000 + 1;

                if(val >= 1 && val < 56){
			cout << "You lost 200 dollars from landing on NeedlesHall" << endl;
                        player->subtractMoney(200, getBoard()->getPlayers());
                }
                else if(val >= 56 && val < 167){
			cout << "You lost 100 dollars from landing on NeedlesHall" << endl;
                        player->subtractMoney(100, getBoard()->getPlayers());
                }
                else if(val >= 167 && val < 334){
			cout << "You lost 50 dollars from landing on NeedlesHall" << endl;
                        player->subtractMoney(50, getBoard()->getPlayers());
                }
                else if(val >= 334 && val < 667){
			cout << "You gained 25 dollars from landing on NeedlesHall" << endl;
                        player->addMoney(25);
                }
                else if(val >= 667 && val < 834){
			cout << "You gained 50 dollars from landing on NeedlesHall" << endl;
                        player->addMoney(50);
		}
		else if(val >= 834 && val < 945){ 
			cout << "You gained 100 dollars from landing on NeedlesHall" << endl;
			player->addMoney(100); 
		}
		else{
			cout << "You gained 200 dollars from landing on NeedlesHall" << endl;
			player->addMoney(200);
		}

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
	}
}




