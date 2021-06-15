#include <iostream>
using namespace std;

template<typename T>
struct Maybe {
    Maybe(bool v, const T& v = T()) : valid(v), value(v)  {}
    union {
        bool something;
        bool success;
        bool valid;
    };
    T value;
};

template <typename T>
Maybe<T> Nothing() {
    return Maybe<T>(false);
}

template <typename T>
Maybe<T> Just(T v) {
    return Maybe<T>(true, v);
}


unsigned strlen(const char *s) {
    char *end = (char *)s;
    while (*end)
        ++end;
    return (end - s);
}

unsigned* create_kmp_tab(const char *str, unsigned size) {
    unsigned *shifts = new unsigned[size];
    shifts[0] = 0;

    unsigned prefix = 0;
    for (int idx = 1; idx < size; ) {
        if (str[idx] == str[prefix]) {
            // substring continues
            shifts[idx++] = ++prefix;
        } else if (prefix > 0) {
            // substring stops, fallback to previous prefix
            prefix = shifts[prefix-1];
        } else {
            // no fallback option
            shifts[idx++] = 0;
        }
    }

    return shifts;
}

Maybe<unsigned> kmp_find(const char *pattern, const char *text) {
    Maybe<unsigned> result = Nothing<unsigned>();

    unsigned pattern_size = strlen(pattern);
    unsigned text_size = strlen(text);
    unsigned *shifts = create_kmp_tab(pattern, pattern_size);

    unsigned remaining = text_size;
    unsigned tidx = 0, pidx = 0;
    while (remaining > 0) {

        if (pattern[pidx] == text[tidx]) {
            ++pidx;
            ++tidx;
            --remaining;
        } else if (pidx == 0) {
            ++tidx;
            --remaining;
        } else {
            pidx = shifts[pidx - 1];
        }

        if (pidx == pattern_size) {
            result = Just<unsigned>(tidx - pidx);
            break;
        }
    }

    delete []shifts;
    return result;
}





int main(int argc, char const *argv[]) {

    const char *S = "ABC ABCDAB ABCDABCDABDX";
    const char *P = "ABCDAB";

    Maybe<unsigned> ret = kmp_find(P, S);
    if (ret.something)
        cout << ret.value << " " << (S + ret.value) << endl;

    return 0;
}