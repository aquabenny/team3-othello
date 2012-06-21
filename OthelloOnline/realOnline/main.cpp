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
	ParseReturn pr;
	pr.str = "";
	pr.val = 0;
	cout << "Welcome to the best Othello game eva!\n";
	
	/*
	//AI play each other
	//ai1
	ai1.setPlayerColor(BLACK);
	ai1.setDifficulty(EASY);
	
	//ai2
	ai2.setPlayerColor(WHITE);
	ai2.setDifficulty(MEDIUM);
	
	//play
	cout << o.print(BLACK);
	while(pr.val != 2){
		//BLACKs turn
		do{
			if(ai1.getColor() == BLACK){
				cout << "\nBLACK>";
				pr = o.parse(ai1.go(o), BLACK);
				cout << pr.str;
			}
			else{
				cout << "\nBLACK>";
				pr = o.parse(ai2.go(o), BLACK);
				cout << pr.str;
			}
		}while(pr.val == 0);
		
		if(pr.val != 2){
			//WHITEs turn
			do{
				if(ai1.getColor() == WHITE){
					cout << "\nWHITE>";
					pr = o.parse(ai1.go(o), WHITE);
					cout << pr.str;
				}
				else{
					cout << "\nWHITE>";
					pr = o.parse(ai2.go(o), WHITE);
					cout << pr.str;
				}
			}while(pr.val == 0);
		}
	}
	*/
	
	
	//You play AI
	//set difficulty
	bool goAgain = false;
	do{
		cout << "\nEnter a difficulty\n>";
		string diffInput;
		getline(cin, diffInput);
		if(diffInput == "EASY"){
			ai1.setDifficulty(EASY);
			goAgain = false;
		}
		else if(diffInput == "MEDIUM"){
			ai1.setDifficulty(MEDIUM);
			goAgain = false;
		}
		else if(diffInput == "HARD"){
			ai1.setDifficulty(HARD);
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
			ai1.setPlayerColor(WHITE);
			goAgain = false;
		}
		else if(colorInput == "WHITE"){
			ai1.setPlayerColor(BLACK);
			goAgain = false;
		}
		else{
			cout << "Invalid color.\n";
			goAgain = true;
		}
	}while(goAgain);
	
	//play
	cout << o.print(BLACK);
	while(pr.val != 2){
		//BLACKs turn
		do{
			if(ai1.getColor() == BLACK){
				cout << "\nBLACK>";
				pr = o.parse(ai1.go(o), BLACK);
				cout << pr.str;
			}
			else{
				cout << "\nBLACK>";
				getline(cin, input);
				pr = o.parse(input, BLACK);
				cout << pr.str;
			}
		}while(pr.val == 0);
		
		if(pr.val != 2){
			//WHITEs turn
			do{
				if(ai1.getColor() == WHITE){
					cout << "\nWHITE>";
					pr = o.parse(ai1.go(o), WHITE);
					cout << pr.str;
				}
				else{
					cout << "\nWHITE>";
					getline(cin, input);
					pr = o.parse(input, WHITE);
					cout << pr.str;
				}
			}while(pr.val == 0);
		}
	}
}
