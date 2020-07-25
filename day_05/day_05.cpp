// --- Advent of Code 2016 Day 05: How About a Nice Game of Chess? ---

#include "../utils.h"
#include "md5.h"

using namespace std;

const string f_name = "day_05.txt";

int main(int argc, char** argv) try {
    string door_id;
    ifstream ifs{f_name};
    if (!ifs)
        throw runtime_error("Can't open file: " + f_name);
    ifs >> door_id;

    string pw1 = "";
    string pw2 = "________";
    const string prefix = "00000";
    for (int count = 0, i = 0; count < 8; ++i) {
        string encoded = md5(door_id + to_string(i));
        if (encoded.rfind(prefix, 0) == 0) {
            cout << i << '\n';
            // Part One
            if (pw1.size() < 8)
                pw1 += encoded[5];

            // Part Two
            int idx = encoded[5] - '0';
            if ((idx < pw2.size()) && (pw2[idx] == '_')) {
                pw2[idx] = encoded[6];
                ++count;
            }
        }
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