#include <iostream>
#include <string>
#include <Windows.h>
#include <cmath>

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

void moveChecker(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	field[nextRow][nextColumn] = field[nowRow][nowColumn];
	field[nowRow][nowColumn].isEmpty = true;
	field[nowRow][nowColumn].space = EMPTY;
}

bool correctMove(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {

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

bool yourChecker(Checker field[SIZE][SIZE], int row, int column, int numPlayer) {
	if (numPlayer % 2 == field[row][column].isWhite) {
		return true;
	}
	return false;
}

bool canMove(Checker field[SIZE][SIZE], int row, int column, int numPlayer) {
	if (yourChecker(field, row, column, numPlayer) && !field[row][column].isEmpty) {
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

bool enemyOnWayChecker(Checker field[SIZE][SIZE], int nowRow, int nowColumn, int nextRow, int nextColumn) {
	if (abs(nowRow - nextRow) == 2 && abs(nowColumn - nextColumn) == 2 && !field[nowRow][nowColumn].isEmpty) {
		if (nextColumn >= 0 && nextRow >= 0 && nextColumn < SIZE && nextRow < SIZE) {
			if (field[nextRow][nextColumn].isEmpty) {

				for (int i = nowRow - 1; i <= nowRow + 1; i += 2) {
					for (int j = nowColumn - 1; j <= nowColumn + 1; j += 2) {
						if (!field[i][j].isEmpty) {
							if (field[nowRow][nowColumn].isWhite != field[i][j].isWhite) {
								return true;
							}
						}
					}
				}

			}
		}
	}
	return false;
}

bool canHitChecker(Checker field[SIZE][SIZE], int row, int column, int numPlayer) {
	if (field[row][column].isEmpty) {
		return false;
	}
	for (int i = row - 2; i <= row + 2; i += 4) {
		for (int j = column - 2; j <= column + 2; j += 4) {
			if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
				if (field[row][column].isWhite == numPlayer % 2) {
					if (enemyOnWayChecker(field, row, column, i, j)) {
						return true;
					}
				}
			}
		}
	}
	return false;
} 



bool isCanHit(Checker field[SIZE][SIZE], int row, int column, int nextRow, int nextColumn, bool* b, bool isHit) { //checker position
	//if (!field[nowRow][nowColumn].isEmpty)
	*b = false;
	for (int i = row - 2; i <= row + 2; i += 4) {
		for (int j = column - 2; j <= column + 2; j += 4) {
			if ((i >= 0 && j >= 0 && i < SIZE && j < SIZE) && field[i][j].isEmpty) {
				int k1 = i < row ? row - 1 : row + 1;
				int k2 = j < column ? column - 1 : column + 1;
				if ((!field[k1][k2].isEmpty) && (field[k1][k2].isWhite != field[row][column].isWhite) ) {
					*b = true;
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

bool shouldHit(Checker field[SIZE][SIZE], int numPlayer) {
	bool temp1 = true;
	for (int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if (!field[i][j].isEmpty && numPlayer%2 == field[i][j].isWhite) {
				if (isCanHit(field, i, j, 0, 0, &temp1, false)) {
					return true;
				}
			}
		}
	}
	return false;
}


int main() {
	system("color F0");
	Checker field[SIZE][SIZE];
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
		
		bool temp = true;
		
		if (shouldHit(field, numPlayer)) {
			cout << "One checker should hit. Choose that checker" << endl;
			cin >> nowRow >> nowColumn;
			nowRow -= 1;
			nowColumn -= 1;
			while (!isCanHit(field, nowRow, nowColumn, 0, 0, &temp, false)) {
				cout << "This checker can't hit now. Try another one!" << endl;
				cin >> nowRow >> nowColumn;
				nowRow -= 1;
				nowColumn -= 1;
			}
		}
		else {
			cout << "Choose fighting checker" << endl;
			cin >> nowRow >> nowColumn;
			nowRow -= 1;
			nowColumn -= 1;
			while (!canMove(field, nowRow, nowColumn, numPlayer) && !canHitChecker(field, nowRow, nowColumn, numPlayer)) {
				cout << "This checker can't run now. Try another one" << endl;
				cin >> nowRow >> nowColumn;
				nowRow -= 1;
				nowColumn -= 1;
			}
		}


		cout << "Choose next position" << endl;

		bool b = true;
		do {
			b = true;
			cin >> nextRow >> nextColumn;
			nextRow -= 1;
			nextColumn -= 1;
		
			if (!correctMove(field, nowRow, nowColumn, nextRow, nextColumn) && !enemyOnWayChecker(field, nowRow, nowColumn, nextRow, nextColumn)) {
				if (yourChecker(field, nowRow, nowColumn, numPlayer)) {
					cout << "This checker can't run like that. Try again" << endl;
				}
				else if (!yourChecker(field, nowRow, nowColumn, numPlayer)) {
					cout << "This is not your checker" << endl;
				}
				else {
					cout << "Too far distance" << endl;
				}
				
				continue;	
			}
			bool b1 = true;
			if (isCanHit(field, nowRow, nowColumn, nextRow, nextColumn, &b1, true)) {
				// move - all OK
				break;
			}
			else {
				if (b1 == true) {
					// считать заново координаты
					continue;
				}
				else {
					// можем ходить
					break;
				}
			}
			
			b = false;
		}while (b);

		moveChecker(field, nowRow, nowColumn, nextRow, nextColumn);
		numPlayer += 1;
	}

	for (int i = 0; i < SIZE; i++) {
		delete[] field[i];
	}
	delete[] field;
	return 0;
}