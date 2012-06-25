Othello Game Mechanics - README
CSCE 315 Team 3
Dylan McDougall, Same Stewart, Stephen Ten Eyck
25 JUN 2012
*****************************************************
Files Included:

Makefile   	- Makefile for all cpp files, creates executables
othello.h   - Header file containing the Othello class and mechanics
ai.h        - Header containing definition and implementation of the AI opponent
main.cpp 	- Source code for local, Human versus AI game
server.cpp  - Telnet server code

*****BELOW ARE TESTING FILES FOR AI DIFFICULTIES*****

easyEasy.cpp	- Tests BLACK: EASY versus WHITE: EASY
easyMedium.cpp	- Tests BLACK: EASY versus WHITE: MEDIUM
easyHard.cpp  	- Tests BLACK: EASY versus WHITE: HARD
mediumEasy.cpp	- Tests BLACK: MEDIUM versus WHITE: EASY
mediumMedium.cpp- Tests BLACK: MEDIUM versus WHITE: MEDIUM
mediumHard.cpp	- Tests BLACK: MEDIUM versus WHITE: HARD
hardEasy.cpp	- Tests BLACK: HARD versus WHITE: EASY
hardMedium.cpp	- Tests BLACK: HARD versus WHITE: MEDIUM
hardHard.cpp	- Tests BLACK: HARD versus WHITE: HARD

*****************************************************
Instructions:

1) To set up the programs, type 'make' and the executables will be created.
The executables can be run by simply typing their names in the command line.
The executable files will be named as follows

main 		- Used to play a local, Human versus AI game
server 		- Runs the game telnet server on port 65144
easyEasy	- Runs a test AI game - BLK: Easy versus WHT: Easy
easyMed		- Runs a test AI game - BLK: Easy versus WHT: Medium
easyHard	- Runs a test AI game - BLK: Easy versus WHT: Hard
medEasy		- Runs a test AI game - BLK: Medium versus WHT: Easy
medMed		- Runs a test AI game - BLK: Medium versus WHT: Medium
medHard		- Runs a test AI game - BLK: Medium versus WHT: Hard 
hardEasy	- Runs a test AI game - BLK: Hard versus WHT: Easy
hardMed		- Runs a test AI game - BLK: Hard versus WHT: Medium
hardHard	- Runs a test AI game - BLK: Hard versus WHT: Hard

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