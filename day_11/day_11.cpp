// --- Advent of Code 2016 Day 11: Radioisotope Thermoelectric Generators ---

#include <queue>

#include "../utils.h"

using namespace std;

const string f_name = "day_11.txt";

using Arrangement = vector<vector<string>>;
using State = tuple<int, int, Arrangement>;
const vector<vector<string>> initial_state_p1{
    {"SG", "SM", "PG", "PM"}, {"TG", "RG", "RM", "CG", "CM"}, {"TM"}, {}};
const vector<vector<string>> final_state_p1{
    {}, {}, {}, {"CG", "CM", "PG", "PM", "RG", "RM", "SG", "SM", "TG", "TM"}};
const vector<vector<string>> initial_state_p2{
    {"SG", "SM", "PG", "PM", "EG", "EM", "DG", "DM"}, {"TG", "RG", "RM", "CG", "CM"}, {"TM"}, {}};
const vector<vector<string>> final_state_p2{
    {},
    {},
    {},
    {"CG", "CM", "EG", "EM", "DG", "DM", "PG", "PM", "RG", "RM", "SG", "SM", "TG", "TM"}};

string get_state_hash(int elevator, const Arrangement& floors) {
    string hash = to_string(elevator);
    for (int i = 0; i < floors.size(); ++i) {
        string generators, microchips;
        for (const auto& item : floors[i]) {
            if (item[1] == 'G')
                generators += "G";
            else if (item[1] == 'M')
                microchips += "M";
        }
        hash += (to_string(i) + generators + microchips);
    }
    return hash;
}

bool is_valid_arrangement(const Arrangement& floors) {
    for (const auto& floor : floors) {
        if (floor.size() < 2)
            continue;
        int num_m = 0, num_g = 0;
        for_each(floor.begin(), floor.end(), [&num_g, &num_m](const string& x) {
            if (x[1] == 'M')
                ++num_m;
            else
                ++num_g;
        });
        if (num_m == 0 || num_g == 0)
            continue;
        for (const string& item : floor) {
            if (item[1] == 'M') {
                auto iter = find_if(floor.begin(), floor.end(), [&item](const string& x) {
                    return x[0] == item[0] && x[1] == 'G';
                });
                if (iter == floor.end()) {
                    return false;
                }
            }
        }
    }
    return true;
};

pair<int, Arrangement> move_items(int direction, int elevator, const Arrangement& floors,
                                  int item_1, int item_2) {
    if ((elevator + direction) < 0 || (elevator + direction) >= floors.size()) {
        return {elevator, floors};
    }

    Arrangement next_state = floors;
    next_state[elevator + direction].push_back(next_state[elevator][item_1]);
    next_state[elevator].erase(next_state[elevator].begin() + item_1);
    if (item_2 != INT32_MAX) {
        next_state[elevator + direction].push_back(next_state[elevator][item_2 - 1]);
        next_state[elevator].erase(next_state[elevator].begin() + item_2 - 1);
    }
    return {elevator + direction, next_state};
}

bool check_new_state(set<string>& hashes, queue<State>& state_queue, int elevator, int moves,
                     const Arrangement& floors, int item_1, int item_2 = INT32_MAX) {
    static const string final_hash_p1 = get_state_hash(3, final_state_p1);
    static const string final_hash_p2 = get_state_hash(3, final_state_p2);
    static const vector<int> directions{1, -1};

    for (int i : directions) {
        Arrangement arr;
        int elev;
        string hash;
        tie(elev, arr) = move_items(i, elevator, floors, item_1, item_2);
        hash = get_state_hash(elev, arr);
        if (!hashes.count(hash) && is_valid_arrangement(arr)) {
            hashes.insert(hash);
            state_queue.push(State{elev, moves + 1, arr});
        }

        if (hash == final_hash_p1 || hash == final_hash_p2)
            return true;
    }
    return false;
}

bool bfs(queue<State>& state_queue, set<string>& hashes) {
    int elevator, moves;
    vector<vector<string>> floors;
    tie(elevator, moves, floors) = state_queue.front();
    for (int i = 0; i < floors[elevator].size(); ++i) {
        for (int j = i + 1; j < floors[elevator].size(); ++j) {
            if (check_new_state(hashes, state_queue, elevator, moves, floors, i, j))
                return true;
        }
        if (check_new_state(hashes, state_queue, elevator, moves, floors, i))
            return true;
    }
    state_queue.pop();
    return false;
}

int main(int argc, char** argv) try {
    set<string> hashes;
    hashes.insert(get_state_hash(0, initial_state_p1));

    queue<State> state_queue;
    state_queue.push(State{0, 0, initial_state_p1});
    bool found = false;

    // Part One
    while (state_queue.size() > 0) {
        found = bfs(state_queue, hashes);
        if (found)
            break;
    }
    cout << "Part One: " << get<1>(state_queue.back()) << '\n';

    // Part Two
    hashes = {};
    hashes.insert(get_state_hash(0, initial_state_p2));
    state_queue = {};
    state_queue.push(State{0, 0, initial_state_p2});
    found = false;

    while (state_queue.size() > 0) {
        found = bfs(state_queue, hashes);
        if (found)
            break;
    }
    cout << "Part Two: " << get<1>(state_queue.back()) << '\n';

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
