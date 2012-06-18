/*
File: main.cpp
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Eyck
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
	string input;
	int rc = 0;
	cout << "Welcome to the best Othello game eva!\n"
		 << "Enter a command\n";
		 
	while(rc != 2){
		//BLACKs turn
		do{
			cout << "\nBLACK>";
			getline(cin, input);
			rc = o.parse(input, BLACK);
		}while(rc == 0);
		
		if(rc != 2){
			//WHITEs turn
			do{
				cout << "\nWHITE>";
				getline(cin, input);
				rc = o.parse(input, WHITE);
			}while(rc == 0);
		}
	}
}
