#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using std::string;
using std::vector;

void rtrim(string& s, string chars_to_trim) {
    unsigned int idx = s.find_last_not_of(chars_to_trim);
    if (idx != s.size())
        s.erase(idx + 1);
}

static inline void error(const string& s1, const string& s2) {
    throw std::runtime_error(s1 + s2);
}

void read_to_vecstr(const string& f_name, vector<string>& v,
                    string chars_to_trim = "") {
    std::ifstream ifs{f_name};
    if (!ifs)
        error("Can't open file: ", f_name);

    for (string s; getline(ifs, s);) {
        rtrim(s, chars_to_trim);
        v.push_back(s);
    }
}

int absmod(int a, int b) { return (a % b + b) % b; }