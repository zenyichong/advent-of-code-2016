// --- Advent of Code 2016 Day 08: Two-Factor Authentication ---

#include <valarray>

#include "../utils.h"

using namespace std;

const string f_name = "day_08.txt";
const int W = 50, H = 6;
const char OFF = ' ', ON = '#';

void print_screen(const valarray<char>& screen, int nrows, int ncols) {
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j)
            cout << screen[i * ncols + j];
        cout << '\n';
    }
}

void parse_instruction(const string& instruction, valarray<char>& screen) {
    static const regex rect{R"(rect (\d+)x(\d+))"};
    static const regex rotate_col{R"(rotate column x=(\d+) by (\d+))"};
    static const regex rotate_row{R"(rotate row y=(\d+) by (\d+))"};
    smatch match;
    if (regex_match(instruction, match, rect)) {
        screen[gslice(0, {stoul(match[2]), stoul(match[1])}, {W, 1})] = ON;

    } else if (regex_match(instruction, match, rotate_col)) {
        size_t a{stoul(match[1])}, b{stoul(match[2])};
        screen[slice(a, H, W)] = valarray<char>(screen[slice(a, H, W)]).cshift(-b);

    } else if (regex_match(instruction, match, rotate_row)) {
        size_t a{stoul(match[1])}, b{stoul(match[2])};
        screen[slice(a * W, W, 1)] = valarray<char>(screen[slice(a * W, W, 1)]).cshift(-b);
    }
}

int main(int argc, char** argv) try {
    vector<string> instructions;
    if (argc == 2)
        read_to_vecstr(argv[1], instructions);
    else
        read_to_vecstr(f_name, instructions);

    valarray<char> screen(OFF, H * W);
    for (string s : instructions)
        parse_instruction(s, screen);

    // Part One
    int num_on = count(begin(screen), end(screen), '#');
    cout << "Part One: " << num_on << '\n';

    // Part Two
    cout << "Part Two: " << '\n';
    print_screen(screen, H, W);

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