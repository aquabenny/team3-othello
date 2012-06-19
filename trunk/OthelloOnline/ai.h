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
	int bestVal;
};


class AI{
	int difficulty;
	char playerColor;
	char state[COLUMNS][ROWS];
	void copyCurrState(Othello &o);
	stack< vector< vector<char> > > states/*[COLUMNS][ROWS]*/;
	Best minmax(int depth);
	int evaluate(vector< vector<char> > state, char player);
	int testMove(int column, int row, char player);
	char opposingPlayer(char player);
	int numMoves(vector< vector<char> > state, char player);
	
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
		states.push(columns);
		
		//mightymax
		Best temp = minmax(2);
		cout << temp.bestMove << endl;
		return temp.bestMove;	
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

//keep initial call even
Best AI::minmax(int depth){

/*
 int MinMax(int depth)
{
    int best = -INFINITY;
    int val;

    if (depth <= 0)
        return Evaluate();

    GenerateLegalMoves();
    while (MovesLeft()) {
        MakeNextMove();
        val = -MinMax(depth - 1);
        UnmakeMove();
        if (val > best)
            best = val;
    }
    return best;
} 
*/
	Best rc;
	rc.bestVal = -INFINITY;
	int val;
	string bestMove;
	
	if(depth <= 0
	   || (numMoves(states.top(), playerColor) == 0 && depth%2 == 0)
	   || (numMoves(states.top(), opposingPlayer(playerColor)) == 0 && depth%2 == 1)){
		Best temp;
		temp.bestMove = "";
		temp.bestVal = evaluate(states.top(), playerColor);
		return temp;
	}
	
	//for each move
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			if(depth%2 == 0){	//even- AI's move
				if(playerColor == BLACK){	//AI is black
					if(states.top()[i][j] == POSSIBLE_BLACK_MOVE
					   || states.top()[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						testMove(i, j, BLACK);		//put new state on the stack
						val = -minmax(depth - 1).bestVal;
						states.pop();
						if( val > rc.bestVal){
							rc.bestVal = val;
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							bestMove = ss.str();
						}
						rc.bestMove = bestMove;
						return rc;
					}
				}
				else{						//AI is white
					if(states.top()[i][j] == POSSIBLE_WHITE_MOVE
					   || states.top()[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						testMove(i, j, WHITE);		//put new state on the stack
						val = -minmax(depth - 1).bestVal;
						states.pop();
						if( val > rc.bestVal){
							rc.bestVal = val;
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							bestMove = ss.str();
						}
						rc.bestMove = bestMove;
						return rc;
					}
				}
			}
			else{				//odd- human's move
				if(playerColor == BLACK){	//AI is black
					if(states.top()[i][j] == POSSIBLE_WHITE_MOVE
					   || states.top()[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						testMove(i, j, WHITE);		//put new state on the stack
						val = -minmax(depth - 1).bestVal;
						states.pop();
						if( val > rc.bestVal){
							rc.bestVal = val;
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							bestMove = ss.str();
						}
						rc.bestMove = bestMove;
						return rc;
					}
				}
				else{						//AI is white
					if(states.top()[i][j] == POSSIBLE_BLACK_MOVE
					   || states.top()[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
						testMove(i, j, BLACK);		//put new state on the stack
						val = -minmax(depth - 1).bestVal;
						states.pop();
						if( val > rc.bestVal){
							rc.bestVal = val;
							stringstream ss;
							ss << (char)(i+97) << (j+1);
							bestMove = ss.str();
						}
						rc.bestMove = bestMove;
						return rc;
					}
				}
			}
		}
	}
}

int AI::evaluate(vector< vector<char> > state, char player){
	int val = 0;
	
	//check corners
	if(state[0][0] == player){
		val += 20;
	}
	if(state[0][7] == player){
		val += 20;
	}
	if(state[7][0] == player){
		val += 20;
	}
	if(state[7][7] == player){
		val += 20;
	}
	
	//number openent moves
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			if(opposingPlayer(player) == BLACK){
				if(state[i][j] == POSSIBLE_BLACK_MOVE
				   || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					val -= 5;
				}
			}
			else{
				if(state[i][j] == POSSIBLE_WHITE_MOVE
				   || state[i][j] == POSSIBLE_BLACK_OR_WHITE_MOVE){
					val -= 5;
				}
			}
		}
	}
	
	//number of pieces
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			if(player == BLACK){
				if(state[i][j] == BLACK){
					val += 1;
				}
				if(state[i][j] == WHITE){
					val -= 1;
				}
			}
			else{
				if(state[i][j] == WHITE){
					val += 1;
				}
				if(state[i][j] == BLACK){
					val -= 1;
				}
			}
		}
	}
}

int AI::testMove(int column, int row, char player){
	//create the next state
	vector< vector <char> > newState = states.top();

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
	
	//put it on the stack
	states.push(newState);
	
	//success
	return 0;
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
