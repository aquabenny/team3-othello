/*
File: main.cpp
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Eyck
Description: This is the main file which takes in user input
			 and passes it to the othello class. The purpose
			 is to test the game mechanics.
*/

#include "othello.h"

/****************************************************************/
/*								MAIN						   	*/
/****************************************************************/

int main(){
	Othello o;
	string input;
	cout << "Welcome to the best Othello game eva!\n"
		 << "Enter a command.\n\n";
	while(o.endGame() == false){
		//BLACKs turn
		do{
			cout << "BLACK>";
			getline(cin, input);
		}while(!o.parse(input, BLACK));
		
		if(o.endGame() == false){
			//WHITEs turn
			do{
				cout << "WHITE>";
				getline(cin, input);
			}while(!o.parse(input, WHITE));
		}
	}
}
