#include <cassert>
#include <iostream>
#include <string>
#include <map>

using namespace std;


int longest = 0;

template<unsigned S>
struct SufixTree {

	struct Node;

	void build(const char *T, unsigned s) {
		assert(s < S);

		size = s;
		for (unsigned i = 0; i < s; ++i)
			text[i] = T[i];
		text[s] = 0;

		for (unsigned i = s; i > 0; --i)
			add_sufix(i-1);
	}

	void add_sufix(unsigned pos) {
		root.add_sufix(text, pos, pos);
	}

	void print() {
		in_order_print(root, 0);
	}

	void in_order_print(Node &n, int depth) {

		// if (n.start_idx != S) 
			// std::cout  << text + (n.start_idx - (depth-1)) << endl;
		// cout  << "At node " << n.start_idx << endl;

		Node *child;
		// cout << "pre\n";
		for (child = n.first_child; child != 0 && text[n.start_idx+1] > text[child->start_idx]; child = child->sibling) {
			// cout << "investigate child " << text[child->start_idx] << endl;
			in_order_print(*child, depth+1);
		}

		// cout << "in\n";
		if (n.start_idx != S) 
			std::cout  << text + (n.start_idx - (depth-1)) << " " << depth << endl;

		// cout << "post\n";
		for (; child != 0; child = child->sibling)
			in_order_print(*child, depth+1);

		if (depth > longest)
			longest = depth;

	}

	unsigned size;
	char text[S];
	Node root;
};

template<unsigned S>
struct SufixTree<S>::Node {

	Node() : start_idx(S), first_child(0), sibling(0) { }

	Node(unsigned s, Node *sib = 0) : start_idx(s), first_child(0), sibling(sib) { }

	void add_sufix(char *text, unsigned pos, unsigned acc) {
		assert(text);

		cout << "adding " << pos << " " << acc << endl;

		if (!text[acc])
			return;

		Node **edge = &first_child;
		for (; edge != 0 && *edge != 0 && text[(*edge)->start_idx] <= text[pos]; edge = &(*edge)->sibling) {
			if (text[(*edge)->start_idx] == text[pos])
				break;
		}
		// if (*prev != 0 && text[(*prev)->start_idx] <= text[pos])
		// 	edge = prev;
		// while (edge != 0 && *edge != 0) {
		// 	Node **next = &(*edge)->sibling;
		// 	cout << text[(*edge)->start_idx]  << ", ";
		// 	if (*next && text[(*next)->start_idx] <= text[acc])
		// 		edge = &(*edge)->sibling;
		// 	else 
		// 		break;
		// }
		// cout << endl;

		// cout << *edge << endl;
		if (*edge) {
			// cout << "start_idx: " << (*edge)->start_idx;
			// cout << " \"" << text[(*edge)->start_idx] << "\"";
			// cout << " pos: " << pos;
			// cout << " \"" << text[pos] << "\"" << endl;
		}
		if (*edge && text[(*edge)->start_idx] == text[acc]) {
			(*edge)->add_sufix(text, pos+1, acc+1);
		}
		else {
			if (*edge)
				cout << "Create before " << (*edge)->start_idx << endl;
			*edge = new Node(acc, *edge);
			// (*edge)->add_sufix(text, pos+1, acc+1);
		}
	}

	unsigned start_idx;
	Node *first_child;
	Node *sibling;
};


int main() {
	static SufixTree<1000> tree;
	// string b = "0111156";
	string b = "1234123";
    //         "0123456789"
	tree.build(b.c_str(), b.length());
	tree.print();

	cout << longest << endl;

	return 0;
}