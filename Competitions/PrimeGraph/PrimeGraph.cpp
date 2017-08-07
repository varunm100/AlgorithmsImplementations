#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unordered_map>
#include <string>

using namespace std;

vector<int> _CountComb;
vector<int> AllCombs;
vector<int> VectorAllCombs;
unordered_map<string, int> AllDisMap;

int TotalNumlCombs = 0;
int PrimePoss = 0;

struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
 
struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
struct MinHeapNode
{
    int  v;
    int dist;
};
 
struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
 
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

void printArr(int dist[], int n)
{
    string EncodedDis;
    string EncodedDisRev;
    for (int i = 1; i < n; ++i) {
        EncodedDis = "";
        EncodedDis = to_string(dist[1]) + to_string(i);
        EncodedDisRev = "";
        EncodedDisRev = to_string(i) + to_string(dist[1]);
        if (AllDisMap.count(EncodedDis) <= 0 && AllDisMap.count(EncodedDisRev) <= 0) {
            if (to_string(dist[1]) == to_string(i)) {
                AllDisMap.emplace(EncodedDis, 0);
            } else {
                AllDisMap.emplace(EncodedDis, dist[i]+1);
            }
        }
    }
}

void dijkstra(struct Graph* graph, int src)
{
    int V = graph->V;
    int dist[V];
    struct MinHeap* minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;
    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
                                          pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    printArr(dist, V);
}

bool isPrime(int n) {
    if (n <= 1)  {
        return false;
    }
    if (n <= 3)  {
        return true;
    }
    if (n%2 == 0 || n%3 == 0) return false;
    for (int i=5; i*i<=n; i=i+6){
        if (n%i == 0 || n%(i+2) == 0){
           return false;
        }
    }
    return true;
}

void AddToCounter(vector<int>& v) {
    string _FinalString = "";
    string _FinalStringRev = "";
    if (v.size() >= 2) {
        int num = 0;
        TotalNumlCombs++;
        _FinalString = to_string(v[0]) + to_string(v[1]);
        _FinalStringRev = to_string(v[1]) + to_string(v[2]);
        if (AllDisMap.count(_FinalString) > 0) {
            num = AllDisMap[_FinalString];
            num = abs(num);
        } else if (AllDisMap.count(_FinalStringRev) > 0) {
            num = AllDisMap[_FinalStringRev];
            num = abs(num);
        }
        if (isPrime(num)) {
            PrimePoss++;
        }
    }
}

void CalcAllCombs(int offset, int k) {
    if (k == 0) {
        AddToCounter(AllCombs);
        return;
    }
    for (int i = offset; i <= _CountComb.size() - k; ++i) {
        AllCombs.push_back(_CountComb[i]);
        CalcAllCombs(i+1, k-1);
        AllCombs.pop_back();
    }
}


int main() {
    int n, k = 2;
    cin >> n;
    int counter = 0;
    int counter1 = 0;
    struct Graph* MainGraph = createGraph(n+1);

    for (int i = 0; i < n-1;i++) {
        counter = 0;
        counter1 = 0;
        cin >> counter >> counter1;
        addEdge(MainGraph, min(counter,counter1), max(counter, counter1), 1);
    }

    for (int i = 1; i < n+1; i++) {
        dijkstra(MainGraph, i);
    }

    for (int i = 0; i < n; ++i) { _CountComb.push_back(i+1); }
    CalcAllCombs(0, k);

    float FinalVal = (float)PrimePoss/(float)TotalNumlCombs;
    cout << FinalVal << endl;
    return 0;
}