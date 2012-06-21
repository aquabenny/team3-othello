Othello Game Mechanics - README
CSCE 315 Team 3
Dylan McDougall, Same Stewart, Stephen Ten Eyck
15 JUN 2012
*****************************************************
Files Included:

Othello    	- Executable output from g++, used to run the program
othello.h   - Header file containing the Othello class and mechanics
ai.h        - Header containing definition and implementation of the AI opponent
main.cpp 	- Source code for running a two-player local game

*****************************************************
Instructions:

1) To run, in the command line type ./Othello and the program should launch.

If there is an issue, please re-compile and run the program with the following commands:
1) g++ main.cpp -o Othello
2) ./Othello

*****************************************************
Program Specifications
This program launches a two player game of Reversi/Othello. It begins by showing the starting game board,
and prompting the BLACK user for a command.

The following commands are accepted by the parser:
BLACK 		- player picks the black side
WHITE 		- player picks the white side
EASY  		- sets AI difficulty to easy
MEDIUM		- sets AI difficulty to medium
HARD		- sets AI difficulty to hard
DISPLAY_OFF	- turns the game's display of the board off
DISPLAY_ON 	- turns the display of the board on (default)
SHOW_NEXT_POS - Show the game board with the next possible moves for the current player's turn
UNDO 		- undo a move
REDO 		- redo a previously undone move
EXIT		- Exit the program

The game will also accept commands for moves, as long as they are in the format [column][row]
For the command to be accepted, it has to start with a letter (a through h) and end with an integer (1-8).
The game will inform you if a move is not valid.