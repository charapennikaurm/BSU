#include "KBinaryTree.h"

struct KFive
{
	KFive(KTreeNode* _ptr,bool HR) :height(0), versh(0),HasRight(HR) ,fl(true), pNode(_ptr) {}
	int height;
	int versh;
	bool fl;
	bool HasRight;
	KTreeNode* pNode;
};

void KBinaryTree::Insert(const int x)
{
	KTreeNode** pp = &fRoot;
	KTreeNode* p = fRoot;
	while (p)
	{
		if (x<p->info)
		{
			pp = &p->pLeft;
			p = p->pLeft;
		}
		else
		{
			pp = &p->pRight;
			p = p->pRight;
		}
	}
	*pp = new KTreeNode(x);
	return;
}

bool KBinaryTree::Add(const int x)
{
	KTreeNode** pp = &fRoot;
	KTreeNode* p = fRoot;
	while (p)
	{
		if (x < p->info)
		{
			pp = &p->pLeft;
			p = p->pLeft;
		}
		else if (x > p->info)
		{
			pp = &p->pRight;
			p = p->pRight;
		}
		else //x==p->info
		{
			return false;
		}
	}
	*pp = new KTreeNode(x);
	return true;
}

bool KBinaryTree::Delete(const int x)
{
	KTreeNode** pp = &fRoot;
	KTreeNode* p = fRoot;
	while (p)
	{
		if (x < p->info) { pp = &p->pLeft; p = p->pLeft; }
		else if (x > p->info) { pp = &p->pRight; p = p->pRight; }
		else  break;//когда значение в данной вершине равно x
	}
	if (!p)//вершина со значением x не найдена
		return false;
	if (IsTwoSons(p))//есть 2 потомка
	{
		pp = &p->pLeft;
		KTreeNode* t = p->pLeft;
		while (t->pRight) { pp = &t->pRight; t = t->pRight; }
		p->info = t->info;
		Delete01Sons(t, pp);
	}
	else
		Delete01Sons(p, pp);
	return true;

}

KTreeNode* KBinaryTree::Find(const int x)
{
	KTreeNode* p = fRoot;
	while (p)
	{
		if (x < p->info)  p = p->pLeft; 
		else if (x > p->info)  p = p->pRight; 
		else/*x==p->info*/ return p;
	}
	return p;
}

int KBinaryTree::Count()
{
	int c = 0;
	KTreeNode* q;
	stack <KTreeNode*> st;
	st.push(fRoot);
	while (!st.empty())
	{
		q = st.top(); st.pop();
		if (q)
		{
			++c; st.push(q->pLeft); st.push(q->pRight);
		}
	}
	return c;
}

void KBinaryTree::PreOrderPrint(ostream& os)
{
	KTreeNode* q;
	stack <KTreeNode*> st{ {fRoot} };
	while (!st.empty())
	{
		q = st.top(); st.pop();
		if (q)
		{
			os << q->info << " ";
			st.push(q->pRight); st.push(q->pLeft);
		}
	}
}

void KBinaryTree::InOrderPrint(ostream& os)
{
	KTreeNode* p=fRoot;
	stack <KTreeNode*> st;
	while (p) { st.push(p); p = p->pLeft; }
	while (!st.empty())
	{
		KTreeNode* q = st.top(); st.pop();
		os << q->info << " ";
		p = q->pRight;
		while (p) { st.push(p); p = p->pLeft; }
	}
}

void KBinaryTree::PostOrderPrint(ostream& os)
{
	stack <KTreeNode*> st;
	KTreeNode* pPrev = nullptr; KTreeNode* q = fRoot;
	while (true)
	{
		while (q) { st.push(q); q = q->pLeft;}
		if (st.empty())
			break;
		else
		{
			q = st.top(); 
			if (q->pRight && q->pRight != pPrev)//pPrev-указатель на последнее дерево, которое обошли
			{
				q = q->pRight;
			}
			else
			{
				os << q->info << " ";
				st.pop();
				pPrev = q;
				q = nullptr;
			}
		}
	}
	return;
}

void  KBinaryTree::PostOrder()
{
	stack<pair<KTreeNode*, int>>st{ {make_pair(fRoot,2)} };
	while (!st.empty())
	{
		KTreeNode* q = st.top().first; auto pr = st.top().second; st.pop();
		if (pr == 0)
		{
				std::cout << q->info << " ";
		}
		else if (pr == 1)//надо обойти правое поддерево
		{
			if (q != nullptr)
			{
				//st.push(make_pair(q, 0));
				st.push(make_pair(q->pRight, 2));
				st.push(make_pair(q, 0));
			}
		}
		else if (pr == 2)//не обошли левое поддерево
		{
			if (q != nullptr)
			{				
				st.push(make_pair(q, 1));
				st.push(make_pair(q->pLeft, 2));
			}
		}
	}
}

KTreeNode* KBinaryTree::LeftGrRightMax()
{
	KTreeNode* q = fRoot, * prev = nullptr, * pMaxTree = nullptr;
	std::stack<KFive> st;
	int h = 0, v = 0;
	bool fl = true;
	int vmax = 0;

	while (true)
	{
		while (q)
		{
			if (q->pRight) st.push(KFive(q, true));
			else st.push(KFive(q, false));
			q = q->pLeft;
		}
		if (st.empty())
			break;
		else
		{
			q = st.top().pNode;
			//обошли левую часть и идем на правую
			if (q->pRight && q->pRight != prev)
			{
				st.top().height = h; st.top().fl = fl; st.top().versh = v;
				q = q->pRight;
				h = 0; v = 0;
				fl = true;
			}
			else
			{
				v = 1 + v + st.top().versh;
				if (IsLeaf(q)) fl = true;
				else
				{
					if (st.top().HasRight)
						fl = fl && st.top().fl && (h < st.top().height);
					else//нет правого поддерева
						fl = fl;
				}
				h = 1 + max(h, st.top().height);
				if (fl && v>vmax)
				{
					vmax = v;
					pMaxTree = q;
				}
				st.pop();
				prev = q;
				q = nullptr;
			}

		}
	}


	return pMaxTree;
}

int KBinaryTree::Height()
{
	stack<pair <KTreeNode*, int>> st;
	KTreeNode* pPrev=nullptr, * q=fRoot;
	int h = 0;
	while (true)
	{
		while (q) { st.push(make_pair(q, 0)); q = q->pLeft; }
		if (st.empty())
			break;
		else
		{
			q = st.top().first;
			if (q->pRight && q->pRight != pPrev)
			{
				st.top().second = h;
				q = q->pRight;
				h = 0;
			}
			else
			{
				h = 1 + max(h, st.top().second);
				st.pop();
				//st.top().second = h;
				pPrev = q; q = nullptr;
			}
		}
	}
	return h;
}

inline bool KBinaryTree::IsLeaf(KTreeNode* p)
{
	return(p->pRight == nullptr && p->pLeft == nullptr);
}

inline bool KBinaryTree::IsTwoSons(KTreeNode* p)
{
	return (p->pRight && p->pLeft);
}

inline void KBinaryTree::Delete01Sons(KTreeNode* p, KTreeNode** pp)
{
	if (p->pLeft)* pp = p->pLeft;
	else *pp = p->pRight;
	delete p;
}