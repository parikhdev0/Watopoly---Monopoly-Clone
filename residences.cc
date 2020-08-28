#include "residences.h"
using namespace std;


Residences::Residences(Board * board,std::string name, int position): 
	Square{board, name, "", position, res_price, nullptr, 0, true, false}{}

bool Residences::isGym(){
	return gym;
}

void Residences::action(Player * player){
		if (getOwner()==nullptr && getCost()>player->getMoney()){
			cout << "No one owns this property but you don't have enough money to normally buy it, so it will be auctioned." << endl;
			auction();
		}
		else if (getOwner()==nullptr){
                        cout << "Noone owns this property yet, you can choose to buy it. Enter \"buy\" to buy the property, or anything else to auction it." << endl;
                        string line = "";
                        cin >> line;
                        if (line=="buy"){
                                buy(player, getCost());
                        }
                        else{
                                cout << "Since you didn't buy the property, we will now auction it." << endl;
                                auction();
                        }
                }
                else if (getOwner()==player){
                        cout << "You own this property, no action is to be taken." << endl;
                }
                else{
                        cout << "The property is owned by " << getOwner()->getName() <<  "." << endl;
                        payRent(player);
                }
}

void Residences::buy(Player * player, int price){
	if(!getOwner()){
		if(player->getMoney() - price >= 0){
			player->subtractMoney(price, getBoard()->getPlayers());
			setOwner(player);
			player->addRes();
                        player->addSquare(getBoard()->getSquares()[getPosition()]);
                        cout << "You bought this property for " << getCost() << endl;
		}
		else{
			cout << "You do not have enough funds to purchase " << getName() << "." << endl;
		}	
	}
	else{
		cout << getOwner()->getName() << " owns " << getName() << "." << endl;
	}
	notifyObservers();
}

void Residences::auction(){ 
	cout << "Commencing auction of " << getName() << endl;
	setImprovementLevel(0);
   	vector<shared_ptr<Player>> players = getBoard()->getPlayers();
        int numPlayers = players.size();
        int auctioneers = players.size();
        vector<bool> withdraw;
        for(int i = 0; i < auctioneers; i++){
                withdraw.push_back(false);
        }
        int currBid = 0;
	bool noBids = true;
        cout << "The starting bid is: $ " << currBid << "." << endl;
        int index=0;
        while (auctioneers != 0){
		if (auctioneers==1 && !noBids){
			break;
		}
                string option;
		if (players[index]->isBankrupt()){
			auctioneers--;
			withdraw[index]=true;
			index = (index+1)%numPlayers;
			while (withdraw[index]){
				index=(index+1)%numPlayers;
			}
			continue;
		}
                cout << "The current bid is: $ " << currBid << "." << endl;
		while (true){
                	cout << players[index]->getName() << ": Enter 'withdraw' to withdraw from the bid or 'bid' to bid a higher value. " << endl;
                	cin >> option;
			if(option == "withdraw"){
                        	withdraw[index] = true;
                        	auctioneers--;
				break;
                	}
                	else if(option == "bid"){
					string newBid;        
                        		cout << "Enter bid value: " << endl;
                        		cin >> newBid;
                        		if(newBid == "withdraw"){
                                		withdraw[index] = true;
                                		auctioneers--;
                                		break;
                        		}
					try{
						int newBidInt = stoi(newBid);
						if (newBidInt>players[index]->getMoney()){
							cout << "You cant afford this bid, withdraw, or enter a lower bid" << endl;
							continue;
						}
						if (newBidInt>currBid){
							noBids=false;
							currBid=newBidInt;
							break;
						}
						else{
                                        		cout << "This bid is not higher than the previous bid. Enter a value higher than the preivous bid or 'withdraw': " << endl;
							continue;
						}

					}	
					catch(invalid_argument &ia){	
        	                                cout << "Enter a valid bid  or 'withdraw': " << endl;
						continue;
					}	
			}
			else{
				cout << "Enter either 'bid' or 'withdraw'" << endl;
			}
		}
		index = (index+1)%numPlayers;
		if (auctioneers==1 || auctioneers==0){
			continue;
		}
		while (withdraw[index]){
			index=(index+1)%numPlayers;
		}

        }
	if (noBids){
		cout << "There were no bids for the auction so it ended. Property will remain belonged to the bank.";
		return;
	}
        int winner = 0;
        for (int i=0; i<numPlayers; i++){
                if(!withdraw[i]){
                        winner=i;
                        break;
                }
        }
	cout << players[winner]->getName() << " has won the auction, and purchased " << getName() << " for " << currBid << "." << endl;
        buy(players[winner].get(), currBid);
}

void Residences::payRent(Player * tenant){
	if(getOwner() && !isMortgaged() && tenant->getName() != getOwner()->getName()){
		int subMoney = 0;
		int res = getOwner()->getResNum();
		if(res == 1)
			subMoney = 25;
		else if(res == 2)
			subMoney = 50;
		else if(res == 3)
			subMoney = 100;
		else if(res == 4)
			subMoney = 200;
		cout << "The rent owed is " << subMoney << "." << endl;
		tenant->subtractMoney(subMoney, getBoard()->getPlayers());
                if(tenant->isBankrupt()){
                        if (getBoard()->getPlayers().size()<3){
				cout << "Game has ended." << endl;
				return;
			}
                        cout << tenant->getName() << " is now bankrupt. All assets go to " << getOwner()->getName() << endl;
                        getOwner()->addMoney(tenant->getMoney());
                        vector<shared_ptr<Square>> squares = tenant->getSquares();
                        int numPropertiesTenant = squares.size();
                        for (int i=0; i<numPropertiesTenant; i++){
                                shared_ptr<Square> square = squares[i];
                                tenant->transferProperty(getOwner(), square, getBoard()->getPlayers());
                        }
                        for (int i=0; i<tenant->getTimCups(); i++){
                                getOwner()->addTimCup();
                        }
                }
                else{
                        getOwner()->addMoney(subMoney);
                }
	}
}

void Residences::mortgage(Player * player){
       if (!getOwner()|| player->getName()!=getOwner()->getName()){
                cout << "You are not the owner" << endl;
                return;
        }
        if (isMortgaged()){
                cout << "This property is already mortgaged." << endl;
                return;
        }
	cout << "The money you get from mortgaging is " << getCost()/2 << "." << endl;
        player->addMoney(getCost() / 2);
        setImprovementLevel(-1);
       	cout << "You have mortgaged " << getName() << "." << endl;

}

void Residences::unmortgage(Player * player){
        if (!getOwner()|| player->getName()!=getOwner()->getName()){
                cout << "You are not the owner" << endl;
                return;
        }
        if (!isMortgaged()){
                cout << "This property is not mortgaged." << endl;
                return;
        }
        int subMoney = (res_price / 2) + (res_price * 0.1);
	cout << "The money you owe from unmortgaging is " << subMoney << "." << endl;
        if (player->getMoney()<subMoney){
                cout << "You don't have enough money to unmortgage." << endl;
                return;
        }
        player->subtractMoney(subMoney, getBoard()->getPlayers());
        setImprovementLevel(0);
       	cout << "You have unmortgaged " << getName() << "." << endl;
}

