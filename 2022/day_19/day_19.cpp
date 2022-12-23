#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;
struct Resources;
void test_update_resources();
int spend(int recipe, Resources resources, int time = 24);

enum ROBOT_TYPE { ORE = 0, CLAY = 1, OBSIDIAN = 2, GEODE = 4 };
const vector<vector<int>> TESTDATA = {{4, 2, 3, 14, 2, 7}, {2, 3, 3, 8, 3, 12}};

const vector<vector<int>> MYDATA = {
    {4, 4, 4, 5, 3, 7},   {3, 3, 2, 20, 2, 20}, {4, 3, 2, 20, 2, 9},
    {4, 3, 3, 7, 3, 9},   {4, 4, 4, 8, 2, 18},  {2, 4, 3, 19, 4, 12},
    {3, 3, 3, 11, 2, 8},  {4, 3, 2, 19, 3, 10}, {3, 4, 3, 18, 4, 19},
    {4, 4, 4, 20, 2, 12}, {4, 4, 3, 5, 4, 11},  {3, 3, 3, 19, 2, 9},
    {2, 4, 4, 18, 2, 11}, {3, 4, 2, 19, 2, 12}, {4, 3, 2, 14, 4, 11},
    {4, 3, 4, 18, 4, 11}, {3, 3, 2, 16, 2, 18}, {4, 3, 3, 7, 2, 7},
    {4, 4, 2, 17, 3, 11}, {3, 3, 3, 9, 2, 10},  {2, 3, 3, 8, 3, 20},
    {4, 3, 4, 19, 4, 12}, {4, 3, 2, 5, 2, 10},  {3, 4, 2, 15, 2, 13},
    {2, 4, 4, 17, 3, 11}, {4, 4, 4, 17, 4, 20}, {4, 4, 2, 8, 3, 9},
    {2, 2, 2, 8, 2, 14},  {2, 3, 3, 17, 3, 10}, {2, 3, 2, 14, 3, 8}};

const vector<vector<int>> *data_under_test;
struct Robot {
    ROBOT_TYPE type = ORE;
    Robot(ROBOT_TYPE type) : type(type){};
};

struct Resources {
    int ore = 0;
    int clay = 0;
    int obsidian = 0;
    int geode = 0;
    int orbots = 0;
    int claybots = 0;
    int obsbots = 0;
    int geobots = 0;
};
constexpr bool operator<(const Resources &lhs, const Resources &rhs) {
    if (lhs.geode < rhs.geode)
        return true;
    if (lhs.geode > rhs.geode)
        return false;
    if (lhs.geobots < rhs.geobots)
        return true;
    if (lhs.geobots > rhs.geobots)
        return false;
    if (lhs.obsidian < rhs.obsidian)
        return true;
    if (lhs.obsidian > rhs.obsidian)
        return false;
    if (lhs.obsbots < rhs.obsbots)
        return true;
    if (lhs.obsbots > rhs.obsbots)
        return false;
    if (lhs.clay < rhs.clay)
        return true;
    if (lhs.clay > rhs.clay)
        return false;
    if (lhs.claybots < rhs.claybots)
        return true;
    if (lhs.claybots > rhs.claybots)
        return false;
    if (lhs.ore < rhs.ore)
        return true;
    if (lhs.ore > rhs.ore)
        return false;
    if (lhs.orbots < rhs.orbots)
        return true;
    return false;
}
constexpr bool operator==(const Resources &lhs, const Resources &rhs) {
    return !(lhs < rhs || rhs < lhs);
}
void add_bots(ROBOT_TYPE type, int count, Resources &r) {
    switch (type) {
    case ORE:
        r.orbots += count;
        break;
    case CLAY:
        r.claybots += count;
        break;
    case OBSIDIAN:
        r.obsbots += count;
        break;
    case GEODE:
        r.geobots += count;
        break;
    default:
        break;
    }
}

void build_options(int recipe, vector<Resources> &r_vec, Resources r) {
    vector<int> costs = (*data_under_test)[recipe];
    int max_orbots = r.ore / costs[ORE];
    for (int i = max_orbots; i >= 0; i--) {
        Resources ir = r;
        ir.ore = ir.ore - i * costs[ORE];
        add_bots(ORE, i, ir);
        int max_claybots = ir.ore / costs[CLAY];
        for (int j = max_claybots; j >= 0; j--) {
            Resources jr = ir;
            jr.ore = jr.ore - j * costs[CLAY];
            add_bots(CLAY, j, jr);
            int max_obsbots =
                min(jr.ore / costs[OBSIDIAN], jr.clay / costs[OBSIDIAN + 1]);
            for (int k = max_obsbots; k >= 0; k--) {
                Resources kr = jr;
                kr.ore = kr.ore - k * costs[OBSIDIAN];
                kr.clay = kr.clay - k * costs[OBSIDIAN + 1];
                add_bots(OBSIDIAN, k, kr);
                int max_geobots =
                    min(kr.ore / costs[GEODE], kr.obsidian / costs[GEODE + 1]);
                for (int l = max_geobots; l + 1 > max_geobots; l--) {
                    Resources lr = kr;
                    lr.ore = lr.ore - l * costs[GEODE];
                    lr.obsidian = lr.obsidian - l * costs[GEODE + 1];
                    add_bots(GEODE, l, lr);
                    r_vec.push_back(lr);
                }
            }
        }
    }
}

void update_resources(Resources &next_r) {
    next_r.geode += next_r.geobots;
    next_r.ore += next_r.orbots;
    next_r.clay += next_r.claybots;
    next_r.obsidian += next_r.obsbots;
}

int collect(int recipe, Resources r, int time) {
    update_resources(r);
    int geode_count = spend(recipe, r, time - 1);
    return geode_count;
}
int maxmax = 0;
int maxmaxrecipe = 0;
int spend(int recipe, Resources resources, int time) {
    if (time == 0) {
        if (resources.geode > maxmax) {
            maxmax = resources.geode;
            maxmaxrecipe = recipe;
        }
        // if (resources.geode > 0)
        //     cout << "Recipe: " << recipe << "      Ore: " << resources.ore
        //          << "     Clay: " << resources.clay
        //          << " Obsidian: " << resources.obsidian
        //          << "   Geodes: " << resources.geode << "\n";
        return resources.geode;
    }

    // This is the upper bound on how many geodes are possible to make given the
    // remaining time assuming best case that we can produce one new geobot per
    // time

    if (resources.geode + time * resources.geobots + (time * time - time) / 2 <=
        maxmax) {
        return 0;
    }
    vector<int> costs = (*data_under_test)[recipe];

    int max_geobots = min(resources.ore / costs[GEODE],
                          resources.obsidian / costs[GEODE + 1]);

    int max_obsbots = min(resources.ore / costs[OBSIDIAN],
                          resources.clay / costs[OBSIDIAN + 1]);
    int max_claybots = resources.ore / costs[CLAY];
    int max_orbots = resources.ore / costs[ORE];
    update_resources(resources);
    int geode_count = spend(recipe, resources, time - 1);
    if (max_geobots > 0) {
        max_geobots = 1;
        auto lr = resources;
        lr.ore = lr.ore - max_geobots * costs[GEODE];
        lr.obsidian = lr.obsidian - max_geobots * costs[GEODE + 1];
        add_bots(GEODE, max_geobots, lr);
        geode_count = max(geode_count, spend(recipe, lr, time - 1));
    }

    if (max_obsbots > 0) {
        max_obsbots = 1;
        Resources kr = resources;
        kr.ore = kr.ore - max_obsbots * costs[OBSIDIAN];
        kr.clay = kr.clay - max_obsbots * costs[OBSIDIAN + 1];
        add_bots(OBSIDIAN, max_obsbots, kr);
        geode_count = max(geode_count, spend(recipe, kr, time - 1));
    }

    if (max_claybots > 0) {
        max_claybots = 1;
        Resources jr = resources;
        jr.ore = jr.ore - max_claybots * costs[CLAY];
        add_bots(CLAY, max_claybots, jr);
        geode_count = max(geode_count, spend(recipe, jr, time - 1));
    }

    if (max_orbots > 0) {
        max_orbots = 1;
        Resources ir = resources;
        ir.ore = ir.ore - max_orbots * costs[ORE];
        add_bots(ORE, max_orbots, ir);
        geode_count = max(geode_count, spend(recipe, ir, time - 1));
    }

    return geode_count;
}

int problem_a(int time_available = 24) {
    Resources r;
    r.orbots = 1;
    // r.robots.push_back(Robot(ORE));
    data_under_test = &MYDATA;
    int max_geodes = 0;
    int result = 0;
    for (int recipe = 0; recipe < MYDATA.size(); recipe++) {
        maxmax = 0;
        int geodes = spend(recipe, r, time_available);
        result += (recipe + 1) * geodes;
        cout << "Max for recipe " << recipe + 1 << " is " << geodes
             << " with best ever being " << maxmax
             << " and current result = " << result << ".\n";
    }

    return result;
}

int problem_b() {
    Resources r;
    r.orbots = 1;
    // r.robots.push_back(Robot(ORE));
    data_under_test = &MYDATA;
    int max_geodes = 0;
    int64_t result = 0;
    int time_available=32;
    for (int recipe = 0; recipe <3; recipe++) {
        maxmax = 0;
        int64_t geodes = spend(recipe, r, time_available);
        result = result * geodes;
        cout << "Part B Max for recipe " << recipe + 1 << " is " << geodes
             << " with best ever being " << maxmax
             << " and current result = " << result << ".\n";
    }

    return result;
    return 0;
}

int main(int argc, char **argv) {
    data_under_test = &MYDATA;
    test_update_resources();
    // int ans1 = problem_a();
    int ans2 = problem_b();

    // cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
    return 0;
}
void test_equal_resources() {
    Resources r;
    r.orbots = 3;
    r.geobots = 2;
    update_resources(r);
    Resources r2;
    r2.orbots = 3;
    r2.geobots = 2;
    r2.ore = 3;
    r2.geode = 2;
    vector<Resources> v = {r, r2};
    sort(v.begin(), v.end());
    assert(r == r2);
}

void test_update_resources() {
    Resources r;
    r.orbots = 1;
    assert(r.ore == 0);
    assert(r.clay == 0);
    assert(r.obsidian == 0);
    assert(r.geode == 0);

    update_resources(r);
    assert(r.ore == 1);
    assert(r.clay == 0);
    assert(r.obsidian == 0);
    assert(r.geode == 0);

    add_bots(CLAY, 1, r);
    update_resources(r);
    assert(r.claybots == 1);
    assert(r.ore == 2);
    assert(r.clay == 1);
    assert(r.obsidian == 0);
    assert(r.geode == 0);

    add_bots(OBSIDIAN, 1, r);
    update_resources(r);
    assert(r.obsbots == 1);
    assert(r.ore == 3);
    assert(r.clay == 2);
    assert(r.obsidian == 1);
    assert(r.geode == 0);

    add_bots(GEODE, 1, r);
    update_resources(r);
    assert(r.geobots == 1);
    assert(r.ore == 4);
    assert(r.clay == 3);
    assert(r.obsidian == 2);
    assert(r.geode == 1);
}