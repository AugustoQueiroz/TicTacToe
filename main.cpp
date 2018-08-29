#include <iostream>
#include <vector>
using namespace std;

typedef struct m {
	int x,
		y;
} Move;

typedef struct mmr {
	Move move;
	int result;
} MinMaxResult;

Move minmax(vector<vector<int> > board);
MinMaxResult max(vector<vector<int> > board);
MinMaxResult min(vector<vector<int> > board);
bool has_victory(vector<vector<int> > board);
bool has_loss(vector<vector<int> > board);
bool has_tied(vector<vector<int> > board);
bool has_triad(vector<vector<int> > board, int value);
void printBoard(vector<vector<int> > board);

Move minmax(vector<vector<int> > board) {
	MinMaxResult bestResult = max(board);
	return bestResult.move;
}

MinMaxResult max(vector<vector<int> > board) {
	//printBoard(board);

	if (has_victory(board)) {
	//	cout << "VICTORY" << endl;
		return (MinMaxResult){{0, 0}, 10};
	} else if (has_loss(board)) {
	//	cout << "LOSS" << endl;
		return (MinMaxResult){{0, 0}, -10};
	} else if (has_tied(board)) {
	//	cout << "TIE" << endl;
		return (MinMaxResult){{0, 0}, -1};
	}

	vector<vector<int> > fboard = board;
	vector<vector<int> > results(3);

	for (int i = 0; i < 3; i++) {
		results[i].resize(3);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (fboard[i][j] == 0) {
				fboard[i][j] = 1;
				results[i][j] = min(fboard).result;
				fboard[i][j] = 0;
			}
		}
	}

	MinMaxResult bestResult = {{0, 0}, -20};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (results[i][j] > bestResult.result && results[i][j] != 0 && results[i][j] != 1 && results[i][j] != 2) {
				bestResult.result = results[i][j];
				bestResult.move.x = i; bestResult.move.y = j;
			}
		}
	}

	return bestResult;
}

MinMaxResult min(vector<vector<int> > board) {
	//printBoard(board);

	if (has_victory(board)) {
	//	cout << "VICTORY" << endl;
		return (MinMaxResult){{0, 0}, 10};
	} else if (has_loss(board)) {
	//	cout << "LOSS" << endl;
		return (MinMaxResult){{0, 0}, -10};
	} else if (has_tied(board)) {
	//	cout << "TIE" << endl;
		return (MinMaxResult){{0, 0}, -1};
	}

	vector<vector<int> > fboard = board;
	vector<vector<int> > results(3);

	for (int i = 0; i < 3; i++) {
		results[i].resize(3);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (fboard[i][j] == 0) {
				fboard[i][j] = 2;
				results[i][j] = max(fboard).result;
				fboard[i][j] = 0;
			}
		}
	}

	MinMaxResult bestResult = {{0, 0}, 20};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (results[i][j] < bestResult.result && results[i][j] != 0 && results[i][j] != 1 && results[i][j] != 2) {
				bestResult.result = results[i][j];
				bestResult.move.x = i; bestResult.move.y = j;
			}
		}
	}

	return bestResult;
}

bool has_victory(vector<vector<int> > board) {
	return has_triad(board, 1);
}

bool has_loss(vector<vector<int> > board) {
	return has_triad(board, 2);
}

bool has_tied(vector<vector<int> > board) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}

	return true;
}

bool has_triad(vector<vector<int> > board, int value) {
	// Check lines
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != value) {
				break;
			}

			if (j == 2)
				return true;
		}
	}

	// Check columns
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			if (board[i][j] != value) {
				break;
			}

			if (i == 2)
				return true;
		}
	}

	// Check diagonal 1
	for (int i = 0; i < 3; i++) {
		if (board[i][i] != value) {
			break;
		}

		if (i == 2) 
			return true;
	}

	// Check diagonal 2
	for (int i = 0; i < 3; i++) {
		if (board[i][2-i] != value) {
			break;
		}

		if (i == 2)
			return true;
	}

	return false;
}

bool moveIsValid(Move move, vector<vector<int> > board) {
	return move.x >= 0 && move.x <= 2 && move.y >= 0 && move.y <= 2 && board[move.x][move.y] == 0;
}

void printBoard(vector<vector<int> > board) {
	for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == 0) {
					cout << "  ";
				} else if (board[i][j] == 1) {
					cout << " O";
				} else if (board[i][j] == 2) {
					cout << " X";
				}
				if (j < 2)
					cout << " |";
			}
			cout << endl;
			if (i < 2)
				cout << "-----------" << endl;
		}
}

int main() {
	vector<vector<int> > board(3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i].push_back(0);
		}
	}

	Move playerMove;

	while (!has_victory(board) && !has_loss(board) && !has_tied(board)) {
		printBoard(board);

		do {
			cout << "Your move: ";
			cin >> playerMove.x >> playerMove.y;
		} while (!moveIsValid(playerMove, board));

		board[playerMove.x][playerMove.y] = 2;

		if (has_loss(board) || has_tied(board))
			break;

		Move computerMove = minmax(board);

		cout << "Best move: x: " << computerMove.x << " y: " << computerMove.y << endl;

		board[computerMove.x][computerMove.y] = 1;
	}

	printBoard(board);

	if (has_victory(board)) {
		cout << "You Lost!" << endl;
	} else if (has_loss(board)) {
		cout << "You Won!" << endl;
	} else {
		cout << "It's a Tie!" << endl;
	}

	return 0;
}