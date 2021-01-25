//------------------------------------------------------------
//Класс дек
//------------------------------------------------------------
#pragma once
#include<iostream>
#include<algorithm>

using namespace std;

class KDeque
{
public:
	explicit KDeque(int size);
	KDeque(const KDeque& deque2);
	~KDeque();

	bool const IsEmpty() const { return begin == end; }
	int const Size() const { return (end - begin + n) % n; }
	void Clear() { while (!IsEmpty()) PopBack(); }
	int const Front()const { return arr[begin]; }
	int &Front(){ return arr[begin]; }
	int Back() const { return arr[(end - 1 + n) % n]; }
	bool PushFront(const int value);
	bool PushBack(const int value);
	void PopFront() {if(!IsEmpty()) begin = (begin + 1) % n;  }
	void PopBack() { if(!IsEmpty())end = (end - 1 + n) % n; }
	friend void Swap(KDeque & deque1,KDeque& deque2);

	bool operator ==(const KDeque& deque2) const;
	bool operator !=(const KDeque& deque2) const { return !(*this == deque2); }

	friend ostream & operator <<(ostream& os, const KDeque& deque);
	//заполнение всего дека
	friend istream & operator >>(istream& in, KDeque& deque);

	KDeque& operator =(const KDeque& deque2);
private:
	int* arr;//указатель на выделенную память
	int begin;//индекс первого элемента массива
	int end;//индекс элемента следующего за последним элементом
	int n;//размер выделенной памяти под дек
};

