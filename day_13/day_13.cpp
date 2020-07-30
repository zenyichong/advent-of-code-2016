// --- Advent of Code 2016 Day 13: A Maze of Twisty Little Cubicles ---

#include <bitset>

#include "../utils.h"

using namespace std;
using Coords = pair<int, int>;
using State = tuple<Coords, int, set<Coords>>;

const string f_name = "day_13.txt";
const int input = 1364;
const int max_steps = 50;

bool is_open_space(Coords& point) {
    int x, y;
    tie(x, y) = point;
    int tmp = x * x + 3 * x + 2 * x * y + y + y * y + input;
    string bits = bitset<32>(tmp).to_string();
    return (count(bits.begin(), bits.end(), '1') % 2 == 0);
}

bool bfs(State& curr_state, const Coords& end, set<Coords>& walls, queue<State>& states,
         set<Coords>& reachable) {
    static const vector<Coords> directions{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    Coords curr_pos;
    int steps, x, y;
    set<Coords> visited;

    tie(curr_pos, steps, visited) = curr_state;
    tie(x, y) = curr_pos;
    for (const auto& elem : directions) {
        int dx, dy;
        tie(dx, dy) = elem;
        Coords next_pos{x + dx, y + dy};
        if (((x + dx) < 0) || ((y + dy) < 0) || walls.count(next_pos) || visited.count(next_pos))
            continue;

        if (is_open_space(next_pos)) {
            set<Coords> sc = visited;
            sc.insert(next_pos);
            states.push({next_pos, steps + 1, sc});

            // Part Two
            if ((steps + 1) <= max_steps)
                reachable.insert(next_pos);

            // Part One
            if (next_pos == end)
                return true;
        } else
            walls.insert(next_pos);
    }
    return false;
}

int main(int argc, char** argv) try {
    Coords start{1, 1};
    Coords end{31, 39};
    set<Coords> walls;
    set<Coords> reachable{start};
    queue<State> states;
    states.push({start, 0, {start}});

    bool found = false;
    while (states.size()) {
        found = bfs(states.front(), end, walls, states, reachable);
        if (found)
            break;
        states.pop();
    }
    cout << "Part One: " << get<1>(states.back()) << '\n';
    cout << "Part Two: " << reachable.size() << '\n';

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
