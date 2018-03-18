//
// https://www.hackerrank.com/challenges/two-two/problem
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <iterator>
using namespace std;

using ivec = vector<int>;
using strvec = vector<string>;
using iset = set<int>;

// Aho Corasick automaton
template <unsigned char MIN_SYMBOL, unsigned char MAX_SYMBOL>
class AhoCorasickMatcher {
	static const auto SYMBOLS_COUNT  = MAX_SYMBOL - MIN_SYMBOL + 1;

	size_t get_child(size_t node, unsigned char symbol) {
		return states_map[node][symbol - MIN_SYMBOL];
	}

	void add_child(size_t parent, unsigned char symbol, size_t child) {
		states_map[parent][symbol - MIN_SYMBOL] = child;
	}

	size_t add_state() {
		states_map.push_back(ivec(SYMBOLS_COUNT, -1));
		fall_back.push_back(-1);
		output.push_back(iset());
		return states_map.size() - 1;
	}


	void build_trie() {
		add_state();
		fall_back[0] = 0;

		for (auto key_idx = 0; key_idx < keys.size(); ++key_idx) {
			auto current = 0;
			for (auto symbol : keys[key_idx]) {
				if (get_child(current, symbol) == -1) {
					add_child(current, symbol, add_state());
				}
				current = get_child(current, symbol);
			}
			output[current].insert(key_idx);
		}
	}

	void build_fallback() {
		auto nodes_queue = queue<int>();
		auto root_id = 0;

		for (auto c = MIN_SYMBOL; c <= MAX_SYMBOL; ++c)
			if (get_child(root_id, c) == -1)
				add_child(root_id, c, root_id);

		for (auto dst_node : states_map[root_id]) {
			if (dst_node == 0)
				continue;
			fall_back[dst_node] = root_id;
			nodes_queue.push(dst_node);
		}

		while (not nodes_queue.empty()) {
			auto node_id = nodes_queue.front(); nodes_queue.pop();

			for (auto symbol = MIN_SYMBOL; symbol <= MAX_SYMBOL; ++symbol) {
				auto child_id = get_child(node_id, symbol);
				if (child_id == -1)
					continue;

				auto back = next_state(fall_back[node_id], symbol);
				fall_back[child_id] = back;

				output[child_id].insert(output[back].begin(),
										output[back].end());
				nodes_queue.push(child_id);
			}
		}
	}

	int next_state(int state, char symbol) {
		auto next = state;

		while (get_child(next, symbol) == -1) {
        	next = fall_back[next];
		}

        return get_child(next, symbol);
	}

public:
	size_t match(const string &text) {
		int matches = 0;
		auto state= 0ul;

		for (auto text_idx = 0ul; text_idx < text.size(); ++text_idx) {
			state = next_state(state, text[text_idx]);
			if (!output[state].size())
				continue;
			matches += output[state].size();
		}
		return matches;
	}

	AhoCorasickMatcher(strvec keys, size_t alphabet_size=26) {
		this->keys = move(keys);

		states_map.reserve(255*800);
		output.reserve(255*800);
		fall_back.reserve(255*800);

		build_trie();
		build_fallback();
	}

private:
	vector<iset> output;
	vector<ivec> states_map;
	ivec fall_back;
	strvec keys;
};


strvec get_powers_of_2(int n) {
	auto powers = vector<string>(n);

	auto p = string("1");
	p.reserve(255);
	powers[0] = p;
	for (auto i = 1; i < powers.size(); ++i) {
		auto carry = char(0);
		for (auto &c : p) {
			auto rem = (c - '0') * 2 / 10;
			c = ((c - '0') * 2) % 10 + carry + '0';
			carry = rem;
		}
		if (carry > 0)
			p.push_back(carry + '0');
		powers[i] = p;
		reverse(powers[i].begin(), powers[i].end());
	}

	return powers;
}


int main() {
   	auto powers = get_powers_of_2(801);
	auto ac_trie = AhoCorasickMatcher<'0', '9'>(powers, 10);
   	auto tests = 0;
   	cin >> tests;
   	auto numbers = string();

   	for (auto t = 0; t < tests; ++t) {
   		numbers.clear();
   		cin >> numbers;
   		cout << ac_trie.match(numbers) << endl;
   	}

    return 0;
}
