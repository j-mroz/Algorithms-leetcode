#include <cstdlib>
#include <time.h>
#include <iostream>
#include <new>
#include <cassert>
#include <vector>
#include <string>

static const unsigned long long RAND_A = 123456789;
static const unsigned long long RAND_B = 12345;
unsigned long long RAND_SEED = 0x123986734;
unsigned long long _rand() {
	RAND_SEED = RAND_A*RAND_SEED + RAND_B;
	return RAND_SEED;
}

template <typename T, unsigned min = 0, unsigned max = 101> 
struct TreapNode {

	TreapNode() : val(), parrent(0), left(0), right(0) {
		randomize();
	}

	TreapNode(T v, TreapNode *p, TreapNode *l, TreapNode *r) 
			: val(v), parrent(p), left(l), right(r) {
		randomize();
	}

	void randomize() {
		priority = _rand() % (max-min) + min;
	}

	T val;
	TreapNode *parrent, *left, *right;
	unsigned int priority;
};

template <typename T>
struct TreapTree {

	typedef TreapNode<T> Node;

	TreapTree() {
		root = 0;
		RAND_SEED = (unsigned long long)&root;
	}

	~TreapTree() {
		clear();
	}

	void clear() {

	}

	Node* insert(T val) {

		// std::cout << "insert: " << val << std::endl;

		Node* node = insert(val, &root, 0);

		while (node != root && node->priority < node->parrent->priority) {
			assert(node->parrent);

			Node *n_parent = node->parrent;
			Node *n_grandpa = node->parrent->parrent;

			Node **edge = 0;
			if (n_parent == root) {
				edge = &root;
			} else if (n_grandpa->left == n_parent) {
				edge = &n_grandpa->left;
			} else {
				assert(n_parent == n_grandpa->right);
				edge = &n_grandpa->right;
			}

			if (node == n_parent->left) {
				rotate_right(edge);
			} else {
				rotate_left(edge);
			}
		}
		assert(node != node->left);
		assert(node != node->right);

		return node;
	}

	Node* insert(T& val, Node **edge, Node *parent) {
		assert(edge);
		Node *node = *edge;

		if (node) {
			if (val < node->val)
				return insert(val, &node->left, node);
			else
				return insert(val, &node->right, node);
		}
		*edge = new (std::nothrow) Node(val, parent, 0, 0);
		return *edge;
	}


	void remove(const T &val) {

	}

	void remove(const T *val) {

	}

	void remove(Node *node) {
		assert(node);
		// std::cout << "remove: " << node->val << std::endl;

		Node **edge = &node->parrent;
		if (node == root) {
			// std::cout << "edge is root" << std::endl;
			edge = &root;
		}

		if (!node->right) {
			// std::cout << "right" << std::endl;
			assert(node != node->left);
			*edge = node->left;
		} else if (!node->left) {
			// std::cout << "left" << std::endl;
			assert(node != node->right);
			*edge = node->right;
		} else {
			// std::cout << "center" << std::endl;
			Node *u = node->right;
			while (u->left)
				u = u->left;
			assert(u != node);

			if (u->parrent != node) {
				u->parrent->left = 0;
				if (u->right) {
					u->parrent->left = u->right;
					u->right->parrent = u->parrent;
				}
			}

			*edge = u;
			u->left = node->left;
			if (node->right != u) 
				u->right = node->right;
			u->parrent = node->parrent;
			assert(u != u->left);
			assert(u != u->right);

			if (node->left && node->left != u)
				node->left->parrent = u;
			if (node->right && node->right != u)
				node->right->parrent = u;
		}

		assert(node != root && "root not change!");


		node->parrent = 0;
		node->left = 0;
		node->right = 0;

		// TODO: rebalance!
		Node *x = *edge;
		if (x) {
			std::cout << "rebalance" << std::endl;
			bool left_unbalanced = x->left && x->left->priority < x->priority;
			bool right_unbalanced = x->right && x->right->priority < x->priority;
			while (left_unbalanced || right_unbalanced) {
				if (left_unbalanced) {
					rotate_right(&x->left);
				} else if (right_unbalanced) {
					rotate_left(&x->right);
				}
			}
		}

	}

	void rotate_left(Node **edge) {
		// std::cout << "rotate_left" << std::endl;
		assert(edge);

		Node *x = *edge;
		assert(x->right);

		Node *y = x->right;

		x->right = y->left;
		if (y->left)
			y->left->parrent = x;
		y->parrent = x->parrent;

		*edge = y;

		y->left = x;
		x->parrent = y;
	}

	void rotate_right(Node **edge) {
		// std::cout << "rotate_right" << std::endl;
		assert(edge);

		Node *x = *edge;
		assert(x->left);

		Node *y = x->left;

		x->left = y->right;
		if (y->right)
			y->right->parrent = x;
		y->parrent = x->parrent;

		*edge = y;

		y->right = x;
		x->parrent = y;
	}

	TreapNode<T> *root;
};


template<typename N>
void print_inorder(N *node) {
	if (!node)
		return;
	print_inorder(node->left);
	// std::cout << "p:" << node->priority << "\tv:" << node->val << std::endl;
	print_inorder(node->right);

}

int tabs = 0;
template<typename N>
void print_tree(N *node) {
	if (!node)
		return;
	// std::cout << "\n" << std::string(2*tabs, ' ') << "p:" << node->priority << "\tv:" << node->val << std::endl;
	
	// std::cout << std::string(2*tabs, ' ')  << "{" ;
	++tabs;
	print_tree(node->left);
	--tabs;
	// std::cout << std::string(2*tabs, ' ')  << "}" << std::endl ;

	// std::cout << std::string(2*tabs, ' ')  << "{";
	++tabs;
	print_tree(node->right);
	--tabs;
	// std::cout << std::string(2*tabs, ' ')  << "}" << std::endl;

}

int main() {

	typedef TreapTree<int> Tree;
	Tree tree;
	
	std::vector<Tree::Node *> v;
	for (int i = 0; i < 10; ++i)
		v.push_back( tree.insert(i) );


	for (int i = 10; i > 0; --i) {	
		if (!tree.root) 
			// std::cout << "tree root is null!!" << std::endl;
		// tree.remove(tree.root);
		tree.remove(v[i]);
		// print_tree(tree.root);
		// std::cout << std::endl;
	}

	return 0;
}