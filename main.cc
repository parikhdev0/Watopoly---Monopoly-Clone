#include <iostream>
#include <stdexcept>
#include <memory>
#include "board.h"
using namespace std;

int main(int argc, char* argv[]){
	cout << "Welcome to Watopoly" << endl;	
	Board game{};
	string load_file = "";
	bool testing = false;
	for (int i=0; i < argc; i++){
		string command = argv[i];
		if (command=="-testing"){
			testing=true;
		}
		else if (command=="-load"){
			if ((i+1)<argc){
				load_file = argv[i+1];
			}
		}
	}

	if (testing){
		cout << "You have started Watopoly in Testing Mode." << endl;
		game.setTesting();
	}
	bool error=false;
	if (load_file!=""){
		try{
			cout << "You have loaded the file: " << load_file << endl;
			game.loadGame(load_file);
			cout << "Successfully loaded the file: " << load_file << endl;
		}
		catch(const std::invalid_argument& ia){
			error = true;
			cerr << ia.what() << endl;
			cout << "Error with loading, play will now resume normally" << endl;
		}
	}
	if (load_file!=""&&!error){
		game.play();
	}
	else{
		cout << "How many players will be playing today?" << endl;
		int count_players = 0;
		string num = "";
		while(true){
			cin>>num;
			try{
				stoi(num);
				count_players = stoi(num);
			}
			catch(const invalid_argument& ia){
				cout << "Enter a number." << endl;
				continue;
			}
			if (count_players<2 || count_players>8){
				cout << "This is an invalid number of players. Their must be 2-8 players playing." << endl;
				continue;
			}
			break;
		}
		game.initialize(count_players);
		game.play();
	}

	return 0;
}

