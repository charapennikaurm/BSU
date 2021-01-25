#pragma once

//доделать перевороты

//doublelinked list

template <typename T>
class List2
{
public:
	List2();
	List2(const List2<T> & a);
	~List2();
	int get_size() { return list_size; }
	void push_back(const T value);
	void push_front(const T value);
	void push_at(const T value, const int index);
	void pop_back();
	void pop_front();
	void pop_at(const int index);
	void clear();
	void reverse();
	void part_reverse(int start_ind, int end_ind);
	T& operator [](const int index);
private:
	template<typename T>
	class Node2
	{public:
		Node2<T>(T info= T(),Node2<T>*pNext=nullptr,Node2<T>*pPrev=nullptr)
		{
			this->info = info;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
		T info;
		Node2<T>* pNext, * pPrev;
	};
	Node2<T>* head, * tail;
	int list_size;
};

template<typename T>
List2<T>::List2()
{
	list_size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
List2<T>::List2(const List2<T>& a)
{
	this->head = nullptr;
	this->tail = nullptr;
	this->list_size = 0;
	Node2<T>* current = a.head;
	for (int i = 0; i < a.list_size; ++i)
	{
		this->push_back(current->info);
		current = current->pNext;
	}
}

template<typename T>
List2<T>::~List2()
{
	clear();
}

template<typename T>
void List2<T>::push_back(const T value)
{
	if(list_size==0)
	{
		tail = head = new Node2<T>(value);
	}
	else if (list_size == 1)
	{
		head->pNext=tail = tail->pNext = new Node2<T>(value, nullptr, head);
	}
	else
	{
		tail = tail->pNext = new Node2<T>(value, nullptr, tail);
	}
	++list_size;
}

template<typename T>
void List2<T>::push_front(const T value)
{
	if (list_size == 0)
	{
		tail = head = new Node2<T>(value);
	}
	else if (list_size == 1)
	{
		tail->pPrev = head = head->pPrev = new Node2<T>(value, head, nullptr);
	}
	else
	{
		head = head->pPrev = new Node2<T>(value, head, nullptr);
	}
	++list_size;
}

template<typename T>
void List2<T>::push_at(const T value, const int index)
{
	/*для более быстрого доступа к позиции будем идити сначала или с концв
	в зависимости от того к чему элемент ближе*/
	if (index == 0) { push_front(value); }
	else if (index == list_size) { push_back(value); }
	else
	{
		if (index<=list_size/2) 
		{
			Node2<T>* current = head;
			for (int i = 0; i < index; ++i)
			{
				current = current->pNext;
			}
			Node2<T>* previous = current->pPrev;
			previous->pNext = current->pPrev = new Node2<T>(value, current, previous);
		}
		else
		{
			Node2<T>* current = tail;
			for (int i = list_size-1; i > index; --i)
			{
				current = current->pPrev;
			}
			Node2<T>* previous = current->pPrev;
			previous->pNext = current->pPrev = new Node2<T>(value, current, previous);
		}
		++list_size;
	}

}

template<typename T>
void List2<T>::pop_back()
{
	if (list_size == 1)
	{
		delete tail;
		tail = nullptr;
		head = nullptr;
	}
	else
	{
		tail = tail->pPrev;
		delete tail->pNext;
		tail->pNext = nullptr;
	}
	--list_size;
}

template<typename T>
void List2<T>::pop_front()
{
	if (list_size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		head = head->pNext;
		delete head->pPrev;
		head->pPrev = nullptr;
	}
	--list_size;
}

template<typename T>
void List2<T>::pop_at(const int index)
{
	if (index == 0) { pop_front(); }
	else if (index == list_size - 1) { pop_back(); }
	else
	{
		if (index<=list_size/2)
		{
			Node2<T>* current = head;
			for (int i = 0; i < index; ++i)
			{
				current = current->pNext;
			}
			Node2<T>* previous=current->pPrev, * next=current->pNext;
			previous->pNext = next;
			next->pPrev = previous;
			delete current;
		}
		else
		{
			Node2<T>* current = tail;
			for (int i = list_size - 1; i > index; --i)
			{
				current = current->pPrev;
			}
			Node2<T>* previous = current->pPrev, * next = current->pNext;
			previous->pNext = next;
			next->pPrev = previous;
			delete current;
		}
		--list_size;
	}
}


template<typename T>
void List2<T>::clear()
{
	while (list_size)
	{
		pop_front();
	}
}

template<typename T>
void List2<T>::reverse()
{
	Node2<T>* current;
	Node2<T>* temp;
	current = head;
	while (current != nullptr)
	{
		temp = current->pNext;
		current->pNext = current->pPrev;
		current->pPrev = temp;
		current = current->pPrev;
	}
	temp = tail;
	tail = head;
	head = temp;
}

template<typename T>
void List2<T>::part_reverse(int start_ind, int end_ind)
{
	if ((start_ind == list_size - 1) || (start_ind == end_ind)) { ; }
	else if ((start_ind = 0) && (end_ind == list_size - 1)) { this->reverse; }
	else
	{
		Node2<T>* current;
		current = head;
		for (int i = 0; i < start_ind; ++i)
		{
			current = current->pNext;
		}
		List2<T> a;
		for (int i = start_ind; i <= end_ind; ++i)
		{
			a.push_back(current->info);
			current = current->pNext;
			this->pop_at(start_ind);
		}
		current = a.head;
		while (current != nullptr)
		{
			this->push_at(current->info, start_ind);
			current = current->pNext;
		}
	}
}

template<typename T>
T& List2<T>::operator[](const int index)
{
	if (index <= list_size / 2)
	{
		Node2<T>* current = head;
		for (int i = 0; i < index; ++i)
		{
			current = current->pNext;
		}
		return current->info;
	}
	else
	{
		Node2<T>* current = tail;
		for (int i = list_size - 1; i > index; --i)
		{
			current = current->pPrev;
		}
		return current->info;
	}
}
