/*
File: othello.h
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Ten Eyck
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
#define EMPTY 'a'
#define BLACK 'b'
#define WHITE 'c'
#define POSSIBLE_BLACK_MOVE 'd'
#define POSSIBLE_WHITE_MOVE 'e'
#define POSSIBLE_BLACK_OR_WHITE_MOVE 'f'	//this is for a space where black or white can move
#define a 0
#define b 1
#define c 2
#define d 3
#define e 4
#define f 5
#define g 6
#define h 7
#define MAX_STATES 64
#define EASY 0
#define MEDIUM 1
#define HARD 2
#define INFINITY 9999999

//return type for the parse function
struct ParseReturn{
	string str;
	int val;
};

/****************************************************************/
/*							OTHELLO CLASS					   	*/
/****************************************************************/

class Othello{
	//private members
	char states[MAX_STATES][COLUMNS][ROWS];										//keeps track of all the states
	bool display;																//user can turn display OFF or ON
	int numStates;																//the number of states in the states array
	int currState;																//index of states pointing to the current state
	
	//private functions
	char opposingPlayer(char player);											//returns the opposing player's color (BLACK or WHITE)
	int numPieces(char state[COLUMNS][ROWS], char player);						//returns the number of pieces a player has on a given state
	int score(char state[COLUMNS][ROWS], char player); 							//returns a player's score given a state
	int numMoves(char state[COLUMNS][ROWS], char player);						//returns the number of possible moves a player can make
	int undo();																	//updates states[currState] and prevState by undoing last move
	int redo();																	//updates states[currState] and prevState by redoing last move
	int move(int column, int row, char player);									//updates states[currState] and prevState. Returns 0 if successful. Returns 1 if invalid move.
	bool isColumn(char test);													//used to determine if char is a column
	bool isRow(char test);														//used to determine if char is a row
	
	/*
	These functions check an empty space's direction. It returns EMPTY if
	no pieces will be flipped in that direction, BLACK if white pieces could
	be flipped in that direction, or WHITE if black pieces could be flipped
	in that direction.
	*/
	
	char left(char state[COLUMNS][ROWS], int column, int row);
	char leftUp(char state[COLUMNS][ROWS], int column, int row);
	char up(char state[COLUMNS][ROWS], int column, int row);
	char rightUp(char state[COLUMNS][ROWS], int column, int row);
	char right(char state[COLUMNS][ROWS], int column, int row);
	char rightDown(char state[COLUMNS][ROWS], int column, int row);
	char down(char state[COLUMNS][ROWS], int column, int row);
	char leftDown(char state[COLUMNS][ROWS], int column, int row);
	
	/*
	This function calls the above functions (checking all of the directions)
	to determine if the spot should be EMPTY, BLACK, WHITE, POSSIBLE_BLACK_MOVE,
	POSSIBLE_WHITE_MOVE, or POSSIBLE_BLACK_OR_WHITE_MOVE.
	*/
	
	char evalSpace(char state[COLUMNS][ROWS], int column, int row);
	
public:
	//constructor
	Othello();

	//public functions
	bool endGame();		//checks if the game is over
	void copyCurrState(char state[COLUMNS][ROWS]);
	int getNumMoves(char player);
	string print(char player);													//prints the board with possible moves for the given player
	
	/*
	This function takes in a player's command, move, or comment
	and handles it accordingly. It returns 1 if it should be
	the next player's turn, 0 if it should stay the same player's
	turn, and returns 2 if the game should end. It also returns
	a string using the ParseReturn type. This string should
	be printed to the client.
	*/

	ParseReturn parse(string input, char player);	
};

/*******************************PRIVATE FUNCTIONS**************************/

//returns the opposing player's color (BLACK or WHITE)
char Othello::opposingPlayer(char player){
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

//returns the number of pieces a player has on a given state
int Othello::numPieces(char state[COLUMNS][ROWS], char player){
	if(player == WHITE){
		int whitePieces=0;
		for(int i=0; i < ROWS; i++){
			for(int j=0; j < COLUMNS; j++){
				if(state[j][i] == WHITE){
					whitePieces++;
				}
			}
		}
		return whitePieces;	
	}
	else if(player == BLACK){
		int blackPieces=0;
		for(int i=0; i < ROWS; i++){
			for(int j=0; j < COLUMNS; j++){
				if(state[j][i] == BLACK){
					blackPieces++;
				}
			}
		}
		return blackPieces;
	}
	else
		error("numPieces: Invalid color");
}

//returns a player's score given a state
int Othello::score(char state[COLUMNS][ROWS], char player){
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

//returns the number of possible moves a player can make
int Othello::numMoves(char state[COLUMNS][ROWS], char player){
	int count = 0;
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			if(player == BLACK){
				if(state[i][j] == POSSIBLE_BLACK_MOVE || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					count++;
				}
			}
			if(player == WHITE){
				if(state[i][j] == POSSIBLE_WHITE_MOVE || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					count++;
				}
			}
		}
	}
	return count;
}

//updates states[currState] and prevState by undoing last move
int Othello::undo(){
	if(currState <= 1){
		cout << "undo: can't undo, no more previous states.\n";
		return 1;
	}
	else{
		currState -= 2;
		return 0;
	}
}

//updates states[currState] and prevState by redoing last move
int Othello::redo(){
	if(currState >= numStates-2){
		cout << "redo: can't redo, no more future states.\n";
		return 1;
	}
	else{
		currState += 2;
		return 0;
	}
}

//Adds the next state to the states array. Returns 0 if successful. Returns 1 if invalid move.
int Othello::move(int column, int row, char player){
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
		if(states[currState][column][row] != POSSIBLE_WHITE_MOVE
			 && states[currState][column][row] != POSSIBLE_BLACK_OR_WHITE_MOVE){
			//cout << "Invalid move. Type \"SHOW_NEXT_POS\" to see possible moves.\n";
			return 1;
		}
	}
	if(player == BLACK){
		if(states[currState][column][row] != POSSIBLE_BLACK_MOVE
			 && states[currState][column][row] != POSSIBLE_BLACK_OR_WHITE_MOVE){
			//cout << "Invalid move. Type \"SHOW_NEXT_POS\" to see possible moves.\n";
			return 1;
		}
	}

	//we got a valid move
	//go to the next state and update the number of states
	currState++;
	numStates = currState + 1;		//the number of states is one more than the index
	memcpy(states[currState], states[currState-1], sizeof(states[currState-1]));

	//check each direction and flip oposing pieces
	int tempColumn;										//the next column to look at
	int tempRow;										//the next row to look at
	//left
	if(player == left(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column - 1;
		tempRow = row;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			tempColumn--;
			//tempRow does not change
		}
	}
	
	//left up
	if(player == leftUp(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column - 1;
		tempRow = row - 1;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			tempColumn--;
			tempRow--;
		}
	}
	
	//up
	if(player == up(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column;
		tempRow = row - 1;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			//tempColumn does not change
			tempRow--;
		}
	}
	
	//right up
	if(player == rightUp(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column + 1;
		tempRow = row - 1;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			tempColumn++;
			tempRow--;
		}
	}
	
	//right
	if(player == right(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column + 1;
		tempRow = row;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			tempColumn++;
			//tempRow does not change
		}
	}
	
	//right down
	if(player == rightDown(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column + 1;
		tempRow = row + 1;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			tempColumn++;
			tempRow++;
		}
	}
	
	//down
	if(player == down(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column;
		tempRow = row + 1;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			//tempColumn does not change
			tempRow++;
		}
	}
	
	//left down
	if(player == leftDown(states[currState], column, row)){
		//state[column][row] = player;
		tempColumn = column - 1;
		tempRow = row + 1;
		while(states[currState][tempColumn][tempRow] != player){
			states[currState][tempColumn][tempRow] = player;
			tempColumn--;
			tempRow++;
		}
	}
	
	//change actual spot
	states[currState][column][row] = player;
	
	/*
	Now we need to re eavluate all of the pieces on the board
	to determine if they have a piece, are a valid move for
	each player, or is simply empty.
	*/
	
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			states[currState][i][j] = evalSpace(states[currState], i, j);
		}
	}
	
	//success
	return 0;
}

//used to determine if char is a column
bool Othello::isColumn(char test){
	if(int(test) >= 97 && int(test) <= 104){
		return true;
	}
	else 
		return false;
}

//used to determine if char is a row
bool Othello::isRow(char test){
	if(int(test) >= 49 && int(test) <= 56){
		return true;
	}
	else
		return false;
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

char Othello::left(char state[COLUMNS][ROWS], int column, int row){
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

char Othello::leftUp(char state[COLUMNS][ROWS], int column, int row){
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

char Othello::up(char state[COLUMNS][ROWS], int column, int row){
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

char Othello::rightUp(char state[COLUMNS][ROWS], int column, int row){
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

char Othello::right(char state[COLUMNS][ROWS], int column, int row){
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

char Othello::rightDown(char state[COLUMNS][ROWS], int column, int row){
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

char Othello::down(char state[COLUMNS][ROWS], int column, int row){
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

char Othello::leftDown(char state[COLUMNS][ROWS], int column, int row){
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
	
char Othello::evalSpace(char state[COLUMNS][ROWS], int column, int row){
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
	char rc = EMPTY;
	
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
	currState = 0;
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			states[currState][i][j] = EMPTY;
		}
	}
	states[currState][d][4] = BLACK;
	states[currState][e][3] = BLACK;
	states[currState][d][3] = WHITE;
	states[currState][e][4] = WHITE;

	//compute possible moves
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			states[currState][i][j] = evalSpace(states[currState], i, j);
		}
	}
	
	display = ON;		//turn off after debugging?
	numStates = 1;
}

/*************************PUBLIC FUNCTIONS**************************/

//checks if the game is over
bool Othello::endGame(){
	if(numMoves(states[currState], WHITE) == 0 && numMoves(states[currState], BLACK) == 0){
		return true;
	}
	else 
		return false;
}

int Othello::getNumMoves(char player){
	return numMoves(states[currState], player);
}

void Othello::copyCurrState(char state[COLUMNS][ROWS]){
	memcpy(state, states[currState], sizeof(states[currState]));
}

//prints the board with possible moves
string Othello::print(char player){
	//first row
	stringstream buf;
	buf << "\n";
	buf << " |__a__|__b__|__c__|__d__|__e__|__f__|__g__|__h__|" << endl;
	if(player == BLACK){
		for(int i=0; i<ROWS; i++){
		buf << i+1 << "|";
			for(int j=0; j<COLUMNS; j++){
				char piece = '_'; //default as a space (no pieces present)
				if(states[currState][j][i] == BLACK){
					piece = '@';
				}
				else if(states[currState][j][i] == WHITE){
					piece = 'O';
				}
				else if(states[currState][j][i] == POSSIBLE_BLACK_MOVE){//mark a square as a potential move
					piece = 'X';
				}
				else if(states[currState][j][i] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					piece = 'X';
				}
				else
					piece = '_';
				buf << "__" << piece << "__|";
			}
		buf << endl;
		}
		buf << endl;
	}
	
	else if(player == WHITE){	
		for(int i=0; i<ROWS; i++){
		buf << i+1 << "|";
			for(int j=0; j<COLUMNS; j++){
				char piece = '_';
				if(states[currState][j][i] == BLACK){
					piece = '@';
				}
				else if(states[currState][j][i] == WHITE){
					piece = 'O';
				}
				else if(states[currState][j][i] == POSSIBLE_WHITE_MOVE){//mark a square as a potential move
					piece = 'X';
				}
				else if(states[currState][j][i] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					piece = 'X';
				}
				else
					piece = '_';
				buf << "__" << piece << "__|";
			}
		buf << endl;
		}
		buf << endl;
	}
	else{
		error("print: invalid player passed");
	}
	return buf.str();
}

/*
This function takes in a player's command, move, or comment
and handles it accordingly. It returns 1 if it should be
the next player's turn, 0 if it should stay the same player's
turn, and returns 2 if the game should end. It also returns
a string using the ParseReturn type. This string should
be printed to the client.
*/

ParseReturn Othello::parse(string input, char player){
	ParseReturn pr;
	pr.val = 0;
	pr.str = "";
	stringstream ss;
	//empty input
	if(input.size() == 0){
		pr.str = "No input found.\n";
		pr.val = 0;
		return pr;
	}
	
	//comment
	else if(input.at(0) == ';'){
		ss << input << endl;
		pr.str = ss.str();
		pr.val = 0;
		return pr;
	}
	
	else if(input == "EXIT"){
		pr.str = "Exiting\n";
		pr.val = 2;
		return pr;
	}
	
	//display on
	else if(input == "DISPLAY_ON"){
		display = ON;
		ss << print(player);
		pr.str = ss.str();
		pr.val = 0;
		return pr;
	}
	
	//display off
	else if(input == "DISPLAY_OFF"){
		display = OFF;
		pr.val = 0;
		return pr;
	}
	
	//easy
	else if(input == "EASY"){
		pr.str = "Cannot change difficulty once game has started.\n";
		pr.val = 0;
		return pr;
	}
	
	//medium
	else if(input == "MEDIUM"){
		pr.str = "Cannot change difficulty once game has started.\n";
		pr.val = 0;
		return pr;
	}
	
	//hard
	else if(input == "HARD"){
		pr.str = "Cannot change difficulty once game has started.\n";
		pr.val = 0;
		return pr;
	}
	
	//black
	else if(input == "BLACK"){
		pr.str = "Cannot change color once game has started.\n";
		pr.val = 0;
		return pr;
	}
	
	//white
	else if(input == "WHITE"){
		pr.str = "Cannot change color once game has started.\n";
		pr.val = 0;
		return pr;
	}
	
	//undo
	else if(input == "UNDO"){
		if(undo()){		//undo didn't work
			pr.val = 0;
			return pr;
		}
		if(display){
			ss << print(player);
		}
		pr.str = ss.str();
		pr.val = 0;
		return pr;
	}
	
	//redo
	else if(input == "REDO"){
		if(redo()){		//redo didn't work
			pr.val = 0;
			return pr;
		}
		if(display){
			ss << print(player);
		}
		pr.str = ss.str();
		pr.val = 0;
		return pr;
	}
	
	//show next position
	else if(input == "SHOW_NEXT_POS"){
		ss << "numMoves: " << numMoves(states[currState], player) << endl;
		ss << print(player);
		pr.str = ss.str();
		pr.val = 0;
		return pr;
	}
	
	//move
	else if(input.size() == 2){
		ss << input << endl;
		if(isColumn(input.at(0))){														//valid column
			if(isRow(input.at(1))){														//valid row
				//convert column and row to ints
				int tempColumn = (int)(input.at(0)) - 97;								//ascii conversion
				int tempRow = (int)(input.at(1)) - 48;									//ascii conversion
				if(!move(tempColumn, tempRow-1, player)){
					//valid move. check if game is over
					if(endGame()){
						if(display){
							ss << print(player);
						}
						if(score(states[currState], WHITE) == score(states[currState], BLACK)){			//tie
							ss << "Tie game! Final scores\nBLACK pieces: "
								 << numPieces(states[currState], BLACK) << "\nWHITE pieces: "
								 << numPieces(states[currState], WHITE) << endl;
							pr.str = ss.str();
							pr.val = 2;
							return pr;
						}
						else if(score(states[currState], WHITE) < score(states[currState], BLACK)){		//Black wins
							ss << "BLACK wins! Final scores\nBLACK pieces: "
								 << numPieces(states[currState], BLACK) << "\nWHITE pieces: "
								 << numPieces(states[currState], WHITE) << "\nBLACK score: "
								 << score(states[currState], BLACK) << endl;
							pr.str = ss.str();
							pr.val = 2;
							return pr;
						}
						else if(score(states[currState], WHITE) > score(states[currState], BLACK)){		//White wins
							ss << "White wins! Final scores\nBLACK pieces: "
								 << numPieces(states[currState], BLACK) << "\nWHITE pieces: "
								 << numPieces(states[currState], WHITE) << "\nWHITE score: "
								 << score(states[currState], WHITE) << endl;
							pr.str = ss.str();
							pr.val = 2;
							return pr;
						}
					}
					else{																//game is not over. Check number of opponent moves
						if(numMoves(states[currState], opposingPlayer(player)) == 0){
							ss << "Opposing player has no move to make. Go again!\n";
							if(display){
								ss << print(player);
							}
							pr.str = ss.str();
							pr.val = 0;
							return pr;
						}
						else{
							if(display){
								ss << print(opposingPlayer(player));
							}
							pr.str = ss.str();
							pr.val = 1;
							return pr;
						}
					}
				}
			}
		}
		ss << "Invalid move. Type \"SHOW_NEXT_POS\" to see possible moves.\n";
		pr.str = ss.str();
		pr.val = 0;
		return pr;																		//invalid move
	}
	
	//invalid command
	else{
		pr.str = "Invalid input.\n";
		pr.val = 0;
		return pr;
	}
}
