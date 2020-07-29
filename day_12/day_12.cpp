// --- Advent of Code 2016 Day 12: Leonardo's Monorail ---

#include "../utils.h"

using namespace std;

const string f_name = "day_12.txt";

int get_value(string s, map<char, int>& registers) try {
    int i = stoi(s);
    return i;
} catch (invalid_argument& e) {
    return registers[s[0]];
}

int parse_line(const string& line, map<char, int>& registers) {
    istringstream iss{line};
    string cmd, arg1, arg2;
    iss >> cmd;

    if (cmd == "cpy") {
        iss >> arg1 >> arg2;
        registers[arg2[0]] = get_value(arg1, registers);
        return 1;
    } else if (cmd == "inc") {
        iss >> arg1;
        ++registers[arg1[0]];
        return 1;
    } else if (cmd == "dec") {
        iss >> arg1;
        --registers[arg1[0]];
        return 1;
    } else if (cmd == "jnz") {
        iss >> arg1 >> arg2;
        if (get_value(arg1, registers) != 0)
            return stoi(arg2);
        return 1;
    } else
        error("Invalid instruction: ", line);
}

int main(int argc, char** argv) try {
    vector<string> assembunny_code;
    if (argc == 2)
        read_to_vecstr(argv[1], assembunny_code);
    else
        read_to_vecstr(f_name, assembunny_code);

    map<char, int> registers{{'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}};

    // Part One
    auto it = assembunny_code.begin();
    while (it != assembunny_code.end()) {
        it += parse_line(*it, registers);
    }
    cout << "Part One: " << registers['a'] << '\n';

    // Part Two
    registers = {{'a', 0}, {'b', 0}, {'c', 1}, {'d', 0}};
    it = assembunny_code.begin();
    while (it != assembunny_code.end()) {
        it += parse_line(*it, registers);
    }
    cout << "Part Two: " << registers['a'] << '\n';

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
