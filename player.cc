#include "player.h"
using namespace std;

Player::Player(char piece, std::string name, int money, int position, int timCups): piece{piece}, name{name}, bankrupt{false},
	money{money}, position{position}, timCups{timCups}, numOfResidences{0}, numOfGyms{0}, inJail{false}, jailTurns{-1}{ }

char Player::getPiece(){
	return piece;
}

string Player::getName(){
	return name;
}

bool Player::isBankrupt(){
	return bankrupt;
}

int Player::getMoney(){
	return money;
}

int Player::getPosition(){
	return position;
}

void  Player::setPosition(int pos){
	position = pos;
}

int Player::getTimCups(){
	return timCups;
}

void Player::addTimCup(){
	timCups++;
}

void Player::useTimCup(){
	timCups--;
}

int Player::getGymNum(){
	return numOfGyms; 
}

void Player::addGym(){
	numOfGyms++;
}

int Player::getResNum(){
	return numOfResidences;
}

void Player::addRes(){
	numOfResidences++;
}

std::vector<std::shared_ptr<Square>> Player::getSquares(){
	return squaresOwned;
}

bool Player::isInJail(){
	return inJail;
}

void Player::setJail(bool jail){
	inJail = jail;
}

int Player::getJailTurns(){
	return jailTurns;
}

void Player::setJailTurns(int jt){
	jailTurns = jt;
}

vector<int> Player::getJailLastRoll(){
	return jailLastRoll;
}

void Player::setJailLastRoll(vector<int> roll){
	jailLastRoll.clear();
	jailLastRoll.push_back(roll[0]);
	jailLastRoll.push_back(roll[1]);
}

int Player::getWorth(){
	int property_worth = 0;
	int size = squaresOwned.size();
	for (int i=0; i<size; i++){
		property_worth+=squaresOwned[i]->getValue();
	}	
	return property_worth+money;

}

void Player::printPlayerAssets(){
	cout << "Name: " << name << endl;
	cout << "Piece: " << piece << endl;
	cout << "Position: " << position << endl;
	if (inJail){
		cout << "Jail: " << (2-jailTurns) << " turns left" <<  endl;
	}
	else{
		cout << "Jail: Not in Jail" << endl;
	}

	if (bankrupt){
		cout << "Money: Is Bankrupt" << endl;
	}
	else{
		cout << "Money: $" << money << endl;
	}

	if (timCups>0){
		cout << "TimCups: " << timCups << endl;
	}
	int size=squaresOwned.size();
	if (size>0){
		cout << "Properties: " << squaresOwned[0]->getName();
	}
	for (int i=1; i<size; i++){
		cout << ", " << squaresOwned[i]->getName();
	}
	if (size>0){
		cout << endl;
	}
}

void Player::move(int pos){
	position+=pos;
}

void Player::addMoney(int amount){
	if (amount<=0){
		cout << "You are trying to add an amount less than 0. This is an invalid operation." << endl;
	}	
	else if (bankrupt){
		cout << "Player is bankrupt, and thus money can't be added." << endl;
	}
	else{
		money+=amount;
		cout <<  name << " now has a balance of " << money << " after completeing the transaction." << endl;
	}
	return;
}

void Player::subtractMoney(int amount, vector < shared_ptr < Player >> otherPlayers) {
        if (bankrupt) {
		cout << "Player is bankrupt, and thus money can't be subtracted." << endl;
                return;
        } else if (money >= amount) {
                money -= amount;
		cout <<  name << " now has a balance of " << money << " after completing the transaction." << endl;
        } else {
                cout << "Your do not have enough money for this transaction. These are your assets: " << endl;
                printPlayerAssets();
                cout << "The following commands are available to you: " << endl;
                cout << "   bankrupt" << endl;
                cout << "   mortgage <property>" << endl;
                cout << "   improve <property> sell" << endl;
                cout << "   trade <player_name> <property> <property>" << endl;
                cout << "   trade <player_name> <property> <money>" << endl;
                cout << "   all" << endl;
                string line = "";

                cout << "Enter a valid command: " << endl;
                while (money < amount) {
                        getline(cin, line);
                        stringstream ss(line);
                        string temp;
                        vector < string > command;
                        while (ss >> temp) {
                                command.push_back(temp);
                        }
                        if (command.size() < 1) {
                                continue;
                        }

                        if (command[0] == "bankrupt") {
                                cout << "You have chosen to declare bankruptcy. You will now be removed from the game." << endl;
				bankrupt = true;
                                return;
                        } else if (command[0] == "mortgage" && command.size()>1) {
                                        int size = squaresOwned.size();
                                        for (int i = 0; i < size; i++) {
                                                if (squaresOwned[i] -> getName() == command[1]) {
                                                        if (!(squaresOwned[i] -> isOwnable())) {
                                                                cout << squaresOwned[i]->getName() << "cannot be mortgaged." << endl;
                                                        } else {
                                                                squaresOwned[i] -> mortgage(this);
                                                        }
                                                        break;
                                                }
                                        }
                        } else if (command[0] == "improve" && command.size()>=3 && command[2]=="sell") {
                                        int size = squaresOwned.size();
                                        for (int i = 0; i < size; i++) {
                                                if (squaresOwned[i] -> getName() == command[1]) {
                                                        if (!(squaresOwned[i] -> isImprovable()) || squaresOwned[i] -> getImprovementLevel() < 1) {
                                                                cout << squaresOwned[i]->getName() << "has no improvements." << endl;
                                                        } else {
                                                                squaresOwned[i] -> improveSell(this);
                                                        }
                                                        break;
                                                }
                                        }
                        } else if (command[0] == "trade" && command.size()>=4) {
                            	int index=-1;
				int size = otherPlayers.size();
				for (int i=0; i<size; i++){
					if (otherPlayers[i]->getName()==command[1]){
						index = i;
						break;
					}
				}
				if (index==-1){
					cout << "Player: " << command[1]  <<" doesn't exist" << endl;
					continue;
				}
				Player* other = otherPlayers[index].get();

				int value=-1;
				try{
					value = stoi(command[3]);
				}
				catch(exception &err){}
				int value2=-1;
				try{
					value2 = stoi(command[2]);
				}
				catch(exception &err){}
				if (value>-1 && value2>-1){
					cout << "You can't trade money for money" << endl;
					continue;
				}
		            	if (value>-1){
					int numPropOwned = squaresOwned.size();
					int square_index=-1;
					string accept="";
					for (int i=0; i<numPropOwned; i++){
						if (squaresOwned[i]->getName()==command[2]){
							square_index=i;
							break;
						}
					}
					if (square_index==-1){
						cout << "You don't own "<< command[2] <<"." << endl;
						continue;
					}
					if (squaresOwned[square_index]->isImprovable()){
						string mono_block = squaresOwned[square_index]->getMonopolyBlock();
						bool failed=false;
						for (int i=0; i<numPropOwned; i++){
							if (squaresOwned[i]->getMonopolyBlock()==mono_block && squaresOwned[i]->getImprovementLevel()>0){
								cout << squaresOwned[i]->getName() << " has improvements." << endl;
								cout << "Cannot trade when the property, or properties in the same block, have improvements" << endl;
								failed = true;
								break;
							}
						}
						if (failed){
							continue;
						}
					}

					if (other->getMoney()<value){
						cout << command[1] << "  doesn't have enough money" << endl;
						cout<<"The other player doesn't have enough money"<<endl;
						continue;
					}
					cout << "Does " << command[1] << " accept the trade (type accept to accept)" << endl;
					getline(cin,accept);
					if (accept!="accept"){
						cout << command[1] << " has not accepted." << endl;
						continue;
					}
					transferProperty(other, squaresOwned[square_index], otherPlayers);
					other->subtractMoney(value, otherPlayers);
					addMoney(value);
				}
				else{
					int numPropOwned = squaresOwned.size();
					int square_index=-1;
					string accept="";
	 			        for (int i=0; i<numPropOwned; i++){
					  	if (squaresOwned[i]->getName()==command[2]){
						  	square_index=i;
						  	break;
				  		}
			        	}
                                	if (square_index==-1){
						cout << "You don't own "<< command[2] <<"." << endl;
						continue;
                                	}
					if (squaresOwned[square_index]->isImprovable()){
						string mono_block = squaresOwned[square_index]->getMonopolyBlock();
						bool failed=false;
						for (int i=0; i<numPropOwned; i++){
							if (squaresOwned[i]->getMonopolyBlock()==mono_block && squaresOwned[i]->getImprovementLevel()>0){
								cout << squaresOwned[i]->getName() << " has improvements." << endl;
								cout << "Cannot trade when the property, or properties in the same block, have improvements" << endl;
								failed=true;
								break;
							}
						}	
						if(failed){
							continue;
						}
					}

					vector<shared_ptr<Square>> otherSquares = other->getSquares();
					int numPropOwnedOther = otherSquares.size();
					int square_index_other=-1;
              				for (int i=0; i<numPropOwnedOther; i++){
						 if (otherSquares[i]->getName()==command[3]){
							  square_index_other=i;
							  break;
					 	}
					}
					if (square_index_other==-1){
							cout<<command[1] <<" doesn't own " << command[3] << "." <<endl;
							continue;
					}
	
					if (otherSquares[square_index_other]->isImprovable()){
						string mono_block = otherSquares[square_index_other]->getMonopolyBlock();
						bool failed=false;
						for (int i=0; i<numPropOwnedOther; i++){
							if (otherSquares[i]->getMonopolyBlock()==mono_block && otherSquares[i]->getImprovementLevel()>0){
								cout << otherSquares[i]->getName() << " has improvements." << endl;
								cout << "Cannot trade when the property, or properties in the same block, have improvements" << endl;
								failed=true;
								break;
							}
						}
						if(failed){
							continue;
						}
					}
					cout << "Does " << command[1] << " accept the trade (type accept to accept)" << endl;
					getline(cin,accept);
					if (accept!="accept"){
						cout << command[1] << " has not accepted." << endl;
						continue;
					}
					transferProperty(other, squaresOwned[square_index], otherPlayers);
					other->transferProperty(this,otherSquares[square_index_other], otherPlayers);
			
				}
			}
			else if (command[0] == "all") {
                        	int numPlayers = otherPlayers.size();
                                for (int i = 0; i < numPlayers; i++) {
                                         otherPlayers[i] -> printPlayerAssets();
                                         cout << endl;
                                }

                        }
                        cout << "Enter a valid command: " << endl;        
                }
                money -= amount;
		cout << name << " now has a balance of " << money << " after raising enough money and completing the transaction." << endl;
        }
}


void Player::addSquare(std::shared_ptr<Square> square){
	cout << square->getName() << " given to " << name << "." << endl;
	squaresOwned.insert(squaresOwned.end(), square);
}

void Player::transferMoney(Player* to, int amount, std::vector<shared_ptr<Player>> otherPlayers){
	try{
		subtractMoney(amount, otherPlayers);
		to->addMoney(amount);
		cout << amount << " transferred from " << name << " to " << to->getName() << "." << endl;
	}
	catch(const invalid_argument& ia){
			cerr << ia.what() << endl;
	}
}

void Player::transferProperty(Player* to, std::shared_ptr<Square> square, vector<shared_ptr<Player>> players){
	int found=-1;
	int size = squaresOwned.size();
	for (int i=0; i<size; i++){
		if (squaresOwned[i]==square){
			found = i;
			break;
		}
	}
	if (found==-1){
		cout << square->getName() << " not found. " << endl;
		return;
	}

	if (square->isMortgaged()){
		cout << square->getName() << " was mortgaged, so the receipient paid 10 percent upfront." << endl;
		to->subtractMoney(square->getCost()*0.1, players);
	}

	if (square->isOwnable() && !square->isImprovable()){
		if (square->isGym()){
			numOfGyms--;
			to->addGym();
		}
		else{
			numOfResidences--;
			to->addRes();
		}		
	}	
	squaresOwned.erase(squaresOwned.begin()+found);
	to->addSquare(square);
	square->setOwner(to);
	cout << square->getName() << " transferred from " << name << " to " << to->getName() << "." << endl;
}

