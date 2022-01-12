#import <iostream>
#import <string>
#import <stdio.h>

/*
	Antonio Padillla
	This is a simple cli tic-tac-toe game I created so that one may play
	against themselves or with someone sitting next to them on the same
	computer. Simple, and just for fun.
*/

/*
	The board looks like below

	  "	01 | 05 | 09
	  \n-----------\n 
	  	25 | 29 | 33
	  \n-----------\n
	    49 | 53 | 57 
	  \n"

	a one-dimensional char array size 61. The numbers in the above
	representation are indices.
*/

/*
	Player one chooses their letter (X or O) upper or lower case, 
	and then selects a region on the board to place their letter.

	  1 | 2 | 3
	  ---------
	  4 | 5 | 6
	  ---------
	  7 | 8 | 9

	The number 1 corresponds to index 1 on the array representing the board, 
	the number 5 corresponds to index 29 on the array, and the number 9 
	corresponds to the index 57 on the board array, and so on and so forth.
	
	Three in a row wins and the program ends. A draw also ends the program.
	Re-run to play again.
*/

#define HI_L 1
#define HI_M 5
#define HI_R 9			
#define MID_L 25        
#define MID_M 29        
#define MID_R 33		
#define LO_L 49		  
#define LO_M 53 		 
#define LO_R 57 		  
#define X 88			
#define x 120			
#define O 79
#define o 111


using namespace std;

// Allow players to only play using X's and O's (upper or lower case)
bool isValidLetter(char player) {
	return (player == X || player == x || player == O || player == o);
}

bool invalidRegion(char* board, int region) {
	if (region < HI_L || region > HI_R) {
		return true;
	}

	//region invalid if any of these indexes is non empty
	int possiblyTaken[] = 
		{HI_L, HI_M, HI_R, MID_R, MID_M, MID_R, LO_L, LO_M, LO_R};

	if (board[possiblyTaken[region-1]] != ' ') {
		return true;
	}

	return false;

}

// check upper row, then middle row, then lowest row for a victory
bool check_row_win(char* board) {
	if (board[HI_L] == board[HI_M] && board[HI_R] == board[HI_L]) {
		return board[HI_L] != ' ';
	} else if (board[MID_L] == board[MID_M] && board[MID_L] == board[MID_R]) {
		return board[MID_L] != ' ';
	} else if (board[LO_L] == board[LO_M] && board[LO_L] == board[LO_R]) {
		return board[LO_L] != ' ';
	}
	return false;
}

// check left col, then middle col, then rightmost col for a victory
bool check_col_win(char* board) {
	if (board[HI_L] == board[MID_L] && board[HI_L] == board[LO_L]) {
		return board[HI_L] != ' ';
	} else if (board[HI_M] == board[MID_M] && board[HI_M] == board[LO_M]) {
		return board[HI_M] != ' ';
	} else if (board[HI_R] == board[MID_R] && board[HI_R] == board[LO_R]) {
		return board[HI_R] != ' ';
	}
	return false;
}

bool check_diag_win(char* board) {
	if (board[HI_L] == board[MID_M] && board[HI_L] == board[LO_R]) {
		return board[HI_L] != ' ';
	} else if (board[LO_L] == board[MID_M] && board[LO_L] == board[HI_R]) {
		return board[HI_R] != ' ';
	}
	return false;
}

bool gameWinner(char* board) {
	return check_row_win(board) || check_col_win(board) || check_diag_win(board);
}

char letterForP2(char player1) {
	switch (player1) {
		case 'O': return 'X'; 
		case 'o': return 'x';
		case 'X': return 'O'; 
		case 'x': return 'o';
		default: return 'O';
	}
}


void drawBoard(char* board, char input, int turn, int region) {
	if (turn == 0) {
		 board[HI_L] = ' '; 
		 board[HI_M] = ' '; 
		 board[HI_R] = ' ';
		 board[MID_L] = ' '; 
		 board[MID_M] = ' '; 
		 board[MID_R] = ' ';
		 board[LO_L] = ' '; 
		 board[LO_M] = ' '; 
		 board[LO_R] = ' ';
	} else {
		switch (region) {
			case 1: board[HI_L] = input; break;
			case 2: board[HI_M] = input; break;
			case 3: board[HI_R] = input; break;
			case 4: board[MID_L] = input; break;
			case 5: board[MID_M] = input; break;
			case 6: board[MID_R] = input; break;
			case 7: board[LO_L] = input; break;
			case 8: board[LO_M] = input; break;
			case 9: board[LO_R] = input; break;
		} 
	}
	//draws the board whether or not replacement was made
	printf("%s\n", board);
}

int main() {

	bool validLetter = false;
	bool isValidRegion;
	bool p1Turn = true;
	bool endGame = false;
	char p1;
	char p2;
	int turnNumber = 0;
	int regionSelected;

	int selections[9 * sizeof(int)];

	printf("\nWelcome to MYTic-Tac-Toe\n");
	printf("When prompted, choose a valid integer corresponding");
	printf("to a region on the board\n below for placement\n\n");

	char board[] =  
		" 1 | 2 | 3 \n-----------\n 4 | 5 | 6 \n-----------\n 7 | 8 | 9 \n";

	//initial board for instruction
	printf("%s\n", board);
	printf("Now, Player 1, choose an X or O -> ");

	//p1 chooses letter and p2 is automatically assigned
	while (!validLetter) {
		cin >> p1;
		if (isValidLetter(p1)) {
			p2 = letterForP2(p1);
			validLetter = true;
		} else {
			printf("Please choose a valid letter!\n-> ");
		} 
	}

	printf("OK, Player 2, your letter is %c\n\n", p2);
	printf("Begin!\n\n");

	drawBoard(board, ' ', turnNumber, 1);
	turnNumber = 1;

	while (!endGame) {

		if (p1Turn) {
			printf("PLAYER ONE please enter a region -> ");
		} else {
			printf("PLAYER TWO please enter a region -> " );
		}

		isValidRegion = false;
		while (!isValidRegion) {

			cin >> regionSelected;
			if (cin.fail()) {
				printf("Please enter an integer... \n-> ");
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			} else if (invalidRegion(board, regionSelected)) { 
				printf("Please enter an valid or empty region... \n-> ");
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			} else {
				char input = p1Turn ? p1:p2;
				drawBoard(board, input, turnNumber, regionSelected);
				if (gameWinner(board)) {
					string winner = p1Turn ? "PLAYER ONE":"PLAYER TWO";
					printf("GAME OVER\n%s WINS!!!\n\n", winner.c_str());
					endGame = true;
				}
				p1Turn = !p1Turn;
				turnNumber++;
				isValidRegion = true;
			}
		}

		// this is the case in a stalemate
		if (turnNumber == 10) {
			printf("\n\nGAME OVER\nIT'S A DRAW!!\n");
			endGame = true;
		}

	}
	return 0;
}



