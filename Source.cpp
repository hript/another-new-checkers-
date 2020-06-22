#include <iostream>
#include <string>
#include <Windows.h>
#include <cmath>

#define SIZE 9
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

void showField(Checker** field) {
	system("cls");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (field[i][j].isEmpty == false) {
				if (field[i][j].isWhite == true) {
					if (field[i][j].isQueen == true) {
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 12));
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

void startingField(Checker** field) {
	for (int i = 0; i < SIZE; i++) {
		field[0][i].space = i + '0';
		field[0][i].isEmpty = false;
		field[i][0].space = i + '0';
		field[i][0].isEmpty = false;
		for (int j = 1; j < SIZE; j++) {
			if (((i + j) % 2 == 0 && (i <= 3) && (i > 0)) || ((i + j) % 2 == 0 && (i >= 6))) {
				if (i <= 3) {
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

void moveChecker(Checker** field, int nowRow, int nowColumn, int nextRow, int nextColumn) {
	field[nextRow][nextColumn] = field[nowRow][nowColumn];
	field[nowRow][nowColumn].isEmpty = true;
	field[nowRow][nowColumn].space = EMPTY;
}

bool correctMove(Checker** field, int nowRow, int nowColumn, int nextRow, int nextColumn) {
	if (nowRow + nowColumn != nextRow + nextColumn && nowRow - nowColumn != nextRow - nextColumn) {
		return false;
	}
	if (nextRow >= SIZE || nextColumn >= SIZE || nextRow < 1 || nextColumn < 1) {
		return false;
	}
	if (field[nextRow][nextColumn].isEmpty == false || nowRow == nextRow && nowColumn == nextColumn) {
		return false;
	}
	if (abs(nowRow - nextRow) > 1 && abs(nowColumn - nextColumn) > 1) {
		return false;
	}
	if (field[nowRow][nowColumn].isWhite == true) {
		if (nowRow < nextRow) {
			return false;
		}
	}
	else {
		if (nowRow > nextRow) {
			return false;
		}
	}
	return true;
}

bool yourChecker(Checker** field, int row, int column, int numPlayer) {
	if (numPlayer % 2 == field[row][column].isWhite) {
		return true;
	}
	return false;
}

bool canMove(Checker** field, int row, int column, int numPlayer) {
	if (yourChecker(field, row, column, numPlayer) == false) {
		return false;
	}
	if (field[row][column].isEmpty == true || numPlayer % 2 != field[row][column].isWhite) {
		return false;
	}
	if (field[row][column].isWhite == true) {
		if (row - 1 > 0 && column - 1 > 0 && field[row - 1][column - 1].isEmpty == true) {
			return true;
		}
		if (row - 1 > 0 && column + 1 < SIZE && field[row - 1][column + 1].isEmpty == true) {
			return true;
		}
	}
	else {
		if (row + 1 < SIZE && column + 1 < SIZE && field[row + 1][column + 1].isEmpty == true) {
			return true;
		}
		if (row + 1 < SIZE && column - 1 > 0 && field[row + 1][column - 1].isEmpty == true) {
			return true;
		}
	}
	return false;
}

bool enemyOnWayChecker(Checker** field, int nowRow, int nowColumn, int nextRow, int nextColumn) {
	if (abs(nowRow - nextRow) == 2 && abs(nowColumn - nextColumn) == 2 && !field[nowRow][nowColumn].isEmpty) {
		if (nextColumn > 0 && nextRow > 0 && nextColumn < SIZE && nextRow < SIZE) {
			if (field[nextRow][nextColumn].isEmpty) {
				if (nowRow < nextRow && nowColumn < nextColumn && !field[nowRow + 1][nowColumn + 1].isEmpty) {
					if (field[nowRow][nowColumn].isWhite != field[nowRow + 1][nowColumn + 1].isWhite) {
						return true;
					}
				}
				if (nowRow < nextRow && nowColumn > nextColumn && !field[nowRow + 1][nowColumn - 1].isEmpty) {
					if (field[nowRow][nowColumn].isWhite != field[nowRow + 1][nowColumn - 1].isWhite) {
						return true;
					}
				}
				if (nowRow > nextRow && nowColumn > nextColumn && !field[nowRow - 1][nowColumn - 1].isEmpty) {
					if (field[nowRow - 1][nowColumn - 1].isWhite != field[nowRow][nowColumn].isWhite) {
						return true;
					}
				}
				if (nowRow > nextRow && nowColumn < nextColumn && !field[nowRow - 1][nowColumn + 1].isEmpty) {
					if (field[nowRow - 1][nowColumn + 1].isWhite != field[nowRow][nowColumn].isWhite) {
						return true;
					}
				}
			}
		}
	}
}

bool canHitChecker(Checker** field, int row, int column, int numPlayer) {
	if (field[row][column].isEmpty) {
		return false;
	}
	for (int i = row - 2; i <= row + 2; i++) {
		for (int j = row - 2; j <= row + 2; j++) {
			if (field[i][j].isWhite == numPlayer % 2) {
				if (i - 2 > 0 && j - 2 > 0) {
					if (enemyOnWayChecker(field, row, column, i - 2, j - 2)) {
						return true;
					}
				}
				if (i - 2 > 0 && j + 2 < SIZE) {
					if (enemyOnWayChecker(field, row, column, i - 2, j + 2)) {
						return true;
					}
				}
				if (i + 2 < SIZE && j - 2 > 0) {
					if (enemyOnWayChecker(field, row, column, i + 2, j - 2)) {
						return true;
					}
				}
				if (i + 2 < SIZE && j + 2 < SIZE) {
					if (enemyOnWayChecker(field, row, column, i + 2, j + 2)) {
						return true;
					}
				}
			}
		}
	}
}

void kill(Checker** field, int nowRow, int nowColumn, int nextRow, int nextColumn) {
	if (nowRow < nextRow && nowColumn < nextColumn && !field[nowRow + 1][nowColumn + 1].isEmpty) {
		if (field[nowRow][nowColumn].isWhite != field[nowRow + 1][nowColumn + 1].isWhite) {
			field[nowRow + 1][nowColumn + 1].isEmpty = true;
			field[nowRow + 1][nowColumn + 1].space = EMPTY;
		}
	}
	if (nowRow < nextRow && nowColumn > nextColumn && !field[nowRow + 1][nowColumn - 1].isEmpty) {
		if (field[nowRow][nowColumn].isWhite != field[nowRow + 1][nowColumn - 1].isWhite) {
			field[nowRow + 1][nowColumn - 1].isEmpty = true;
			field[nowRow + 1][nowColumn - 1].space = EMPTY;
		}
	}
	if (nowRow > nextRow && nowColumn > nextColumn && !field[nowRow - 1][nowColumn - 1].isEmpty) {
		if (field[nowRow - 1][nowColumn - 1].isWhite != field[nowRow][nowColumn].isWhite) {
			field[nowRow - 1][nowColumn - 1].isEmpty = true;
			field[nowRow - 1][nowColumn - 1].space = EMPTY;
		}
	}
	if (nowRow > nextRow && nowColumn < nextColumn && !field[nowRow - 1][nowColumn + 1].isEmpty) {
		if (field[nowRow - 1][nowColumn + 1].isWhite != field[nowRow][nowColumn].isWhite) {
			field[nowRow - 1][nowColumn + 1].isEmpty = true;
			field[nowRow - 1][nowColumn + 1].space = EMPTY;
		}
	}
}

int main() {
	system("color F0");
	Checker** field = new Checker * [SIZE];
	for (int i = 0; i < SIZE; i++) {
		field[i] = new Checker[SIZE];
	}
	startingField(field);

	int numPlayer = 1;
	string firstPlayer, secondPlayer;
	cout << "First player name (red)" << endl;
	cin >> firstPlayer;
	cout << "Second player name (black)" << endl;
	cin >> secondPlayer;

	int nowRow, nowColumn;
	int nextRow, nextColumn;
	while (1) {
		showField(field);
		if (numPlayer % 2 != 0) {
			cout << firstPlayer << " turn" << endl;
		}
		else {
			cout << secondPlayer << " turn" << endl;
		}
		
		cout << "Choose fighting checker" << endl;
		cin >> nowRow >> nowColumn;
		while (!canMove(field, nowRow, nowColumn, numPlayer) && !canHitChecker(field, nowRow, nowColumn, numPlayer)) {
			cout << "This checker can't run now. Try another one" << endl;
			cin >> nowRow >> nowColumn;
		}

		cout << "Choose next position" << endl;
		cin >> nextRow >> nextColumn;
		while (!correctMove(field, nowRow, nowColumn, nextRow, nextColumn) && !enemyOnWayChecker(field, nowRow, nowColumn, nextRow, nextColumn)) {
			if (yourChecker(field, nowRow, nowColumn, numPlayer)) {
				cout << "This checker can't run like that. Try again" << endl;
			}
			else if (!yourChecker(field, nowRow, nowColumn, numPlayer)) {
				cout << "This is not your checker" << endl;
			}
			else {
				cout << "Too far distance" << endl;
			}
			cin >> nextRow >> nextColumn;
		}
		moveChecker(field, nowRow, nowColumn, nextRow, nextColumn);
		if (enemyOnWayChecker(field, nowRow, nowColumn, nextRow, nextColumn)) {
			kill(field, nowRow, nowColumn, nextRow, nextColumn);
		}
		numPlayer += 1;
	}

	for (int i = 0; i < SIZE; i++) {
		delete[] field[i];
	}
	delete[] field;
	return 0;
}