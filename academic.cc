#include "academic.h"
using namespace std;


AcademicProperty::AcademicProperty(Board * board,std::string name, std::string monopolyBlock, int position, int cost, int improvementCost, vector<int> tuition): 
			Square{board, name, monopolyBlock, position, cost, nullptr, 0, true, true}, 
			improvementCost{improvementCost}, tuition{tuition}{	
}


void AcademicProperty::action(Player* player){
		cout << "You have landed on " << getName() <<  "." << endl;
		
		if (getOwner()==nullptr && getCost()>player->getMoney()){
			cout << "No one owns this property but you don't have enough money to normally buy it, so it will be auctioned." << endl;
			auction();
		}
		else if (getOwner()==nullptr){
			cout << "No one owns this property yet, you can choose to buy it. Enter \"buy\" to buy the property, or anything else to auction it." << endl;
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
			cout << "The property is owned by " << getOwner()->getName() <<  ". The tuition is currently " << tuition[getImprovementLevel()] << "." << endl;
			payTuition(player);
		}
}

void AcademicProperty::buy(Player* player, int price){
        if(!getOwner()){
		if(player->getMoney() - price >= 0){
                        
			player->subtractMoney(price, getBoard()->getPlayers());
                        setOwner(player);
                        player->addSquare(getBoard()->getSquares()[getPosition()]);
			cout << player->getName() << " bought this property for " << price << endl;
                }
                else{
                        cout << player->getName() << " does not have enough funds to purchase " << getName() << "." << endl;
                }
        }
        else{
                cout << getOwner()->getName() << " owns " << getName() << "." << endl;
        }
}

void AcademicProperty::auction(){
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

void AcademicProperty::payTuition(Player* tenant){
        if(getOwner() && !isMortgaged() && tenant->getName() != getOwner()->getName()){    
		int subMoney = 0;
		subMoney = tuition[getImprovementLevel()];
                if (hasMonopoly()&&getImprovementLevel()<1){
			subMoney*=2;
			cout << "Since the owner owns a monopoly of this unimproved property, the tuition is doubled." << endl;
		}
		cout << "The tuition owed is: " << subMoney << endl;
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


void AcademicProperty::improveBuy(Player* player){
	if (!getOwner()|| player->getName()!=getOwner()->getName()){
		cout << "You are not the owner." << endl;
		return;
	}	
	if (isMortgaged()){
		cout << "Can't improve a mortgaged property." << endl;
		return;
	}
	if (getImprovementLevel()>=5){
		cout << "Already at max improvement." << endl;
		return;
	}
	if (!hasMonopoly()){
		cout << "You don't have the full monopoly." << endl;
		return;
	}
	cout << "The improvement cost is " << improvementCost << "." << endl;
	if (player->getMoney()<improvementCost){
		cout << "You don't have enough money." << endl;
		return;
	}
					
	player->subtractMoney(improvementCost, getBoard()->getPlayers());
	setImprovementLevel(getImprovementLevel()+1);
       	cout << "You have bought an improvement on " << getName() << "." << endl;
       	if (getImprovementLevel()<5){
		cout << "You now have a new bathroom " << getName() << "." << endl;
	}
	else{
		cout << "You now have a new cafeteria " << getName() << "." << endl;
	}
}

void AcademicProperty::improveSell (Player* player){        
	if (!getOwner()|| player->getName()!=getOwner()->getName()){
                cout << "You are not the owner." << endl;
                return;
        }
        if (getImprovementLevel()<1){
                cout << "No improvements to sell." << endl;
                return;
        }
        int profit = improvementCost*0.5;
	cout << "The money you get back is " << profit << "." << endl;
	player->addMoney(profit);
        setImprovementLevel(getImprovementLevel()-1);
       	cout << "You have sold an improvement on " << getName() << "." << endl;
	if (getImprovementLevel()<4){
		cout << "You sold a bathroom on " << getName() << "." << endl;
	}
	else{
		cout << "You sold a cafeteria on " << getName() << "." << endl;
	}
}


void AcademicProperty::mortgage(Player* player){
        if (!getOwner()|| player->getName()!=getOwner()->getName()){
                cout << "You are not the owner." << endl;
                return;
        }
        if (isMortgaged()){
                cout << "This property is already mortgaged." << endl;
                return;
        }
        if (getImprovementLevel()>0){
                cout << "Cannot mortgage a property with improvements." << endl;
                return;
        }
	cout << "The money you get from mortgaging is " << getCost()/2 << "." << endl;
        player->addMoney(getCost() / 2);
       	setImprovementLevel(-1);
       	cout << "You have mortgaged " << getName() << "." << endl;
}

void AcademicProperty::unmortgage(Player* player){        
	if (!getOwner()|| player->getName()!=getOwner()->getName()){
                cout << "You are not the owner." << endl;
                return;
        }
        if (!isMortgaged()){
                cout << "This property is not mortgaged." << endl;
                return;
        }
        int subMoney = (getCost() / 2) + (getCost() * 0.1);
	cout << "The money you owe from unmortgaging is " << subMoney << "." << endl;
        if (player->getMoney()<subMoney){
                cout << "You don't have enough money to unmortgage." << endl;
                return;
        }
        player->subtractMoney(subMoney, getBoard()->getPlayers());
	setImprovementLevel(0);
       	cout << "You have unmortgaged " << getName() << "." << endl;
}


int AcademicProperty::getValue(){
	return getCost() + (improvementCost*getImprovementLevel());
}

int AcademicProperty::getImprovementCost(){
	return improvementCost;
}

vector<int> AcademicProperty::getTuition(){
	return tuition;
}

bool AcademicProperty::hasMonopoly(){
	vector<shared_ptr<Square>> squares = getBoard()->getSquares();
	int numSquares = squares.size();
	for(int i = 0; i < numSquares; i++){
		shared_ptr<Square> square = squares[i];
		if(square->getMonopolyBlock() == getMonopolyBlock() && !(square->getOwner()==getOwner())){
				return false;
		}
	}
	return true;
}
