#include <Grid.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <raylib.h>
#include <vector>
using namespace std;

vector<bool (*)(const map<pair<int, int>, int> &, const pair<int, int> &)>
    check_direction;

std::vector<std::pair<int, int>> direction_modifiers = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

inline bool check_alone(const std::map<std::pair<int, int>, int> &pos2elf,
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
inline bool check_north(const std::map<std::pair<int, int>, int> &pos2elf,
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
inline bool check_south(const std::map<std::pair<int, int>, int> &pos2elf,
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
inline bool check_east(const std::map<std::pair<int, int>, int> &pos2elf,
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
inline bool check_west(const std::map<std::pair<int, int>, int> &pos2elf,
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
        return elf;
    }
    pair<int, int> new_pos = {elf.first + direction_modifiers[move_dir].first,
                              elf.second +
                                  direction_modifiers[move_dir].second};

    return new_pos;
}
int get_empty_spaces_and_bounds(const vector<pair<int, int>> &elves, int &minx,
                                int &maxx, int &miny, int &maxy) {
    minx = INT_MAX;
    miny = INT_MAX;
    maxx = INT_MIN;
    maxy = INT_MIN;
    for (auto elf : elves) {
        minx = min(minx, elf.first);
        maxx = max(maxx, elf.first);
        miny = min(miny, elf.second);
        maxy = max(maxy, elf.second);
    }
    int empty_spaces = (maxx - minx + 1) * (maxy - miny + 1) - elves.size();

    return empty_spaces;
}
void Grid::init(vector<pair<int, int>> elves,
                map<pair<int, int>, int> pos2elf) {
    this->elves = elves;
    this->pos2elf = pos2elf;
    check_direction.clear();
    check_direction.push_back(check_north);
    check_direction.push_back(check_south);
    check_direction.push_back(check_west);
    check_direction.push_back(check_east);
}

void Grid::update() {
    no_move_count = 0;
    proposed_positions.clear();
    for (int j = 0; j < elves.size(); j++) {
        auto elf = elves[j];
        auto new_pos = propose_position(pos2elf, elf, tick);
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

    int empty_spaces =
        get_empty_spaces_and_bounds(elves, minx, maxx, miny, maxy);
    
    tick++;
}

void Grid::draw() {
    for (int r = minx; r <= maxx; r++) {
        for (int c = miny; c <= maxy; c++) {
            if (pos2elf.find({r, c}) != pos2elf.end()) {
                
                DrawCubeTexture(elftext,Vector3(c*scale,r*scale,0),elftext.width/2,-elftext.height/2,0,WHITE);

            }
        }        
    }
}