#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <assert.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::abs;
using std::max;
using std::pair;
using std::reverse;
using std::swap;

/*
 * Interval Power Tree (drzewpo toęgowe)
 */
template<typename ValType>
class IntervalPTree {
public:

	IntervalPTree(size_t size) {
		this->size = size;
		load.resize(size, 0);
	}

	ValType sumFromStart(size_t end) {
		assert(end < size);

		ValType result = ValType();

		while (end > 0) {
			result += load[end];
			end -= ((end ^ (end - 1)) + 1)/2;
		}
		return result;
	}

	ValType query(size_t begin, size_t end) {
		assert(begin <= end);
		assert(end < size);

		if (begin != 0)
			--begin;

		return sumFromStart(end) - sumFromStart(begin);
	}

	void insert(size_t pos, ValType val) {
		assert(pos < size);

		while (pos < size) {
			load[pos] += val;
			pos += ((pos ^ (pos - 1)) + 1) / 2;
		}
	}

private:
	size_t size;
	vector<ValType> load;
};




/*
 * Interval Cover Tree
 */
template<typename ValType>
class IntervalCTree {

private:
	inline size_t leftChild(size_t pos) {
		return 2 * pos;
	}

	inline size_t rightChild(size_t pos) {
		return 2 * pos + 1;
	}

	inline bool isLeftChild(size_t pos) {
		return pos % 2 == 0;
	}

	inline bool isRightChild(size_t pos) {
		return pos % 2 == 1;
	}

	inline size_t rightSibling(size_t pos) {
		return pos+1;
	}

	inline size_t leftSibling(size_t pos) {
		assert(pos > 0);
		return pos-1;
	}

	inline size_t parrent(size_t pos) {
		return pos / 2;
	}

public:

	IntervalCTree(size_t size) {

		// Compute the next power of 2 the evil way
		size--;
		size |= size >> 1;
		size |= size >> 2;
		size |= size >> 4;
		size |= size >> 8;
		size |= size >> 16;
		size++;

		this->size = size;

		load.resize(2 * size, ValType());
		sub.resize(2 * size, ValType());
	}


	ValType query(size_t begin, size_t end) {
		assert(begin <= end);
		assert(end < size);

		ValType result = ValType();

		int length = 1;
		int left_length = 1;
		int right_length = 0;
		if (begin != end)
			right_length = 1;

		begin += size;
		end   += size;


		while (begin >= 1) {

			result += left_length*load[begin] + right_length*load[end];

			if (begin < end - 1) {
				if (isLeftChild(begin)) {
					result += sub[rightSibling(begin)];
					left_length += length;
				}
				if (isRightChild(end)) {
					result += sub[leftSibling(end)];
					right_length += length;
				}
			}

			// Move one level upward, length of interval increses twice
			begin  = parrent(begin);
			end = parrent(end);
			length *= 2;
		}


		return result;
	}

	void insert(size_t begin, size_t end, ValType val) {
		assert(begin <= end);
		assert(end <= size);

		int length = 1;

		begin += size;
		end   += size;
		load[begin] += val;
		sub[begin]  += val;

		if (begin != end) {
			load[begin] += val;
			sub[begin]  += val * length;			
		}

		while (begin >= 1) {

			if (begin < end - 1) {
				if (isLeftChild(begin)) {
					load[rightSibling(begin)] += val;
					sub[rightSibling(begin)]  += val * length;
				}
				if (isRightChild(end)) {
					load[leftSibling(end)] += val;
					sub[leftSibling(end)]  += val * length;
				}
			}

			// Not a a leaf, update sub
			if (end < size) {
				sub[begin] = sub[leftChild(begin)] + sub[rightChild(begin)] + load[begin] * length;
				sub[end] = sub[leftChild(end)] + sub[rightChild(end)] + load[end] * length;
			}

			// Move one level upward, length of interval increses twice
			begin  = parrent(begin);
			end = parrent(end);
			length *= 2;
		}
	}

private:
	size_t size;
	vector<ValType> load;
	vector<ValType> sub;
};


int main(int argc, char* argv[]) {
	std::ios::sync_with_stdio(false);

	// IntervalPTree<double> intervals(10);
	// intervals.insert(1, 1.0);
	// intervals.insert(2, 1.2);
	// intervals.insert(4, 1);

	// cout << intervals.query(0, 0) << endl;
	// cout << intervals.query(1, 1) << endl;
	// cout << intervals.query(2, 2) << endl;
	// cout << intervals.query(3, 3) << endl;


	IntervalCTree<double> intervals2(10);
	intervals2.insert(0, 0, 1);
	intervals2.insert(1, 1, 1.0);
	intervals2.insert(2, 2, 1.2);
	intervals2.insert(2, 4, 1);
	intervals2.insert(10, 10, 1);

	cout << intervals2.query(0, 0) << endl;
	cout << intervals2.query(1, 1) << endl;
	cout << intervals2.query(2, 2) << endl;
	cout << intervals2.query(2, 4) << endl;
	cout << intervals2.query(10, 10) << endl;
	cout << intervals2.query(0, 10) << endl;


	return 0;
}