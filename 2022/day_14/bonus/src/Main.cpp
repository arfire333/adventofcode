#include "Grid.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <raylib.h>
#include <string>
#include <vector>

using namespace std;
void get_data(const string fn, vector<vector<pair<int, int>>> &scans);
int main(int argc, char **argv) {
    // Put command line argument parser here
    vector<vector<pair<int, int>>> scans = {
        {{498, 4}, {498, 6}, {496, 6}},
        {{503, 4}, {502, 4}, {502, 9}, {494, 9}}};
    pair<int, int> start_point = {500, 0};

    if (argc > 1) {
        get_data(argv[1], scans );
    }
    Grid g;
    int SCALE=4;
    g.init(scans, SCALE);
    auto s = g.size();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow((s.second * SCALE +20)* 2, s.second*SCALE+20, argv[0]);
    SetExitKey(0);
    // Move this later
    InitAudioDevice();
    SetTargetFPS(120);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        g.update();
        g.draw();
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}

void get_data(const string fn, vector<vector<pair<int, int>>> &scans) {
    ifstream fs(fn);

    if (fs.is_open()) {
        scans.clear();
        string s;
        while (getline(fs, s)) {
            int x = 0;
            int y = 0;
            int start = 0;
            int end = 0;
            vector<pair<int, int>> scan;

            while (start < s.size()) {
                while (end < s.size() && s[end] != '-') {
                    end++;
                }
                sscanf_s(s.substr(start, end - start).c_str(), "%d,%d", &x, &y);
                start = end + 2;
                end = start + 1;
                scan.push_back({x, y});
            }

            scans.push_back(scan);
        }
    }
}