#pragma once
struct myData
{
	int index;
	double value;
};
class PQueue
{
public:
	PQueue();
	PQueue(int max);
	~PQueue();
	int getNumElems() { return numElems; }
	bool isEmpty();
	bool isFull();
	int getParent(int child);
	int getLeftChild(int parent);
	int getRightChild(int parent);
	void push(int index, double value);
	myData pop();
	void decreaseKey(int index, double value);
	void buildMinHeap();
	void display();
private:
	void minHeapify(int index, int size);
	int cap;
	int numElems;
	myData* queue;
};

