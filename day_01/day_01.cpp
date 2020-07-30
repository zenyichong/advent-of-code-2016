// --- Advent of Code 2016 Day 01: No Time for a Taxicab ---

#include "../utils.h"

using namespace std;

const string f_name = "day_01.txt";

// deliberately initialized in this manner so R corresponds to next idx
// and conversely for L
const vector<char> directions{'N', 'E', 'S', 'W'};

struct Position {
    pair<int, int> coords;  // first: x, second: y
    char direction;
};

void read_from_file(const string& f_name, vector<string>& v) {
    ifstream ifs{f_name};
    if (!ifs)
        throw runtime_error("Can't open file: " + f_name);

    for (string s; ifs >> s;) {
        rtrim(s, ", \n");
        v.push_back(s);
    }
}

char update_heading(char dir, char ch) {
    int idx = find(directions.begin(), directions.end(), dir) - directions.begin();
    int n = directions.size();
    switch (ch) {
        case 'R':
            return directions[absmod(idx + 1, n)];
        case 'L':
            return directions[absmod(idx - 1, n)];
        default:
            throw runtime_error("Unknown character: must be R or L");
    }
}

Position update_position(Position pos, string instruction) {
    char ch = instruction[0];
    int distance = stoi(instruction.substr(1));
    pos.direction = update_heading(pos.direction, ch);
    switch (pos.direction) {
        case 'N':
            pos.coords.second += distance;
            break;
        case 'E':
            pos.coords.first += distance;
            break;
        case 'S':
            pos.coords.second -= distance;
            break;
        case 'W':
            pos.coords.first -= distance;
            break;
        default:
            throw runtime_error("Unknown direction specified");
    }
    return pos;
}

pair<Position, bool> update_position_and_visited(Position pos, string instruction,
                                                 set<pair<int, int>>& visited) {
    char ch = instruction[0];
    int distance = stoi(instruction.substr(1));
    pos.direction = update_heading(pos.direction, ch);

    int dx, dy;
    switch (pos.direction) {
        case 'N':
            dx = 0;
            dy = 1;
            break;
        case 'E':
            dx = 1;
            dy = 0;
            break;
        case 'S':
            dx = 0;
            dy = -1;
            break;
        case 'W':
            dx = -1;
            dy = 0;
            break;
        default:
            throw runtime_error("Unknown direction specified");
    }

    for (; distance > 0; --distance) {
        pos.coords.first += dx;
        pos.coords.second += dy;
        auto res = visited.insert(pos.coords);
        if (!res.second)  // if insertion failed, i.e. visited this coordinate
            return {pos, true};
    }

    return {pos, false};
}

int main() try {
    vector<string> instructions;
    read_from_file(f_name, instructions);
    Position pos;

    // Part One
    pos = {{0, 0}, 'N'};
    for (string s : instructions)
        pos = update_position(pos, s);
    cout << "Part One: " << abs(pos.coords.first) + abs(pos.coords.second) << '\n';

    // Part Two
    pos = {{0, 0}, 'N'};
    bool found;
    set<pair<int, int>> visited{{0, 0}};
    for (string s : instructions) {
        // 'destructure' the returned pair
        tie(pos, found) = update_position_and_visited(pos, s, visited);
        if (found)
            break;
    }
    cout << "Part Two: " << abs(pos.coords.first) + abs(pos.coords.second) << '\n';

} catch (runtime_error& e) {
    cerr << "Runtime error: " << e.what() << '\n';
    return 1;
} catch (...) {
    cerr << "Unhandled exception\n";
    return 2;
}