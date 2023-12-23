/*
* README at the end 
* testcases at the end
*/
#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <vector>
#include <time.h>
using namespace std;

void getSudoku(vector<vector<int>>& S, int& dim);
bool InBox(const vector<vector<int>>& S, int row, int col, int num, int d);
bool InRow(const vector<vector<int>>& S, int row, int num, int dim);
bool InColumn(const vector<vector<int>>& S, int col, int num, int dim);
bool Validator(const vector<vector<int>>& S, int row, int col, int num, int dim);
void print(vector<vector<int>>& S);


/*
* Will get input from user to populate S and get dim size
* arguements: vector<vector<int>> &S and int &dim
*/
void getSudoku(vector<vector<int>> &S, int &dim) {
	//usage
	cout << "Enter Sudoku Dimension (perfect square): ";
	cin >> dim;

	//to know if this is a real puzzle
	bool real(false);

	int row = dim;
	int col = dim;
	cout << "Fill out Sudoku, for blanks enter 0." << endl;
	cout << "Your biggest number entered should be: " << dim << endl;

	S.resize(dim + 1);
	for (int i = 0; i <= dim; i++) {
		S[i].resize(dim); 
	}

	//loop to get user information
	for (int i(0); i < row; i++) {
		for (int j(0); j < col; j++) {
			cin >> S[i][j];
			while (S[i][j] > dim || S[i][j] < 0) {
				cout << "Invalid, try again: ";
				cin >> S[i][j];
			}
			if (S[i][j] == 0) { real = true; }

		}
	}
	
	//if puzzle is already filled out
	if (!real) {
		cout << "Sudoku is already filled out" << endl;
		exit(1);
	}


}

/*
* arguements: 
*	S - 2d vector holding matrix
*	row - the row the box belongs to 
*	col - the column the box belongs to 
*	num - the number we are checking
*	d = sqrt(dim)
*/
bool InBox(const vector<vector<int>> &S, int row, int col, int num, int d) {
	for (int r = 0; r < d; r++) {
		for (int c = 0; c < d; c++) {
			if (S[row + r][col + c] == num) {
				return true;
			}
		}
	}
	return false;
}

/*
* arguements:
*	S - 2d vector holding matrix
*	row - the current row we are in
*	num - the number we are checking
*	dim - dimension
*/
bool InRow(const vector<vector<int>> &S, int row, int num, int dim) {
	for (int col(0); col < dim; col++ ) {
		if (num == S[row][col]) {
			return true;
		}
	}
	return false;
}

/*
* arguements:
*	S - 2d vector holding matrix
*	col - the current column we are in
*	num - the number we are checking
*	dim - dimension
*/
bool InColumn(const vector<vector<int>> &S, int col, int num, int dim) {
	for (int row(0); row < dim; row++) {
		if (num == S[row][col]) {
			return true;
		}
	}
	return false;
}

/* will return false if it is a valid number - means that num is not present in col/row/box */
/*
* arguements:
*	S - 2d vector holding matrix
*	row - the current row we are in
*	col - the current column we are in
*	num - the number we are checking
*	dim - dimension
*/
bool Validator(const vector<vector<int>> &S, int row, int col, int num, int dim) {
	int d = sqrt(dim);
	return (InBox(S, row - (row % d), col - (col % d), num, d) || InColumn(S, col, num, dim) || InRow(S, row, num, dim));
}

/*
* arguements:
*	S - 2d vector holding matrix
*	row - 0
*	col - 0
*	dim - dimension
*/
bool SudokuSolver(vector<vector<int>>& S, int row, int col, const int dim) {

	if (row == dim - 1 && col == dim) { // base case
		return true;
	}
	//resetting the values
	if (col == dim) {
		col = 0;
		row++;
	}
	//if the square we are at is not 0
	//recursively call SudokuSolver
	if (S[row][col] != 0) {
		return SudokuSolver(S, row, col+1, dim);
	}

	//valid numbers and create branch
	for (int num(1); num <= dim; num++) {	
		if (!Validator(S, row, col, num, dim)) {  //means number is vaild
			S[row][col] = num;
			if (SudokuSolver(S, row, col + 1, dim)) {
				return true;
			}
		}
		S[row][col] = 0;
	}
	return false;
}

//Print the matrix 
void print(vector<vector<int>>& S) {
	cout << "------------------\n";
	for (int i(0); i < (int)S.size() - 1; i++) {
		for (int j(0); j < (int)S.size() - 1; j++) {
			cout << S[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {

	int dim(0);
	vector<vector<int>> S;
	getSudoku(S, dim);
	cout << "loading...\n";
	SudokuSolver(S, 0, 0, dim);
	print(S);
	
}

/* README
HOW TO USE:
enter dimension, it should be a perfect square
	dim = 4, 9, 16, 25, 36, ...

enter values to populate S 
	- S is the matrix that holds the sudoku puzzle
	- blanks are represented by 0
	- largest value should be dim
	- enter a total of dim x dim numbers
*/


/*
input:
16
0 2 3 4 0 6 7 8 9 10 0 12 13 14 15 0
5 0 7 8 1 0 3 4 13 14 0 16 9 0 11 12
0 10 11 12 13 0 15 16 1 2 0 4 5 6 0 8
0 14 15 0 9 10 11 12 5 6 7 0 1 2 3 0
2 1 4 3 6 0 8 7 10 0 0 0 14 13 16 15
0 5 8 7 2 1 4 3 0 13 16 15 0 9 12 0
0 9 12 0 14 13 16 15 2 1 4 3 6 5 0 0
14 0 16 15 10 0 0 11 6 5 0 7 2 1 4 3
3 0 1 2 7 0 5 6 11 12 0 10 15 16 0 14
0 8 5 6 3 4 1 2 0 16 13 0 11 12 9 0
0 12 9 10 0 16 13 14 0 4 1 2 7 8 5 0
15 0 13 14 11 0 9 10 7 0 0 6 3 4 1 2
0 3 2 0 8 7 0 5 12 11 10 9 16 15 14 0
8 7 6 5 4 0 0 1 16 0 0 13 12 11 10 9
12 11 10 9 16 0 14 13 4 0 0 1 8 7 0 5
0 15 14 0 12 11 10 9 8 7 6 5 0 3 2 0


output:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
5 6 7 8 1 2 3 4 13 14 15 16 9 10 11 12
9 10 11 12 13 14 15 16 1 2 3 4 5 6 7 8
13 14 15 16 9 10 11 12 5 6 7 8 1 2 3 4
2 1 4 3 6 5 8 7 10 9 12 11 14 13 16 15
6 5 8 7 2 1 4 3 14 13 16 15 10 9 12 11
10 9 12 11 14 13 16 15 2 1 4 3 6 5 8 7
14 13 16 15 10 9 12 11 6 5 8 7 2 1 4 3
3 4 1 2 7 8 5 6 11 12 9 10 15 16 13 14
7 8 5 6 3 4 1 2 15 16 13 14 11 12 9 10
11 12 9 10 15 16 13 14 3 4 1 2 7 8 5 6
15 16 13 14 11 12 9 10 7 8 5 6 3 4 1 2
4 3 2 1 8 7 6 5 12 11 10 9 16 15 14 13
8 7 6 5 4 3 2 1 16 15 14 13 12 11 10 9
12 11 10 9 16 15 14 13 4 3 2 1 8 7 6 5
16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

*/

/*
input:
4
1 0 3 4
3 4 1 2
0 1 4 0
4 0 2 1

output:
1 2 3 4
3 4 1 2
2 1 4 3
4 3 2 1

*/



/*
input
9
0 0 5 0 3 0 0 0 6
0 0 0 8 0 0 0 0 0
0 1 0 0 0 0 3 2 7
2 9 0 0 4 0 0 0 0
0 0 0 0 0 0 0 0 9
0 0 0 0 1 6 0 0 0
0 5 0 3 8 0 9 7 0
3 0 0 0 0 0 8 0 0
0 2 0 0 0 0 1 0 0

output:
9 7 5 2 3 1 4 8 6
6 3 2 8 7 4 5 9 1
8 1 4 6 9 5 3 2 7
2 9 1 7 4 3 6 5 8
4 6 3 5 2 8 7 1 9
5 8 7 9 1 6 2 4 3
1 5 6 3 8 2 9 7 4
3 4 9 1 5 7 8 6 2
7 2 8 4 6 9 1 3 5


/*
input:
9
8 0 0 0 0 3 7 1 0
2 0 3 1 4 0 0 0 8
4 0 1 7 8 0 3 0 0 
5 1 9 0 7 0 0 0 0 
0 3 0 0 0 1 4 9 7
0 2 0 0 0 9 0 3 0
0 0 0 6 0 7 0 0 5
0 5 0 4 0 2 0 6 9
1 4 0 0 5 0 2 0 0 

output:
8 6 5 2 9 3 7 1 4
2 7 3 1 4 6 9 5 8
4 9 1 7 8 5 3 2 6
5 1 9 3 7 4 6 8 2
6 3 8 5 2 1 4 9 7
7 2 4 8 6 9 5 3 1
9 8 2 6 3 7 1 4 5
3 5 7 4 1 2 8 6 9
1 4 6 9 5 8 2 7 3
*/


/*
input
16
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

output:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
5 6 7 8 1 2 3 4 13 14 15 16 9 10 11 12
9 10 11 12 13 14 15 16 1 2 3 4 5 6 7 8
13 14 15 16 9 10 11 12 5 6 7 8 1 2 3 4
2 1 4 3 6 5 8 7 10 9 12 11 14 13 16 15
6 5 8 7 2 1 4 3 14 13 16 15 10 9 12 11
10 9 12 11 14 13 16 15 2 1 4 3 6 5 8 7
14 13 16 15 10 9 12 11 6 5 8 7 2 1 4 3
3 4 1 2 7 8 5 6 11 12 9 10 15 16 13 14
7 8 5 6 3 4 1 2 15 16 13 14 11 12 9 10
11 12 9 10 15 16 13 14 3 4 1 2 7 8 5 6
15 16 13 14 11 12 9 10 7 8 5 6 3 4 1 2
4 3 2 1 8 7 6 5 12 11 10 9 16 15 14 13
8 7 6 5 4 3 2 1 16 15 14 13 12 11 10 9
12 11 10 9 16 15 14 13 4 3 2 1 8 7 6 5
16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

*/



/*
input:
9
0 7 5 3 9 6 0 0 0
7 0 0 0 5 0 2 0 9
9 6 8 0 0 0 0 5 7 
4 3 0 6 0 0 8 1 0 
6 0 0 5 4 3 0 0 0
0 0 9 1 0 0 6 0 3
0 0 7 0 0 5 0 2 6
0 9 6 0 0 2 0 3 0
5 0 0 0 6 1 0 7 0

output:
0 7 5 3 9 6 0 0 0
7 0 0 0 5 0 2 0 9
9 6 8 0 0 0 0 5 7
4 3 0 6 0 0 8 1 0
6 0 0 5 4 3 0 0 0
0 0 9 1 0 0 6 0 3
0 0 7 0 0 5 0 2 6
0 9 6 0 0 2 0 3 0
5 0 0 0 6 1 0 7 0

*/


