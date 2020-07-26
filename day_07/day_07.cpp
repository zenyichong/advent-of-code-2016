// --- Advent of Code 2016 Day 07: Internet Protocol Version 7 ---

#include "../utils.h"

using namespace std;

const string f_name = "day_07.txt";

vector<string> split_string(string s, char delim) {
    vector<string> result;
    istringstream iss{s};
    for (string segment; getline(iss, segment, delim);)
        result.push_back(segment);
    return result;
}

bool supports_tls(const vector<string>& vs) {
    static const regex abba{R"(([a-z])([a-z])(?!\1)\2\1)"};
    bool flag = false;
    for (int i = 0; i < vs.size(); ++i) {
        if (regex_search(vs[i], abba)) {
            if (i % 2)
                return false;
            flag = true;
        }
    }
    return flag;
}

bool supports_ssl(const vector<string>& vs) {
    static const regex aba{R"((?=(([a-z])(?!\2)[a-z]\2)).)"};
    set<string> bab_patterns;
    for (int i = 0; i < vs.size(); i += 2) {
        auto m_begin = sregex_iterator(vs[i].begin(), vs[i].end(), aba);
        auto m_end = sregex_iterator();
        for (auto i = m_begin; i != m_end; ++i) {
            string match = (*i).str(1);
            bab_patterns.insert(match.substr(1) + match[1]);
        }
    }
    if (!bab_patterns.size())
        return false;

    for (int i = 1; i < vs.size(); i += 2) {
        for (string s : bab_patterns) {
            if (vs[i].find(s) != string::npos)
                return true;
        }
    }
    return false;
}

int main(int argc, char** argv) try {
    vector<string> addresses;
    if (argc == 2)
        read_to_vecstr(argv[1], addresses);
    else
        read_to_vecstr(f_name, addresses);

    int tls_count = 0;
    int ssl_count = 0;
    for (string addr : addresses) {
        replace(addr.begin(), addr.end(), '[', ']');
        vector<string> segments = split_string(addr, ']');

        // Part One
        if (supports_tls(segments))
            ++tls_count;

        // Part Two
        if (supports_ssl(segments))
            ++ssl_count;
    }
    cout << "Part One: " << tls_count << '\n';
    cout << "Part Two: " << ssl_count << '\n';

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