// --- Advent of Code 2016 Day 10: Balance Bots ---

#include "../utils.h"

using namespace std;

const string f_name = "day_10.txt";

bool insert_val(map<string, pair<int, int>>& m, const string& key, int val) {
    if (m.find(key) != m.end()) {
        int a, b;
        tie(a, b) = m[key];
        if (a == 0 && b == 0)
            m[key] = {val, 0};
        else if (b == 0)
            m[key] = {a, val};
        else
            return false;
    } else
        m[key] = {val, 0};
    return true;
}

void reset_val(map<string, pair<int, int>>& m, const string& key) {
    if (m.find(key) != m.end())
        m[key] = {0, 0};
    else
        error("Key not in map: ", key);
}

map<string, pair<int, int>> init_bots(vector<string>& instructions) {
    static const regex init_regex{R"(value (\d+) goes to ([a-z0-9 ]+))"};
    map<string, pair<int, int>> res;
    smatch match;
    for (auto it = instructions.begin(); it != instructions.end();) {
        if (regex_match(*it, match, init_regex)) {
            int val = stoi(match[1]);
            string bot = match[2];
            insert_val(res, bot, val);
            instructions.erase(it);
        } else
            ++it;
    }
    return res;
}

bool update_chip_positions(map<string, pair<int, int>>& m,
                           const string& instruction) {
    static const regex cmp_regex{
        R"(([a-z0-9 ]+) gives low to ([a-z0-9 ]+) and high to ([a-z0-9 ]+))"};
    smatch match;
    regex_match(instruction, match, cmp_regex);
    string src = match[1];
    string dst_low = match[2];
    string dst_hi = match[3];

    int a, b;
    tie(a, b) = m[src];
    if ((a == 61 || a == 17) && (b == 61 || b == 17)) {
        cout << "Part One: " << src << '\n';
    }

    if (a == 0 || b == 0) {
        return false;
    }
    reset_val(m, src);
    insert_val(m, dst_low, min(a, b));
    insert_val(m, dst_hi, max(a, b));
    return true;
}

int main(int argc, char** argv) try {
    vector<string> instructions;
    if (argc == 2)
        read_to_vecstr(argv[1], instructions);
    else
        read_to_vecstr(f_name, instructions);

    map<string, pair<int, int>> chip_positions = init_bots(instructions);

    auto it = instructions.begin();
    while (instructions.size() > 0) {
        if (it == instructions.end())
            it = instructions.begin();

        bool success = update_chip_positions(chip_positions, *it);
        if (success)
            it = instructions.erase(it);
        else
            ++it;
    }

    // Part Two
    int ans = chip_positions["output 0"].first *
              chip_positions["output 1"].first *
              chip_positions["output 2"].first;
    cout << "Part Two: " << ans << '\n';

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