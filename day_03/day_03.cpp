// --- Advent of Code 2016 Day 03: Squares With Three Sides ---

#include "../utils.h"

using namespace std;

const string f_name = "day_03.txt";

void read_from_file(const string& f_name, vector<vector<int>>& v1, vector<vector<int>>& v2) {
    ifstream ifs{f_name};
    vector<int> tmp;
    if (!ifs)
        throw runtime_error("Can't open file: " + f_name);

    for (int i; ifs >> i;)
        tmp.push_back(i);

    for (int i = 0; i < tmp.size(); i += 3)
        v1.push_back(vector<int>{tmp.at(i), tmp.at(i + 1), tmp.at(i + 2)});

    for (int i = 0; i < tmp.size(); i += 9) {
        for (int j = 0; j < 3; ++j) {
            v2.push_back(vector<int>{tmp.at(i + j), tmp.at(i + j + 3), tmp.at(i + j + 6)});
        }
    }
}

bool is_valid_triangle(const vector<int>& v) {
    int sum_of_lengths = accumulate(v.begin(), v.end(), 0);
    int longest = *max_element(v.begin(), v.end());
    return (sum_of_lengths - longest) > longest;
}

int main(int argc, char** argv) try {
    vector<vector<int>> lengths_part1;
    vector<vector<int>> lengths_part2;
    if (argc == 2)
        read_from_file(argv[1], lengths_part1, lengths_part2);
    else
        read_from_file(f_name, lengths_part1, lengths_part2);
    int count;

    // Part One
    count = 0;
    for (const auto& v : lengths_part1) {
        if (is_valid_triangle(v))
            count += 1;
    }
    cout << "Part One: " << count << '\n';

    // Part Two
    count = 0;
    for (const auto& v : lengths_part2) {
        if (is_valid_triangle(v))
            count += 1;
    }
    cout << "Part Two: " << count << '\n';

} catch (runtime_error& e) {
    cerr << "Runtime error: " << e.what() << '\n';
    return 1;
} catch (out_of_range& e) {
    cerr << "Out of range access: " << e.what() << '\n';
    return 2;
} catch (...) {
    cerr << "Unhandled exception\n";
    return 3;
}