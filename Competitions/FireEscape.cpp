#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

long long unsigned int FinalProduct = 1;
long long unsigned int FinalSumCounter = 0;

int findGap(vector<int> vec, int RangeInclusive) {
	int FinalCounter = 0;
	int k = 0;
	for (int i = 0; i < RangeInclusive; i++) {
	    if (vec[k] == i + 1) {
	        k++;
	    }
	    else if (vec[k] != i + 1) {
	        FinalCounter++;
	    }
	}
	return FinalCounter;
}

vector<int> EmployArr;
vector<int> DuplicateArr;

bool BoolCheckPeopleArrQ(int _EmployID) {
	if (EmployArr.size() > 0) {
		for (int i = 0; i < EmployArr.size(); ++i) {
			if (_EmployID == EmployArr[i]) {
				return true;
			}
		}
	} 
	return false;
}

class node {
public:
	vector<node> AdjNode;
	int EmployId;
	node(int _EmployId) {
		EmployId = _EmployId;
	}
	~node() {
		//EmployArr.erase(find(EmployArr.begin(),EmployArr.end(),EmployId));	
	}
};

vector<node> Graph;
vector<int> COUNTERDuplicates;

bool InVectorQ(int SearchIDD) {
	for (int i = 0; i < COUNTERDuplicates.size(); i++) {
		if (COUNTERDuplicates[i] == SearchIDD) {
			return true;
		}
	}
	return false;
}

bool searchDFS(node &StartNode, int SearchId, int QFindAppendId) {
	if (StartNode.EmployId == SearchId) {
		node *NewCounterNode = new node(QFindAppendId);
		StartNode.AdjNode.push_back(*NewCounterNode);
		delete NewCounterNode;
		return true;
	} else {
		for (int i = 0; i < StartNode.AdjNode.size(); i++) {
			return searchDFS(StartNode.AdjNode[i], SearchId, QFindAppendId);
		}
	}
	return false;
}

unsigned long long int searchDFSProduct(node &_StartNode) {
	for (int i = 0; i < _StartNode.AdjNode.size(); i++) {
		if (!InVectorQ(_StartNode.AdjNode[i].EmployId)) {
			DuplicateArr.push_back(_StartNode.AdjNode[i].EmployId);
			if (_StartNode.AdjNode.size() > 0) {
				FinalSumCounter+=_StartNode.AdjNode.size();
				//FinalSumCounter+=1;
			}
			return searchDFSProduct(_StartNode.AdjNode[i]);
		}
	}
	if (FinalSumCounter > 0) {
		return FinalSumCounter;
	} else {
		return 1;
	}
	/*if (FinalSumCounter > 0) {
		return FinalSumCounter;
	} else {
	}*/
}

/*void RemoveDuplicatesGraph(node &StartingNode) {
	for (int i = 0; i < _StartNode.AdjNode.size(); i++) {
		if (!InVectorQ(_StartNode.AdjNode[i].EmployId)) {
			DuplicateArr.push_back(_StartNode.AdjNode[i].EmployId);
			
			return searchDFSProduct(_StartNode.AdjNode[i]);
		}
	}
}*/

int main() {
	int NumEmploy = 0;
	int NumRelations = 0;
	cin >> NumEmploy >> NumRelations;
	for (int i = 0; i < NumRelations; ++i) {
		int Person1 = 0;
		int Person2 = 0;
		cin >> Person1 >> Person2;
		if(find(EmployArr.begin(), EmployArr.end(), Person1) == EmployArr.end()) {
			EmployArr.push_back(Person1);
		} 
		if(find(EmployArr.begin(), EmployArr.end(), Person2) == EmployArr.end()) {
			EmployArr.push_back(Person2);
		}

		if (Graph.size() > 0) {
			if (!searchDFS(Graph.back(), Person1, Person2)) {
				Graph.push_back(Person2);
			}
			if (!searchDFS(Graph.back(), Person2, Person1)) {
				Graph.push_back(Person1);
			}
		} else {
            node *FirstNode = new node(Person1);
            Graph.push_back(*FirstNode);
            delete FirstNode;
			//----------------------------------------
            node *FirstNodeChild = new node(Person2);
			Graph.back().AdjNode.push_back(*FirstNodeChild);
            delete FirstNodeChild;
		}
	}


	int MaxNumPath = Graph.size() + findGap(EmployArr, NumEmploy);
	cout << endl;
	for (int i = 0; i < Graph.size(); i++) {
		FinalSumCounter = 1;
		cout << FinalProduct << " ";
		FinalProduct = FinalProduct*searchDFSProduct(Graph[i]);
		cout << FinalProduct << " ";
	}
	cout << endl;
	cout << MaxNumPath << " ";
	cout << FinalProduct << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	//cout << Graph.size() << endl;
	cout << Graph[0].AdjNode.size() << endl;
	cout << Graph[1].AdjNode.size() << endl;
	return 0;
}