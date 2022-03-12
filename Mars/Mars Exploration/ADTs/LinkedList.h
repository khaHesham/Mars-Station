#pragma once
#include "ListInterface.h"
#include "Node.h"
#include <iostream>
#include<exception>

using namespace std;

class precondViolatedExcep :public exception
{
public:
	precondViolatedExcep(const char *message) :exception(message)
	{}
};

template<class T>
class LinkedList : public ListInterface<T>
{
	Node<T>* head;
	int itemCount;

	Node<T>* getNodeAt(int position)const
	{
		if (position < 1)
			return nullptr;
		Node<T>* p = head;
		int i = 1;
		while (p)
		{
			if (i == position)
				return p;
			p = p->getNext();
			i++;
		}
		return nullptr;
	}

	Node<T>* getPointerTo( T& item) const
	{
		Node<T>* p = head;
		while (p)
		{
			if (p->getItem() == item)
				return p;
			p = p->getNext();
		}
		return nullptr;
	}



public:
	LinkedList() :itemCount(0)
	{
		head = nullptr;
	}
	~LinkedList()
	{
		clear();
	}
	

	virtual bool isEmpty()const
	{
		return(!head);

	}

	virtual int getLength() const
	{
		return itemCount;
	}

	virtual bool insert(int position,T newentry)
		{
		if (position < 1 || position > itemCount + 1)
		return false;

		Node<T>* nptr = new Node<T>(newentry);

		if (position == 1)
		{
			nptr->setNext(head);
			head = nptr;
		}
		else
		{
			Node<T>* prv = getNodeAt(position - 1);
			if (!prv)
				return false;
			nptr->setNext(prv->getNext());
			prv->setNext(nptr);
		}
		itemCount++;
		return true;
	}

	virtual bool remove(int position)
	{
		bool abletoremove = (position >= 1) && (position <= itemCount);
		if (abletoremove)
		{
			Node<T>* cur = nullptr;
			if (position == 1)
			{
				cur = head;
				head = head->getNext();

			}
			else
			{
				Node<T>* prv = getNodeAt(position - 1);
				if (!prv)
					return false;
				cur = prv->getNext();
				prv->setNext(cur->getNext());

			}
			cur->setNext(nullptr);
			delete cur;
			cur = nullptr;
			itemCount--;
		}
		return true;
	}

	virtual T getEntry(int position)
	{
		bool abletoget = (position >= 1) && (position <= itemCount);
		if (abletoget)
		{
			Node<T>* ptr = getNodeAt(position);
			return ptr->getItem();
		}

		else
		{
			const char* message ="getEntry() is called with an Empty List or invalid position.";
			throw(precondViolatedExcep(message));
		}
	}

	virtual T replace(int position, T entry)
	{
		Node<T>* ptr = getNodeAt(position);
		T temp = ptr->getItem();
		ptr->setItem(entry);
		return temp;
	}

	virtual void clear()
	{
		Node<T>* ptr = head;
		while (ptr)
		{
			Node<T>* temp = ptr;
			ptr = ptr->getNext();
			delete temp;
		}
		head = nullptr;
	}

	virtual void print()
	{
		Node<T>* p = head;
		while (p)
		{
			cout << p->getItem() << "-->";
			p = p->getNext();
		}
		cout << "NULL" << endl;

	}

	LinkedList(const LinkedList<T>& list)   //copy constructor
	{
		if (list.isEmpty())
			return;
		Node<T>* newN = new Node<T>(list.getNodeAt(1)->getItem());

		head = newN;

		Node<T>* ptr = head;
		Node<T>* ptr2 = (list.head->getNext());
		while (ptr2)
		{
			Node<T>* newNN = new Node<T>(ptr2->getItem());
			ptr->setNext(newNN);
			ptr = ptr->getNext();
			ptr2 = ptr2->getNext();
		}
		itemCount = list.itemCount;
	}
	void operator = (const LinkedList<T>& list)  //overloaded Assignment operator
	{
		clear();
		Node<T>* newN = new Node<T>(list.getNodeAt(1)->getItem());
		head = newN;
		
		Node<T>* ptr = head;
		Node<T>* ptr2 = (list.head->getNext());
		while (ptr2)
		{
			Node<T>* newNN = new Node<T>(ptr2->getItem());
			ptr->setNext(newNN);
			ptr = ptr->getNext();
			ptr2 = ptr2->getNext();
		}
		itemCount = list.itemCount;

	}
};



