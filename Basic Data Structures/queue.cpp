#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

using namespace std;

void PrintError(string _ERROR) {
	cout << RED << "ERROR: " << RESET << _ERROR << endl;
}

struct Node {
	int data;
	struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

void Enqueue(int x) {
	struct Node* CounterBuff = new Node;
	CounterBuff->data =x; 
	CounterBuff->next = NULL;
	if(front == NULL && rear == NULL){
		front = rear = CounterBuff;
		return;
	}
	rear->next = CounterBuff;
	rear = CounterBuff;
}

void Dequeue() {
	struct Node* CounterBuff = front;
	if(front == NULL) {
		PrintError("Queue is Empty");
	}
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		front = front->next;
	}
	delete CounterBuff;
}

int Front() {
	if(front == NULL) {
		PrintError("Queue is Empty");
		return 0;
	}
	return front->data;
}

void Print() {
	struct Node* CounterBuff = front;
	while(CounterBuff != NULL) {
		printf("%d ",CounterBuff->data);
		CounterBuff = CounterBuff->next;
	}
	printf("\n");
}

int main(){
	Dequeue();
	Enqueue(2); 
	Print(); 
	Enqueue(4); 
	Print();
	Enqueue(6); 
	Print();
	Dequeue();  
	Print();
	Enqueue(8); 
	Print();
}