// --- Advent of Code 2016 Day 06: Signals and Noise ---

#include "../utils.h"

using namespace std;

const string f_name = "day_06.txt";

void count_chars(const vector<string>& vs, vector<map<char, int>>& vm) {
    for (const string& s : vs) {
        for (int i = 0; i < s.size(); ++i)
            ++vm[i][s.at(i)];
    }
}

int main(int argc, char** argv) try {
    vector<string> messages;
    if (argc == 2)
        read_to_vecstr(argv[1], messages);
    else
        read_to_vecstr(f_name, messages);

    vector<map<char, int>> letter_counts(8);
    count_chars(messages, letter_counts);

    string pw1 = "";
    string pw2 = "";
    for (const auto& lc_map : letter_counts) {
        int most = 0, least = INT32_MAX;
        char pw1_next = ' ', pw2_next = ' ';

        // Part One
        for (const auto& elem : lc_map) {
            if (elem.second > most) {
                most = elem.second;
                pw1_next = elem.first;
            }
        }
        pw1 += pw1_next;

        // Part Two
        for (const auto& elem : lc_map) {
            if (elem.second < least) {
                least = elem.second;
                pw2_next = elem.first;
            }
        }
        pw2 += pw2_next;
    }
    cout << "Part One: " << pw1 << '\n';
    cout << "Part Two: " << pw2 << '\n';

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
