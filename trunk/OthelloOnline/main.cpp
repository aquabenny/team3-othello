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
	AI ai1, ai2;
	string input;
	int rc = 0;
	cout << "Welcome to the best Othello game eva!\n";
	
	//ai1
	ai1.setPlayerColor(BLACK);
	ai1.setDifficulty(MEDIUM);
	
	//ai2
	ai2.setPlayerColor(WHITE);
	ai2.setDifficulty(HARD);
		 
	//set difficulty
	/*
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
			ai2.setPlayerColor(BLACK);
			goAgain = false;
		}
		else if(colorInput == "WHITE"){
			ai.setPlayerColor(BLACK);
			ai2.setPlayerColor(WHITE);
			goAgain = false;
		}
		else{
			cout << "Invalid color.\n";
			goAgain = true;
		}
	}while(goAgain);
	*/
	
	//play
	while(rc != 2){
		//BLACKs turn
		do{
			if(ai1.getColor() == BLACK){
				cout << "\nBLACK>";
				rc = o.parse(ai1.go(o), BLACK);
			}
			else{
				cout << "\nBLACK>";
				//getline(cin, input);
				rc = o.parse(ai2.go(o), BLACK);
			}
		}while(rc == 0);
		
		if(rc != 2){
			//WHITEs turn
			do{
				if(ai1.getColor() == WHITE){
					cout << "\nWHITE>";
					rc = o.parse(ai1.go(o), WHITE);
				}
				else{
					cout << "\nWHITE>";
					//getline(cin, input);
					rc = o.parse(ai2.go(o), WHITE);
				}
			}while(rc == 0);
		}
	}
}
