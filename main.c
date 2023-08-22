#include <stdio.h>

typedef unsigned char uint8_t;

enum { win = 0, draw, cont };
enum { wrong = 0, notWrong };
enum cell { invalid = 0, valid };

void resetBoard(uint8_t* board);
void initBoard();
void drawBoard(uint8_t* board);
void updateBoard(uint8_t* board, uint8_t position, uint8_t value);
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol);
void setPlayerConfig(uint8_t* configArray);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t* board, uint8_t* gameState);


uint8_t board[9] = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
uint8_t configArray[2] = { ' ', ' ' };
uint8_t gameState = cont;
enum cell cellStatus = valid;

int	main() {
		uint8_t playAgain = ' ';
		initBoard();
		setPlayerConfig(configArray);
		do {
			resetBoard(board);
			uint8_t playerNumber = 1;
			drawBoard(board);

			do {

				playerNumber = (playerNumber % 2) ? 1 : 2;
				printf("Please, Player %d ", playerNumber);
				loadAndUpdate(playerNumber);
				if (cellStatus == invalid) {
					playerNumber--;
					cellStatus = valid;
				}
				drawBoard(board);
				getGameState(board, &gameState);
				playerNumber++;
			} while (gameState == cont);

			if (gameState == win) {
				printf("Player %d Win\n", --playerNumber);
			}
			else {
				printf("Game Over\n");
			}
			printf("If Want To Play Again press y/Y If Not Press any Key");
			scanf_s(" %c", &playAgain, 1);
		} while (playAgain == 'y' || playAgain == 'Y');
}

void resetBoard(uint8_t* board) {
	for (int i = 0; i < 9; i++) {
		board[i] = ' ';
	}
}

void initBoard() {
	printf("     |     |    \n");
	printf("  1  |  2  |  3  \n");
	printf("-----|-----|-----\n");
	printf("  4  |  5  |  6  \n");
	printf("-----|-----|-----\n");
	printf("  7  |  8  |  9  \n");
	printf("     |     |    \n");
	fflush(stdout);
}

void drawBoard(uint8_t* board) {
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c  \n", board[0], board[1], board[2]);

	printf("-----|-----|-----\n");

	printf("  %c  |  %c  |  %c  \n", board[3], board[4], board[5]);

	printf("-----|-----|-----\n");

	printf("  %c  |  %c  |  %c  \n", board[6], board[7], board[8]);

	printf("     |     |     \n");
}

void updateBoard(uint8_t* board, uint8_t position, uint8_t value) {


	if (position == 1 && board[0] == ' ') {
		board[(position - 1)] = value;

	}
	else if (position == 2 && board[1] == ' ') {
		board[position - 1] = value;
	}
	else if (position == 3 && board[2] == ' ') {
		board[position - 1] = value;
	}
	else if (position == 4 && board[3] == ' ') {
		board[position - 1] = value;
	}
	else if (position == 5 && board[4] == ' ') {
		board[position - 1] = value;
	}
	else if (position == 6 && board[5] == ' ') {
		board[position - 1] = value;
	}
	else if (position == 7 && board[6] == ' ') {
		board[position - 1] = value;
	}
	else if (position == 8 && board[7] == ' ') {
		board[position - 1] = value;
	}
	else if (position == 9 && board[8] == ' ') {
		board[(position - 1)] = value;
	}
	else {
		printf("Invalid Cell\n");
		cellStatus = invalid;
	}
}

uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol) {

	static uint8_t previous_symbol = ' ';
	uint8_t retVal = notWrong;
	printf("Please, Player %d Choose Symbol X or O \n", playerNumber);
	fflush(stdout);
	fflush(stdin);
	scanf_s(" %c",symbol,1);

	if (*symbol == 'X' || *symbol == 'x' || *symbol == 'O' || *symbol == 'o') {
		if ((*symbol != previous_symbol) && (*symbol != (previous_symbol-32))&& (*symbol != (previous_symbol+32))) {
			retVal = notWrong;
		}
		else {
			retVal = wrong;
		}

	}
	else {
		retVal = wrong;
	}
	previous_symbol = *symbol;
	return retVal;
}


void setPlayerConfig(uint8_t* configArray) {

	uint8_t retSymbol;
	uint8_t symbol = ' ';
	int flag = 1;
	for (int i = 0; i < 2; i++) {
		while (flag == 1) {
			retSymbol = getPlayerSymbol(i + 1, &symbol);
			if (retSymbol == notWrong) {
				configArray[i] = symbol;
				flag = 0;
			}
			else {
				printf("the input symbol is wrong and/or was chosen before\n");
				fflush(stdout);
				flag = 1;
			}
		}
		flag = 1;
	}
}

void loadAndUpdate(uint8_t playerNumber) {

	int position;
	printf("Choose Cell From 1 to 9 \n");
	fflush(stdout);
	fflush(stdin);
	scanf_s("%d",&position);
	updateBoard(board, (uint8_t)position, configArray[playerNumber - 1]);

}

void getGameState(uint8_t* board, uint8_t* gameState) {

	if (board[0] == board[1] && board[1] == board[2] && board[1] != ' ') {
		*gameState = win;
	}
	else if (board[3] == board[4] && board[4] == board[5] && board[4] != ' ') {
		*gameState = win;
	}
	else if (board[6] == board[7] && board[7] == board[8] && board[7] != ' ') {
		*gameState = win;
	}
	else if (board[0] == board[3] && board[3] == board[6] && board[3] != ' ') {
		*gameState = win;
	}
	else if (board[1] == board[4] && board[4] == board[7] && board[4] != ' ') {
		*gameState = win;
	}
	else if (board[2] == board[5] && board[5] == board[8] && board[5] != ' ') {
		*gameState = win;
	}
	else if (board[0] == board[4] && board[4] == board[8] && board[4] != ' ') {
		*gameState = win;
	}
	else if (board[2] == board[4] && board[4] == board[6] && board[4] != ' ') {
		*gameState = win;
	}

	else {
		for (int i = 0; i < 9; i++) {
			if (board[i] == ' ') {
				*gameState = cont;
				break;
			}
			else {
				*gameState = draw;
			}
		}
	}
}