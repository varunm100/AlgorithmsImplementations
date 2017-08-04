#include <iostream>
#include <vector>
#include <stack>

using namespace std;


class node {
public:
    int c,r;
    node(int _c, int _r) {
        c = _c;
        r = _r;
    }

    bool operator == (const node& a) const {
        return c == a.c and r == a.r;
    } 
};


bool isValid(int c, int r, vector <string> _grid, int row, int col) {
    return c >= 0 and r >= 0 and c < col and r < row and _grid[r][c] != '%';
}
vector<node> Graph;

void GenerateGraph(vector<string> _grid, int _pacman_c, int _pacman_r, int _c) {
    int _r = _grid.size();
    for (int i = 0; i < _grid.size(); i++) {
        for (int a = 0; a < _grid[i].length(); a++) {
            if (isValid(a, i, _grid, _grid.size(), _grid[i].length())) {
                cout << "True" << " ";
            } else {
                cout << "False" << " ";
            }
        }
        cout << endl;
    }
    //Convert Graph to char vector


}

void dfs( int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> grid){
    //rour logic here
    GenerateGraph(grid, pacman_c, pacman_r, pacman_c);
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