#ifndef __list_h__
#define __list_h__

#include <cstdlib>

#pragma warning(disable:4715)

template <class ItemType>
class listNode
{
public:
	listNode();
	listNode<ItemType>* next;
	ItemType data;
};

template <class ItemType>
class list
{
public:
	list();
	~list();
	list(const list&);

	bool IsEmpty();
	bool IsFull();
	void Insert(ItemType newItem);
	void Remove(ItemType target);
	void Remove();
	ItemType Retrieve();
	bool PrevPosition();
	bool NextPosition();
	bool IsFirstPosition();
	bool IsLastPosition();
	void FirstPosition();
	void LastPosition();
	void Clear();
	void operator=(const list<ItemType>&);
	ItemType operator[](unsigned int);

private:
	listNode<ItemType>* head;
	listNode<ItemType>* tail;
	listNode<ItemType>* currPos;
};

template <class ItemType>
listNode<ItemType>::listNode()
{
	next = NULL;
}

template <class ItemType>
list<ItemType>::list()
{
	head = NULL;
	tail = NULL;
	currPos = NULL;
}

template <class ItemType>
list<ItemType>::~list()
{
	currPos = NULL;
	while(head != NULL)
	{
		tail = head;
		head = head->next;
		delete tail;
		tail = NULL;
	}
}

template <class ItemType>
list<ItemType>::list(const list<ItemType>& rtOp)
{
	head = NULL;
	tail = NULL
	currPos = NULL;

	operator=(rtOp);
}

template <class ItemType>
void list<ItemType>::Clear()
{
	while(head)
		Remove(head->data);
}

template <class ItemType>
void list<ItemType>::operator=(const list<ItemType>& rtOp)
{
	Clear();

	listNode<ItemType> temp = rtOp.head->next;
	listNode<ItemType> temp2 = NULL;
	
	if(temp != NULL)
	{
		head = new listNode<ItemType>;
		head->data = rtOp.head->data;
		tail = head;
		temp2 = head;
	}

	while (temp != NULL)
	{
		temp2->next = new listNode<ItemType>;
		temp2 = temp2->next;
		temp2->data = temp->data;
		temp = temp->next;
	}

	tail = temp2;
}

template <class ItemType>
bool list<ItemType>::IsEmpty()
{
	return head == NULL;
}

template <class ItemType>
bool list<ItemType>::IsFull()
{
	return false;
}

template <class ItemType>
void list<ItemType>::Insert(ItemType newItem)
{
	listNode<ItemType>* temp = head;
	if(head != NULL)
	{

		while(temp->next!= NULL && temp->data < newItem)
		{
			temp = temp->next;
		}

		if(temp == head)
		{
			tail->next = head;
			head = new listNode<ItemType>;
			head->next = tail->next;
			tail->next = NULL;
			temp = head;
		}
		else if(temp->data != newItem)
		{
			if(temp == tail)
			{
				tail->next = new listNode<ItemType>;
				tail = tail->next;
				temp = tail;
			}
			else
			{
			tail->next = temp->next;
			temp = temp->next = new listNode<ItemType>;
			temp->next = tail->next;
			tail->next = NULL;
			}
		}
	}
	else
	{
		temp = tail = head = new listNode<ItemType>;
		tail->next = NULL;
	}

	temp->data = newItem;
}

template <class ItemType>
void list<ItemType>::Remove(ItemType target)
{
	if(head != NULL)
	{
		listNode<ItemType>* temp = head;
		listNode<ItemType>* temp2 = head;
		
		while(temp->next != NULL && temp->data != target)
		{
			temp2 = temp;
			temp = temp->next;
		}

		if(temp->data == target)
		{
			if(temp != head)
			{
				temp2->next = temp->next;
				delete temp;
			}
			else
			{
				if(tail == head)
					tail = NULL;
				head = head->next;
				delete temp2;
			}
		}
	}
}

template <class ItemType>
bool list<ItemType>::PrevPosition()
{
	if(currPos != head)
	{
		tail->next = currPos;
		currPos = head;
		
		if(currPos != tail->next)
		{
            while(currPos->next != tail->next)
			{
				currPos = currPos->next;
			}
		}

		tail->next = NULL;
		
		return true;
	}
	else
	{
		return false;
	}
}

template <class ItemType>
bool list<ItemType>::NextPosition()
{
	if(currPos != tail)
	{
		currPos = currPos->next;
		return true;
	}
	else
	{
		return false;
	}
}

template <class ItemType>
void list<ItemType>::Remove()
{
	if(currPos != NULL)
	{
		tail->next = currPos;
		currPos = currPos->next;
		delete tail->next;
		tail->next = NULL;
	}

}

template <class ItemType>
ItemType list<ItemType>::Retrieve()
{
	if(currPos != NULL)
		return currPos->data;
}

template <class ItemType>
bool list<ItemType>::IsFirstPosition()
{
	return currPos == head;
}

template <class ItemType>
bool list<ItemType>::IsLastPosition()
{
	return currPos == tail;
}

template <class ItemType>
void list<ItemType>::FirstPosition()
{
	currPos = head;
}

template <class ItemType>
void list<ItemType>::LastPosition()
{
	currPos = tail;
}

template <class ItemType>
ItemType list<ItemType>::operator[](unsigned int index)
{
	if(head != NULL)
	{
	listNode<ItemType>* temp = head;
	while(index > 0 && temp != NULL)
	{
		temp = temp->next;
		--index;
	}
	if(temp != NULL)
	{
		return temp->data;
	}
	}
}


#include "list.cpp"

#endif