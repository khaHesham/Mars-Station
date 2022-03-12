#pragma once
#include "QueueADT.h"
#include<iostream>
using namespace std;

template <typename T, int size = 100>   //assume default size
class PriorityQueue :public QueueADT<T>
{
private:

	T arr[size];
	int count;
	int count2;    //to solve deleting prpblems as i work with pairs;

	int getLeftChild(int parent) const
	{
		return 2 * parent + 1;
	}

	int getRightChild(int parent) const
	{
		return 2 * parent + 2;
	}


	int getParent(int child) const
	{
		return (child - 1) / 2;
	}


	void reHeapUp(int child)
	{
		// if child is not root then continue
		if (child != 0)
		{
			// get parent of the child
			int curr_parent = getParent(child);
			//if data at child index is more than at
			//parent index then swap and continue again
			//till the condition gets false
			if (arr[child] > arr[curr_parent])
			{
				swap(arr[child], arr[curr_parent]);
				reHeapUp(curr_parent);
			}
		}
	}


	void reHeapDown(int parent)
	{

		int left = getLeftChild(parent);

		// if there exists a left subtree
		if (left < count)
		{

			int right = getRightChild(parent);

			// if there exists a right subtree
			if (right < count)
			{

				if (arr[left] < arr[right])
				{

					swap(arr[parent], arr[right]);

					parent = right;
					reHeapDown(parent);

				}
				else
				{
					if (arr[parent] < arr[left])
					{
						swap(arr[parent], arr[left]);

						parent = left;
						reHeapDown(parent);
					}
				}
			}
			// if no right subtree
			else
			{
				if (arr[parent] < arr[left])
				{
					swap(arr[parent], arr[left]);

				}
			}

		}
	}



public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntryr);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~PriorityQueue();


	//copy constructor   
	//PriorityQueue(const PriorityQueue<T>& LQ);
	//void operator=(const PriorityQueue<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T, int size>
PriorityQueue<T, size>::PriorityQueue()
{
	count = 0;
	count2 = size - 1;
}
/////////////////////////////////////////////////////////////////////////////////////////


template <typename T, int size>
bool PriorityQueue<T, size>::isEmpty() const
{
	return (count == 0);
}

/////////////////////////////////////////////////////////////////////////////////////////


template <typename T, int size>
bool PriorityQueue<T, size>::enqueue(const T& newEntry)
{
	arr[count] = newEntry;
	reHeapUp(count);
	count++;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T, int size>
bool PriorityQueue<T, size>::dequeue(T& frntEntry)
{
	//index++;

	if (count != 0)
	{
		frntEntry = arr[0];

		if (count == 1)    //
		{
			swap(arr[0], arr[count2--]);    
			count--;
			return true;
		}

		swap(arr[0], arr[count - 1]);  //bring last element to be root

		count--;    //decreament arr size    

		reHeapDown(0);     //finding max element again and put it in front

		return true;
	}
	else
		return false;

}
/////////////////////////////////////////////////////////////////////////////////////////

template <typename T, int size>
bool PriorityQueue<T, size>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;
	else
		frntEntry = arr[0];
	return true;
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T, int size>
PriorityQueue<T, size>::~PriorityQueue()
{
}

