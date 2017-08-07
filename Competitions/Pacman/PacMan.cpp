#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class node {
public:
    int c,r;
    bool Visited;
    bool IsPacManQ;
    bool IsFoodQ;
    vector<node> AdjNode;
    node(int _c, int _r) {
        c = _c;
        r = _r;
        Visited = false;
        IsPacManQ = false;
        IsFoodQ = false;
    }

    bool operator == (const node& a) const {
        return c == a.c and r == a.r;
    } 
};


bool isValid(int c, int r, vector <string> _grid, int row, int col) {
	if (c >= 0 and r >= 0 and c < col and r < row and _grid[r][c] != '%') {
		return true;
	}
    return false;
}
vector<node> VisitVec;
vector<node> Graph;

void GenerateGraph(vector<string> _grid, int _pacman_c, int _pacman_r, int _c) {
    int _r = _grid.size();
    for (int i = 0; i < _grid.size(); i++) {
        for (int a = 0; a < _grid[i].length(); a++) {
            //node CounterNode(a,i);
            node *CounterNode = new node(a,i);
            Graph.push_back(*CounterNode);
            delete CounterNode
            if (isValid(a+1, i, _grid, _grid.size(), _grid[i].length())) {
                node *CounterNode = new node(a+1,i);
                Graph.back().AdjNode.push_back(*CounterNode);
                delete CounterNode;
            }
            if (isValid(a-1, i, _grid, _grid.size(), _grid[i].length())) {
                node *CounterNode = new node(a-1,i);
                Graph.back().AdjNode.push_back(*CounterNode);
                delete CounterNode;        
            }
            if (isValid(a, i+1, _grid, _grid.size(), _grid[i].length())) {
                node *CounterNode = new node(a,i+1);
                Graph.back().AdjNode.push_back(*CounterNode);
                delete CounterNode;            
            }
            if (isValid(a, i-1, _grid, _grid.size(), _grid[i].length())) {
                node *CounterNode = new node(a,i-1);
                Graph.back().AdjNode.push_back(*CounterNode);
                delete CounterNode; 
            }
            if (i == 8 && a == 3 || a == 8 && i == 3) {
            	cout << "YEAY" << endl;
            	cout << isValid(a+1, i, _grid, _grid.size(), _grid[i].length()) << endl;
            	cout << isValid(a-1, i, _grid, _grid.size(), _grid[i].length()) << endl;
            	cout << isValid(a, i+1, _grid, _grid.size(), _grid[i].length()) << endl;
            	cout << isValid(a, i-1, _grid, _grid.size(), _grid[i].length()) << endl;
            	cout << Graph.back().AdjNode.size() << endl;
            }
        }
        cout << endl;
    }
    /*cout << Graph.size() << endl;
*/  /*for (int i = 0; i < Graph.size(); i++) {
		cout << Graph[i].c << " " << Graph[i].r << endl;
		cout << Graph[i].AdjNode.size() << endl;
		cout << endl;
		cout << endl;
		cout << endl;
        if (Graph[i].AdjNode.size() > 0) {
            for (int a = 0; a < Graph[i].AdjNode.size(); a++) {
                cout << Graph[i].AdjNode[a].c << "  ";
                cout << Graph[i].AdjNode[a].r << "  ";
                cout << endl;
            }
        }
    }*/
    cout << endl;
}

bool CheckVisited(node &visitedQNode) {
	if (VisitVec.size() > 0) {
		for (int y = 0; y < VisitVec.size(); y++) {
			if (VisitVec[y].c == visitedQNode.c && VisitVec[y].r == visitedQNode.r) {
				return true;
			}
		}
	}
	return false;
}

void RecDFS(node &StartNode, node &TargetNode) {
	cout << StartNode.c << " " << StartNode.r << endl;
	cout << TargetNode.c << " " << TargetNode.r << endl;
	cout << StartNode.AdjNode.size() << endl;
	
    for (int i = 0; i < Graph.size(); ++i) {
        if (TargetNode.c == StartNode.c && TargetNode.r == StartNode.r) {
        	cout << "FOUND!" << endl;
            break;
        }
        if (CheckVisited(StartNode) == false && StartNode.AdjNode.size() > 0) {
        	VisitVec.push_back(StartNode);
            for (int a = 0; a < StartNode.AdjNode.size();a++) {
            	if (CheckVisited(StartNode.AdjNode[a]) == false) {
            		VisitVec.push_back(StartNode.AdjNode[a]);
                	RecDFS(StartNode.AdjNode[a], TargetNode);
            	}
            }
        	StartNode.Visited = true;
        }
    }
}

void dfs( int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> grid){
	cout << "Range: " << r <<" " << c << endl;
	cout << isValid(8,4,grid, r, c) << endl;
    /*bool logic = */

    //your logic here
    GenerateGraph(grid, pacman_c, pacman_r, c);
    /*cout << "Length is: " <<  << endl;*/
    node *PacNode = new node(1,1);
    node *FoodNode = new node(1,1);
    for (int a = 0; a < Graph.size(); a++) {
        if (Graph[a].r == pacman_r && Graph[a].c == pacman_c) {
            cout << "Found Pacman Node!" << endl;
            PacNode = &Graph[a];
        } else if (Graph[a].r == food_r && Graph[a].c == food_c) {
            cout << "Found Food Node!" << endl;
            FoodNode = &Graph[a];
        }
    }
    RecDFS(*PacNode, *FoodNode);
}
int main(void) {

    int r,c, pacman_r, pacman_c, food_r, food_c;
    
    cin >> pacman_r >> pacman_c;
    cin >> food_r >> food_c;
    cin >> r >> c;
    
    vector <string> grid;

    for(int i=0; i<r; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    dfs( r, c, pacman_r, pacman_c, food_r, food_c, grid);

    return 0;
}