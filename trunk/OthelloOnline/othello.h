/*
File: othello.h
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Eyck
Description: This is the Othello class. It consists of a state and
			 takes an input string to execute on using the parse()
			 function.
*/

//includes
#include "std_lib_facilities.h"

//global definitions
#define COLUMNS 8
#define ROWS 8
#define OFF 0
#define ON 1
#define EMPTY -1
#define BLACK 0
#define WHITE 1
#define POSSIBLE_BLACK_MOVE 2
#define POSSIBLE_WHITE_MOVE 3
#define POSSIBLE_BLACK_OR_WHITE_MOVE 4
#define a 0
#define b 1
#define c 2
#define d 3
#define e 4
#define f 5
#define g 6
#define h 7

/****************************************************************/
/*							OTHELLO CLASS					   	*/
/****************************************************************/

class Othello{
	//private members
	int currState[COLUMNS][ROWS];
	int prevState[COLUMNS][ROWS];
	bool display;		//user can turn display OFF or ON
	
	//private functions
	int numPieces(int state[COLUMNS][ROWS], int player);
	int score(int state[COLUMNS][ROWS], int player); 
	int value(int state[COLUMNS][ROWS], int player);		//only used in the AI version
	int numMoves(int state[COLUMNS][ROWS], int player);
	void print(int state[COLUMNS][ROWS]);
	void print(int state[COLUMNS][ROWS], int player);		//when player argument is included, it also prints the possible moves
	int *undo();
	int *redo();
	int *move(int state[COLUMNS][ROWS], int column, int row, int player);		//returns a game state
	
	
	/*
	These functions check an empty space's direction. It returns EMPTY if
	no pieces will be flipped in that direction, BLACK if white pieces could
	be flipped in that direction, or WHITE if black pieces could be flipped
	in that direction.
	*/
	
	int left(int state[COLUMNS][ROWS], int column, int row);
	int leftUp(int state[COLUMNS][ROWS], int column, int row);
	int up(int state[COLUMNS][ROWS], int column, int row);
	int rightUp(int state[COLUMNS][ROWS], int column, int row);
	int right(int state[COLUMNS][ROWS], int column, int row);
	int rightDown(int state[COLUMNS][ROWS], int column, int row);
	int down(int state[COLUMNS][ROWS], int column, int row);
	int leftDown(int state[COLUMNS][ROWS], int column, int row);
	
	/*
	This function calls the above functions (checking all of the directions)
	to determine if the spot should be EMPTY, BLACK, WHITE, POSSIBLE_BLACK_MOVE,
	POSSIBLE_WHITE_MOVE, or POSSIBLE_BLACK_OR_WHITE_MOVE.
	*/
	
	int evalSpace(int state[COLUMNS][ROWS], int column, int row);
	
public:
	//constructor
	Othello();

	//public functions
	bool endGame(int state[COLUMNS][ROWS]);
	bool parse(string input, int player);		//returns true only if it should be the next player's turn
};

/*******************************PRIVATE FUNCTIONS**************************/

int Othello::numPieces(int state[COLUMNS][ROWS], int player){

}

int Othello::score(int state[COLUMNS][ROWS], int player){
	if(player == WHITE){
		return numPieces(state, WHITE) - numPieces(state, BLACK);
	}
	else if(player == BLACK){
		return numPieces(state, BLACK) - numPieces(state, WHITE);
	}
	else{
		error("score: Invalid player.");
	}
}

int Othello::value(int state[COLUMNS][ROWS], int player){
	//only used in the AI version
}

int Othello::numMoves(int state[COLUMNS][ROWS], int player){

}

void Othello::print(int state[COLUMNS][ROWS]){

}

//when player argument is included, it also prints the possible moves
void Othello::print(int state[COLUMNS][ROWS], int player){

}

int *Othello::undo(){

}

int *Othello::redo(){

}

//returns a game state
int *Othello::move(int state[COLUMNS][ROWS], int column, int row, int player){

}

/*************************HELPER FUNCTIONS**********************************/

/*
These functions check an empty space's direction. It returns EMPTY if
no pieces will be flipped in that direction, BLACK if white pieces could
be flipped in that direction, or WHITE if black pieces could be flipped
in that direction.
*/
	
int Othello::left(int state[COLUMNS][ROWS], int column, int row){

}

int Othello::leftUp(int state[COLUMNS][ROWS], int column, int row){

}

int Othello::up(int state[COLUMNS][ROWS], int column, int row){

}

int Othello::rightUp(int state[COLUMNS][ROWS], int column, int row){

}

int Othello::right(int state[COLUMNS][ROWS], int column, int row){

}

int Othello::rightDown(int state[COLUMNS][ROWS], int column, int row){

}

int Othello::down(int state[COLUMNS][ROWS], int column, int row){

}

int Othello::leftDown(int state[COLUMNS][ROWS], int column, int row){

}
	
/*
This function calls the above functions (checking all of the directions)
to determine if the spot should be EMPTY, BLACK, WHITE, POSSIBLE_BLACK_MOVE,
POSSIBLE_WHITE_MOVE, or POSSIBLE_BLACK_OR_WHITE_MOVE.
*/
	
int Othello::evalSpace(int state[COLUMNS][ROWS], int column, int row){

}


/***************************CONSTRUCTOR*****************************/

Othello::Othello(){

}

/*************************PUBLIC FUNCTIONS**************************/

bool Othello::endGame(int state[COLUMNS][ROWS]){

}

//returns true only if it should be the next player's turn
bool Othello::parse(string input, int player){

}
