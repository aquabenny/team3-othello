/*
File: ai.h
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Eyck
Description: This is the AI class. It can take in a state and
				output a string for its next move.
*/

#include "othello.h"

class AI{
	int difficulty;
	void setDifficulty(int diff);
	char playerColor;
	void setPlayerColor(char color);
	
public:

	AI();
	string go(Othello &o);
	char getColor();
};

AI::AI(){
	difficulty = EASY;
	playerColor = WHITE;
}

void AI::setDifficulty(int diff){
	if(d == EASY || d == MEDIUM || d == HARD){
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
	}
	else if(difficulty == MEDIUM){
	
	}
	else if(difficulty == HARD){
	
	}
	else{
		error("go: Difficulty not valid\n");
	}
}

char AI::getColor(){
	return playerColor;
}
