#include <iostream>
#include <utility>
#include <vector>
#include <limits>
#include <iterator>
#include <cassert>
#include <list>
#include <type_traits>
using namespace std;


template<typename I>
void ins_sort(I first, I last) {
	for (auto pos = first+1; pos != last; ++pos) {
		for (auto k = pos; k != first && *k < *(k-1); --k) {
			swap(*k, *(k-1));
		}
	}
}

template<typename I>
void ins_sort2(I first, I last) {
	for (auto pos = first+1; pos != last; ++pos) {
		auto k = pos;
		auto el = *pos;
		for (; k != first && el < *(k-1); --k) {
			*k = *(k-1);
		}
		*k = el;
	}
}

template<typename I>
void sel_sort(I first, I last) {
	for ( ; first != last; ++first) {
		auto min = first;
		for (auto el = first+1; el != last; ++el) {
			if (*el < *min) {
				min = el;
			}
		}
		swap(*first, *min);
	}
}

template<typename I>
void sel_sort_r(I first, I last) {
	if (first == last)
		return;
	auto min = first;
	for (auto el = first+1; el != last; ++el)
		if (*el < *min)
			min = el;
	sel_sort_r(++first, last);
}



template <typename T, T min, T max, typename I>
void count_sort(I first, I last) {
	static_assert(numeric_limits<T>::is_integer, "requires integers");

	vector<T> cnt(max-min+1, 0);
	for (auto it = first; it != last; ++it)
		++cnt[(*it)-min];
	for (size_t i = 0; i < cnt.size(); ++i) {
		while (cnt[i]-- > 0 && first != last) {
			*(first++) = (T)(i+min);
		}
	}
}

template <typename I, typename T>
void _merge_sort(I first, I last, vector<T> &buff) {
	size_t n =  distance(first, last);
	auto pivot = first;
	advance(pivot, n/2);

	if (n > 1) {
		_merge_sort(first, pivot, buff);
		_merge_sort(pivot, last, buff);
	}

	auto left = first;
	auto right = pivot;

	while (n--) {
		if ((left != pivot && *left <= *right) || right == last) {
			buff.push_back(move(*(left++)));
		} else if (right != last && *left > *right){
			buff.push_back(move(*(right++)));
		} else {
			break;
		}
	}
	move(left, pivot, back_inserter(buff));
	move(right, last, back_inserter(buff));
	move(buff.begin(), buff.end(), first);
	buff.clear();
}

template <typename I>
void merge_sort(I first, I last) {
	using T = typename remove_reference<decltype(*first)>::type;
	vector<T> buff;
	buff.reserve(distance(first, last));
	_merge_sort(first, last, buff);
}


template <typename T>
struct ListNode {
	T val;
	ListNode *next;
};


template <typename T>
void _list_merge(ListNode<T> **edge, ListNode<T> *left, ListNode<T> *right) {
	if (left && (!right || left->val < right->val)) {
		*edge = left;
		_list_merge(&left->next, left->next, right);
	} else if (right) {
		*edge = right;
		_list_merge(&right->next, left, right->next);
	}
}

template <typename T>
ListNode<T>* _list_merge_sort(ListNode<T> *first, ListNode<T> *last, size_t size) {
	assert(first != nullptr);

	if (first->next == last || size <= 1) {
		first->next = nullptr;
		return first;
	}

	ListNode<T> *pivot = first;
	for (size_t dist = size/2; pivot->next && dist > 0; --dist)
		pivot = pivot->next;

	ListNode<T> *left =  _list_merge_sort(first, pivot, size/2);
	ListNode<T> *right = _list_merge_sort(pivot, last, size-size/2);

	ListNode<T> *result;
	ListNode<T> **edge = &result;
	// _list_merge(&result, left, right); //backup if below not working
	while (size--) {
		if (left && (!right || left->val < right->val)) {
			*edge = left;
			left = left->next;
		} else if (right) {
			*edge = right;
			right = right->next;
		}
		edge = &(*edge)->next;
	}

	return result;
}


template <typename T>
ListNode<T>* list_merge_sort(ListNode<T> *first) {
	assert(first != nullptr);

	size_t size = 1;
	for (ListNode<T>* node = first; node->next != nullptr; node = node->next)
		++size;

	return _list_merge_sort(first, (ListNode<T>*)nullptr, size);
}


template <typename T>
int partition(T *array, int p, int b, int e) {
	// TODO: will not work for [1, 1]
	while (b < e) {
		while (array[p] < array[e]) // pivot < pivot will stop it
			--e;
		while (b < e && array[b] <= array[p])
			++b;
		if (b < e)
			swap(array[b], array[e]);
	}
	swap(array[b], array[p]);
	return e;
}

template <typename T>
void quick_sort(T *array, int b, int e) {
	if (e-b <= 0)
		return;
	int p = partition(array, b, b, e);
	quick_sort(array, b, p-1);
	quick_sort(array, p+1, e);
}

int main() {
	int tab[] = {1, 4, 2, 3, -1, 100, 88, 0, 0};
	// int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	// ins_sort2(tab, tab+9);
	// merge_sort(tab, tab+9);
	// quick_sort(tab, 0, 8);
	// for (auto e: tab)
	// 	cout << e << " ";
	// cout << endl;

	ListNode<int> *list;
	ListNode<int> **edge = &list;
	for (auto& v : tab) {
		ListNode<int> *node = new ListNode<int>;
		node->val = v;
		*edge = node;
		edge = &node->next;
	}
	list = list_merge_sort(list);
	size_t size = 9;
	for (auto *node = list; node != nullptr && size-- > 0; node = node->next) {
		cout << node->val << " -> ";
	}
	cout << endl;

	// list<int> l{99, 0, 1, -10, 100, -10, 3, 8};
	// // count_sort<int, -10, 100>(l.begin(), l.end());
	// merge_sort(l.begin(), l.end());

	// for (auto e: l)
	// 	cout << e << " ";
	// cout << endl;
	return 0;
}
