#include "dcTimsLine.h"
using namespace std;


DCTimsLine::DCTimsLine(Board * board,string name, int position) : Square{board, name, "", position, 0, nullptr, 0, false, false} {}

void DCTimsLine::action(Player* player){
	cout << "You are in jail." << endl;
	bool pay=true;
	bool last=false;
	while(true){
		if (player->getJailTurns()==2){
			cout << "Enter 'pay' or 'up' to leave, this is your last term." << endl;
			last=true;
		}
		else{
			cout << "Enter 'roll' to roll the die, 'pay' to pay the jail fee, or 'up' to use your Roll Up card" << endl;
		}
		string playTurn;
		cin >> playTurn;
	
		if(playTurn == "roll"){
			if (player->getJailTurns()==2){
				cout << "This is not a valid option, please select pay or up. " << endl;
				continue;
			}
			rollDice(player);
			break;
		}
		else if(playTurn == "pay"){
			
			if(pay&& (!(player->getJailTurns()==2)) && player->getMoney()<jailFee){
				cout << "Warning: You don't have the money to pay" << endl;
				cout << "Type in pay again to continue, or choose something else." << endl;
				pay=false;
				continue;
			}
			payJailFee(player);
			break;
		}
		else if(playTurn == "up"){
			if(player->getTimCups() > 0){
				useRollUp(player);
				break;
			}
			else{
				cout << "Please pick another option as you do not own a Roll Up card!" << endl;
			}
		}
		else{
			cout << "Invalid option. Please choose one of the options given." << endl;
		}		
	}
	if(last){
		rollDice(player);
	}
}

void DCTimsLine::rollDice(Player* player){
	bool release=false;
	if(player->getJailTurns() == 2 || player->getJailTurns()==-1){
		release=true;
	}
	else if (!release){
		vector<int> dice;
		int die1=-1;
		int die2=-1;
		if (!getBoard()->isInTestMode()){
			dice = getBoard()->rollDice(-1,-1);
			die1=dice[0];
			die2=dice[1];
		}
		else{
			cout << "You are in test mode, enter <die1> <die2> to roll dice, or anything else to roll normally." << endl;
			string temp;
			try{
				cin>>temp;
				die1=stoi(temp);
				cin>>temp;
				die2=stoi(temp);
			}
			catch(invalid_argument& e){
			}
			
			if (die1==-1 || die2==-1){
				dice = getBoard()->rollDice(-1,-1);
				die1=dice[0];
				die2=dice[1];
			}
		}

		cout << "You rolled " << die1 << " & " << die2 << "." << endl;
		dice.clear();
		dice.push_back(die1);
		dice.push_back(die2);
		player->setJailLastRoll(dice);
		if(die1 == die2){
			release=true;
		}
		else{
			player->setJailTurns(player->getJailTurns()+1);
		}	
	}
	if(release && !player->isBankrupt()){
			
			player->setJail(false);
			player->setJailTurns(-1);
			vector<int> releaseRoll = player->getJailLastRoll();
			if (releaseRoll.size()<2){
				cout << "You got out, but their is no last roll stored on record due to a loaded game." << endl;
				cout << "Roll next turn." << endl;
				return;
			}
			int dice1 = releaseRoll[0];
			int dice2 = releaseRoll[1];
			player->move(dice1 + dice2);
			while(player->getPosition()>=40){
				player->move(-40);
			}
			cout << "Rolled " << dice1 << " and " << dice2 << "." << endl;
			cout << "Landed on " << getBoard()->getSquares()[player->getPosition()]->getName() << endl;
	}
}

void DCTimsLine::payJailFee(Player* player){
	player->subtractMoney(jailFee, getBoard()->getPlayers());
	if(!player->isBankrupt()){
		player->setJail(false);
		player->setJailTurns(-1);
	}
	else{
		if(getBoard()->getPlayers().size()<3){
			cout << "Game has ended" << endl;
		}
		else{
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

void DCTimsLine::useRollUp(Player* player){
	player->useTimCup();
	getBoard()->setRollUpCards(getBoard()->getRollUpCards()-1);
	player->setJail(false);
	player->setJailTurns(-1);
}


