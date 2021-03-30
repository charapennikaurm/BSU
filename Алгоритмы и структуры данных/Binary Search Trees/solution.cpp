#include <iostream>
#include <fstream>
#include <algorithm>

//BINARY SEARCH TREE CLASS

struct tree_node {
	tree_node(long long key = 0) : key(key), right(nullptr), left(nullptr), height(0),
		number_of_farthest_leafs(0), max_semipath_length(0), b(0), a(0) {};

	bool is_leaf() { return (left == nullptr) && (right == nullptr); }
	bool has_two_sons() { return left && right; }
	bool has_right_son() { return right != nullptr; }
	bool has_left_son() { return left != nullptr; }

	long long key;
	tree_node* left;
	tree_node* right;
	long long height;
	long long number_of_farthest_leafs;//number of leafs,that node->leaf path length = height of node
	long long max_semipath_length;
	long long b;//number of max semipath with root in this node
	long long a;//number of max semipath through this node(node!=root of semipath)
};

class tree {
public:
	tree() :root(nullptr), max_semipath_len(0) {};
	void insert(const long long& key);
	void print(std::ostream& out) { print_subtree(out, root); }
	void del(const long long& key);
	//sets correct values for height and number_of_farthest_leafs of every node,
	//sets max_semipath_len for both every node and whole tree,
	void set_heights() { set_heights(root); }
	void set_b() { set_b(root); }
	void set_a_and_print(std::ostream& out) { set_a_and_print(root, nullptr, out); }
	tree_node* get_root() { return root; }
private:
	void set_b(tree_node* root);
	void set_a_and_print(tree_node* root, tree_node* parrent, std::ostream& out);
	void set_heights(tree_node* root);
	void print_subtree(std::ostream& out, tree_node* root);
	void delete_01sons(tree_node* ptr, tree_node** pptr);
private:
	long long max_semipath_len;
	tree_node* root;
};

void tree::insert(const long long& key) {
	tree_node** pptr = &root;
	tree_node* ptr = root;
	while (ptr) {
		if (key == ptr->key) {
			return;
		}
		else if (key > ptr->key) {
			pptr = &ptr->right;
			ptr = ptr->right;
		}
		else {
			pptr = &ptr->left;
			ptr = ptr->left;
		}
	}
	*pptr = new tree_node(key);
}

void tree::del(const long long& key) {
	tree_node** pptr = &root;
	tree_node* ptr = root;
	while (ptr != nullptr && key != ptr->key) {
		if (key < ptr->key) {
			pptr = &ptr->left;
			ptr = ptr->left;
		}
		else if (key > ptr->key) {
			pptr = &ptr->right;
			ptr = ptr->right;
		}
	}
	if (ptr == nullptr) return;
	if (ptr->has_two_sons()) {
		pptr = &ptr->right;
		tree_node* p = ptr->right;
		while (p->left != nullptr) { pptr = &p->left; p = p->left; }
		ptr->key = p->key;
		delete_01sons(p, pptr);
	}
	else {
		delete_01sons(ptr, pptr);
	}
}

void tree::print_subtree(std::ostream& out, tree_node* root) {
	if (!root) { return; }
	out << root->key << " " << (root->a + root->b) << "\n";
	print_subtree(out, root->left);
	print_subtree(out, root->right);
}

void tree::delete_01sons(tree_node* ptr, tree_node** pptr) {
	if (ptr->left != nullptr) { *pptr = ptr->left; }
	else { *pptr = ptr->right; }
	delete ptr;
}

void tree::set_heights(tree_node* root) {
	if (!root) { return; }
	set_heights(root->left); set_heights(root->right);
	if (root->is_leaf()) {
		root->height = 0;
		root->number_of_farthest_leafs = 1;
		root->max_semipath_length = 0;
	}
	else if (root->has_two_sons()) {
		root->height = std::max(root->left->height, root->right->height) + 1;
		root->max_semipath_length = root->left->height + root->right->height + 2;
		if (root->max_semipath_length > this->max_semipath_len) {
			this->max_semipath_len = root->max_semipath_length;
		}
		if (root->right->height == root->left->height) {
			root->number_of_farthest_leafs = root->left->number_of_farthest_leafs + root->right->number_of_farthest_leafs;
		}
		else if (root->right->height > root->left->height) {
			root->number_of_farthest_leafs = root->right->number_of_farthest_leafs;
		}
		else/*root->right->height < root->left->height*/ {
			root->number_of_farthest_leafs = root->left->number_of_farthest_leafs;
		}
	}
	else if (root->has_left_son()) {
		root->height = root->left->height + 1;
		root->number_of_farthest_leafs = root->left->number_of_farthest_leafs;
		root->max_semipath_length = root->left->height + 1;
		if (root->max_semipath_length > this->max_semipath_len) {
			this->max_semipath_len = root->max_semipath_length;
		}
	}
	else /*root->has_right_son()*/ {
		root->height = root->right->height + 1;
		root->number_of_farthest_leafs = root->right->number_of_farthest_leafs;
		root->max_semipath_length = root->right->height + 1;
		if (root->max_semipath_length > this->max_semipath_len) {
			this->max_semipath_len = root->max_semipath_length;
		}
	}
}

void tree::set_b(tree_node* root) {
	if (!root) { return; }
	if (root->max_semipath_length == this->max_semipath_len) {
		if (root->has_two_sons()) { root->b = root->left->number_of_farthest_leafs * root->right->number_of_farthest_leafs; }
		else if (root->has_left_son()) { root->b = root->left->number_of_farthest_leafs; }
		else if (root->has_right_son()) { root->b = root->right->number_of_farthest_leafs; }
		else if (root->is_leaf()) { root->b = 1; }
	}
	set_b(root->left);
	set_b(root->right);
}

void tree::set_a_and_print(tree_node* root, tree_node* parrent, std::ostream& out) {
	if (!root) { return; }
	if (root == this->root) { root->a = 0; }
	else if (parrent->has_two_sons()) {
		if (parrent->right->height == parrent->left->height) {
			root->a = parrent->b + root->number_of_farthest_leafs * parrent->a / parrent->number_of_farthest_leafs;
		}
		else if (parrent->right->height > parrent->left->height) {
			if (root == parrent->right) { root->a = parrent->a + parrent->b; }
			else if (root == parrent->left) { root->a = parrent->b; }
		}
		else if (parrent->right->height < parrent->left->height) {
			if (root == parrent->left) { root->a = parrent->a + parrent->b; }
			else if (root == parrent->right) { root->a = parrent->b; }
		}
	}
	else if (!parrent->is_leaf()) {
		root->a = parrent->a + parrent->b;
	}
	out << root->key << " " << (root->a + root->b) << "\n";
	set_a_and_print(root->left, root, out);
	set_a_and_print(root->right, root, out);
}

//BINARY SEARCH TREE CLASS

void task(std::ifstream& in, std::ofstream& out) {
	long long root_value, value;
	tree t;
	in >> root_value; t.insert(root_value);
	while (in >> value) { t.insert(value); }
	t.del(root_value);
	t.set_heights();
	t.set_b();
	t.set_a_and_print(out);
}

int main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	task(in, out);
}