#include "Data.h"
#include "Elf.h"
#include "Grid.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
void get_data(const string fn, Grid &g);
void get_data_from_vector(const vector<string> &in, Grid &g);
int main(int argc, char **argv) {
    Grid g;

    if (argc > 1) {
        get_data(argv[1], g);
    } else {
        get_data_from_vector(MINE_IN, g);
    }
    int rows = 200;
    int cols = 150;
    int SCALE = 6;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1024, 1024, argv[0]);
    Image elfimage = LoadImageFromMemory(".png", ELF_DATA, ELF_SIZE);
    g.setElfText(elfimage);
    SetExitKey(0);
    SetTargetFPS(30);
    Camera3D camera = {0};
    camera.position = Vector3(00.0f, 00.0f, 400.0f); // Camera position
    camera.target = Vector3(0.0f, 0.0f, 0.0f);       // Camera looking at point
    camera.up =
        Vector3(0.0f, 1.0f, 0.0f); // Camera up vector (rotation towards target)
    camera.fovy = 80.0f;           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    CameraMode(CAMERA_FREE);
    stringstream ss;
    Vector3 c = {25.0f * SCALE, 25.0f * SCALE, 25.0f * SCALE};
    g.setScale(elfimage.width / 2);
    while (!WindowShouldClose()) {
        auto time = GetTime();
        auto scale = (2.0f + sin(time)) * 0.7f;

        g.update();
        camera.position = g.getCenter();
        camera.target = camera.position;
        camera.target.z = 0;

        BeginDrawing();
        ClearBackground(BLACK);
        ss.str("");
       
        DrawText(ss.str().c_str(), 20, 20, 24, WHITE);
        BeginMode3D(camera);
        g.draw();
        EndMode3D();
        EndDrawing();
    }

    CloseWindow();    
    return 0;
}

void get_data(const string fn, Grid &grid) {
    ifstream fs(fn);
    vector<string> data;
    if (fs.is_open()) {
        string s;
        
        while (getline(fs, s)) {
            data.push_back(s);            
        }
    }
    fs.close();
    get_data_from_vector(data,grid);
}

void get_data_from_vector(const vector<string> &in, Grid &g) {
    vector<pair<int, int>> elves;
    map<pair<int, int>, int> pos2elf;
    int r = 0;
    for (auto s : in) {
        for (int c = 0; c < s.size(); c++) {
            if (s[c] == '#') {
                elves.push_back({r, c});
                pos2elf[elves.back()] = r;
            }
        }
        r++;
    }
    g.init(elves, pos2elf);
}