/*
File: ai.h
Project: CSCE315 Project 2
Authors: Team 3 - Dylan McDougall, Sam Stewart, Stephen Ten Eyck
Description: This is the AI class. It can take in a state and
				output a string for its next move.
*/

#include "othello.h"

struct Best{
	string bestMove;
	int val;
};


class AI{
	int difficulty;
	char playerColor;
	char state[COLUMNS][ROWS];
	void copyCurrState(Othello &o);
	//stack< vector< vector<char> > > states/*[COLUMNS][ROWS]*/;
	//Best minmax(int depth);
	Best minMax(vector< vector<char> > state);
	Best maxMove(vector< vector<char> > state);
	Best minMove(vector< vector<char> > state); 
	int evaluate(vector< vector<char> > state);
	vector <vector<char> > testMove(vector <vector<char> >, int column, int row, char player);
	char opposingPlayer(char player);
	int numMoves(vector< vector<char> > state, char player);
	void print(vector< vector<char> > state, char player);
	int depth;
	
	//helper functions for testMove
	char evalSpace(vector< vector<char> >, int column, int row);
	char left(vector< vector<char> > state, int column, int row);
	char leftUp(vector< vector<char> > state, int column, int row);
	char up(vector< vector<char> > state, int column, int row);
	char rightUp(vector< vector<char> > state, int column, int row);
	char right(vector< vector<char> > state, int column, int row);
	char rightDown(vector< vector<char> > state, int column, int row);
	char down(vector< vector<char> > state, int column, int row);
	char leftDown(vector< vector<char> > state, int column, int row);
	
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
	srand(time(NULL));
	depth = 0;
}

void AI::setDifficulty(int diff){
	if(diff == EASY || diff == MEDIUM || diff == HARD || diff == EXPERT){
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
	cout << "Please wait. AI thinking\n\n";
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
		//put currstate on the stack alone
		char tempState[COLUMNS][ROWS];
		o.copyCurrState(tempState);
		vector<char> rows;
		vector< vector<char> > columns; 
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				rows.push_back(tempState[i][j]);
			}
			columns.push_back(rows);
			rows.clear();
		}
		
		//mightymax
		depth = 0;
		Best temp = minMax(columns);
		cout << temp.bestMove << endl;
		return temp.bestMove;	
	}
	else if(difficulty == HARD){
		//put currstate on the stack alone
		char tempState[COLUMNS][ROWS];
		o.copyCurrState(tempState);
		vector<char> rows;
		vector< vector<char> > columns; 
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				rows.push_back(tempState[i][j]);
			}
			columns.push_back(rows);
			rows.clear();
		}
		
		//mightymax
		depth = 0;
		Best temp = minMax(columns);
		cout << temp.bestMove << endl;
		return temp.bestMove;	
	}
	else if(difficulty == EXPERT){
		//put currstate on the stack alone
		char tempState[COLUMNS][ROWS];
		o.copyCurrState(tempState);
		vector<char> rows;
		vector< vector<char> > columns; 
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				rows.push_back(tempState[i][j]);
			}
			columns.push_back(rows);
			rows.clear();
		}
		
		//mightymax
		Best temp = minMax(columns);
		cout << temp.bestMove << endl;
		return temp.bestMove;	
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

Best AI::minMax(vector< vector<char> > state){
	depth = 0;
	return maxMove(state);
}

Best AI::maxMove(vector< vector<char> > state){
	depth++;
	//cout << depth << endl;
	if(depth >= 3 || (numMoves(state, playerColor) == 0 && numMoves(state, opposingPlayer(playerColor)))){
		Best temp;
		temp.val = evaluate(state);
		temp.bestMove = "";
		depth--;
		return temp;
	}
	else{
		Best temp;
		temp.val = -INFINITY;
		temp.bestMove = "";
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				if(playerColor == BLACK){
					if(state[i][j] == POSSIBLE_BLACK_MOVE || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						vector< vector<char> > minState = testMove(state, i, j, playerColor);
						Best moveVal = minMove(minState);
						if(moveVal.val > temp.val){
							temp.val = moveVal.val;
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							temp.bestMove = ss.str();
						}
					}
				}
				else{
					if(state[i][j] == POSSIBLE_WHITE_MOVE || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						vector< vector<char> > minState = testMove(state, i, j, playerColor);
						Best moveVal = minMove(minState);
						if(moveVal.val > temp.val){
							temp.val = moveVal.val;
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							temp.bestMove = ss.str();
						}
					}
				}
			}
		}
		depth--;
		return temp;
	}
}

Best AI::minMove(vector< vector<char> > state){
	depth++;
	Best temp;
	temp.val = INFINITY;
	temp.bestMove = "";
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			if(playerColor == BLACK){
				if(state[i][j] == POSSIBLE_WHITE_MOVE || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					vector< vector<char> > maxState = testMove(state, i, j, opposingPlayer(playerColor));
					Best moveVal = maxMove(maxState);
					if(moveVal.val < temp.val){
						temp.val = moveVal.val;
						stringstream ss;
						ss << (char)(i+97) << (j+1);
						temp.bestMove = ss.str();
					}
				}
			}
			else{
				if(state[i][j] == POSSIBLE_BLACK_MOVE || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					vector< vector<char> > maxState = testMove(state, i, j, opposingPlayer(playerColor));
					Best moveVal = maxMove(maxState);
					if(moveVal.val < temp.val){
						temp.val = moveVal.val;
						stringstream ss;
						ss << (char)(i+97) << (j+1);
						temp.bestMove = ss.str();
					}
				}
			}
		}
	}
	depth--;
	return temp;
}

int AI::evaluate(vector< vector<char> > state){
	if(difficulty == MEDIUM){
		int val = 0;
	
		//number of pieces
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				if(state[i][j] == playerColor){
					val += 1;
				}
				if(state[i][j] == opposingPlayer(playerColor)){
					val -= 1;
				}
			}
		}
		return val;
	}
	else{
		int val = 0;
		
		//check corners
		if(state[0][0] == playerColor){
			val += 300;
		}
		if(state[0][7] == playerColor){
			val += 300;
		}
		if(state[7][0] == playerColor){
			val += 300;
		}
		if(state[7][7] == playerColor){
			val += 300;
		}
		
		//check opposing corners
		if(state[0][0] == opposingPlayer(playerColor)){
			val -= 300;
		}
		if(state[0][7] == opposingPlayer(playerColor)){
			val -= 300;
		}
		if(state[7][0] == opposingPlayer(playerColor)){
			val -= 300;
		}
		if(state[7][7] == opposingPlayer(playerColor)){
			val -= 300;
		}
		
		//number openent moves
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				if(playerColor == WHITE){
					if(state[i][j] == POSSIBLE_BLACK_MOVE
					   || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						val -= 10;
					}
				}
				else{
					if(state[i][j] == POSSIBLE_WHITE_MOVE
					   || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						val -= 10;
					}
				}
			}
		}
		
		//end of game means worry about winning
		int numSpaces = 0;
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				if(state[i][j] != BLACK && state[i][j] != WHITE){
					numSpaces++;
				}
			}
		}
		
		//number of pieces
		for(int i=0; i<COLUMNS; i++){
			for(int j=0; j<ROWS; j++){
				if(state[i][j] == playerColor){
					if(numSpaces < 10){
						val += 10;
					}
					else{
						val += 3;
					}
				}
				if(state[i][j] == opposingPlayer(playerColor)){
					if(numSpaces < 10){
						val += 10;
					}
					else{
						val += 3;
					}
				}
			}
		}
		
		return val;
	}
	
}

vector <vector<char> > AI::testMove(vector <vector<char> > state, int column, int row, char player){
	//create the next state
	vector< vector <char> > newState = state;

	//check each direction and flip oposing pieces
	int tempColumn;										//the next column to look at
	int tempRow;										//the next row to look at
	//left
	if(player == left(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column - 1;
		tempRow = row;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			tempColumn--;
			//tempRow does not change
		}
	}
	
	//left up
	if(player == leftUp(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column - 1;
		tempRow = row - 1;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			tempColumn--;
			tempRow--;
		}
	}
	
	//up
	if(player == up(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column;
		tempRow = row - 1;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			//tempColumn does not change
			tempRow--;
		}
	}
	
	//right up
	if(player == rightUp(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column + 1;
		tempRow = row - 1;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			tempColumn++;
			tempRow--;
		}
	}
	
	//right
	if(player == right(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column + 1;
		tempRow = row;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			tempColumn++;
			//tempRow does not change
		}
	}
	
	//right down
	if(player == rightDown(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column + 1;
		tempRow = row + 1;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			tempColumn++;
			tempRow++;
		}
	}
	
	//down
	if(player == down(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column;
		tempRow = row + 1;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			//tempColumn does not change
			tempRow++;
		}
	}
	
	//left down
	if(player == leftDown(newState, column, row)){
		//state[column][row] = player;
		tempColumn = column - 1;
		tempRow = row + 1;
		while(newState[tempColumn][tempRow] != player){
			newState[tempColumn][tempRow] = player;
			tempColumn--;
			tempRow++;
		}
	}
	
	//change actual spot
	newState[column][row] = player;
	
	/*
	Now we need to re eavluate all of the pieces on the board
	to determine if they have a piece, are a valid move for
	each player, or is simply empty.
	*/
	
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			newState[i][j] = evalSpace(newState, i, j);
		}
	}
	
	return newState;
	
}

char AI::opposingPlayer(char player){
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

int AI::numMoves(vector< vector<char> > state, char player){
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

char AI::left(vector< vector<char> > state, int column, int row){
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

char AI::leftUp(vector< vector<char> > state, int column, int row){
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

char AI::up(vector< vector<char> > state, int column, int row){
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

char AI::rightUp(vector< vector<char> > state, int column, int row){
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

char AI::right(vector< vector<char> > state, int column, int row){
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

char AI::rightDown(vector< vector<char> > state, int column, int row){
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

char AI::down(vector< vector<char> > state, int column, int row){
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

char AI::leftDown(vector< vector<char> > state, int column, int row){
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

char AI::evalSpace(vector< vector<char> > state, int column, int row){
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

void AI::print(vector< vector<char> > state, char player){
	//first row
	cout << "\n";
	cout << " |__a__|__b__|__c__|__d__|__e__|__f__|__g__|__h__|" << endl;
	if(player == BLACK){
		for(int i=0; i<ROWS; i++){
		cout << i+1 << "|";
			for(int j=0; j<COLUMNS; j++){
				char piece = '_'; //default as a space (no pieces present)
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
					piece = '_';
				cout << "__" << piece << "__|";
			}
		cout << endl;
		}
		cout << endl;
	}
	
	else if(player == WHITE){	
		for(int i=0; i<ROWS; i++){
		cout << i+1 << "|";
			for(int j=0; j<COLUMNS; j++){
				char piece = '_';
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
					piece = '_';
				cout << "__" << piece << "__|";
			}
		cout << endl;
		}
		cout << endl;
	}
	else 
		error("print: invalid player passed");
}
