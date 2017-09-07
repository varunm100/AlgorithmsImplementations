#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

void SolveFinal(int NumNodes, int StartNode, const vector<list<int>>& edges, const int EdgeWeight) {
    vector<int> DistArr(NumNodes + 1, -1);
    queue<int> q;
    DistArr[StartNode] = 0;
    q.push(StartNode);

    while (!q.empty()) {
        int tempNode = q.front();
        q.pop();
        for (auto node : edges[tempNode]) {
            if (DistArr[node] == -1) {
                DistArr[node] = DistArr[tempNode] + EdgeWeight;
                q.push(node);
            }
        }
    }

    for (int i = 1; i < DistArr.size(); i++) {
        if (DistArr[i] != 0)
            cout << DistArr[i] << " ";
    }
    cout << endl;
}

int main() {
    int NumTests;
    cin >> NumTests;

    for (int i = 0; i < NumTests; i++) {
        int NumNodes, NumEdges;
        cin >> NumNodes;
        cin >> NumEdges;
        vector<list<int>> edges(NumNodes + 1);
        for (int j = 0; j < NumEdges; j++) {
            int NodeOne, NodeTwo;
            cin >> NodeOne >> NodeTwo;
            edges[NodeOne].push_back(NodeTwo);
            edges[NodeTwo].push_back(NodeOne);
        }

        int StartNode;
        cin >> StartNode;
        SolveFinal(NumNodes, StartNode, edges, 6);
    }

    return 0;
}