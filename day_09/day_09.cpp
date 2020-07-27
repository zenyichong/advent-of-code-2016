// --- Advent of Code 2016 Day 09: Explosives in Cyberspace ---

#include "../utils.h"

using namespace std;

const string f_name = "day_09.txt";

pair<int, int> parse_marker(const string& marker) {
    static const regex m_regex{R"((\d+)x(\d+))"};
    smatch match;
    if (!regex_match(marker, match, m_regex))
        error("Invalid marker: ", marker);
    return {stoi(match[1]), stoi(match[2])};
}

size_t get_decompressed_len(const string& s, bool is_part_2) {
    int i = 0;
    size_t length = 0;
    while (i < s.size()) {
        if (s[i] == '(') {
            string marker = "";
            ++i;
            while (s[i] != ')') {
                marker += s[i];
                ++i;
            }

            int n_chars, cnt;
            tie(n_chars, cnt) = parse_marker(marker);

            if (is_part_2)
                length +=
                    cnt * get_decompressed_len(s.substr(i + 1, n_chars), true);
            else
                length += cnt * n_chars;
            i += n_chars + 1;

        } else {
            ++length;
            ++i;
        }
    }
    return length;
}

int main(int argc, char** argv) try {
    string data;
    ifstream ifs;
    if (argc == 2)
        read_to_str(argv[1], data);
    else
        read_to_str(f_name, data);

    // Part One
    size_t length_p1 = get_decompressed_len(data, false);
    cout << "Part One: " << length_p1 << '\n';

    // Part Two
    size_t length_p2 = get_decompressed_len(data, true);
    cout << "Part Two: " << length_p2 << '\n';

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