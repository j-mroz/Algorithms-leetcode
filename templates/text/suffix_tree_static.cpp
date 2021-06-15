#include <cassert>
#include <iostream>
#include <string>
#include <map>

using namespace std;

template<unsigned S>
struct SufixTree {

	struct Node;

	void build(const char *T, unsigned s) {
		assert(s < S);

		size = s;
		for (unsigned i = 0; i < s; ++i)
			text[i] = T[i];
		text[s] = 0;

		nodes[0] = Node();
		next_node = 1;

		for (unsigned i = s; i > 0; --i)
			add_sufix(i-1);
	}

	void add_sufix(unsigned pos) {
		// node 0 is root
		nodes[0].add_sufix(text, pos, pos, nodes[next_node++]);
	}

	void print() {
		in_order_print(nodes[0]);
	}

	unsigned suffix(unsigned i) {
		unsigned res;
		suffix(nodes[0], res, i);
		return res;
	}

	bool suffix(Node &n, unsigned &pos, unsigned &remaining) {
		if (remaining == 0) {
			pos = n.start_idx != S ? n.start_idx : size;
			return false;
		}

		Node *child = n.first_child;
		while (child != 0 && suffix(*child, pos, --remaining))
			child = child->sibling;

		return true;
	}	

	void in_order_print(Node &n) {
		Node *child;
		for (child = n.first_child; child != 0 &&  text[n.start_idx] > text[child->start_idx]; child = child->sibling)
			in_order_print(*child);

		if (n.start_idx != S)
			std::cout << text + n.start_idx << endl;

		for (; child != 0; child = child->sibling)
			in_order_print(*child);

	}

	unsigned size;
	char text[S];
	Node nodes[S];
	unsigned next_node;
};


template<unsigned S>
struct SufixTree<S>::Node {

	Node() : start_idx(S), first_child(0), sibling(0) { }

	Node(unsigned s, Node *sib = 0) : start_idx(s), first_child(0), sibling(sib) { }

	void add_sufix(char *text, unsigned pos, unsigned acc, Node& memory) {
		assert(text);

		if (!text[acc])
			return;

		Node **edge = &first_child;
		while (edge != 0 && *edge != 0 && text[(*edge)->start_idx] <= text[pos])
			edge = &(*edge)->sibling;

		if (*edge && text[(*edge)->start_idx] == text[pos])
			(*edge)->add_sufix(text, pos, acc+1, memory);
		else {
			memory = Node(pos, *edge);
			*edge = &memory;
		}
	}

	unsigned start_idx;
	Node *first_child;
	Node *sibling;
};


int main() {
	static SufixTree<1000> tree;
	string b = "monster";
	// string b = "bananaasdxeaabbcctasd";
	tree.build(b.c_str(), b.length());
	tree.print();

	cout << endl;

	for (unsigned i = 0; i <= b.length(); ++i) 
		cout <<  tree.suffix(i) << endl;

	return 0;
}