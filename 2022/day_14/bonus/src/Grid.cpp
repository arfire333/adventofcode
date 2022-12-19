#include <Grid.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <raylib.h>
#include <vector>
using namespace std;

int64_t Sand::last_id = 0;

void Grid::init(const vector<vector<pair<int, int>>> &scans,int scale) {
    min_x = INT_MAX;
    min_y = INT_MAX;
    max_x = INT_MIN;
    max_y = INT_MIN;
    for (auto scan : scans) {
        this->scans.push_back(scan);
        for (auto p : scan) {
            max_x = max(max_x, p.first);
            max_y = max(max_y, p.second);
            min_x = min(min_x, p.first);
            min_y = min(min_y, p.second);
        }
    }
    SCALE=scale;
    int Y = max_y + 3;
    int X = Y + (max_x - min_x + 1) + Y;
    X_SHIFT = Y - min_x;
    grid = vector<vector<int>>(Y, vector<int>(X, AIR));
    for (auto scan : scans) {
        for (auto i = 1; i < scan.size(); i++) {
            int startx = scan[i - 1].first;
            int starty = scan[i - 1].second;
            int endx = scan[i].first;
            int endy = scan[i].second;
            if (startx == endx) {
                if (starty < endy) {
                    for (int y = starty; y <= endy; y++) {
                        grid[y][startx + X_SHIFT] = GROUND;
                    }
                } else {
                    for (int y = endy; y <= starty; y++) {
                        grid[y][startx + X_SHIFT] = GROUND;
                    }
                }
            } else {
                if (startx < endx) {
                    for (int x = startx; x <= endx; x++) {
                        grid[starty][x + X_SHIFT] = GROUND;
                    }
                } else {
                    for (int x = endx; x <= startx; x++) {
                        grid[starty][x + X_SHIFT] = GROUND;
                    }
                }
            }
        }
    }
    for (int x = 0; x < X; x++) {
        grid[max_y + 2][x] = GROUND;
    }
}

void Grid::update() {
    if (dropping.size() == 0 ||
        (dropping.size() < 100 && dropping.back().y == 2)) {
        dropping.push_back(Sand());
    }
    queue<int64_t> ids2delete;
    for (auto grain = dropping.begin(); grain != dropping.end(); grain++) {
        int y = grain->y;
        int x = grain->x + X_SHIFT;

        if (y + 1 >= grid.size()) {
            if (y < 100) {
                grain->y++;
            } else {
                ids2delete.push(grain->id);
            }
        } else if (grid[y + 1][x] == AIR) {
            grain->y++;
        } else if (grid[y + 1][x - 1] == AIR) {
            grain->y++;
            grain->x--;
        } else if (grid[y + 1][x + 1] == AIR) {
            grain->y++;
            grain->x++;
        } else {
            grid[y][x] = SAND;
            ids2delete.push(grain->id);
            stopped.push_back(*grain);
        }
    }
    while (ids2delete.size() > 0) {
        auto id = ids2delete.front();
        ids2delete.pop();
        auto it = find_if(dropping.begin(), dropping.end(),
                          [&](const Sand &grain) { return grain.id == id; });
        dropping.erase(it);
    }
}

void Grid::draw() {

    int X_OFF = -Sand::STARTING_X*SCALE/2+grid.size()*SCALE;
    int Y_OFF = 10;
    for (auto scan : scans) {
        for (auto i = 0; i + 1 < scan.size(); i++) {
            int x1 = (scan[i].first - Sand::STARTING_X) * SCALE + SCALE*Sand::STARTING_X/2 + X_OFF ;
            int x2 = (scan[i + 1].first - Sand::STARTING_X) * SCALE + SCALE*Sand::STARTING_X/2 + X_OFF;
            int y1 = scan[i].second * SCALE + Y_OFF;
            int y2 = scan[i + 1].second * SCALE + Y_OFF;
            Vector2 p1, p2;
            p1.x = x1;
            p1.y = y1;
            p2.x = x2;
            p2.y = y2;
            DrawLineEx(p1, p2, static_cast<float>(SCALE) - 1, WHITE);
        }
    }
    for (auto p : stopped) {
        Vector2 p1 = {(p.x - Sand::STARTING_X) * SCALE + Sand::STARTING_X*SCALE/2 + X_OFF, p.y * SCALE + Y_OFF};
        DrawCircle(p1.x, p1.y, SCALE / 2, p.color);
    }
    for (auto p : dropping) {
        Vector2 p1 = {(p.x - Sand::STARTING_X) * SCALE + Sand::STARTING_X*SCALE/2 + X_OFF, p.y * SCALE + Y_OFF};
        DrawCircle(p1.x, p1.y, SCALE / 2, p.color);
    }
}

std::pair<int, int> Grid::size() { return {max_x, max_y}; }