#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

vector<bool (*)(const map<pair<int, int>, int> &, const pair<int, int> &)>
    check_direction;

vector<pair<int, int>> direction_modifiers = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

inline bool check_alone(const map<pair<int, int>, int> &pos2elf,
                        const pair<int, int> &elf) {
    if (pos2elf.find({elf.first, elf.second - 1}) != pos2elf.end())
        return false;
    if (pos2elf.find({elf.first, elf.second + 1}) != pos2elf.end())
        return false;
    int checkx = elf.first - 1;
    if (pos2elf.find({checkx, elf.second}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second - 1}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second + 1}) != pos2elf.end())
        return false;
    checkx = elf.first + 1;
    if (pos2elf.find({checkx, elf.second}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second - 1}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second + 1}) != pos2elf.end())
        return false;
    return true;
}
inline bool check_north(const map<pair<int, int>, int> &pos2elf,
                        const pair<int, int> &elf) {
    int checkx = elf.first - 1;
    if (pos2elf.find({checkx, elf.second}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second - 1}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second + 1}) != pos2elf.end())
        return false;
    return true;
}
inline bool check_south(const map<pair<int, int>, int> &pos2elf,
                        const pair<int, int> &elf) {
    int checkx = elf.first + 1;
    if (pos2elf.find({checkx, elf.second}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second - 1}) != pos2elf.end())
        return false;
    if (pos2elf.find({checkx, elf.second + 1}) != pos2elf.end())
        return false;
    return true;
}
inline bool check_east(const map<pair<int, int>, int> &pos2elf,
                       const pair<int, int> &elf) {
    int checky = elf.second + 1;
    if (pos2elf.find({elf.first, checky}) != pos2elf.end())
        return false;
    if (pos2elf.find({elf.first - 1, checky}) != pos2elf.end())
        return false;
    if (pos2elf.find({elf.first + 1, checky}) != pos2elf.end())
        return false;
    return true;
}
inline bool check_west(const map<pair<int, int>, int> &pos2elf,
                       const pair<int, int> &elf) {
    int checky = elf.second - 1;
    if (pos2elf.find({elf.first, checky}) != pos2elf.end())
        return false;
    if (pos2elf.find({elf.first - 1, checky}) != pos2elf.end())
        return false;
    if (pos2elf.find({elf.first + 1, checky}) != pos2elf.end())
        return false;
    return true;
}
pair<int, int> propose_position(const map<pair<int, int>, int> &pos2elf,
                                const pair<int, int> &elf, const int round) {
    if (check_alone(pos2elf, elf)) {
        return {elf};
    }
    int j = round;
    int move_dir = -1;
    for (j = round; j < round + 4; j++) {
        if (check_direction[j % 4](pos2elf, elf)) {
            move_dir = j % 4;
            break;
        }
    }
    if (move_dir == -1) {
        // cout << "Elf at " << elf.first << ", " << elf.second
        //      << " isn't moving.\n";
        return elf;
    }
    pair<int, int> new_pos = {elf.first + direction_modifiers[move_dir].first,
                              elf.second +
                                  direction_modifiers[move_dir].second};

    // cout << "Elf at " << elf.first << ", " << elf.second
    //      << " proposes moving to " << new_pos.first << ", " << new_pos.second
    //      << "\n";
    return new_pos;
}
int get_empty_spaces_and_bounds(const vector<pair<int, int>> &elves, int &minx,
                                int &maxx, int &miny, int &maxy) {
    minx = INT_MAX;
    miny = INT_MAX;
    maxx = INT_MIN;
    maxy = INT_MIN;
    for (auto elf : elves) {
        // cout << elf.first << ", " << elf.second << "\n";
        minx = min(minx, elf.first);
        maxx = max(maxx, elf.first);
        miny = min(miny, elf.second);
        maxy = max(maxy, elf.second);
    }
    int empty_spaces = (maxx - minx + 1) * (maxy - miny + 1) - elves.size();

    return empty_spaces;
}

void print(const vector<pair<int, int>> &elves,
           const map<pair<int, int>, int> pos2elf) {
    int minx, maxx, miny, maxy;
    int empty_spaces =
        get_empty_spaces_and_bounds(elves, minx, maxx, miny, maxy);
    for (int r = minx; r <= maxx; r++) {
        for (int c = miny; c <= maxy; c++) {
            if (pos2elf.find({r, c}) == pos2elf.end()) {
                cout << ".";
            } else {
                cout << "#";
            }
        }
        cout << "\n";
    }
}
int problem_a(vector<pair<int, int>> elves, map<pair<int, int>, int> pos2elf) {
    map<pair<int, int>, vector<int>> proposed_positions;
    cout << "---Starting------------------------\n";
    print(elves, pos2elf);
    for (int i = 0; i < 10; i++) {
        proposed_positions.clear();
        for (int j = 0; j < elves.size(); j++) {
            auto elf = elves[j];
            auto new_pos = propose_position(pos2elf, elf, i);
            if (proposed_positions.find(new_pos) == proposed_positions.end()) {
                proposed_positions[new_pos] = vector<int>(1, j);
            } else {
                proposed_positions[new_pos].push_back(j);
            }
        }
        for (auto proposed_position : proposed_positions) {
            if (proposed_position.second.size() > 1) {
                continue;
            } else {
                int elfid = proposed_position.second[0];
                pos2elf.erase(elves[elfid]);
                elves[elfid] = proposed_position.first;
                pos2elf[proposed_position.first] = elfid;
            }
        }
        cout << "---After Round " << i + 1 << " --------------------\n";
        print(elves, pos2elf);
    }
    int minx, maxx, miny, maxy;
    int empty_spaces =
        get_empty_spaces_and_bounds(elves, minx, maxx, miny, maxy);

    return empty_spaces;
}

int problem_b(vector<pair<int, int>> elves, map<pair<int, int>, int> pos2elf) {
    map<pair<int, int>, vector<int>> proposed_positions;
    cout << "---Starting------------------------\n";
    print(elves, pos2elf);
    int N = elves.size();
    int no_move_count = 0;
    int i = 0;
    while (no_move_count != N) {
      no_move_count=0;
        proposed_positions.clear();
        for (int j = 0; j < elves.size(); j++) {
            auto elf = elves[j];
            auto new_pos = propose_position(pos2elf, elf, i);
            if (new_pos.first == elf.first && new_pos.second == elf.second) {
                no_move_count++;
            }
            if (proposed_positions.find(new_pos) == proposed_positions.end()) {
                proposed_positions[new_pos] = vector<int>(1, j);
            } else {
                proposed_positions[new_pos].push_back(j);
            }
        }
        for (auto proposed_position : proposed_positions) {
            if (proposed_position.second.size() > 1) {
                continue;
            } else {
                int elfid = proposed_position.second[0];
                pos2elf.erase(elves[elfid]);
                elves[elfid] = proposed_position.first;
                pos2elf[proposed_position.first] = elfid;
            }
        }
        if (i % 42 == 0) {
            cout << "---After Round " << i + 1 << ": " << no_move_count << " of the " << N << " elves stayed put. ------------\n";
            print(elves, pos2elf);
        }
        i++;
    }

    return i;
}

int main(int argc, char **argv) {

    string s;
    int r = 0;
    vector<pair<int, int>> elves;
    map<pair<int, int>, int> pos2elf;
    while (getline(cin, s)) {
        for (int c = 0; c < s.size(); c++) {
            if (s[c] == '#') {
                elves.push_back({r, c});
                pos2elf[elves.back()] = r;
            }
        }
        r++;
    }

    check_direction.push_back(check_north);
    check_direction.push_back(check_south);
    check_direction.push_back(check_west);
    check_direction.push_back(check_east);

    int ans1 = problem_a(elves, pos2elf);
    int ans2 = problem_b(elves, pos2elf);

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
}