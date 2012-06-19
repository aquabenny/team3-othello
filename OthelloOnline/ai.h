/*
File: ai.h
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Ten Eyck
Description: This is the AI class. It can take in a state and
				output a string for its next move.
*/

#include "othello.h"

class AI{
	int difficulty;
	char playerColor;
	char state[COLUMNS][ROWS];
	void copyCurrState(Othello &o);
	
public:

	AI();
	string go(Othello &o);
	char getColor();
	void setDifficulty(int diff);
	void setPlayerColor(char color);
};

AI::AI(){
	difficulty = EASY;
	playerColor = WHITE;
}

void AI::setDifficulty(int diff){
	if(diff == EASY || diff == MEDIUM || diff == HARD){
		difficulty = diff;
	}
	else{
		error("setDifficulty: Difficulty invalid\n");
	}
}

void AI::setPlayerColor(char color){
	if(color == BLACK || color == WHITE){
		playerColor = color;
	}
	else{
		error("setPlayerColor: Invalid color\n");
	}
}

string AI::go(Othello &o){
	if(difficulty == EASY){
		//do a random move
		int moveNum = 0;
		int randomNum = rand()%(o.getNumMoves(playerColor));
		copyCurrState(o);
		
		//check if it is a valid move
		//check if valid move
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				if(playerColor == WHITE){
					if(state[i][j] == POSSIBLE_WHITE_MOVE
						 || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						if(moveNum == randomNum){
							//do this move
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							cout << ss.str() << endl;
							return ss.str();
						}
						else{
							//don't do this move
							moveNum++;
						}
					}
				}
				if(playerColor == BLACK){
					if(state[i][j] == POSSIBLE_BLACK_MOVE
						 || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						if(moveNum == randomNum){
							//do this move
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							cout << ss.str() << endl;
							return ss.str();
						}
						else{
							//don't do this move
							moveNum++;
						}
					}
				}	
			}
		}
	}
	else if(difficulty == MEDIUM){
		//not supported yet
		error("YOU BROKE IT!!!\n");
	}
	else if(difficulty == HARD){
		//not supported yet
		error("YOU BROKE IT!!!\n");
	}
	else{
		error("go: Difficulty not valid\n");
	}
}

char AI::getColor(){
	return playerColor;
}

void AI::copyCurrState(Othello &o){
	o.copyCurrState(state);
}
