#ifndef __list_h__
#define __list_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>

#pragma warning(disable:4715)

namespace OpenArena{
	typedef unsigned int LIST_ARRAY_INDEX_TYPE;

	/*!
	 * \brief
	 * Write brief comment for listNode here.
	 * 
	 * \param ItemType
	 * Description of parameter ItemType.
	 * 
	 * Write detailed description for listNode here.
	 * 
	 * \remarks
	 * Write remarks for listNode here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	template <class ItemType>
	class listNode
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for listNode here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for listNode here.
		 * 
		 * \remarks
		 * Write remarks for listNode here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		listNode();
		ItemType data;
		listNode<ItemType>* next;
	};

	/*!
	 * \brief
	 * Write brief comment for list here.
	 * 
	 * \param ItemType
	 * Description of parameter ItemType.
	 * 
	 * Write detailed description for list here.
	 * 
	 * \remarks
	 * Write remarks for list here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	template <class ItemType>
	class list
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for list here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for list here.
		 * 
		 * \remarks
		 * Write remarks for list here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		list();
		/*!
		 * \brief
		 * Write brief comment for ~list here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~list here.
		 * 
		 * \remarks
		 * Write remarks for ~list here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		~list();
		/*!
		 * \brief
		 * Write brief comment for list here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for list here.
		 * 
		 * \remarks
		 * Write remarks for list here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		list(const list&);

		/*!
		 * \brief
		 * Write brief comment for IsEmpty here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for IsEmpty here.
		 * 
		 * \remarks
		 * Write remarks for IsEmpty here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool IsEmpty() const;
		/*!
		 * \brief
		 * Write brief comment for IsFull here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for IsFull here.
		 * 
		 * \remarks
		 * Write remarks for IsFull here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool IsFull() const;
		/*!
		 * \brief
		 * Write brief comment for Insert here.
		 * 
		 * \param newItem
		 * Description of parameter newItem.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Insert here.
		 * 
		 * \remarks
		 * Write remarks for Insert here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Insert(ItemType newItem);
		/*!
		 * \brief
		 * Write brief comment for Remove here.
		 * 
		 * \param target
		 * Description of parameter target.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Remove here.
		 * 
		 * \remarks
		 * Write remarks for Remove here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Remove(ItemType target);
		/*!
		 * \brief
		 * Write brief comment for Remove here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Remove here.
		 * 
		 * \remarks
		 * Write remarks for Remove here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Remove();
		/*!
		 * \brief
		 * Write brief comment for Retrieve here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Retrieve here.
		 * 
		 * \remarks
		 * Write remarks for Retrieve here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		ItemType Retrieve() const;
		/*!
		 * \brief
		 * Write brief comment for PrevPosition here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for PrevPosition here.
		 * 
		 * \remarks
		 * Write remarks for PrevPosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool PrevPosition();
		/*!
		 * \brief
		 * Write brief comment for NextPosition here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for NextPosition here.
		 * 
		 * \remarks
		 * Write remarks for NextPosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool NextPosition();
		/*!
		 * \brief
		 * Write brief comment for IsFirstPosition here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for IsFirstPosition here.
		 * 
		 * \remarks
		 * Write remarks for IsFirstPosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool IsFirstPosition() const;
		/*!
		 * \brief
		 * Write brief comment for IsLastPosition here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for IsLastPosition here.
		 * 
		 * \remarks
		 * Write remarks for IsLastPosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool IsLastPosition() const;
		/*!
		 * \brief
		 * Write brief comment for FirstPosition here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for FirstPosition here.
		 * 
		 * \remarks
		 * Write remarks for FirstPosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void FirstPosition();
		/*!
		 * \brief
		 * Write brief comment for LastPosition here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for LastPosition here.
		 * 
		 * \remarks
		 * Write remarks for LastPosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void LastPosition();
		/*!
		 * \brief
		 * Write brief comment for Clear here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Clear here.
		 * 
		 * \remarks
		 * Write remarks for Clear here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Clear();
		/*!
		 * \brief
		 * Write brief comment for Contains here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Contains here.
		 * 
		 * \remarks
		 * Write remarks for Contains here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool Contains(ItemType) const;
		/*!
		 * \brief
		 * Write brief comment for Length here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Length here.
		 * 
		 * \remarks
		 * Write remarks for Length here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		unsigned int Length();
		/*!
		 * \brief
		 * Write brief comment for operator = here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator = here.
		 * 
		 * \remarks
		 * Write remarks for operator = here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void operator=(const list<ItemType>&);
		/*!
		 * \brief
		 * Write brief comment for operator [] here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator [] here.
		 * 
		 * \remarks
		 * Write remarks for operator [] here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		ItemType operator[](LIST_ARRAY_INDEX_TYPE) const;
		/*!
		 * \brief
		 * Write brief comment for operator [] here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator [] here.
		 * 
		 * \remarks
		 * Write remarks for operator [] here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
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
