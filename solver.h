#include <queue>
#include <vector>
using namespace std;

//defined comparator for the priority queue
class Compare{
	public:
		bool operator()(node* A, node* B){
			return (A->getWeight()+A->getPathDepth()) > (B->getWeight()+B->getPathDepth());
		}
};

//uses a priority queue with the manhatten distance as weight and pre defined comparator to
//expand the ndoes in order
void manhattenSearch(node* root, int type){
	node* curr = root;
	priority_queue<node*, vector<node*>, Compare> ready;
	node* tmp;
	int expanded = 0;
	while(!curr->isSolution()){
		++expanded;
		tmp = curr->createLeft(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createRight(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createUp(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createDown(type);
		if(tmp != NULL) ready.push(tmp);
		if(ready.top() != NULL){
			curr = ready.top();
			ready.pop();
		}
		else break;
		if(expanded % 1000 && root->getDepth() >= 40) break;
	}
	if(curr->isSolution()){
		cout << "number of nodes expanded " << expanded << endl;
		cout << "solution" << endl;
		root->printSolution();
	}
	else cout << "failed to find solution by a depth of 40. Aborting." << endl;
	return;
}

//same as above but misplaced tile weight
void misplacedTileSearch(node* root, int type){
	node* curr = root;
	priority_queue<node*, vector<node*>, Compare> ready;
	node* tmp;
	int expanded = 0;
	while(!curr->isSolution()){
		++expanded;
		tmp = curr->createLeft(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createRight(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createUp(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createDown(type);
		if(tmp != NULL) ready.push(tmp);
		if(ready.top() != NULL){
			curr = ready.top();
			ready.pop();
		}
		else break;
		if((expanded % 1000 == 0) && (root->getDepth() >= 40)) break;
	}
	if(curr->isSolution()){
		cout << "number of nodes expanded " << expanded << endl;
		root->printSolution();
	}
	else cout << "failed to find solution by a depth of 40. Aborting" << endl;
	return;
}

//uses a fifo queue to expand nodes left right up down order
void uniformCostSearch(node* root, int type){
	node* curr = root;
	queue<node*> ready;
	node* tmp;
	long long expanded = 0;
	while(!curr->isSolution()){
		++expanded;
		tmp = curr->createLeft(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createRight(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createUp(type);
		if(tmp != NULL) ready.push(tmp);
		tmp = curr->createDown(type);
		if(tmp != NULL) ready.push(tmp);
		if(ready.front() != NULL){
			curr = ready.front();
			ready.pop();
		}
		else break;
		if((expanded % 1000000 == 0) && (root->getDepth() >= 40)) break;
	}
	if(curr->isSolution()){
		cout << "number of nodes expanded " << expanded << endl;
		cout << "solution" << endl;
		root->printSolution();
	}
	else cout << "failed to find solution by a depth of 40. Aborting. nodes expanded: " << expanded << endl;
	return;
}
