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
#define POSSIBLE_BLACK_OR_WHITE_MOVE 4	//this is for a space where black or white can move
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
	int opposingPlayer(int player);		//returns the opposing player's color (BLACK or WHITE)
	void copyState(int state1[COLUMNS][ROWS], int state2[COLUMNS][ROWS]);		//copies state1 to state2
	int numPieces(int state[COLUMNS][ROWS], int player);		//returns the number of pieces a player has on a given state
	int score(int state[COLUMNS][ROWS], int player); 		//returns a player's score given a state
	int value(int state[COLUMNS][ROWS], int player);		//only used in the AI version
	int numMoves(int state[COLUMNS][ROWS], int player);		//returns the number of possible moves a player can make
	void print(int state[COLUMNS][ROWS]);		//prints the board
	void print(int state[COLUMNS][ROWS], int player);		//prints the board with possible moves for the given player
	int undo();		//updates currState and prevState by undoing last move
	int redo();		//updates currState and prevState by redoing last move
	int move(int state[COLUMNS][ROWS], int column, int row, int player);		//updates currState and prevState. Returns 0 if successful. Returns 1 if invalid move.
	
	
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
	bool endGame(int state[COLUMNS][ROWS]);		//checks if the game is over
	
/*
This function takes in a player's command, move, or comment
and handles it accordingly. It returns true if it should be
the next player's turn.
*/

	bool parse(string input, int player);	
};

/*******************************PRIVATE FUNCTIONS**************************/

//returns the opposing player's color (BLACK or WHITE)
int Othello::opposingPlayer(int player){
	if(player == WHITE){
		return BLACK;
	}
	else if(player == BLACK){
		return WHITE;
	}
	else{
		error("opposingPlayer: Invalid color.");
	}
}

//copies state1 to state2
void Othello::copyState(int state1[COLUMNS][ROWS], int state2[COLUMNS][ROWS]){
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			state2[i][j] = state1[i][j];
		}
	}
}

//returns the number of pieces a player has on a given state
int Othello::numPieces(int state[COLUMNS][ROWS], int player){

}

//returns a player's score given a state
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

//only used in the AI version
int Othello::value(int state[COLUMNS][ROWS], int player){
	cout << "This function not supported in this version.\n";
	return 0;
}

//returns the number of possible moves a player can make
int Othello::numMoves(int state[COLUMNS][ROWS], int player){

}

//Displays the board in current state
void Othello::print(int state[COLUMNS][ROWS]){

	//We want to loop through the state arrays to check for pieces
	//first print top row
	cout << "  |__a__|__b__|__c__|__d__|__e__|__f__|__g__|__h__|" << endl;
	
	for(int i=0; i<=ROWS; i++){
		cout << i + "|"; //start with row number (ex: 0| )
		for(int j=0; j<=COLUMNS; j++){
			char piece = ' ';
			if(state[j][i] == BLACK){
				piece = '@';
			}
			else if(state[j][i] == WHITE){
				piece = 'O';
			}
			else
				piece = ' ';
			cout << "  " << piece << "  |";
		}
		cout << endl;
	}
}

//prints the board with possible moves
void Othello::print(int state[COLUMNS][ROWS], int player){
	//first row
	cout << "  |__a__|__b__|__c__|__d__|__e__|__f__|__g__|__h__|" << endl;
	if(player == BLACK){
		for(int i=0; i<=ROWS; i++){
		cout << i + "|";
			for(int j=0; j<=COLUMNS; j++){
				char piece = ' '; //default as a space (no pieces present)
				if(state[j][i] == BLACK){
					piece = '@';
				}
				else if(state[j][i] == WHITE){
					piece = 'O';
				}
				else if(state[j][i] == POSSIBLE_BLACK_MOVE){//mark a square as a potential move
					piece = 'X';
				}
				else if(state[j][i] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					piece = 'X';
				}
				else
					piece = ' ';
				cout << "  " << piece << "  |";
			}
		cout << endl;
		}	
	}
	else if(player == WHITE){	
		for(int i=0; i<=ROWS; i++){
		cout << i + "|";
			for(int j=0; j<=COLUMNS; j++){
				char piece = ' ';
				if(state[j][i] == BLACK){
					piece = '@';
				}
				else if(state[j][i] == WHITE){
					piece = 'O';
				}
				else if(state[j][i] == POSSIBLE_WHITE_MOVE){//mark a square as a potential move
					piece = 'X';
				}
				else if(state[j][i] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					piece = 'X';
				}
				else
					piece = ' ';
				cout << "  " << piece << "  |";
			}
		cout << endl;
		}
	}
	else 
		error("print: invalid player passed");
}

//updates currState and prevState by undoing last move
int Othello::undo(){

}

//updates currState and prevState by redoing last move
int Othello::redo(){

}

//updates currState and prevState. Returns 0 if successful. Returns 1 if invalid move.
int Othello::move(int state[COLUMNS][ROWS], int column, int row, int player){
	//check for valid player
	if(player != WHITE && player != BLACK){
		error("move: Invalid player.");
	}
	
	//check column and row bounds
	if(column >= COLUMNS || column < 0 ||  row >= ROWS || row < 0){
		error("evalSpace: Column or row range error.");
	}
	
	//check if valid move
	if(player == WHITE){
		if(state[column][row] != POSSIBLE_WHITE_MOVE
			 && state[column][row] != POSSIBLE_BLACK_OR_WHITE_MOVE){
			cout << "Invalid move. Type \"SHOW_NEXT_POS\" to see possible moves.\n";
			return 1;
		}
	}
	if(player == BLACK){
		if(state[column][row] != POSSIBLE_BLACK_MOVE
			 && state[column][row] != POSSIBLE_BLACK_OR_WHITE_MOVE){
			cout << "Invalid move. Type \"SHOW_NEXT_POS\" to see possible moves.\n";
			return 1;
		}
	}
	
	//check each direction and flip oposing pieces
	int tempColumn;		//the next column to look at
	int tempRow;		//the next row to look at
	//left
	if(player == left(state, column, row)){
		tempColumn = column - 1;
		tempRow = row;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			tempColumn--;
			//tempRow does not change
		}
	}
	
	//left up
	if(player == leftUp(state, column, row)){
		tempColumn = column - 1;
		tempRow = row + 1;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			tempColumn--;
			tempRow--;
		}
	}
	
	//up
	if(player == up(state, column, row)){
		tempColumn = column;
		tempRow = row + 1;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			//tempColumn does not change
			tempRow--;
		}
	}
	
	//right up
	if(player == rightUp(state, column, row)){
		tempColumn = column + 1;
		tempRow = row + 1;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			tempColumn++;
			tempRow--;
		}
	}
	
	//right
	if(player == right(state, column, row)){
		tempColumn = column + 1;
		tempRow = row;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			tempColumn++;
			//tempRow does not change
		}
	}
	
	//right down
	if(player == rightDown(state, column, row)){
		tempColumn = column + 1;
		tempRow = row - 1;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			tempColumn++;
			tempRow++;
		}
	}
	
	//down
	if(player == down(state, column, row)){
		tempColumn = column;
		tempRow = row - 1;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			//tempColumn does not change
			tempRow++;
		}
	}
	
	//left down
	if(player == leftDown(state, column, row)){
		tempColumn = column - 1;
		tempRow = row - 1;
		while(state[tempColumn][tempRow] != player){
			state[tempColumn][tempRow] = opposingPlayer(player);
			tempColumn--;
			tempRow++;
		}
	}
	
	/*
	Now we need to re eavluate all of the pieces on the board
	to determine if they have a piece, are a valid move for
	each player, or is simply empty.
	*/
	
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			state[i][j] = evalSpace(state, i, j);
		}
	}
	
	//success
	return 0;
}

/*************************HELPER FUNCTIONS**********************************/

/*
These functions check an empty space's direction. It returns EMPTY if
no pieces will be flipped in that direction, BLACK if white pieces could
be flipped in that direction, or WHITE if black pieces could be flipped
in that direction.
*/

/*
Each of these functions compares its next space with the current space
while the next space is not off the board. If the next space is the
opposite color of the current space, then it returns the next space.
If the next space is not a black or white piece, then it returns EMPTY,
meaning nothing would happen in that direction, regardless of which player
made the move.
*/

int Othello::left(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(column > a){
		currSpace = state[column][row];
		nextSpace = state[column-1][row];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			column--;	//go to left space
		}
	}
	return EMPTY;
}

int Othello::leftUp(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(column > a && row > 0){
		currSpace = state[column][row];
		nextSpace = state[column-1][row-1];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			column--;	//go to left, upper space
			row--;
		}
	}
	return EMPTY;
}

int Othello::up(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(row > 0){
		currSpace = state[column][row];
		nextSpace = state[column][row-1];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			row--;	//go to the space above
		}
	}
	return EMPTY;
}

int Othello::rightUp(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(column < h && row > 0){
		currSpace = state[column][row];
		nextSpace = state[column+1][row-1];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			column++;	//go to right, upper space
			row--;
		}
	}
	return EMPTY;
}

int Othello::right(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(column < h){
		currSpace = state[column][row];
		nextSpace = state[column+1][row];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			column++;	//go to right space
		}
	}
	return EMPTY;
}

int Othello::rightDown(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(column < h && row < 7){
		currSpace = state[column][row];
		nextSpace = state[column+1][row+1];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			column++;	//go to right, lower space
			row++;
		}
	}
	return EMPTY;
}

int Othello::down(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(row < 7){
		currSpace = state[column][row];
		nextSpace = state[column][row+1];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			row++;	//go to the space below
		}
	}
	return EMPTY;
}

int Othello::leftDown(int state[COLUMNS][ROWS], int column, int row){
	int nextSpace, currSpace;
	while(column > a && row < 7){
		currSpace = state[column][row];
		nextSpace = state[column-1][row+1];
		if(nextSpace != BLACK && nextSpace != WHITE){
			return EMPTY;
		}
		else if(opposingPlayer(nextSpace) == currSpace){
			return nextSpace;
		}
		else{
			column--;	//go to left, lower space
			row++;
		}
	}
	return EMPTY;
}
	
/*
This function calls the above functions (checking all of the directions)
to determine if the spot should be EMPTY, BLACK, WHITE, POSSIBLE_BLACK_MOVE,
POSSIBLE_WHITE_MOVE, or POSSIBLE_BLACK_OR_WHITE_MOVE.
*/
	
int Othello::evalSpace(int state[COLUMNS][ROWS], int column, int row){
	//check column and row bounds
	if(column >= COLUMNS || column < 0 ||  row >= ROWS || row < 0){
		error("evalSpace: Column or row range error.");
	}
	
	//check if there is already a piece in that spot
	if(state[column][row] == WHITE){
		return WHITE;
	}
	if(state[column][row] == BLACK){
		return BLACK;
	}
	
	//keep count of white and black move possibilities
	int whiteCount = 0;
	int blackCount = 0;
	
	//return code for direction
	int rc = EMPTY;
	
	//check each direction for each color
	//left
	rc = left(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//left up
	rc = leftUp(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//up
	rc = up(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//right up
	rc = rightUp(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//right
	rc = right(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//right down
	rc = rightDown(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//down
	rc = down(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//left down
	rc = leftDown(state, column, row);
	if(rc == WHITE){
		whiteCount++;
	}
	else if(rc == BLACK){
		blackCount++;
	}
	
	//return new space value
	if(whiteCount > 0 && blackCount > 0){
		return POSSIBLE_BLACK_OR_WHITE_MOVE;
	}
	else if(whiteCount > 0){
		return POSSIBLE_WHITE_MOVE;
	}
	else if(blackCount > 0){
		return POSSIBLE_BLACK_MOVE;
	}
	else{
		return EMPTY;
	}
}

/***************************CONSTRUCTOR*****************************/

Othello::Othello(){
	//set initial state
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			currState[i][j] = EMPTY;
		}
	}
	currState[d][5] = BLACK;
	currState[e][4] = BLACK;
	currState[d][4] = WHITE;
	currState[e][5] = WHITE;

	//compute possible moves
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			currState[i][j] = evalSpace(currState, i, j);
		}
	}
	
	copyState(currState, prevState);
	display = OFF;
}

/*************************PUBLIC FUNCTIONS**************************/

//checks if the game is over
bool Othello::endGame(int state[COLUMNS][ROWS]){

}

/*
This function takes in a player's command, move, or comment
and handles it accordingly. It returns true if it should be
the next player's turn.
*/

bool Othello::parse(string input, int player){

}
