// --- Advent of Code 2016 Day 02: Bathroom Security ---

#include "../utils.h"

using namespace std;
using coords = pair<int, int>;

constexpr int null = '0';
const string f_name = "day_02.txt";
const map<char, coords> directions{
    {'U', {0, -1}}, {'D', {0, 1}}, {'L', {-1, 0}}, {'R', {1, 0}}};
const vector<vector<char>> keypad{
    {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
const vector<vector<char>> actual_keypad{{null, null, '1', null, null},
                                         {null, '2', '3', '4', null},
                                         {'5', '6', '7', '8', '9'},
                                         {null, 'A', 'B', 'C', null},
                                         {null, null, 'D', null, null}};

void read_from_file(const string& f_name, vector<string>& v) {
    ifstream ifs{f_name};
    if (!ifs)
        throw runtime_error("Can't open file: " + f_name);

    for (string s; ifs >> s;)
        v.push_back(s);
}

pair<char, coords> decode_instruction(const string& instruction,
                                      const vector<vector<char>>& keypad,
                                      coords curr_pos) {
    int x, y;
    tie(x, y) = curr_pos;
    int width = keypad[0].size();
    int height = keypad.size();
    int tmp_x, tmp_y;
    for (char ch : instruction) {
        coords next_move = directions.at(ch);
        tmp_x = x + next_move.first;
        tmp_y = y + next_move.second;
        if ((tmp_x >= 0 && tmp_x < width) && (tmp_y >= 0 && tmp_y < width) &&
            keypad[tmp_y][tmp_x] != null) {
            x = tmp_x;
            y = tmp_y;
        }
    }

    return {keypad[y][x], {x, y}};
}

int main(int argc, char** argv) try {
    vector<string> instructions;
    if (argc == 2)
        read_from_file(argv[1], instructions);
    else
        read_from_file(f_name, instructions);
    pair<int, int> curr_pos;
    string pw;
    char next_char;

    // Part One
    curr_pos = {1, 1};
    pw = "";
    for (string s : instructions) {
        tie(next_char, curr_pos) = decode_instruction(s, keypad, curr_pos);
        pw += next_char;
    }
    cout << "Part One: " << pw << '\n';

    // Part Two
    curr_pos = {0, 2};
    pw = "";
    for (string s : instructions) {
        tie(next_char, curr_pos) =
            decode_instruction(s, actual_keypad, curr_pos);
        pw += next_char;
    }
    cout << "Part Two: " << pw << '\n';

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