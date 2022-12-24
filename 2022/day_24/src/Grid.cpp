#include <Grid.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <raylib.h>
#include <set>
#include <string>
#include <vector>
using namespace std;

void Grid::draw(int tick) {
    float height_offset = (GetRenderHeight() - height * scale) / 2;
    float width_offset = (GetRenderWidth() - width * scale) / 2;
    float t_shrink = 3;
    for (auto w : walls) {
        int x = w.first * scale + width_offset;
        int y = w.second * scale + height_offset;
        DrawRectangle(x, y, scale, scale, BROWN);
    }

    for (auto b : blizzards[tick % blizzards.size()]) {
        auto direction = b.first;
        float x = b.second.first * scale + width_offset;
        float y = b.second.second * scale + height_offset;
        switch (direction) {
        case '>':
            // x += scale / 4;
            DrawTriangle({x + t_shrink, y + t_shrink},
                         {x + t_shrink, y + scale - t_shrink},
                         {x + scale - t_shrink, y + scale / 2}, WHITE);
            break;
        case '<':
            // x -= scale / 4;
            DrawTriangle({x + scale - t_shrink, y + t_shrink},
                         {x + t_shrink, y + scale / 2},
                         {x + scale - t_shrink, y + scale - t_shrink}, WHITE);
            break;
        case '^':
            // y -= scale / 4;
            DrawTriangle({x + t_shrink, y + scale - t_shrink},
                         {x + scale - t_shrink, y + scale - t_shrink},
                         {x + scale / 2, y + t_shrink}, WHITE);
            break;
        case 'v':
            // y += scale / 4;
            DrawTriangle({x + t_shrink, y + t_shrink},
                         {x + scale / 2, y + scale - t_shrink},
                         {x + scale - t_shrink, y + t_shrink}, WHITE);
            break;
        default:
            DrawText("X", x, y, scale, RED);
            break;
        }
    }

    auto E = path[tick % path.size()];
    float x = E.first * scale + width_offset;
    float y = E.second * scale + height_offset - elf.height/2;
    DrawTexture(elf, x, y, WHITE);
}

int Grid::findPathBFS(pair<int, int> cstart, pair<int, int> cdest, int startt) {
    queue<pair<int, vector<pair<int, int>>>> q;
    std::set<int64_t> visited;
    q.push({startt, {cstart}});
    visited.insert(spaceTimeId(start, 0));
    while (q.size() > 0) {
        auto t = q.front().first;
        auto p = q.front().second;
        q.pop();
        if (p.back().first == cdest.first && p.back().second == cdest.second) {
            path.insert(path.end(), p.begin() + 1, p.end());
            min_path_length = t;
            return t;
        }
        t++;
        int next_b_idx = t % blizzards.size();
        vector<pair<int, int>> next_vec({p.back()});
        next_vec.push_back({p.back().first + 1, p.back().second});
        next_vec.push_back({p.back().first - 1, p.back().second});
        next_vec.push_back({p.back().first, p.back().second + 1});
        next_vec.push_back({p.back().first, p.back().second - 1});

        for (auto next : next_vec) {
            if (next.first < 0 || next.first >= width || next.second < 0 ||
                next.second >= height) {
                continue;
            } else {
                auto nextId = spaceTimeId(next, next_b_idx);
                if (visited.find(nextId) == visited.end()) {
                    if (occupied_spaces[next_b_idx].find(next) ==
                        occupied_spaces[next_b_idx].end()) {
                        visited.insert(nextId);
                        p.push_back(next);
                        q.push({t, p});
                        p.pop_back();
                    }
                }
            }
        }
    }
}

void Grid::init(const vector<string> &in, int scale) {
    this->scale = scale;

    grid = in;
    height = grid.size();
    width = grid[0].size();
    int num_positions = std::lcm(height - 2, width - 2);
    std::vector<std::pair<char, std::pair<int, int>>> starting_blizzards;
    set<pair<int, int>> starting_occupied_spaces;
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            if (grid[r][c] == '#') {
                walls.push_back({c, r});
                starting_occupied_spaces.insert({c, r});
            } else if (grid[r][c] == '.') {
                if (r == 0) {
                    start = {c, r};
                    curr = {c, r};
                } else if (r + 1 == height) {
                    dest = {c, r};
                }
            } else {
                starting_blizzards.push_back({in[r][c], {c, r}});
                starting_occupied_spaces.insert({c, r});
            }
        }
    }

    for (int i = 0; i < num_positions; i++) {
        blizzards.push_back(starting_blizzards);
        occupied_spaces.push_back(starting_occupied_spaces);
        updateBlizzards(starting_blizzards);
        starting_occupied_spaces.clear();
        for (auto w : walls) {
            starting_occupied_spaces.insert(w);
        }
        for (auto b : starting_blizzards) {
            starting_occupied_spaces.insert(b.second);
        }
    }
    std::set<int64_t> visited;
    visited.insert(spaceTimeId({start.first, start.first - 1}, 0));
    std::vector<std::pair<int, int>> p;
    min_path_length = INT_MAX;
    int t = 0;

    t = findPathBFS(start, dest, t);
    t = findPathBFS(dest, start, t);
    t = findPathBFS(start, dest, t);
}

void Grid::setElf(Texture2D elf) { this->elf = elf; }
/*
 * This will break if we use a board that has a dimension >1024
 * or a time index > 2^44.
 */
int64_t Grid::spaceTimeId(std::pair<int, int> point, int b_idx) {
    int64_t hash = 0;
    hash = static_cast<int64_t>(b_idx);
    hash = hash << 16;
    hash += static_cast<int64_t>(point.first);
    hash = hash << 16;
    hash += static_cast<int64_t>(point.second);
    return hash;
}

void Grid::update() {}
void Grid::updateBlizzards(
    std::vector<std::pair<char, std::pair<int, int>>> &blizzards) {
    for (auto &b : blizzards) {
        auto direction = b.first;
        int nx = b.second.first;
        int ny = b.second.second;
        switch (direction) {
        case '>':
            nx++;
            if (nx >= width - 1)
                nx = 1;
            break;
        case '<':
            nx--;
            if (nx == 0)
                nx = width - 2;
            break;
        case '^':
            ny--;
            if (ny == 0)
                ny = height - 2;
            break;
        case 'v':
            ny++;
            if (ny >= height - 1)
                ny = 1;
            break;
        default:
            break;
        }
        b.second.first = nx;
        b.second.second = ny;
    }
}

Vector2 Grid::windowSize() {
    return {scale * static_cast<float>(width),
            scale * static_cast<float>(height)};
}
