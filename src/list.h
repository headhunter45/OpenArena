#ifndef __list_h__
#define __list_h__

#include <cstdlib>

#pragma warning(disable:4715)

namespace OpenArena{
	typedef unsigned int LIST_ARRAY_INDEX_TYPE;

	template <class ItemType>
	class listNode
	{
	public:
		listNode();
		ItemType data;
		listNode<ItemType>* next;
	};

	template <class ItemType>
	class list
	{
	public:
		list();
		~list();
		list(const list&);

		bool IsEmpty() const;
		bool IsFull() const;
		void Insert(ItemType newItem);
		void Remove(ItemType target);
		void Remove();
		ItemType Retrieve() const;
		bool PrevPosition();
		bool NextPosition();
		bool IsFirstPosition() const;
		bool IsLastPosition() const;
		void FirstPosition();
		void LastPosition();
		void Clear();
		bool Contains(ItemType) const;
		unsigned int Length();
		void operator=(const list<ItemType>&);
		ItemType operator[](LIST_ARRAY_INDEX_TYPE) const;
		ItemType& operator[](LIST_ARRAY_INDEX_TYPE);

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
		tail = NULL;
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

		if(!rtOp.IsEmpty())
		{
			listNode<ItemType>* temp = rtOp.head->next;
			listNode<ItemType>* temp2 = NULL;

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
	}

	template <class ItemType>
	bool list<ItemType>::IsEmpty() const
	{
		return head == NULL;
	}

	template <class ItemType>
	bool list<ItemType>::IsFull() const
	{
		return false;
	}

	template <class ItemType>
	void list<ItemType>::Insert(ItemType newItem)
	{
		listNode<ItemType>* temp = head;
		listNode<ItemType>* temp2 = NULL;

		if(head == NULL)
		{
			temp = tail = head = new listNode<ItemType>;
		}
		else
		{
			if(newItem < head->data)
			{
				temp2 = head;
				temp = head = new listNode<ItemType>;
				head->next = temp2;
				temp2 = NULL;
			}
			else
			{
				//temp = head;
				while(temp->next != NULL && newItem > temp->next->data)
				{
					temp = temp->next;
				}
				temp2 = temp->next;
				temp = temp->next = new listNode<ItemType>;
				temp->next = temp2;
				temp2 = NULL;
			}
		}

		temp->data = newItem;

		if(temp->next == NULL)
		{
			tail = temp;
		}
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
	ItemType list<ItemType>::Retrieve() const
	{
		if(currPos != NULL)
			return currPos->data;
	}

	template <class ItemType>
	bool list<ItemType>::IsFirstPosition() const
	{
		return currPos == head;
	}

	template <class ItemType>
	bool list<ItemType>::IsLastPosition() const
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
	ItemType list<ItemType>::operator[](LIST_ARRAY_INDEX_TYPE index) const
	{
		if(head == NULL)
		{
			//We should throw an exception here but instead I'll just return shit guess for now if somebody does this they're just fucked.
		}
		else
		{
			listNode<ItemType>* temp = head;
			LIST_ARRAY_INDEX_TYPE current;

			for(current=0;current <index; current++)
			{
				if(temp->next == NULL)
				{
					temp->next = new listNode<ItemType>;
				}
				temp = temp->next;
			}
			return temp->data;
		}
	}

	template <class ItemType>
	ItemType& list<ItemType>::operator[](LIST_ARRAY_INDEX_TYPE index)
	{
		if(head == NULL)
		{
			tail = currPos = head = new listNode<ItemType>;
			return (ItemType&)(head->data);
		}
		else
		{
			listNode<ItemType>* temp = head;
			LIST_ARRAY_INDEX_TYPE current;

			for(current=0;current <index; current++)
			{
				if(temp->next == NULL)
				{
					temp->next = new listNode<ItemType>;
				}
				temp = temp->next;
			}
			return (ItemType&)(temp->data);
		}
	}

	template <class ItemType>
	unsigned int list<ItemType>::Length()
	{
		if (head == NULL)
		{
			return 0;
		}
		else
		{
			int len = 1;
			listNode<ItemType> temp = head->next;
			while (temp != NULL)
			{
				temp = temp->next;
				len++;
			}
			return len;
		}
	}

	template<class ItemType>
	bool list<ItemType>::Contains(ItemType value) const
	{
		listNode<ItemType>* temp = head;
		while(temp != NULL)
		{
			if(temp->data == value)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;	
	}
};
#endif
