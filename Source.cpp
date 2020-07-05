#include <iostream> 
#include <cmath>
#include <Windows.h>
#include <string>

#define SIZE 8
#define CHECKER '*'
#define EMPTY '-'

using namespace std;

class Checker {
public:
	bool isQueen = false;
	bool isEmpty = true;
	bool isWhite = false;
	char space = EMPTY;

};

void showField(Checker field[SIZE][SIZE]) {
	system("cls");
	for (int i = 0; i <= SIZE; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < SIZE; i++) {
		for (int j = -1; j < SIZE; j++) {
			if (j == -1) {
				cout << i + 1 << " ";
				continue;
			}
			if (field[i][j].isEmpty == false) {
				if (field[i][j].isWhite == true) {
					if (field[i][j].isQueen == true) {
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 13));
					}
					else {
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 4));
					}
				}
				else {
					if (field[i][j].isQueen == true) {
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 1));
					}
					else {
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
					}
				}
			}
			cout << field[i][j].space << " ";
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		}
		cout << endl;
	}
}

void startingField(Checker field[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (((i + j) % 2 == 0 && (i < 3) && (i >= 0)) || ((i + j) % 2 == 0 && (i >= 5))) {
				if (i < 3) {
					if ((i + j) % 2 == 0) {
						field[i][j].space = CHECKER;
						field[i][j].isWhite = false;
						field[i][j].isEmpty = false;
					}
				}
				if (i >= 5) {
					if ((i + j) % 2 == 0) {
						field[i][j].space = CHECKER;
						field[i][j].isWhite = true;
						field[i][j].isEmpty = false;
					}
				}
			}
		}

	}
}

void killEnemyOnWayQueen(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	int startingRow = nowRow > nextRow ? nextRow : nowRow;
	int finishingRow = nowRow > nextRow ? nowRow : nextRow;
	int startingColumn = nowColumn > nextColumn ? nextColumn : nowColumn;
	int finishingColumn = nowColumn > nextColumn ? nowColumn : nextColumn;

	for (int i = startingRow; i < finishingRow; i++) {
		for (int j = startingColumn; j < finishingColumn; j++) {
			if ((i + j == nowRow + nowColumn) || (i - j == nowRow - nowColumn)) {
				if (!field[i][j].isEmpty) {
					if (field[i][j].isWhite != field[nowRow][nowColumn].isWhite) {
						field[i][j].isEmpty = true;
						field[i][j].space = EMPTY;
					}
				}
			}
		}
	}
}

bool correctMoveQueen(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	if (nowRow - nowColumn == nextRow - nextColumn || nowRow + nowColumn == nextRow + nextColumn) {
		if (nextRow > nowRow && nextColumn > nowColumn) {
			for (int i = 1; i < SIZE; i++) {
				int row = nowRow + i;
				int column = nowColumn + i;
				if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
					if (!field[row][column].isEmpty) {
						if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
							if (row + 1 < SIZE && column + 1 < SIZE && field[row + 1][column + 1].isEmpty) {
								if (row + 1 == nextRow && column + 1 == nextColumn) {
									return true;
								}
							}
						}

					}
				}
			}
		}
	    
		if (nextRow > nowRow && nextColumn < nowColumn) {
			for (int i = 1; i < SIZE; i++) {
				int row = nowRow + i;
				int column = nowColumn - i;
				if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
					if (!field[row][column].isEmpty) {
						if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
							if (row + 1 < SIZE && column - 1 >= 0 && field[row + 1][column - 1].isEmpty) {
								if (row + 1 == nextRow && column - 1 == nextColumn) {
									return true;
								}
							}
						}
						
					}
				}
			}
		}
		if (nextRow < nowRow && nextColumn < nowColumn) {
			for (int i = 1; i < SIZE; i++) {
				int row = nowRow - i;
				int column = nowColumn - i;
				if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
					if (!field[row][column].isEmpty) {
						if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
							if (row - 1 >= 0 && column - 1 >= 0 && field[row - 1][column - 1].isEmpty) {
								if (row - 1 == nextRow && column - 1 == nextColumn) {
									return true;
								}
							}
						}
						
					}
				}
			}
		}
		if (nextRow < nowRow && nextColumn > nowColumn) {
			for (int i = 1; i < SIZE; i++) {
				int row = nowRow - i;
				int column = nowColumn + i;
				if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
					if (!field[row][column].isEmpty) {
						if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
							if (row - 1 >= 0 && column + 1 < SIZE && field[row - 1][column + 1].isEmpty) {
								if (row - 1 == nextRow && column + 1 == nextColumn) {
									return true;
								}
							}
						}
						
					}
				}
			}
		}
		
	}
	return false;
}

bool isCanHitQueen(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	/*for (int i = 1; i < SIZE; i++) {
		int k1 = nowRow > nextRow ? -i : i;
		int k2 = nowColumn > nextColumn ? -i : i;
		int n1 = nowRow > nextRow ? -i - 1 : i + 1;
		int n2 = nowColumn > nextColumn ? -i - 1 : i + 1;

		int row = nowRow + k1, nRow = nowRow + n1;
		int column = nowColumn + k2, nColumn = nowColumn + n2;

		if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
			if (!field[row][column].isEmpty) {
				if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
					if (nRow >= 0 && nRow < SIZE && nColumn >= 0 && nColumn < SIZE && field[nRow][nColumn].isEmpty) {
						if (field[nRow][nColumn].isEmpty) {
							return true;
						}
					}
				}
				else {
					return false;
				}
			}
		}
	}
	return false; */
	if (field[nowRow][nowColumn].isQueen) {
		for (int i = 1; i < SIZE; i++) {
			int row = nowRow + i;
			int column = nowColumn + i;
			if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
				if (!field[row][column].isEmpty) {
					if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
						if (row + 1 < SIZE && column + 1 < SIZE && field[row + 1][column + 1].isEmpty) {
							return true;
						}
					}
					break;
				}
			}
		}
		for (int i = 1; i < SIZE; i++) {
			int row = nowRow + i;
			int column = nowColumn - i;
			if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
				if (!field[row][column].isEmpty) {
					if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
						if (row + 1 < SIZE && column - 1 >= 0 && field[row + 1][column - 1].isEmpty) {
							return true;
						}
					}
					break;
				}
			}
		}
		for (int i = 1; i < SIZE; i++) {
			int row = nowRow - i;
			int column = nowColumn - i;
			if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
				if (!field[row][column].isEmpty) {
					if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
						if (row - 1 >= 0 && column - 1 >= 0 && field[row - 1][column - 1].isEmpty) {
							return true;
						}
					}
					break;
				}
			}
		}
		for (int i = 1; i < SIZE; i++) {
			int row = nowRow - i;
			int column = nowColumn + i;
			if (row >= 0 && column >= 0 && row < SIZE && column < SIZE) {
				if (!field[row][column].isEmpty) {
					if (field[row][column].isWhite != field[nowRow][nowColumn].isWhite) {
						if (row - 1 >= 0 && column + 1 < SIZE && field[row - 1][column + 1].isEmpty) {
							return true;
						}
					}
					break;
				}
			}
		}
	}
	return false; 
}

bool isCanHit(Checker field[SIZE][SIZE], int row, int column, int nextRow, int nextColumn, bool isHit) { //checker position
	//if (!field[nowRow][nowColumn].isEmpty)
	//*b = false;
	if (field[row][column].isQueen) {
		return isCanHitQueen(field, row, column, nextRow, nextColumn);
	}

	for (int i = row - 2; i <= row + 2; i += 4) {
		for (int j = column - 2; j <= column + 2; j += 4) {
			if ((i >= 0 && j >= 0 && i < SIZE && j < SIZE) && field[i][j].isEmpty) {
				int k1 = i < row ? row - 1 : row + 1;
				int k2 = j < column ? column - 1 : column + 1;
				if ((!field[k1][k2].isEmpty) && (field[k1][k2].isWhite != field[row][column].isWhite)) {
					//*b = true;
					if (!isHit) {
						return true;
					}
					if (nextRow == i && nextColumn == j) {
						field[k1][k2].isEmpty = true;// Die checker
						field[k1][k2].space = EMPTY;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool shouldHitChecker(Checker field[SIZE][SIZE], int numPlayer) {
	//bool temp1 = true;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!field[i][j].isEmpty && numPlayer % 2 == field[i][j].isWhite) {
				if (isCanHit(field, i, j, -1, -1, false) || isCanHitQueen(field, i, j, -1, -1)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool canMoveChecker(Checker field[SIZE][SIZE], int row, int column, int numPlayer) {
	if (field[row][column].isWhite == numPlayer % 2 && !field[row][column].isEmpty) {
		if (field[row][column].isWhite == true) {
			if (row - 1 >= 0 && column - 1 >= 0 && field[row - 1][column - 1].isEmpty == true) {
				return true;
			}
			if (row - 1 >= 0 && column + 1 < SIZE && field[row - 1][column + 1].isEmpty == true) {
				return true;
			}
		}
		else {
			if (row + 1 < SIZE && column + 1 < SIZE && field[row + 1][column + 1].isEmpty == true) {
				return true;
			}
			if (row + 1 < SIZE && column - 1 >= 0 && field[row + 1][column - 1].isEmpty == true) {
				return true;
			}
		}
	}

	return false;
}

/*bool correctMoveQueen(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	if (nowRow + nowColumn == nextRow + nextColumn || nowRow - nowColumn == nextRow - nextColumn) {
		if (nextRow < SIZE && nextColumn < SIZE && nextRow >= 0 && nextColumn >= 0) {
			if (field[nextRow][nextColumn].isEmpty == true && nowRow != nextRow && nowColumn != nextColumn) {
				int k2 = nowColumn > nextColumn ? -1 : 1;
				int k1 = nowRow > nextRow ? -1 : 1;
				for (int i = nowRow; i <= nextRow; i += k1) {
					for (int j = nowColumn; j <= nextColumn; j += k2) {
						if (!field[i][j].isEmpty && field[i][j].isWhite == field[nowRow][nowColumn].isWhite) {
							return false;
						}
					}
				}
				return true;
			}
		}
	}
	return false;
} */

bool correctMoveChecker(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	if (field[nowRow][nowColumn].isQueen) {
		return correctMoveQueen(field, nowRow, nowColumn, nextRow, nextColumn);
	}

	if (nowRow + nowColumn == nextRow + nextColumn || nowRow - nowColumn == nextRow - nextColumn) {
		if (nextRow < SIZE && nextColumn < SIZE && nextRow >= 0 && nextColumn >= 0) {
			if (field[nextRow][nextColumn].isEmpty == true && nowRow != nextRow && nowColumn != nextColumn) {
				if (abs(nowRow - nextRow) == 1 && abs(nowColumn - nextColumn) == 1) {

					if (field[nowRow][nowColumn].isWhite == true) {
						if (nowRow > nextRow) {
							return true;
						}
					}
					else {
						if (nowRow < nextRow) {
							return true;
						}
					}
					
				}
			}
		}
	}

	return false;
}

void moveChecker(Checker field[SIZE][SIZE], int* nowRow, int* nowColumn, int nextRow, int nextColumn) {
	field[nextRow][nextColumn] = field[*nowRow][*nowColumn];
	field[*nowRow][*nowColumn].isEmpty = true;
	field[*nowRow][*nowColumn].space = EMPTY;
	*nowRow = nextRow;
	*nowColumn = nextColumn;
}

bool out(Checker field[SIZE][SIZE]) {
	bool whiteExist = false, blackExist = false;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!field[i][j].isEmpty) {
				if (field[i][j].isWhite) {
					whiteExist = true;
				}
				else {
					blackExist = true;
				}
			}
		}
	}
	if (!whiteExist || !blackExist) {
		return true;
	}
	return false;
}

void whoMoves(int numPlayer, string first, string second) {
	if (numPlayer % 2 != 0) {
		cout << first << " turn!" << endl;
	}
	else {
		cout << second << " turn!" << endl;
	}
}

void queen(Checker field[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		if (!field[0][i].isEmpty && field[0][i].isWhite) {
			field[0][i].isQueen = true;
		}
		if (!field[7][i].isEmpty && !field[7][i].isWhite) {
			field[7][i].isQueen = true;
		}
	}
}

int main() {
	system("color F0");
	Checker field[SIZE][SIZE];
	string firstPlayer, secondPlayer;
	int nowRow, nowColumn, nextRow, nextColumn;
	int numPlayer = 1;

	cout << "Write nickname of first player (red)" << endl;
	cin >> firstPlayer;
	cout << "Write nickname of second player (black)" << endl;
	cin >> secondPlayer;

	startingField(field);
	/*
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			field[i][j].space = EMPTY;
			field[i][j].isEmpty = true;
			field[i][j].isQueen = false;
		}
	}
	*/

	/*field[0][7].isQueen = true;
	field[0][7].isWhite = true;
	field[0][7].isEmpty = false;
	field[0][7].space = CHECKER;

	field[4][3].isWhite = true;
	field[4][3].isEmpty = false;
	field[4][3].space = CHECKER;

	field[6][1].isWhite = false;
	field[6][1].isEmpty = false;
	field[6][1].space = CHECKER;

	field[1][2].isWhite = false;
	field[1][2].isEmpty = false;
	field[1][2].space = CHECKER;

	field[1][6].isWhite = false;
	field[1][6].isEmpty = false;
	field[1][6].space = CHECKER;

	field[5][6].isWhite = false;
	field[5][6].isEmpty = false;
	field[5][6].space = CHECKER; */

	bool isHit = false;
	while (!out(field)) {
		queen(field);
		showField(field);
		isHit = false;

		whoMoves(numPlayer, firstPlayer, secondPlayer);

		if (shouldHitChecker(field, numPlayer)) {
			cout << "One of your checkers should hit. Choose this checker" << endl;
			do {
				cin >> nowRow >> nowColumn;
				nowRow -= 1;
				nowColumn -= 1;
				if (field[nowRow][nowColumn].isEmpty) {
					cout << "This is empty cell" << endl;
				}
				else if (!isCanHit(field, nowRow, nowColumn, -1, -1, isHit)) {
					cout << "Try another one" << endl;
				}
			} while (field[nowRow][nowColumn].isEmpty || !isCanHit(field, nowRow, nowColumn, -1, -1, isHit));

			cout << "Choose next position" << endl;
			//system("pause");


			bool firstTime = true;
			do {
				if (!firstTime) {
					cout << "Eat one more time" << endl;
				}
				firstTime = false;

				isHit = true;
				bool outFromWhile = false;
				do {
					cin >> nextRow >> nextColumn;
					nextRow -= 1;
					nextColumn -= 1;
					if (!isCanHit(field, nowRow, nowColumn, nextRow, nextColumn, isHit)) {
						cout << "You should eat! Choose another next position" << endl;
					}
					else {
						outFromWhile = true;
					}
				} while (!outFromWhile);
				if (field[nowRow][nowColumn].isQueen) {
					killEnemyOnWayQueen(field, nowRow, nowColumn, nextRow, nextColumn);
				}
				moveChecker(field, &nowRow, &nowColumn, nextRow, nextColumn);
				
				isHit = false;
				showField(field);
			} while (isCanHit(field, nowRow, nowColumn, nextRow, nextColumn, isHit));
		}
		else {
			cout << "Choose fighting checker" << endl;
			do {
				cin >> nowRow >> nowColumn;
				nowRow -= 1;
				nowColumn -= 1;
				if (field[nowRow][nowColumn].isEmpty) {
					cout << "This is empty cell" << endl;
				}
				else if (field[nowRow][nowColumn].isWhite != numPlayer % 2) {
					cout << "This is not your checker" << endl;
				}
				else if (!canMoveChecker(field, nowRow, nowColumn, numPlayer)) {
					cout << "This checker can't run now" << endl;
				}
			} while (!canMoveChecker(field, nowRow, nowColumn, numPlayer));

			cout << "Choose next position" << endl;

			do {
				cin >> nextRow >> nextColumn;
				nextRow -= 1;
				nextColumn -= 1;

				if (!correctMoveChecker(field, nowRow, nowColumn, nextRow, nextColumn)) {
					cout << "You can't move like that" << endl;
				}
			} while (!correctMoveChecker(field, nowRow, nowColumn, nextRow, nextColumn));
			moveChecker(field, &nowRow, &nowColumn, nextRow, nextColumn);
		}
		numPlayer += 1;
	}

	if ((numPlayer - 1) % 2 != 0) {
		cout << firstPlayer << " win!!!" << endl;
	}
	else {
		cout << secondPlayer << " win!!!" << endl;
	}

	return 0;
}