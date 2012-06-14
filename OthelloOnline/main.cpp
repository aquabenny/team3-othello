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
	while(!o.endGame()){
		//BLACKs turn
		do{
			getline(cin, input);
		}while(!o.parse(input, BLACK));
		
		//WHITEs turn
		do{
			getline(cin, input);
		}while(!o.parse(input, WHITE));
	}
}
