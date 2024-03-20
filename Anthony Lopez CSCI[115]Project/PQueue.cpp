#include "PQueue.h"
#include <iostream>
using namespace std;
void swap(myData *to, myData *from)
{
	myData *temp = to;
	to->value = from->value;
	to->index = from->index;
	from->value = temp->value;
	from->index = temp->index;
}
PQueue::PQueue()
{
	cap = 0;
	numElems = 0;
	queue = nullptr;
}
PQueue::PQueue(int max)
{
	cap = max;
	numElems = 0;
	queue = new myData[cap];
}
PQueue::~PQueue()
{
	delete[] queue;
}
bool PQueue::isEmpty()
{
	return (numElems == 0);
}
bool PQueue::isFull()
{
	return (numElems == cap);
}
int PQueue::getParent(int child)
{
	if (child % 2 == 0)
		return (child / 2) - 1;
	else
		return child / 2;
}
int PQueue::getLeftChild(int parent)
{
	return (2 * parent + 1);
}
int PQueue::getRightChild(int parent)
{
	return (2 * parent + 2);
}
void PQueue::minHeapify(int i, int size)
{
	int left, right, min;
	left = 2 * i + 1;
	right = 2 * i + 2;
	min = i;
	if ((left < size) && (queue[left].value < queue[min].value))
		min = left;
	if ((right < size) && (queue[right].value < queue[min].value))
		min = right;
	if(min != i)
	{
		swap(queue[i], queue[min]);
		minHeapify(min, size);
	}
}
void PQueue::buildMinHeap()
{
	for (int i = numElems / 2 - 1; i >= 0; i--)
		minHeapify(i, numElems);
}
void PQueue::push(int index, double value)
{
	if (numElems < cap)
	{
		myData temp;
		temp.index = index;
		temp.value = value;
		int i = numElems;
		while ((i != 0) && (temp.value < queue[i / 2].value))
		{
			queue[i] = queue[i / 2];
			i /= 2;
		}
		queue[i] = temp;
		numElems++;
	}
}
myData PQueue::pop()
{
	if (numElems > 0)
	{
		myData temp = queue[0];
		queue[0] = queue[numElems - 1];
		minHeapify(0, numElems);
		numElems--;
		return temp;
	}
	else
	{
		myData temp;
		temp.value = 0;
		temp.index = -1;
		return temp;
	}
}
void PQueue::display()
{
	cout << "Priority queue" << endl;
	for (int i = 0; i < numElems; i++)
		cout << i << ": (" << queue[i].index << "," << queue[i].value << ")" << endl;
	cout << endl;
}
void PQueue::decreaseKey(int index, double value)
{
	int i = 0;
	bool found = false;
	while ((!found) && (i < numElems))
	{
		if (queue[i].index == index)
		{
			queue[i].value = value;
			found = true;
		}
		i++;
	}
		if (found)
		{
			int child = i - 1;
			int parent = getParent(child);
			while ((queue[child].value < queue[parent].value) && ((child >= 0) && (parent >= 0)))
			{
				swap(queue[child], queue[parent]);
				child = parent;
				parent = getParent(child);
			}
		}
}