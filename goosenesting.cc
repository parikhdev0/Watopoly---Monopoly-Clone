#include "goosenesting.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


GooseNesting::GooseNesting(Board * board,string name, int position) : Square{board, name, "", position, 0, nullptr, 0, false, false} {}

void GooseNesting::action(Player * player){
	
	ifstream board_text("goose.txt");
	vector<vector<char>> goose;
	string line;
	while (getline(board_text, line)){
		int string_size = line.length();
		for (int i=0; i<string_size; i++){
			cout << line[i];
		}
		cout << endl;
	}
	cout << "A flock geese is attacking. Take cover!" << endl;
}

