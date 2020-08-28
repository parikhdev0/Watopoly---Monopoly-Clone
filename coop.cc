#include "coop.h" 
using namespace std;  


Coop::Coop(Board * board,string name, int position) : Square{board, name, "", position, 0, nullptr, 0, false, false} {}

void Coop::action(Player* player){
	cout << "You are being charged with coop fees." << endl;
	player->subtractMoney(payMoney, getBoard()->getPlayers());
	if (player->isBankrupt()){
		if(getBoard()->getPlayers().size()<3){
			cout << "Game has ended" << endl;
		}
		else{
			cout << "You have been bankrupted, your properties will be auctionned, your other assets will return to the bank." << endl;
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

