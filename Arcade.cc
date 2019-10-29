#include "Arcade.h"
#include "Testgame.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// default constructor
Arcade::Arcade() {
	cout << "LOG: Arcade.cc: constructor called\n";
	game_selection = "no_selection";
	score = 0;
	record = "no_record";
}

// starts the Arcade Machine
void Arcade::run() {
	cout << "LOG: Arcade.cc: run() method called\n";

	selectGame(); // get game
	
	score = executeGame(); // run game and get score

	record = createRecord(); // create and store record

	bool worked = sendRecord(); // send record to database
	
	if (worked == false) { // send error message if it didn't work
		cout << "ERROR: Record couldn't send!\n";
	}
}

// present options to user and get selection
void Arcade::selectGame() {
	clog << "LOG: Arcade.cc: selectGame() method called\n";
	clog << "Welcome to the Arcade Machine!\nOptions:\n1) Testgame\n2) Quit\n";
	int choice;
	cout << "Choice => ";
	cin >> choice;
	if (choice == 1) {
		clog << "'" << choice << "' selected.\n";
		game_selection = "Testgame";
		
	}
	else if (choice == 2) {
		cout << "'" << choice << "' selected. Exiting!\n";
		exit(1);
	}
	else {
		cerr << "Error! '" << choice << "' wasn't an option! Please try again.\n";
		exit(2);
	}
}

// loads instance of selected game type
int Arcade::executeGame() {
	clog << "LOG: Arcade.cc: executeGame() method called\n";

	int temp = 0;

	if (game_selection == "Testgame") { // OPTION ONE -> 'Testgame' replaceable
		Testgame Game;
		temp = Game.run();
	}
	else if (game_selection == "no_selection") { // this shouldn't run
		cerr << "ERROR: No selection made! Exiting!\n";
		exit(3);
	}
	// MORE OPTIONS LATER

	return temp;
}

// creates record of gameplay in preparation to send
string Arcade::createRecord() {
	clog << "LOG: Arcade.cc: createRecord() method called\n";
	stringstream ss;
	ss << "Game selected: '" << game_selection << "'\n"
	   << "Score: '" << score << "'";
	return ss.str();
}

// sends record to database on another computer
bool Arcade::sendRecord() {
	clog << "LOG: Arcade.cc: sendRecord() method called\n";

	ofstream fss;
	fss.open("record.txt");
	fss << record;

	fss.close();	

	system("scp ./record.txt dmstephe@albany.cs.colostate.edu:/s/bach/l/under/dmstephe/CS370/group/SERVER"); // need to make this send without a password required, maybe change where it's going?

	return true; // when would there be a fail condition?
}

/* 

GOALS

[ ] replace testgame with an actual game
[ ] improve creation of record
[ ] allow sending of record without a password
[ ] edit selectGame to use the Communicator class instead of Cin to get input
[ ] create visuals for the game OR comment out log files and use console (QUESTION: Would the Communicator class still work if we used the console? I think so.)

*/
