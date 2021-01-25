#pragma once
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include "Iterator.h"

using namespace std;

//==============================================
//TODO:
// emplace
//==============================================

//structure for []
template <typename T>
struct SubSet
{
	SubSet<T> operator =(const KSet<T>& set2)
	{
		*pset /= subset;
		*pset += set2;
		return SubSet<T>();
	}
	void print()
	{
		cout << subset;
	}
	KSet<T>* pset;
	KSet<T> subset;
};

template <typename T>
class KSet
{
	friend class Iterator<T>;
public:
	KSet(): root(nullptr) {}
	KSet(std::initializer_list<T> l);
	explicit KSet(const KSet<T>& set2);
	KSet(KSet<T>&& set2):root(set2.root) { set2.root = nullptr; } 
	~KSet() { erase(root); }
	bool is_empty()const { return root == nullptr; }
	int size()const;
	bool insert(const T& x);
	bool delete_element(T val);
	void clear() { erase(root); root = nullptr; }
	void swap(KSet<T>& s2);
	friend ostream& operator << <>(ostream& os, const KSet<T>& s);
	friend istream& operator >> <>(istream& in, KSet<T>& s);

	//methods for iterator
	Iterator<T> begin() { return ++Iterator<T>(root); }
	Iterator<T> end() { return Iterator<T>(nullptr); }


	//for move = operator test
	KSet<T> clone()
	{
		KSet<T> t(*this);
		return t;
	}
	
	//boolean operators for sets of different types
	template <typename U>
	bool operator ==(const KSet<U>& set2) const { return false; }
	template <typename U>
	bool operator !=(const KSet<U>& set2) const { return true; }
	template <typename U>
	bool operator >(const KSet<U>& set2) const { return false; }
	template <typename U>
	bool operator >=(const KSet<U>& set2) const { return false; }
	template <typename U>
	bool operator <(const KSet<U>& set2) const { return false; }
	template <typename U>
	bool operator <=(const KSet<U>& set2) const { return false; }

	//boolean operators for sets of same type
	bool operator == (const KSet<T>& set2)const;
	bool operator != (const KSet<T>& set2)const { return !(*this == set2); }
	bool operator <  (const KSet<T>& set2)const;
	bool operator <= (const KSet<T>& set2)const { return *this < set2 || *this == set2; }
	bool operator >  (const KSet<T>& set2)const;
	bool operator >= (const KSet<T>& set2)const { return *this > set2 || *this == set2; }

	KSet<T>& operator = (const KSet<T>& set2);
	KSet<T>& operator = (KSet<T>&& set2)
	{
		if(this!=&set2)
		{
			this->clear();
			root = set2.root;
			set2.root = nullptr;
		}
		return *this;
	}

	//объединение
	KSet<T>& operator += (const KSet<T>& set2);
	KSet<T> const operator +  (const KSet<T>& set2)const
	{
		KSet<T> c = (*this);
		c += set2;
		return c;
	}
	//симметрическая разность
	KSet<T>& operator -= (const KSet<T>& set2);
	KSet<T> const operator -  (const KSet<T>& set2)const
	{
		KSet<T> c = (*this);
		c -= set2;
		return c;
	}
	//разность
	KSet<T>& operator /= (const KSet<T>& set2);
	KSet<T> const operator /  (const KSet<T>& set2)const
	{
		KSet<T> c = (*this);
		c /= set2;
		return c;
	}
	//пересечение
	KSet<T>& operator *= (const KSet<T>& set2);
	KSet<T> const operator *  (const KSet<T>& set2)const
	{
		KSet<T> c = (*this);
		c *= set2;
		return c;
	}

	SubSet<T> operator [] (const KSet<T> & set2);

	template<typename...Args>
	void emplace(Args&& ...args)
	{
		SetEl<T> new_el(args...);
		SetEl<T>* p = root;
		SetEl<T>** pp = &root;
		while (p)
		{
			if (new_el.info < p->info)
			{
				pp = &p->left;
				p = p->left;
			}
			else if (new_el.info == p->info)
			{
				return;
			}
			else 
			{
				pp = &p->right;
				p = p->right;
			}

		}
		*pp = new SetEl<T>(new_el.info);
	}

private:
	void delete01(SetEl<T>* p, SetEl<T>** pp);
	void erase(SetEl<T>* ptr)
	{
		if (ptr) { erase(ptr->left); erase(ptr->right); delete ptr; }
	}
private:
	SetEl<T>* root;
};


//==============================================
//      class methods and friend functions      
//==============================================


template<typename T>
KSet<T>::KSet(std::initializer_list<T> l)
{
	root = nullptr;
	for (auto x : l)
	{
		insert(x);
	}
}

template<typename T>
KSet<T>::KSet(const KSet<T>& set2)
{
	root = nullptr;
	SetEl<T>* q;
	stack<SetEl<T>*> st{ {set2.root} };
	while (!st.empty())
	{
		q = st.top(); st.pop();
		if (q)
		{
			this->insert(q->info);
			st.push(q->left);
			st.push(q->right);
		}
	}
}

template<typename T>
int KSet<T>::size()const
{
	int c = 0;
	SetEl<T>* q;
	stack<SetEl<T>*> st;
	st.push(root);
	while (!st.empty())
	{
		q = st.top(); st.pop();
		if (q)
		{
			++c; st.push(q->left); st.push(q->right);
		}
	}
	return c;
}

template<typename T>
bool KSet<T>::insert(const T& x)
{
	SetEl<T>** pp = &root;
	SetEl<T>* p = root;
	while (p)
	{
		if (x < p->info)
		{
			pp = &p->left;
			p = p->left;
		}
		else if (x == p->info)
		{
			return false;
		}
		else //x > p->info
		{
			pp = &p->right;
			p = p->right;
		}
		
	}
	*pp = new SetEl<T>(x);
	return true;
}

template<typename T>
bool KSet<T>::delete_element(T val)
{
	SetEl<T>** pp = &root;
	SetEl<T>* p = root;
	while (p)
	{
		if (val < p->info)
		{
			pp = &p->left; p = p->left;
		}
		else if (val > p->info)
		{
			pp = &p->right; p = p->right;
		}
		else
			break;
	}
	if (!p)
		return false;
	else if (p->right && p->left)
	{
		pp = &p->left;
		SetEl<T>* t = p->left;
		while (t->right) { pp = &t->right; t = t->right; }
		p->info = t->info;
		delete01(t, pp);
	}
	else
		delete01(p, pp);
	return true;
}

template<typename T>
bool KSet<T>::operator==(const KSet<T>& set2)const
{
	if (size() != set2.size())
		return false;
	else
	{
		SetEl<T>* p1 = root; SetEl<T>* p2 = set2.root;
		stack<SetEl<T>*> st1, st2;
		while (p1) { st1.push(p1); p1 = p1->left; }
		while (p2) { st2.push(p2); p2 = p2->left; }
		while (!st1.empty() && !st2.empty())
		{
			SetEl<T>* q1 = st1.top(); st1.pop();
			SetEl<T>* q2 = st2.top(); st2.pop();
			if (q1->info != q2->info) { return false; }
			p1 = q1->right; p2 = q2->right;
			while (p1) { st1.push(p1); p1 = p1->left; }
			while (p2) { st2.push(p2); p2 = p2->left; }
		}

	}
	return true;
}

template<typename T>
bool KSet<T>::operator<(const KSet<T>& set2)const
{
	if (size() >= set2.size())
	{
		return false;
	}
	else
	{
		SetEl<T>* p1 = root;
		SetEl<T>* p2 = set2.root;
		stack<SetEl<T>*> st1, st2;
		while (p1) { st1.push(p1); p1 = p1->left; }
		while (p2) { st2.push(p2); p2 = p2->left; }
		while (!st1.empty() && !st2.empty())
		{
			SetEl<T>* q1 = st1.top(); st1.pop();
			SetEl<T>* q2 = st2.top(); st2.pop();
			if (q1->info == q2->info)
			{
				p1 = q1->right;
				p2 = q2->right;
				while (p1) { st1.push(p1); p1 = p1->left; }
				while (p2) { st2.push(p2); p2 = p2->left; }
			}
			else if (q1->info > q2->info)
			{
				p2 = q2->right;
				while (p2) { st2.push(p2); p2 = p2->left; }
			}
			else if (q1->info < q2->info)
			{
				return false;
			}
		}
	}
	return true;
}

template <typename T>
bool KSet<T>::operator>(const KSet<T>& set2)const
{
	if (size() <= set2.size())
	{
		return false;
	}
	else
	{
		SetEl<T>* p1 = root;
		SetEl<T>* p2 = set2.root;
		stack<SetEl<T>*> st1, st2;
		while (p1) { st1.push(p1); p1 = p1->left; }
		while (p2) { st2.push(p2); p2 = p2->left; }
		while (!st1.empty() && !st2.empty())
		{
			SetEl<T>* q1 = st1.top(); st1.pop();
			SetEl<T>* q2 = st2.top(); st2.pop();
			if (q1->info == q2->info)
			{
				p1 = q1->right;
				p2 = q2->right;
				while (p1) { st1.push(p1); p1 = p1->left; }
				while (p2) { st2.push(p2); p2 = p2->left; }
			}
			else if (q1->info > q2->info)
			{
				p1 = q1->right;
				while (p1) { st1.push(p1); p1 = p1->left; }
			}
			else if (q1->info > q2->info)
			{
				return false;
			}
		}
	}
	return true;
}

template<typename T>
KSet<T>& KSet<T>::operator=(const KSet<T>& set2)
{
	if(this != &set2)
	{
		clear();
		SetEl<T>* q;
		stack<SetEl<T>*> st{ {set2.root} };
		while (!st.empty())
		{
			q = st.top(); st.pop();
			if (q)
			{
				this->insert(q->info);
				st.push(q->left);
				st.push(q->right);
			}
		}
	}
	return *this;
}

template<typename T>
KSet<T>& KSet<T>::operator+=(const KSet<T>& set2)
{
	SetEl<T>* q;
	stack<SetEl<T>*> st{ {set2.root} };
	while (!st.empty())
	{
		q = st.top(); st.pop();
		if (q)
		{
			this->insert(q->info);
			st.push(q->left);
			st.push(q->right);
		}
	}
	return *this;
}

template<typename T>
KSet<T>& KSet<T>::operator-=(const KSet<T>& set2)
{

	KSet<T> tmp(set2);
	tmp /= *this;
	*this /= set2;
	*this += tmp;
	if (is_empty())
		throw std::exception("Empty set exception!");
	return*this;
}

template<typename T>
KSet<T>& KSet<T>::operator/=(const KSet<T>& set2)
{
	SetEl<T>* q;
	stack<SetEl<T>*> st{ {set2.root} };
	while (!st.empty())
	{
		q = st.top(); st.pop();
		if (q)
		{
			this->delete_element(q->info);
			st.push(q->left);
			st.push(q->right);
		}
	}
	return *this;
	return *this;
}

template<typename T>
KSet<T>& KSet<T>::operator*=(const KSet<T>& set2)
{
	SetEl<T>* p1 = root; SetEl<T>* p2 = set2.root;
	stack<SetEl<T>*> st1; stack<SetEl<T>*> st2;
	while (p1) { st1.push(p1); p1 = p1->left; }
	while (p2) { st2.push(p2); p2 = p2->left; }
	while (!st1.empty() && !st2.empty())
	{
		SetEl<T>* q1; SetEl<T>* q2;
		q1 = st1.top(); q2 = st2.top();
		if (q1->info == q2->info)
		{
			st1.pop(); st2.pop();
			p1 = q1->right; p2 = q2->right;
			while (p1) { st1.push(p1); p1 = p1->left; }
			while (p2) { st2.push(p2); p2 = p2->left; }
		}
		if (q2->info > q1->info)
		{
			st1.pop();
			p1 = q1->right;
			while (p1) { st1.push(p1); p1 = p1->left; }
			delete_element(q1->info);

		}
		if (q2->info < q1->info)
		{
			st2.pop();
			p2 = q2->right;
			while (p2) { st2.push(p2); p2 = p2->left; }
		}
	}
	while (!st1.empty())
	{
		SetEl<T>* q = st1.top(); st1.pop();
		p1 = q->right;
		while (p1) { st1.push(p1); p1 = p1->left; }
		delete_element(q->info);
	}
	return*this;
}

template<typename T>
inline void KSet<T>::swap(KSet<T>& s2)
{
	std::swap(s2.root, root);
}

template<typename T>
SubSet<T> KSet<T>::operator[](const KSet<T> & set2)
{
	SubSet<T> res; res.pset = this;
	SetEl<T>* p1 = root;
	SetEl<T>* p2 = set2.root;
	stack<SetEl<T>*> st1, st2;
	while (p1) { st1.push(p1); p1 = p1->left; }
	while (p2) { st2.push(p2); p2 = p2->left; }
	while (!st1.empty() && !st2.empty())
	{
		SetEl<T>* q1 = st1.top(); 
		SetEl<T>* q2 = st2.top(); 
		if (q1->info == q2->info)
		{
			res.subset.insert(q1->info);
			st1.pop();
			st2.pop();
			p1 = q1->right;
			p2 = q2->right;
			while (p1) { st1.push(p1); p1 = p1->left; }
			while (p2) { st2.push(p2); p2 = p2->left; }
		}
		else if (q1->info > q2->info)
		{
			st2.pop();
			p2 = q2->right;
			while (p2) { st2.push(p2); p2 = p2->left; }
		}
		else if (q1->info < q2->info)
		{
			st1.pop();
			p1 = q1->right;
			while (p1) 
			{
				st1.push(p1);
				p1 = p1->left; 
			}
		}
	}
	return res;
}

template<typename T>
void KSet<T>::delete01(SetEl<T>* p, SetEl<T>** pp)
{
	if (p->left)
		* pp = p->left;
	else
		*pp = p->right;
	delete p;
}

template <typename T>
ostream& operator << (ostream& os, const KSet<T>& s)
{
	SetEl<T>* p = s.root;
	stack <SetEl<T>*> st;
	while (p) { st.push(p); p = p->left; }
	while (!st.empty())
	{
		SetEl<T>* q = st.top(); st.pop();
		os << q->info << " ";
		p = q->right;
		while (p) { st.push(p); p = p->left; }
	}
	return os;
}

template <typename T>
istream& operator >> (istream& in, KSet<T>& s)
{
	int n;
	T val;
	in >> n;
	for (int i = 0; i < n; i++)
	{
		in >> val;
		s.insert(val);
	}
	return in;
}