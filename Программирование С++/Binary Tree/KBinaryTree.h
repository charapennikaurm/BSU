#pragma once
#include <iostream>
#include <algorithm>
#include <stack>
#include <tuple>
using namespace std;

struct KTreeNode
{
	explicit KTreeNode(int inf = 0, KTreeNode * left = nullptr, KTreeNode * right = nullptr) : info(inf), pLeft(left), pRight(right) {};

	KTreeNode* pLeft;
	KTreeNode* pRight;
	int info;
};

class KBinaryTree
{
public:
	KBinaryTree() :fRoot (nullptr){}; 
	~KBinaryTree() { this->Clear(); }
	//Add element doesn't  matter if unique or not
	void Insert(const int x);
	//Add unique element(true if added)
	bool Add(const int x);
	bool Delete(const int x);
	int Height();
	bool Delete(KTreeNode* p) { return Delete(p->info); }
	void Clear() { while (fRoot) Delete(fRoot); }
	bool IsEmpty() {return fRoot == nullptr; } 
	KTreeNode* Find(const int x);
	//Amount of nodes in tree
	int Count();
	void PreOrderPrint(ostream & os);//(root-left-right)
	void InOrderPrint(ostream & os);//(left-root-right), prints in sorted order
	void PostOrderPrint(ostream & os);//(left-right-root)
	void PostOrder();//left-right-root with varriables for flag
	KTreeNode* LeftGrRightMax();
private:
	bool IsLeaf(KTreeNode* p);
	bool IsTwoSons(KTreeNode* p);
	void Delete01Sons(KTreeNode *p,KTreeNode **pp);
private:
	KTreeNode* fRoot;
};