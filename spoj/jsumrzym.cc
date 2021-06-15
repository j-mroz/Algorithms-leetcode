#include <array>
#include <iostream>
#include <unordered_map>
using namespace std;

static const unordered_map<char, int> _roman_to_arabic {
    {'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}
};

int roman_to_arabic(const string &roman_num) {
    int result = 0, prev_val = 0;
    for (auto roman_symbol : roman_num) {
        int val = _roman_to_arabic.at(roman_symbol);
        result += (prev_val < val) ? val - 2 * prev_val : val;
        prev_val = val;
    }
    return result;
}

static const array<string, 10> div100 {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
static const array<string, 10> div10  {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
static const array<string, 10> div1   {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

string arabic_to_roman(int roman_num) {
    string result;

    result += string(roman_num / 1000, 'M');
    roman_num = roman_num % 1000;
    result += div100[roman_num/100];
    roman_num = roman_num % 100;
    result += div10[roman_num/10];
    roman_num = roman_num % 10;
    result += div1[roman_num];

    return result;
}

int main(int argc, char const *argv[]) {
    string a, b;
    while (cin >> a >> b) {
        auto sum = arabic_to_roman(roman_to_arabic(a) +  roman_to_arabic(b));
        cout << sum << endl;
    }

    return 0;
}

