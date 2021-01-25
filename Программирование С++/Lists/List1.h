#pragma once
#include<iostream>

//доделать переворот части списка

//singlelinked list
template <typename T>
class List1
{
public:
	List1();
	List1(List1<T> & a);
	~List1();
	int get_size() { return list_size; }
	void push_back(const T value);
	void push_front(const T value);
	void push_at(const T value,const int index);
	void pop_back();
	void pop_front();
	void pop_at(const int index);
	void clear();
	void reverse();
	void part_reverse(const int start_ind,const int end_ind);
	T& operator [](const int index);
private:
	template<typename T>
	class Node1
	{public:
		Node1(T info = T(), Node1* pnext = nullptr)
		{
			this->info = info;
			this->pNext = pnext;
		}
		T info;
		Node1 * pNext;
	};
	Node1<T>* head;
	Node1<T>* tail;
	int list_size;
};

template <typename T>
List1<T>::List1()
{
	list_size = 0;
	tail=head = nullptr;
}

template<typename T>
List1<T>::List1(List1<T>& a)
{
	Node1<T>* current = a.head;
	for (int i = 0; i < a.get_size(); ++i)
	{
		this->push_back(current->info);
		current = current->pNext;
	}
}

template <typename T>
List1<T>:: ~List1()
{
	this->clear();
}

template<typename T>
void List1<T>::push_back(const T value)
{
	if (list_size == 0) { tail=head = new Node1<T>(value); }
	else if (list_size == 1)
	{
		head->pNext = tail = new Node1<T>(value);
	}
	else
	{
		tail = tail->pNext = new Node1<T>(value);
	}
	++list_size;
}

template<typename T>
void List1<T>::push_front(const T value)
{
	if (list_size == 0)
	{
		tail = head = new Node1<T>(value);
	}
	else if (list_size == 1)
	{
		head = new Node1<T>(value, head);
	}
	else
	{
		head = new Node1<T>(value, head);
	}
	++list_size;
}

template<typename T>
void List1<T>::push_at(const T value, const int index)
{
	if (index == 0) { push_front(value); }
	else if (index == list_size) { push_back(value); }
	else
	{
		Node1<T>* previous = this->head;
		for (int i = 0; i < index-1 ; ++i)
		{
			previous = previous->pNext;
		}
		Node1<T>* newnode = new Node1<T>(value, previous->pNext);
		previous->pNext = newnode;
		++list_size;
	}
}

template<typename T>
void List1<T>::pop_back()
{
	if (list_size == 1) 
	{
		delete tail;
		tail = head = nullptr;
	}
	this->pop_at(list_size - 1);
}

template<typename T>
void List1<T>::pop_front()
{
	if (list_size == 1)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node1<T>* temp = head;
		head = head->pNext;
		delete temp;
	}
		--list_size;
}

template <typename T>
void List1<T>::pop_at(const int index)
{
	if (index == 0) { this->pop_front(); }
	else
	{
		Node1<T>* previous;
		previous = head;
		for (int i = 0; i < index - 1; ++i)
		{
			previous = previous->pNext;
		}
		Node1<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		if (index == list_size - 1) { tail = previous; }
		--list_size;
	}
}

template<typename T>
void List1<T>::clear()
{
	while (list_size) this->pop_front();
}

template<typename T>
void List1<T>::reverse()
{
	if (list_size == 0 || list_size == 1) { ; }
	else {
		Node1<T>* prev,*current,* next;
		current = head;
		prev = nullptr;
		next = current->pNext;
		while (next->pNext != nullptr)
		{
			current->pNext = prev;
			prev = current;
			current = next;
			next = next->pNext;
		}
		current->pNext = prev;
		next->pNext = current;
		head->pNext = nullptr;
		this->head = next;
	}	
}

//reverse part of list from start ind to end ind
template<typename T>
void List1<T>::part_reverse(const int start_ind, const int end_ind)
{
	if (start_ind == list_size - 1 || start_ind == end_ind) { ; }
	else
	{
		Node1<T>* current;
		current = head;
		for (int i = 0; i < start_ind; ++i)
		{
			current = current->pNext;
		}
		List1<T> a;
		for (int i = start_ind; i <= end_ind; ++i)
		{
			a.push_back(current->info);
			current = current->pNext;
			this->pop_at(start_ind);
		}
		current = a.head;
		while(current!=nullptr)
		{
			this->push_at(current->info, start_ind);
			current = current->pNext;
		}
	}
}

template<typename T>
T& List1<T>::operator[](const int index)
{

	Node1<T>* current = head;
	int counter = 0;
	while (current->pNext != nullptr)
	{
		if(counter==index) return current->info;
		current = current->pNext;
		++counter;
	}
	//if index greater than size of list returns last element
}
