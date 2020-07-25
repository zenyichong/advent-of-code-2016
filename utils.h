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

void rtrim(std::string& s, std::string chars_to_trim) {
    unsigned int idx = s.find_last_not_of(chars_to_trim);
    if (idx != s.size())
        s.erase(idx + 1);
}

int absmod(int a, int b) { return (a % b + b) % b; }