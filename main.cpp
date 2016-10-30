#include <iostream>
#include "node.h"
#include "solver.h"
using namespace std;

int main(){
	char tmp;
	int toSolve[3][3] = {{1, 2, 3}, {4, 8 , 0}, {7, 6, 5}};
	cout << "Welcome to Preston Giorgianni's 8-puzzle solver." << endl;
	cout << "Type 1 to use default puzzle, or 2 to enter your own." << endl;
	cin >> tmp;
	
	while(tmp != '2' && tmp!= '1'){
		cout << tmp << " is not a valid entry." << endl;
		cout << "Type 1 to use default puzzle, or 2 to enter your own." << endl;
		cin >> tmp;
	}
	if(tmp == '2'){
		cout << "Enter your puzzle, use zero to represent the blank." << endl;
		cout << "Enter your first row, use spaces between numbers.	";
		cin >> toSolve[0][0];
		cin >> toSolve[0][1];
		cin >> toSolve[0][2];
		cout << "Enter your second row, use spaces between numbers.	";
		cin >> toSolve[1][0];
		cin >> toSolve[1][1];
		cin >> toSolve[1][2];
		cout << "Enter your third row, use spaces between numbers.	";
		cin >> toSolve[2][0];
		cin >> toSolve[2][1];
		cin >> toSolve[2][2];
	}
	node* root = new node(toSolve, 0);

	cout << "Enter your choice of algorithum." << endl;
	cout << "	1. Uniform search cost." << endl;
	cout << " 	2. A* with Misplaced tile heuristic." << endl;
	cout << "	3. A* with Manhattan distance heuristic." << endl;
	cin >> tmp;

	while(tmp != '2' && tmp!= '1' && tmp != '3'){
		cout << tmp << " is not a valid entry." << endl;
		cout << "	1. Uniform search cost." << endl;
		cout << " 	2. A* with Misplaced tile heuristic." << endl;
		cout << "	3. A* with Manhattan distance heuristic." << endl;
		cin >> tmp;
	}

	cout << endl << "Initial state." << endl;
	root->printPuzzle();
	if(tmp == '1'){uniformCostSearch(root, 1);}
	else if(tmp == '2'){misplacedTileSearch(root, 2);}
	else if(tmp == '3'){manhattenSearch(root, 3);}


	return 0;
};
