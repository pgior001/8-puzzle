#include <utility>
#include <vector>
#include <cmath>
using namespace std;

class node{
	private:
		node* left;
		node* right;
		node* up;
		node* down;
		int weight;
		int nodeDepth;
		int puzzle[3][3];
		bool Solution;
		bool lastLeft, lastRight, lastUp, lastDown;
		pair<int, int> findBlank(){
			for(int i = 0; i < 3;++i){
				for(int j = 0; j < 3; ++j){
					if(puzzle[i][j] == 0){
						return make_pair(i, j);
					}
				}
			}
		};
		int misplacedTile(){
			int misplaced = 0;
			int position = 1;
			for(int i = 0; i < 3; ++i){
				for(int j = 0; j < 3; ++j){
					if(puzzle[i][j] != position && (i + j) != 4){
						++misplaced;
					}
					++position;
				}
			}
			return misplaced;
		};
		int manhattenDistance(){
			int manhatten = 0;
			int R = 0;
			int C = 0;
			int i = 0;
			int j = 0;
			bool eq = false;
			for(int k = 1; k < 9; ++k){
				eq = false;
				for(i = 0; i < 3; ++i){
					for(j = 0; j < 3; ++j){
						if(puzzle[i][j] == k) eq = true;
						if(eq) break;
					}
					if(eq) break;
				}
				if(i == 3) i = 2;
				if(j == 3) j = 2;
				manhatten += (abs(i-R)+abs(j-C));
				if(C == 2){
					C = 0;
					++R;
				}
				else ++C;
			}
			return manhatten;
		};
		int getDepth(int depth, int deepest){
			++depth;
			int tmp = 0;
			if(depth > deepest) deepest = depth;
			if(left != NULL) tmp = left->getDepth(depth, deepest);
			if(tmp > deepest) deepest = tmp;
			if(right != NULL) tmp = right->getDepth(depth, deepest);
			if(tmp > deepest) deepest = tmp;
			if(up != NULL) tmp = up->getDepth(depth, deepest);
			if(tmp > deepest) deepest = tmp;
			if(down != NULL) tmp = down->getDepth(depth, deepest);
			if(tmp > deepest) deepest = tmp;
			return deepest;
		}
		void setLeft(){lastLeft = true;};
		void setRight(){lastRight = true;};
		void setUp(){lastUp = true;};
		void setDown(){lastDown = true;};
	public:
		node(){Solution = false;};
		node(int puz[][3], int depth){
			for(int i = 0; i < 3; ++i){
				for(int j = 0;j < 3; ++j){
					puzzle[i][j] = puz[i][j];
				}
			}
			left = NULL;
			right = NULL;
			up = NULL;
			down = NULL;
			weight = 0;
			nodeDepth = depth;
			Solution = lastLeft = lastRight = lastUp = lastDown = false;
		};
		void setWeight(int i){
			weight = i;
		};
		int getDepth(){
			return getDepth(-1, 0);
		}
		bool printSolution(){
			if(Solution){
				cout << "Solution at depth: " << nodeDepth << endl;
				printPuzzle();
				cout << endl;
				return Solution;
			}
			bool solutionFound = false;
			if(left != NULL){
				solutionFound = left->printSolution();
			}
			if(!solutionFound && right != NULL){
				solutionFound = right->printSolution();
			}
			if(!solutionFound && up != NULL){
				solutionFound = up->printSolution();
			}
			if(!solutionFound && down != NULL){
				solutionFound = down->printSolution();
			}
			if(solutionFound){
				printPuzzle();
				cout << endl;
			}
			return solutionFound;
		}
		void printPuzzle(){
			for(int i = 0; i < 3; ++i){
				for(int j = 0; j < 3; ++j){
					cout << puzzle[i][j] << ' ';
				}
				cout << endl;
			}
		}
		bool isSolution(){
			
			Solution = (misplacedTile() == 0);
			return Solution;
		}
		node* createLeft(int type){
			pair<int, int> tmp = findBlank();
			if(tmp.second != 0 && !lastRight){
				int tmp2[3][3];
				for(int i = 0; i < 3; ++i){
					for(int j = 0; j < 3; ++j){
						tmp2[i][j] = puzzle[i][j];
					}
				}
				swap(tmp2[tmp.first][tmp.second], tmp2[tmp.first][tmp.second - 1]);
				if(type == 1){
					node* child = new node(tmp2, nodeDepth+1);
					left = child;
				}
				else if(type == 2){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->misplacedTile());
					left = child;
				}
				else if(type == 3){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->manhattenDistance());
					left = child;
				}
				left->setLeft();
			}
			return left;
		};
		node* createRight(int type){
			pair<int, int> tmp = findBlank();
			if(tmp.second != 2 && !lastLeft){
				int tmp2[3][3];
				for(int i = 0; i < 3; ++i){
					for(int j = 0; j < 3; ++j){
						tmp2[i][j] = puzzle[i][j];
					}
				}
				swap(tmp2[tmp.first][tmp.second], tmp2[tmp.first][tmp.second + 1]);
				node* child;
				if(type == 1){
					node* child = new node(tmp2, nodeDepth+1);
					right = child;
				}
				else if(type == 2){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->misplacedTile());
					right = child;
				}
				else if(type == 3){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->manhattenDistance());
					right = child;
				}
				right->setRight();
			}
			return right;
		};
		node* createUp(int type){
			pair<int, int> tmp = findBlank();
			if(tmp.first != 0 && !lastDown){
				int tmp2[3][3];
				for(int i = 0; i < 3; ++i){
					for(int j = 0; j < 3; ++j){
						tmp2[i][j] = puzzle[i][j];
					}
				}
				swap(tmp2[tmp.first][tmp.second], tmp2[tmp.first - 1][tmp.second]);
				if(type == 1){
					node* child = new node(tmp2, nodeDepth+1);
					up = child;
				}
				else if(type == 2){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->misplacedTile());
					up = child;
				}
				else if(type == 3){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->manhattenDistance());
					up = child;
				}
				up->setUp();
			}
			return up;
		};
		node* createDown(int type){
			pair<int, int> tmp = findBlank();
			if(tmp.first != 2 && !lastUp){
				int tmp2[3][3];
				for(int i = 0; i < 3; ++i){
					for(int j = 0; j < 3; ++j){
						tmp2[i][j] = puzzle[i][j];
					}
				}
				swap(tmp2[tmp.first][tmp.second], tmp2[tmp.first + 1][tmp.second]);
				if(type == 1){
					node* child = new node(tmp2, nodeDepth+1);
					down = child;
				}
				else if(type == 2){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->misplacedTile());
					down = child;
				}
				else if(type == 3){
					node* child = new node(tmp2, nodeDepth+1);
					child->setWeight(child->manhattenDistance());
					down = child;
				}
				down->setDown();
			}
			return down;
		}
		node* getLeft(){return left;};
		node* getRight(){return right;};
		node* getUp(){return up;};
		node* getDown(){return down;};
		int getWeight(){return weight;};
		int* getPuzzle(){return &puzzle[0][0];};
		int getPathDepth(){return nodeDepth;};
};
