#include <iostream>s
#include <string>
#include <algorithm>
using namespace std;

struct computersTurn {
	int compRow;
	int compColumn ;
};
void printBoard(char board[3][3]) {
	for (int i = 0; i < 3; ++i) {
		cout << "\t";
		for (int j = 0; j < 3; ++j) {
			cout << board[i][j];
		}
		cout << endl;
	}
}
bool isMovesLeft(char board[3][3]) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == '-') {
				return true;
			}
		}
	}
}
int evaluate(char board[3][3]) {
	for (int i = 0; i < 3; ++i) {
		if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X') {
			return -10;
		}
		else if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') {
			return -10;
		}
		else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O') {
			return 10;
		}
		else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') {
			return 10;
		}
	}
	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
		return -10;
	}
	else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
		return -10;
	}
	else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
		return 10;
	}
	else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
		return 10;
	}
	else {
		return 0;
	}
}
int minMax(char board[3][3], int depth, bool computersTurn) {
	int score = evaluate(board);
	if (score == 10){
		return score;
	}
	if (score == -10){
		return score;
	}
	if (isMovesLeft(board) == false) {
		return 0;
	}

	if (computersTurn == true){
		int bestScore = -1000;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (board[i][j] == '-') {
					board[i][j] = 'O';
					bestScore = max(bestScore, minMax(board, depth + 1, !computersTurn));
					board[i][j] = '-';
				}
			}
		}
		return bestScore;
	}
	else if (computersTurn == false){
		int bestScore = 1000;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (board[i][j] == '-') {
					board[i][j] = 'X';
					bestScore = min(bestScore, minMax(board, depth + 1, !computersTurn));
					board[i][j] = '-';
				}
			}
		}
		return bestScore;
	}
}
struct computersTurn optimalMove(char board[3][3]) {
	struct computersTurn AI;
	AI.compRow = 2;
	AI.compColumn = 2;
	int bestScore = -1000;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == '-') {
				board[i][j] = 'O';
				int moveScore = minMax(board, 0, false);
				board[i][j] = '-';
				if (moveScore > bestScore) {
					AI.compRow = i;
					AI.compColumn = j;
					bestScore = moveScore;
				}

			}
		}
	}
	return AI;
}
int main()
{
	struct computersTurn AI;
	AI.compColumn = 0;
	AI.compRow = 0;
	char board[3][3];
	cout << "Welcome to tic-tac-toe" << endl;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			board[i][j] = '-';
		}
	}
	cout << "You are X and the computer is O" << endl;
	cout << "Who do you want to go first? You or the Computer? type \"me\" or \"computer\"" << endl;
	string turn;
	cin >> turn;
	bool movesLeft = true;
	if (turn == "me") {
		while (movesLeft == true) {
			try{
				movesLeft = isMovesLeft(board);
				if (movesLeft == false) {
					break;
				}
				cout << "Your turn." << endl;
				cout << "Row Number?" << endl;
				int row = 0;
				cin >> row;
				cout << "Column Number?" << endl;
				int column = 0;
				cin >> column;
				if (board[row - 1][column - 1] == 'X' || board[row - 1][column - 1] == 'O') {
					throw runtime_error("invalid selection");
				}
				board[row - 1][column - 1] = 'X';
				printBoard(board);
				movesLeft = isMovesLeft(board);
				if (movesLeft == false) {
					break;
				}
				if (evaluate(board) == 10) {
					cout << "Sorry, the computer won." << endl;
					break;
				}
				else if (evaluate(board) == -10) {
					cout << "Congratulations, you won!" << endl;
					break;
				}
				cout << "computers turn" << endl;
				AI = optimalMove(board);
				board[AI.compRow][AI.compColumn] = 'O';
				printBoard(board);
				if (evaluate(board) == 10) {
					cout << "Sorry, the computer won." << endl;
					break;
				}
				else if (evaluate(board) == -10) {
					cout << "Congratulations, you won!" << endl;
					break;
				}
			}
			catch (runtime_error & excpt) {
				cout << excpt.what() << endl;
				cout << "input empty board spot." << endl;
			}
		}
	}
	else{
		while (movesLeft == true) {
			try {
				movesLeft = isMovesLeft(board);
				if (movesLeft == false) {
					break;
				}
				cout << "computers turn" << endl;
				AI = optimalMove(board);
				board[AI.compRow][AI.compColumn] = 'O';
				printBoard(board);
				if (evaluate(board) == 10) {
					cout << "Sorry, the computer won." << endl;
					break;
				}
				else if (evaluate(board) == -10) {
					cout << "Congratulations, you won!" << endl;
					break;
				}
				cout << "Your turn." << endl;
				cout << "Row Number?" << endl;
				int row = 0;
				cin >> row;
				cout << "Column Number?" << endl;
				int column = 0;
				cin >> column;
				if (board[row - 1][column - 1] == 'X' || board[row - 1][column - 1] == 'O') {
					throw runtime_error("invalid selection");
				}
				board[row - 1][column - 1] = 'X';
				printBoard(board);
				movesLeft = isMovesLeft(board);
				if (movesLeft == false) {
					break;
				}
				if (evaluate(board) == 10) {
					cout << "Sorry, the computer won." << endl;
					break;
				}
				else if (evaluate(board) == -10) {
					cout << "Congratulations, you won!" << endl;
					break;
				}
				
			}
			catch (runtime_error & excpt) {
				cout << excpt.what() << endl;
				cout << "input empty board spot." << endl;
			}
		}
		
		}

}


	

