#pragma once
#include <stack>
#include <iostream>

template <typename T>
struct SetEl
{
	SetEl(T val, SetEl* r = nullptr, SetEl* l = nullptr) :info(val), right(r), left(l) {}
	template <typename...Args>
	SetEl(Args&& ... args) : info{ std::forward<Args>(args)... }, left(nullptr), right(nullptr){}

	T info;
	SetEl* right;
	SetEl* left;
};

template <typename T>
class KSet;

template <typename T>
class Iterator
{
	friend class KSet<T>;
public:
	Iterator() :cur(nullptr), q(nullptr) {}
	Iterator& operator ++();
	T operator *() { return cur->info; }
	bool operator ==(const Iterator<T>& it2)const
	{
		return cur == it2.cur;
	}
	bool operator !=(const Iterator<T>& it2)const
	{
		return cur != it2.cur;
	}
	void print()
	{
		std::cout << cur->info<<" ";
	}
private:
	Iterator(SetEl<T>* pEl) : cur(pEl), q(pEl) {}
private:
	SetEl<T>* cur;
	SetEl<T>* q;
	std::stack < SetEl<T>* > st;
};

template<typename T>
Iterator<T>& Iterator<T>::operator++()
{
	while (true)
	{
		while (q) { st.push(q); q = q->left; }
		if (st.empty()) { cur = 0; break; }
		q = st.top(); st.pop();
		cur = q; q = q->right;  break;
	}
	return *this;
}
