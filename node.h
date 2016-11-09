#include <utility>
#include <vector>
#include <cmath>
#include <stack>
using namespace std;

const int rows = 3;
const int cols = 3;
int maxNum = 9;
int solutionArry[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

class node{
	private:
		node* left;
		node* right;
		node* up;
		node* down;
		int weight;
		int nodeDepth;
		int puzzle[rows][cols];
		bool Solution;
		bool lastLeft, lastRight, lastUp, lastDown;
		//function to find where the blank tile is. used to calculate where you can move in createing nodes.
		pair<int, int> findBlank(){
			for(int i = 0; i < rows;++i){
				for(int j = 0; j < cols; ++j){
					if(puzzle[i][j] == 0){
						return make_pair(i, j);
					}
				}
			}
		};
		//uses nested loops to determine which nodes are misplaced
		int misplacedTile(){
			int misplaced = 0;
			int position = 1;
			for(int i = 0; i < rows; ++i){
				for(int j = 0; j < cols; ++j){
					if(puzzle[i][j] != solutionArry[i][j] && (i + j) != 4){
						++misplaced;
					}
				}
			}
			return misplaced;
		};
		//calculates the manhatten distance with a nested loops. Keeps track of what row and col
		//that each number should be in and compares it to where it was found.
		int manhattenDistance(){
			int manhatten = 0;
			int R = 0;
			int C = 0;
			int i = 0;
			int j = 0;
			bool eq = false;
			for(int k = 1; k < maxNum; ++k){
				eq = false;
				for(i = 0; i < rows; ++i){
					for(j = 0; j < cols; ++j){
						if(puzzle[i][j] == solutionArry[R][C]) eq = true;
						if(eq) break;
					}
					if(eq) break;
				}
				if(i == rows) i = rows -1;
				if(j == cols) j = cols - 1;
				manhatten += (abs(i-R)+abs(j-C));
				if(C == (cols-1)){
					C = 0;
					++R;
				}
				else ++C;
			}
			return manhatten;
		};
		//old function to get the depth before the varriable was added
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
		//sets the varriable that keeps track of the last move so that it is not repeated
		void setLeft(){lastLeft = true;};
		void setRight(){lastRight = true;};
		void setUp(){lastUp = true;};
		void setDown(){lastDown = true;};
	public:
		//constructors for the nodes.
		node(){Solution = false;};
		node(int puz[][cols], int depth){
			for(int i = 0; i < rows; ++i){
				for(int j = 0;j < cols; ++j){
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
		//allows the weight to be set for the node
		void setWeight(int i){
			weight = i;
		};
		// another getter
		int getDepth(){
			return getDepth(-1, 0);
		}
		//recursive function to go through the tree and find the solution. When it finds it prints solution to initial puzzle
		bool traceSolution(stack<node*>* solutionStack){
			if(Solution){
				cout << "Solution at depth: " << nodeDepth << endl;
				solutionStack->push(this);
				return Solution;
			}
			bool solutionFound = false;
			if(left != NULL){
				solutionFound = left->traceSolution(solutionStack);
			}
			if(!solutionFound && right != NULL){
				solutionFound = right->traceSolution(solutionStack);
			}
			if(!solutionFound && up != NULL){
				solutionFound = up->traceSolution(solutionStack);
			}
			if(!solutionFound && down != NULL){
				solutionFound = down->traceSolution(solutionStack);
			}
			if(solutionFound){
				solutionStack->push(this);
			}
			return solutionFound;
		}
		//utiltiy function to print the current puzzle
		void printPuzzle(){
			for(int i = 0; i < rows; ++i){
				for(int j = 0; j < cols; ++j){
					cout << puzzle[i][j] << ' ';
				}
				cout << endl;
			}
		}
		//uses misplaced tile to tell if the nodes puzzle is a solution
		bool isSolution(){
			
			Solution = (misplacedTile() == 0);
			return Solution;
		}
		//the 4 create functions create nodes that will be added to the path. since there is not 
		//tree class in this implementation there is no tree class the just expands on the node
		node* createLeft(int type){
			pair<int, int> tmp = findBlank();
			if(tmp.second != 0 && !lastRight){
				int tmp2[rows][cols];
				for(int i = 0; i < rows; ++i){
					for(int j = 0; j < cols; ++j){
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
				int tmp2[rows][cols];
				for(int i = 0; i < rows; ++i){
					for(int j = 0; j < cols; ++j){
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
				int tmp2[rows][cols];
				for(int i = 0; i < rows; ++i){
					for(int j = 0; j < cols; ++j){
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
				int tmp2[rows][cols];
				for(int i = 0; i < rows; ++i){
					for(int j = 0; j < cols; ++j){
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
		//getters and setters for the varriables that might need to be acessed
		node* getLeft(){return left;};
		node* getRight(){return right;};
		node* getUp(){return up;};
		node* getDown(){return down;};
		int getWeight(){return weight;};
		int* getPuzzle(){return &puzzle[0][0];};
		int getPathDepth(){return nodeDepth;};
};
