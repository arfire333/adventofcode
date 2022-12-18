#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;

enum CellSide {
    EMPTY = 0,
    PRESENT = 1,
    LEFT = 2,
    RIGHT = 4,
    BOTTOM = 8,
    TOP = 16,
    BACK = 32,
    FRONT = 64,
    STEAM = 128
};

int side_count(int cell_value) {
    int retVal = 0;
    retVal += (cell_value & LEFT) != 0;
    retVal += (cell_value & RIGHT) != 0;
    retVal += (cell_value & BOTTOM) != 0;
    retVal += (cell_value & TOP) != 0;
    retVal += (cell_value & BACK) != 0;
    retVal += (cell_value & FRONT) != 0;
    return retVal;
}

int surface_area(const vector<vector<vector<int>>> &grid,
                 const CellSide type = PRESENT) {
    int area = 0;
    for (auto x : grid) {
        for (auto y : x) {
            for (auto val : y) {
                if (val & type) {
                    area += side_count(val);
                }
            }
        }
    }
    return area;
}

bool add_point(vector<vector<vector<int>>> &grid, const vector<int> &pos) {
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];
    int N = grid.size();
    if (grid[x][y][z] != EMPTY) {
        cerr << "Attempted to add point to a filled location!\n";
        return false;
    }
    grid[x][y][z] = PRESENT;
    if (x - 1 >= 0 && (grid[x - 1][y][z] & PRESENT)) {
        grid[x - 1][y][z] ^= RIGHT;
    } else {
        grid[x][y][z] |= LEFT;
    }
    if (x + 1 < N && (grid[x + 1][y][z] & PRESENT)) {
        grid[x + 1][y][z] ^= LEFT;
    } else {
        grid[x][y][z] |= RIGHT;
    }
    if (y - 1 >= 0 && (grid[x][y - 1][z] & PRESENT)) {
        grid[x][y - 1][z] ^= TOP;
    } else {
        grid[x][y][z] |= BOTTOM;
    }
    if (y + 1 < N && (grid[x][y + 1][z] & PRESENT)) {
        grid[x][y + 1][z] ^= BOTTOM;
    } else {
        grid[x][y][z] |= TOP;
    }
    if (z - 1 >= 0 && (grid[x][y][z - 1] & PRESENT)) {
        grid[x][y][z - 1] ^= FRONT;
    } else {
        grid[x][y][z] |= BACK;
    }
    if (z + 1 < N && (grid[x][y][z + 1] & PRESENT)) {
        grid[x][y][z + 1] ^= BACK;
    } else {
        grid[x][y][z] |= FRONT;
    }
    return true;
}

bool add_steam(vector<vector<vector<int>>> &grid, const vector<int> &pos) {
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];
    int N = grid.size();
    if (grid[x][y][z] != EMPTY) {        
        return false;
    }
    grid[x][y][z] = STEAM;
    if (x - 1 >= 0 && (grid[x - 1][y][z] & PRESENT)) {
        grid[x][y][z] |= LEFT;
    }
    if (x + 1 < N && (grid[x + 1][y][z] & PRESENT)) {
        grid[x][y][z] |= RIGHT;
    }
    if (y - 1 >= 0 && (grid[x][y - 1][z] & PRESENT)) {
        grid[x][y][z] |= BOTTOM;
    }
    if (y + 1 < N && (grid[x][y + 1][z] & PRESENT)) {
        grid[x][y][z] |= TOP;
    }
    if (z - 1 >= 0 && (grid[x][y][z - 1] & PRESENT)) {
        grid[x][y][z] |= BACK;
    }
    if (z + 1 < N && (grid[x][y][z + 1] & PRESENT)) {
        grid[x][y][z] |= FRONT;
    }
    return true;
}

int problem_a(const vector<vector<int>> scan, int mincoord, int maxcoord) {
    int N = maxcoord + 1;
    vector<vector<vector<int>>> grid(N, vector<vector<int>>(N, vector<int>(N)));
    assert(N * N * N * 6 < INT_MAX);
    for (auto p : scan) {
        if (!add_point(grid, p)) {
            cerr << "Add Point Failed\n";
        }
    }

    return surface_area(grid);
}

void fill_q(vector<vector<vector<int>>> &grid, const vector<int> &pos,
            queue<vector<int>> &q) {
    int N=grid.size();
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];
    if (x - 1 >= 0 && add_steam(grid, {{x - 1}, {y}, {z}})) {
        q.push({{x-1},{y},{z}});
    }
    if (x + 1 < N && add_steam(grid, {{x + 1}, {y}, {z}})) {
        q.push({{x+1},{y},{z}});
    }
    if (y - 1 >= 0 && add_steam(grid, {{x}, {y - 1}, {z}})) {
        q.push({{x},{y-1},{z}});
    }
    if (y + 1 < N && add_steam(grid, {{x}, {y + 1}, {z}})) {
        q.push({{x},{y+1},{z}});
    }
    if (z - 1 >= 0 && add_steam(grid, {{x}, {y}, {z - 1}})) {
        q.push({{x},{y},{z-1}});
    }
    if (z + 1 < N && add_steam(grid, {{x}, {y}, {z + 1}})) {
        q.push({{x},{y},{z+1}});
    }    
}
int problem_b(const vector<vector<int>> scan, int mincoord, int maxcoord) {
    // 3 to make sure there is a free spot to fill later.
    int N = maxcoord + 3;
    vector<vector<vector<int>>> grid(N, vector<vector<int>>(N, vector<int>(N)));
    assert(N * N * N * 6 < INT_MAX);
    for (auto p : scan) {
        // Add one so nothing is on the edge and
        // thus steam can fill.
        p[0]++;
        p[1]++;
        p[2]++;
        if (!add_point(grid, p)) {
            cerr << "Add Point Failed\n";
        }
    }
    queue<vector<int>> q;
    // No points here so it is safe to start here.
    q.push({N - 1, N - 1, N - 1});
    while (q.size() > 0) {
        vector<int> pos = q.front();
        q.pop();
        fill_q(grid, pos, q);
    }

    return surface_area(grid, STEAM);
}

void test1() {
    vector<vector<int>> scan({{1, 1, 1}});
    int result = problem_a(scan, 1, 2);
    assert(result == 6);
}

void test2() {
    vector<vector<int>> scan({{1, 1, 1}, {2, 1, 1}});
    int result = problem_a(scan, 1, 2);
    assert(result == 10);
    int result_steam = problem_b(scan, 1, 2);
    assert(result_steam == 10);
}

int main(int argc, char **argv) {
    test1();
    test2();
    vector<vector<int>> scan;
    set<vector<int>> scan_check;
    string s;
    int mincoord = INT_MAX;
    int maxcoord = INT_MIN;
    while (getline(cin, s)) {
        int x, y, z;
        sscanf(s.c_str(), "%d,%d,%d", &x, &y, &z);
        mincoord = min(mincoord, min(x, min(y, z)));
        maxcoord = max(maxcoord, max(x, max(y, z)));
        scan.push_back({x, y, z});
        scan_check.insert({x, y, z});
    }
    assert(mincoord >= 0);
    assert(scan.size() == scan_check.size());
    int ans1 = problem_a(scan, mincoord, maxcoord);
    int ans2 = problem_b(scan, mincoord, maxcoord);

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
}