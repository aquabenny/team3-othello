/*
File: main.cpp
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Ten Eyck
Description: This is the main file which takes in user input
			 and passes it to the othello class. The purpose
			 is to test the game mechanics.
*/

#include "ai.h"

/****************************************************************/
/*								MAIN						   	*/
/****************************************************************/

int main(){
	Othello o;
	AI ai;
	string input;
	int rc = 0;
	cout << "Welcome to the best Othello game eva!\n";
		 
	//set difficulty
	bool goAgain = false;
	do{
		cout << "\nEnter a difficulty\n>";
		string diffInput;
		getline(cin, diffInput);
		if(diffInput == "EASY"){
			ai.setDifficulty(EASY);
			goAgain = false;
		}
		else if(diffInput == "MEDIUM"){
			ai.setDifficulty(MEDIUM);
			goAgain = false;
		}
		else if(diffInput == "HARD"){
			ai.setDifficulty(HARD);
			goAgain = false;
		}
		else{
			cout << "Invalid difficulty.\n";
			goAgain = true;
		}
	}while(goAgain);
	
	//set color
	do{
		cout << "\nEnter your color\n>";
		string colorInput;
		getline(cin, colorInput);
		if(colorInput == "BLACK"){
			ai.setPlayerColor(WHITE);
			goAgain = false;
		}
		else if(colorInput == "WHITE"){
			ai.setPlayerColor(BLACK);
			goAgain = false;
		}
		else{
			cout << "Invalid difficulty.\n";
			goAgain = true;
		}
	}while(goAgain);
	
	//play
	while(rc != 2){
		//BLACKs turn
		do{
			if(ai.getColor() == BLACK){
				cout << "\nBLACK>";
				rc = o.parse(ai.go(o), BLACK);
			}
			else{
				cout << "\nBLACK>";
				getline(cin, input);
				rc = o.parse(input, BLACK);
			}
		}while(rc == 0);
		
		if(rc != 2){
			//WHITEs turn
			do{
				if(ai.getColor() == WHITE){
					cout << "\nWHITE>";
					rc = o.parse(ai.go(o), WHITE);
				}
				else{
					cout << "\nWHITE>";
					getline(cin, input);
					rc = o.parse(input, WHITE);
				}
			}while(rc == 0);
		}
	}
}
