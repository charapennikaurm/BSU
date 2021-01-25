#include "KDeque.h"

KDeque::KDeque(int size)
{
	n = size + 1;
	begin = 0;
	end = 0;
	arr = new int[n];
}

KDeque::KDeque(const KDeque& deque2)
{
	n = deque2.n;
	begin = deque2.begin;
	end = deque2.end;
	arr = new int[n];
	int j = deque2.begin;
	while (j != deque2.end)
	{
		arr[j] = deque2.arr[j];
		j = (j + 1) % n;
	}
}

KDeque::~KDeque()
{
	delete[]arr;
}

bool KDeque::PushFront(const int value)
{
	if ((end + 1) % n == begin)
	{
		return false;
	}
	else
	{
		begin = (n + begin - 1) % n;
		arr[begin] = value;
		return true;
	}
}

bool KDeque::PushBack(const int value)
{
	if ((end + 1) % n == begin)//проверка на заполненость
	{
		return false;
	}
	else
	{
		arr[end] = value;
		end = (end + 1) % n;
		return true;
	}
}

bool KDeque::operator==(const KDeque& deque2) const
{
	if (this->Size() != deque2.Size())return false;
	int i = this->begin;
	int j = deque2.begin;
	while (i != this->end)
	{
		if (this->arr[i] != deque2.arr[j]) return false;
		i = (i + 1) % this->n;
		j = (j + 1) % deque2.n;
	}
	return true;
}

KDeque& KDeque::operator=(const KDeque& deque2)
{
	if (this != &deque2)
	{
		KDeque temp(deque2);
		Swap(*this, temp);
	}
	return *this;
}

void Swap(KDeque& deque1,KDeque & deque2)
{
	swap(deque1.n, deque2.n);
	swap(deque1.begin, deque2.begin);
	swap(deque1.end, deque2.end);
	swap(deque1.arr, deque2.arr);
}

ostream & operator<<(ostream& out, const KDeque& deque)
{
	int i = deque.begin;
	while (i != deque.end)
	{
		out << deque.arr[i]<<" ";
		i = (i + 1) % deque.n;
	}
	return out;
}

istream& operator>>(istream& in, KDeque& deque)
{
	for (int i = 1; i < deque.n; ++i)
	{
		int k;
		in >> k;
		deque.PushBack(k);
	}
	return in;
}
