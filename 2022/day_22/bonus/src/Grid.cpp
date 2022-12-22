#include <Grid.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <raylib.h>
#include <vector>
using namespace std;
void Grid::draw_cube(const int SCALE) {
    float BUFFER = 0.707;
    DrawCube(Vector3(25 * SCALE, 25 * SCALE, 25 * SCALE), 48*SCALE,48*SCALE,48*SCALE, WHITE);
    for (int r = 1; r + 1 < grid.size(); r++) {
        for (int c = 1; c + 1 < grid[0].size(); c++) {
            float x = 0;
            float y = 0;
            float z = 0;
            float xSize = 2;
            float ySize = 2;
            float zSize = 2;
            auto cubeColor = ColorFromHSV(((x + y + z) * SCALE), 0.75f, 0.9f);
            cubeColor = GREEN;
            float cubeSize = SCALE - 2;
            int new_side = 0;
            if (r > 3 * N) {
                if (c <= N) { // Face 6
                    z = N - c + 1;
                    x = ((r - 1) % N) + 1;
                    y = N;
                    new_side = 6;
                }

            } else if (r > 2 * N) {
                if (c <= N) { // Face 4
                    z = N - c + 1;
                    y = (r - 1) % N;
                    x = 1;
                    new_side = 4;
                } else if (c > N && c <= 2 * N) { // Face 5
                    z = 1;
                    x = ((c - 1) % N) + 1;
                    y = ((r - 1) % N) + 1;
                    new_side = 5;
                }
            } else if (r > N) {
                if (c > N && c < 2 * N) { // Face 3
                    z = N - ((r - 1) % N);
                    x = ((c - 1) % N) + 1;
                    y = 0;
                    new_side = 3;
                }
            } else {
                if (c > N && c <= 2 * N) { // Face 1
                    z = N;
                    x = ((c - 1) % N) + 1;
                    y = N - r;
                    new_side = 1;
                } else if (c > 2 * N) { // Face 2
                    z = N - ((c - 1) % N);
                    x = N;
                    y = N - r;
                    new_side = 2;
                }
            }

            if (grid[r][c] == '#') {
                cubeColor = RED;         
                zSize=4;
                xSize=4;
                ySize=4;
            }
            if (current.first == r && current.second == c) {
                pos3d.x = x * SCALE;
                pos3d.y = y * SCALE;
                pos3d.z = z * SCALE;
                cubeColor =ColorFromHSV(240,1,1);
                
                if (new_side == 1 || new_side == 5) {
                    zSize = 8;
                    ySize = 4;
                    zSize = 4;
                } else if (new_side == 6 || new_side == 3) {
                    ySize = 8;
                    zSize = 4;
                    xSize = 4;
                } else if (new_side == 2 || new_side == 4) {
                    xSize = 8;
                    ySize = 4;
                    zSize = 4;
                }

                _side = new_side;
            }
            if (grid[r][c] == ' ') {
                continue;
            }
            DrawCube(Vector3(x * SCALE, y * SCALE, z * SCALE), xSize, ySize,
                     zSize, cubeColor);
        }
    }
}
void Grid::step_cube() {
    if (current_command >= commands.size()) {
        return; // Reached the end
    }
    bool moved = false;
    while (!moved &&
           current_command_progress < commands[current_command].first) {
        switch (orientation) {
        case '>':
            moved = move_right_cube();
            break;
        case '<':
            moved = move_left_cube();
            break;
        case 'v':
            moved = move_down_cube();
            break;
        case '^':
            moved = move_up_cube();
            break;
        default:
            break;
        }
    }
    if (current_command_progress >= commands[current_command].first) {
        turn(commands[current_command].second);
        current_command++;
        current_command_progress = 0;
    }
}
void Grid::step() {
    if (current_command >= commands.size()) {
        return; // Reached the end
    }
    switch (orientation) {
    case '>':
        move_right();
        break;
    case '<':
        move_left();
        break;
    case 'v':
        move_down();
        break;
    case '^':
        move_up();
        break;
    default:
        break;
    }
    if (current_command_progress >= commands[current_command].first) {
        turn(commands[current_command].second);
        current_command++;
        current_command_progress = 0;
    }
}

void Grid::init(const vector<string> &g, const string &commands) {

    parseCommands(commands);
    pos3d.x = 50;
    pos3d.y = 50;
    pos3d.z = 50;

    size_t R = g.size() + 2;
    size_t C = 0;
    for (auto r : g) {
        C = max(C, r.size());
    }
    if (C > R) { // example format

    } else {

        N = C / 3;
        cout << "N=" << N << "   C=" << C << "   R=" << R - 2 << "   R/3"
             << (R - 2) / 3 << "\n";

        C = C + 2;
        grid.resize(R, vector<char>(C, ' '));
        bool looking_for_first = true;
        int row = 1;
        for (auto r : g) {
            int col = 1;
            for (auto c : r) {
                if (looking_for_first && c == '.') {
                    start = {row, col};
                    looking_for_first = false;
                }
                grid[row][col] = c;
                col++;
            }
            row++;
        }
        current = start;
        orientation = '>';
    }
}
void Grid::print(const Show &show) {
    cout << "+";
    for (auto i = 0; i < grid[0].size(); i++) {
        cout << "-";
    }
    cout << "+\n";
    int row = 0;
    for (auto r : grid) {
        cout << "|";
        int col = 0;
        for (auto c : r) {
            if (show & START_POSITION && row == start.first &&
                col == start.second) {
                cout << "s";
            } else if (show & CURRENT_POSITION && row == current.first &&
                       col == current.second) {
                cout << orientation;
            } else {
                cout << c;
            }
            col++;
        }
        row++;
        cout << "|\n";
    }
    cout << "+";
    for (auto i = 0; i < grid[0].size(); i++) {
        cout << "-";
    }
    cout << "+\n";
}

void Grid::parseCommands(const string &s) {
    int start = 0;
    int end = 0;
    while (start < s.size()) {
        end = start + 1;
        while (s[end] >= '0' && s[end] <= '9') {
            end++;
        }
        int distance = stoi(s.substr(start, end - start));
        commands.push_back({distance, s[end]});
        start = end + 1;
    }
}

void Grid::printCommands() {
    for (auto [d, c] : commands) {
        cout << "Move " << d << " spaces then turn " << c << ".\n";
    }
}

void Grid::move_up() {
    current_command_progress++;
    int r = current.first - 1;
    if (r == 0) {
        r = grid.size() - 2;
    }
    while (grid[r][current.second] == ' ') {
        r--;
        if (r == 0) {
            r = grid.size() - 2;
        }
    }
    if (grid[r][current.second] == '#')
        return;

    current.first = r;
}
void Grid::move_down() {
    current_command_progress++;
    int r = current.first + 1;
    if (r == grid.size()) {
        r = 1;
    }
    while (grid[r][current.second] == ' ') {
        r++;
        if (r == grid.size()) {
            r = 1;
        }
    }
    if (grid[r][current.second] == '#')
        return;

    current.first = r;
}
void Grid::move_right() {
    current_command_progress++;
    int c = current.second + 1;
    if (c == grid[current.first].size()) {
        c = 1;
    }
    while (grid[current.first][c] == ' ') {
        c++;
        if (c == grid[current.first].size()) {
            c = 1;
        }
    }
    if (grid[current.first][c] == '#')
        return;

    current.second = c;
}
void Grid::move_left() {
    current_command_progress++;
    int r = current.first;
    int c = current.second - 1;
    if (c == 0) {
        c = grid[r].size() - 2;
    }
    while (grid[r][c] == ' ') {
        c--;
        if (c == 0) {
            c = grid[r].size() - 2;
        }
    }
    if (grid[r][c] == '#')
        return;

    current.second = c;
}

void Grid::turn(char direction) {
    if (direction == 'L' || direction == 'R') {
        switch (orientation) {
        case '>':
            if (direction == 'L')
                orientation = '^';
            else
                orientation = 'v';
            break;
        case '<':
            if (direction == 'L')
                orientation = 'v';
            else
                orientation = '^';

            break;
        case 'v':
            if (direction == 'L')
                orientation = '>';
            else
                orientation = '<';

            break;
        case '^':
            if (direction == 'L')
                orientation = '<';
            else
                orientation = '>';
            break;
        default:
            break;
        }
    }
}

int Grid::password() {
    int orientation_val = 0;
    if (orientation == '>')
        orientation_val = 0;
    if (orientation == 'v')
        orientation_val = 1;
    if (orientation == '<')
        orientation_val = 2;
    if (orientation == '^')
        orientation_val = 3;
    return current.first * 1000 + current.second * 4 + orientation_val;
}
/*
 3->1 left faces right
 2->1 top facing down
 1->2 top facing down
 6->4 right facing left
 */
bool Grid::move_up_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r - 1;
    int nc = c;
    int no = orientation;
    if (grid[nr][c] == '#') {
        return false;
    }
    if (grid[nr][c] == ' ') {
        // wrapping
        if (c <= N) {
            nr = N + c;
            nc = N + 1;
            no = '>';
        } else if (c > N && c <= 2 * N) {
            nr = 3 * N + ((c - 1) % N) + 1;
            nc = 1;
            no = '>';
        } else { // c>2N
            nr = 4 * N;
            nc = ((c - 1) % N) + 1;
        }
        if (grid[nr][nc] == '#') {
            return false;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
    return true;
}
bool Grid::move_down_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r + 1;
    int nc = c;
    int no = orientation;
    if (grid[nr][c] == '#') {
        return false;
    }
    if (grid[nr][c] == ' ') {
        // wrapping
        if (c <= N) {
            nr = 1;
            nc = 2 * N + c;
        } else if (c > N && c <= 2 * N) {
            nr = 2 * N + c;
            nc = N;
            no = '<';
        } else { // c>2N
            nr = c - N;
            nc = 2 * N;
            no = '<';
        }
        if (grid[nr][nc] == '#') {
            return false;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
    return true;
}
bool Grid::move_right_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r;
    int nc = c + 1;
    int no = orientation;
    if (grid[r][nc] == '#') {
        return false;
    }
    if (grid[r][nc] == ' ') {
        // wrapping
        if (r > 3 * N) {
            nr = 3 * N;
            nc = r - 2 * N;
            no = '^';
        } else if (r > 2 * N) {
            nr = N - ((r - 1) % N);
            nc = 3 * N;
            no = '<';
        } else if (r > N) {
            nr = N;
            nc = r + N;
            no = '^';
        } else {
            nr = 3 * N - ((r - 1) % N);
            nc = 2 * N;
            no = '<';
        }
        if (grid[nr][nc] == '#') {
            return false;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
    return true;
}
bool Grid::move_left_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r;
    int nc = c - 1;
    int no = orientation;
    if (grid[r][nc] == '#') {
        return false;
    }
    if (grid[r][nc] == ' ') {
        // wrapping
        if (r > 3 * N) {
            nr = 1;
            nc = r - 2 * N;
            no = 'v';
        } else if (r > 2 * N) {
            nr = N - ((r - 1) % N);
            nc = N + 1;
            no = '>';
        } else if (r > N) {
            nr = 2 * N + 1;
            nc = r - N;
            no = 'v';
        } else {
            nr = 3 * N - ((r - 1) % N);
            nc = 1;
            no = '>';
        }
        if (grid[nr][nc] == '#') {
            return false;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
    return true;
}
