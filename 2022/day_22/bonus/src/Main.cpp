#include "Grid.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
void get_data(const string fn, Grid &g);
int main(int argc, char **argv) {
    Grid g;

    if (argc > 1) {
        get_data(argv[1], g);
    } else {
        get_data("day_22.input", g);
    }
    int rows = 200;
    int cols = 150;
    int SCALE = 4;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(cols * SCALE, rows * SCALE, argv[0]);
    SetExitKey(0);
    // Move this later
    InitAudioDevice();
    SetTargetFPS(30);
    Camera3D camera = {0};
    camera.position = Vector3(400.0f, 400.0f, 400.0f); // Camera position
    camera.target = Vector3(0.0f, 0.0f, 0.0f);       // Camera looking at point
    camera.up =
        Vector3(0.0f, 1.0f, 0.0f); // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    CameraMode(CAMERA_FREE);
    stringstream ss;
    Vector3 c= { 25.0f*SCALE, 25.0f*SCALE, 25.0f*SCALE };
    
    while (!WindowShouldClose()) {
        auto time = GetTime();
        auto scale = (2.0f + sin(time)) * 0.7f;

        /* Move camera around the scene */
        // auto cameraTime = time*0.5 ;
        // camera.position.x = cos(cameraTime) * 400.0f;
        // camera.position.y = sin(cameraTime) * 400.0f;
        auto p = g.position();
        camera.target = g.position();
        // camera.position.x = static_cast<int>(time*1000) % 1400;
        camera.position.x = c.x +  4*(p.x-c.x);
        camera.position.y = c.y +  4*(p.y-c.y);
        camera.position.z = c.z +  4*(p.z-c.z);        

        //  camera.position = Vector3(400.0f, 400.0f, 400.0f); // Camera position
        switch (g.side()) {
        case 1:
            // camera.position = Vector3(400.0f, 400.0f, 400.0f); // Camera position
            camera.up=Vector3( 0.0f, 1.0f, 0.0f);
            break;
        case 2:
            // camera.position = Vector3(400.0f, 400.0f, 400.0f); // Camera position
            camera.up=Vector3( 0.0f, 1.0f, 0.0f);
            break;
        case 3:
            // camera.position = Vector3( p.x, p.y+1000, p.z);
            camera.up=Vector3( 0.0f, 1.0f, 0.0f);
            break;
        case 4:
            // camera.position = Vector3( p.x-400, p.y, p.z);
            camera.up=Vector3( 0.0f, 1.0f, 0.0f);
            break;
        case 5:
            // camera.position = Vector3( p.x, p.y, p.z-400);
            camera.up=Vector3( 0.0f, 1.0f, 0.0f);
            break;
        case 6:
            //  camera.position = Vector3(400.0f, 400.0f, 400.0f); // Camera position
            camera.up=Vector3( 0.0f, 1.0f, 0.0f);
            break;
        default:
        break;
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        ss.str("");
        //   ss << " side: " << g.side() << " x=" << p.x << ", y=" << p.y << ", z=" << p.z << "  cam.x=" << camera.position.x << "\n";
        DrawText(ss.str().c_str(),20,20,24,WHITE);
        g.step_cube();
        BeginMode3D(camera);        
        g.draw_cube(SCALE);
        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}

void get_data(const string fn, Grid &grid) {
    ifstream fs(fn);

    if (fs.is_open()) {
        string s;

        vector<string> g;
        bool more_grid = true;

        while (more_grid) {
            getline(fs, s);
            if (s.size() > 0) {
                g.push_back(s);
            } else {
                getline(fs, s);
                more_grid = false;
            }
        }
        grid.init(g, s);
    }
    fs.close();
}
