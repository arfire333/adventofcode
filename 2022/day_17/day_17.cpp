#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;
const vector<vector<pair<int64_t, int64_t>>> ROCKS = {
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}};

const vector<int64_t> ROCK_HEIGHT = {1, 3, 3, 4, 2};
const vector<int64_t> ROCK_WIDTH = {4, 3, 3, 1, 2};
// Lower left corner of rock spawns relative to
// the first free space above top rock/ground.
const pair<int64_t, int64_t> SPAWN_POINT = {3, 2};
set<vector<int64_t>> top_value;
vector<pair<int64_t, int64_t>> heights;
enum Material { AIR, ROCK };
map<Material, char> MATERIAL_TO_SYMBOL = {{AIR, '.'}, {ROCK, '@'}};

const int64_t CHAMBER_WIDTH = 7;

void draw_chamber(const vector<vector<Material>> &chamber) {
    int64_t H = chamber.size();

    for (int64_t h = H - 1; h >= 0; h--) {
        cout << std::setfill('0') << std::setw(5) << h << "|";
        for (int64_t w = 0; w < CHAMBER_WIDTH; w++) {
            cout << MATERIAL_TO_SYMBOL[chamber[h][w]];
        }
        cout << "|\n";
    }
    cout << "GND  +";
    for (int64_t w = 0; w < CHAMBER_WIDTH; w++) {
        cout << "-";
    }
    cout << "+\n";
}

/**
 * Add a rock to the chamber if it can.  Grow the chamber as necessary to
 * fit the rock.
 * Return true if successful
 * Return false if it would hit something other than air.
 */
bool add_rock(vector<vector<Material>> &chamber, pair<int, int> point,
              int64_t type) {
    int64_t free_space = chamber.size() - point.first - ROCK_HEIGHT[type];
    while (free_space < 0) {
        chamber.push_back(vector<Material>(CHAMBER_WIDTH, AIR));
        free_space++;
    }
    auto ROCK_FORM = ROCKS[type];
    for (int64_t i = 0; i < ROCK_FORM.size(); i++) {
        int64_t y = point.first + ROCK_FORM[i].first;
        int64_t x = point.second + ROCK_FORM[i].second;
        // bounds check
        if (y < 0 || x < 0 || x >= CHAMBER_WIDTH) {
            return false;
        }
        // air check
        if (chamber[y][x] != AIR) {
            return false;
        }
    }
    for (int64_t i = 0; i < ROCK_FORM.size(); i++) {
        int64_t y = point.first + ROCK_FORM[i].first;
        int64_t x = point.second + ROCK_FORM[i].second;
        chamber[y][x] = ROCK;
    }
    return true;
}
/**
 * Remove  a rock to the chamber if it can.
 * fit the rock.
 * Return true if successful
 * Return false if it would hit something other than air.
 */
bool remove_rock(vector<vector<Material>> &chamber, pair<int, int> point,
                 int64_t type) {
    auto ROCK_FORM = ROCKS[type];
    for (int64_t i = 0; i < ROCK_FORM.size(); i++) {
        int64_t y = point.first + ROCK_FORM[i].first;
        int64_t x = point.second + ROCK_FORM[i].second;
        // bounds check
        if (y >= chamber.size() || y < 0 || x < 0 || x >= CHAMBER_WIDTH) {
            return false;
        }
        // Rock isn't there
        if (chamber[y][x] != ROCK) {
            return false;
        }
    }
    for (int64_t i = 0; i < ROCK_FORM.size(); i++) {
        int64_t y = point.first + ROCK_FORM[i].first;
        int64_t x = point.second + ROCK_FORM[i].second;
        chamber[y][x] = AIR;
    }
    return true;
}

int64_t loop(const vector<int> &shifts, vector<vector<Material>> &chamber,
             int64_t num_rocks) {
    int64_t top_of_pile = 0;
    int64_t time = 0;
    int64_t last_time = 0;
    int64_t blow = 0;
    int64_t rock_count = 0;
    int64_t match_count = 0;
    int64_t last_val = 0;
    
    while (rock_count < num_rocks) {
        int64_t type = rock_count % ROCKS.size();

        pair<int, int> pos;
        pos.first = top_of_pile + SPAWN_POINT.first;
        pos.second = SPAWN_POINT.second;
        if (!add_rock(chamber, pos, type)) {
            cerr << "Error adding rock of type: " << type << " at "
                 << "height: " << pos.first << " and x coord: " << pos.second
                 << "\n";
            cerr << "\n";
        }
        bool not_grounded = true;
        while (not_grounded) {
            blow = shifts[time % shifts.size()];
            auto new_pos = pos;
            // blow the rock
            new_pos.second = pos.second + blow;
            if (remove_rock(chamber, pos, type)) {
                if (add_rock(chamber, new_pos, type)) {
                    pos.first = new_pos.first;
                    pos.second = new_pos.second;
                } else {
                    add_rock(chamber, pos, type);
                }
            } else {
                cerr << "Tried to remove a rock that didn't exist!\n";
                return -1;
            }
            new_pos.first = pos.first - 1;
            new_pos.second = pos.second;
            if (remove_rock(chamber, pos, type)) {
                if (add_rock(chamber, new_pos, type)) {
                    pos = new_pos;
                } else {
                    add_rock(chamber, pos, type);
                    top_of_pile =
                        max(top_of_pile, pos.first + ROCK_HEIGHT[type]);
                    not_grounded = false;
                }
            } else {
                cerr << "Tried to remove a rock that didn't exist!\n";
                return -1;
            }
            time++;
        }
        int val = 0;
        for (int i = 0; i < CHAMBER_WIDTH; i++) {
            val = val << 1;
            val = val | (chamber[top_of_pile - 1][i] == ROCK);
        }
        int64_t last_shift_idx = (time - 1LL) % shifts.size();
        top_value.insert({type, val, last_val, last_shift_idx});
        last_val = val;
        last_time = time;
        rock_count++;
        if (rock_count < 100000) {
            heights.push_back({val, top_of_pile});
        }
    }
    
    return top_of_pile;
}

int64_t auto_corr(int range) {
    vector<int64_t> r(range + 1);
    int64_t maxi = 0;
    int64_t maxsum = 0;
    for (int i = 1; i < range; i++) {
        int64_t sum = 0;
        for (int j = 0; j < heights.size() - range; j++) {
            sum += heights[j].first * heights[j + i].first;
        }
        r[i] = sum;
        if (r[i] > maxsum) {
            maxsum = r[i];
            maxi = i;
        }
    }
    return maxi;
}

int64_t problem_a(const vector<int> shifts) {        
    vector<vector<Material>> chamber(4, vector<Material>(CHAMBER_WIDTH, AIR));
    return loop(shifts, chamber, 2022);
}

int64_t problem_b(const vector<int> shifts) { 
    int64_t GOAL = 1000000000000;   
    vector<vector<Material>> chamber(4, vector<Material>(CHAMBER_WIDTH, AIR));

    // Gen fresh heights data for autocorr;
    heights.clear();
    loop(shifts, chamber, 5000);
    int64_t seq_length = auto_corr(top_value.size());
    cout << "Repeating Sequence Length: " << seq_length << "\n";
    int64_t base = top_value.size() - seq_length;
    cout << "Non-Repeating Sequence Length: " << base << "\n";
    int64_t base_height = heights[base].second;
    vector<int64_t> delta_height;
    for (int i = 0; i <= seq_length; i++) {
        delta_height.push_back(heights[base + i].second - heights[base].second);        
    }
    
    int64_t complete_cycles = (GOAL - base) / seq_length;
    int64_t remaining_cycles = (GOAL - base) % seq_length;
    int64_t final_height = base_height + complete_cycles * delta_height[seq_length] +
                           delta_height[remaining_cycles] - 1;

    // Get a plot for fun
    chamber.clear();
    loop(shifts,chamber,base+seq_length*2-1);
    draw_chamber(chamber);

    return final_height;
}

int main(int argc, char **argv) {

    string s;
    vector<int> shifts;
    getline(cin, s);
    for (auto c : s) {
        if (c == '<') {
            shifts.push_back(-1);
        } else if (c == '>') {
            shifts.push_back(1);
        }
    }

    int64_t ans1 = problem_a(shifts);
    int64_t ans2 = problem_b(shifts);

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
}