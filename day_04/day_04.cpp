// --- Advent of Code 2016 Day 04: Security Through Obscurity ---

#include "../utils.h"

using namespace std;
using letter_count = pair<char, int>;

const string f_name = "day_04.txt";

void read_from_file(const string& f_name, vector<string>& v) {
    ifstream ifs{f_name};
    if (!ifs)
        throw runtime_error("Can't open file: " + f_name);

    for (string s; ifs >> s;)
        v.push_back(s);
}

bool is_valid_room(const string& name, const string& checksum) {
    map<char, int> letter_map;
    for (char ch : name) {
        if (ch != '-')
            ++letter_map[ch];
    }
    if (checksum.size() > letter_map.size())
        return false;

    vector<letter_count> letter_vec;
    for (const auto& elem : letter_map) {
        letter_vec.push_back(elem);
    }
    stable_sort(letter_vec.begin(), letter_vec.end(),
                [](const letter_count& a, const letter_count& b) {
                    return a.second > b.second;
                });

    for (int i = 0; i < checksum.size(); ++i) {
        if (checksum.at(i) != letter_vec.at(i).first)
            return false;
    }
    return true;
}

string caesar_cipher(string name, int shift_amt) {
    for (int i = 0; i < name.size(); ++i) {
        if (name[i] == '-') {
            name[i] = ' ';
            continue;
        }
        int ord = name[i];
        ord += absmod(shift_amt, 26);
        if (ord > int('z'))
            ord -= 26;
        name[i] = char(ord);
    }
    return name;
}

int main(int argc, char** argv) try {
    vector<string> rooms;
    if (argc == 2)
        read_from_file(argv[1], rooms);
    else
        read_from_file(f_name, rooms);
    int sector_id_sum;
    regex pattern{R"(([a-z\-]+)(\d+)\[([a-z]+)\])"};
    vector<string> valid_rooms;

    // Part One
    sector_id_sum = 0;
    for (string s : rooms) {
        smatch matches;
        if (!regex_match(s, matches, pattern))
            throw runtime_error("Bad string: " + s);

        string name = matches[1];
        int sector_id = stoi(matches[2]);
        string checksum = matches[3];

        if (is_valid_room(name, checksum)) {
            valid_rooms.push_back(s);
            sector_id_sum += sector_id;
        }
    }
    cout << "Part One: " << sector_id_sum << '\n';

    // Part Two
    string decrypted;
    for (string s : valid_rooms) {
        smatch matches;
        if (!regex_match(s, matches, pattern))
            throw runtime_error("Bad string: " + s);

        string name = matches[1];
        int sector_id = stoi(matches[2]);

        decrypted = caesar_cipher(name, sector_id);
        if (decrypted.find("north") != string::npos) {
            cout << "Part Two: " << sector_id << '\n';
            break;
        }
    }

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