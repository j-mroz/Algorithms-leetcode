#include <iostream>
#include <unordered_map>
#include <cassert>
#include <string>

static const unsigned Inf = (unsigned)-1;


struct Node {
	Node(unsigned b, unsigned e, char *t, Node *p) 
		: begin(b), end(e), text(t), parent(p), suffix_link(0) {}

	void add_child(char c, Node *n) {
		assert(children.count(c) == 0);
		children[c] = n;
	}

	bool is_leaf() {
		return !children.size();
	}

	unsigned begin;
	unsigned end;

	char *text;
	Node *parent;
	Node *suffix_link;
	std::unordered_map<char, Node*> children;
};


template<unsigned S>
struct SuffixTree {

	SuffixTree() : root(0), end(0) {}

	Node* build(const char* x, unsigned size) {

		active_length = 0;
		active_begin = 0;
		active_end = 0;
		prev_split_node = 0;
		remainder = 1;

		for (int i = 0; i < size; ++i)
			text[i] = x[i];

		root = new Node(0, 0, text, 0);
		active_dst = new Node(0, 0, text, root);
		root->add_child(text[0], active_dst);
		active_node = root;

		for (int i = 1; i < size; ++i)
			add_prefix(i);

		return 0;
	}

	void add_prefix(unsigned end_idx) {

		std::cout << "add prefix " << text[end_idx] << std::endl;


		Node *dst;
		dst = find_edge(active_node, text[end_idx]);
		// if (active_dst->begin <= active_dst->end) {

		// 	dst = find_edge(active_node, text[active_dst->begin]);
		// 	long long span = (long long)active_dst->end - active_dst->begin;

		// 	if (text[end_idx] != text[dst->begin + span + 1]) {
		// 		std::cout << "???" << std::endl;
		// 	}

		// } else {
		// 	dst = find_edge(active_node, text[end_idx]);
		// }

		if (dst != 0) {
			// dst->end++;

			if (remainder == 1) {
				active_begin = end_idx;
			}
			remainder++;
			// active_node = dst->parent; // ???
			// active_end = end_idx;
			active_length++;
			std::cout << "\nextend r=" << remainder << std::endl;
			std::cout << dst->begin << " " << dst->end << " " << end << std::endl;
			if (active_begin+active_length <= active_node->end) {
				std::cout << "end of edge" << std::endl;
			}
		} else if (!dst && remainder == 1) {
			std::cout << "Add " << text[end_idx] << std::endl;
			dst = new Node(end_idx, Inf, text, active_node);
			root->add_child(text[end_idx], dst);
		} else {

			while (remainder > 0) {

				std::cout << "Split " << std::endl;

				Node *split_node;
				if (active_length > 0) {
					split_node = find_edge(active_node, text[active_begin]);
					unsigned split_point = split_node->begin+active_length;

					std::cout << "Truncate " << text[split_node->begin]  << " to " << split_point-1 << std::endl;
					split_node->end = split_point-1;

					std::cout << "Add " << text[split_point] << " to " << text[split_node->begin] << std::endl;
					split_node->add_child(text[split_point], new Node(split_point, Inf, text, split_node));

					// TODO: add only when possible
					std::cout << "Add " << text[end_idx] << " to " << text[split_node->begin] << std::endl;
					split_node->add_child(text[end_idx], new Node(end_idx, Inf, text, split_node));
				} else {
					std::cout << "Add " << text[end_idx] << " to root" << std::endl;
					root->add_child(text[end_idx], new Node(end_idx, Inf, text, root));
				}

				remainder--;

				if (active_node == root) {
					std::cout << "rule 1" << std::endl;
					active_begin++;
					active_length--;
				}

				if (prev_split_node) {
					std::cout << "rule 2" << std::endl;
					prev_split_node->suffix_link = split_node;
				}
				prev_split_node = split_node;
			}
			prev_split_node = 0;
		}
		// active_dst->end++;
		end++;


		for (int j = 0; j < end_idx; ++j) {


			// // Find the end of the path from the root labelled S[j..i] in the current tree.
			// Node *node = find_node(i, j);
			// int pos -1 //= find_pos(node, )

			// // case 1
			// if (node->is_leaf()) {
			// 	// ++node->len;
			// 	// do nothing
			// }
			// // case 2: add a leaf edge
			// else if (!node->is_leaf()) {
			// 	if (pos == Inf || pos) {
			// 		node->add_child(new Node(i, Inf, text, node));
			// 	} else {
			// 		node->split(pos);
			// 	}
			// }
			// // case 3
			// // else if () {

			// // }

			// // Extend that path by adding character S[i+l] if it is not there already
			// ++end;
		}
	}


	Node* find_edge(Node *node, char c) {
		if (node->children.count(c))
			return node->children[c];
		return 0;
	}


	Node *root;
	Node *active_node;
	Node *active_dst;
	Node *prev_split_node;

	unsigned active_begin;
	unsigned active_end;
	unsigned active_length;
	unsigned remainder;

	unsigned end;
	char text[S];
};


int main() {
	// std::string x = "banana";
	std::string x = "abcabxabcd";
	SuffixTree<1000> tree;
	tree.build(x.c_str(), x.length());
	return 0;
}