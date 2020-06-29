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

bool isCanHit(Checker field[SIZE][SIZE], int row, int column, int nextRow, int nextColumn, bool isHit) { //checker position
	//if (!field[nowRow][nowColumn].isEmpty)
	//*b = false;
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
				if (isCanHit(field, i, j, -1, -1, false)) {
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

bool correctMoveChecker(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {

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

void moveChecker(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	field[nextRow][nextColumn] = field[nowRow][nowColumn];
	field[nowRow][nowColumn].isEmpty = true;
	field[nowRow][nowColumn].space = EMPTY;
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

	bool isHit = false;
	while (!out(field)) {
		showField(field);
		isHit = false;

		if (numPlayer % 2 != 0) {
			cout << firstPlayer << " turn!" << endl;
		}
		else {
			cout << secondPlayer << " turn!" << endl;
		}

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
		}
		moveChecker(field, nowRow, nowColumn, nextRow, nextColumn);
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