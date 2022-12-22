#include <algorithm>
#include <raylib.h>
#include <vector>
#include <string>

class Grid {
    std::vector<std::vector<char>> grid;
    std::pair<int, int> start;
    std::pair<int, int> current;
    Vector3 pos3d;
    int _side=0;
    std::vector<std::pair<int, char>> commands;
    char orientation;
    int current_command = 0;
    int current_command_progress = 0;
    int N = 0;

    void parseCommands(const std::string &s);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    bool move_left_cube();
    bool move_right_cube();
    bool move_up_cube();
    bool move_down_cube();
    void turn(char direction);
    bool new_c=false;
  public:
    enum Show {
        GRID = 0,
        START_POSITION = 1,
        CURRENT_POSITION = 2,
        BOTH_POSITIONS = 3
    };
    void print(const Show &show = GRID);
    void printCommands();
    void init(const std::vector<std::string> &in, const std::string &s);
    void step();
    void step_cube();
    void draw_cube(const int scale=4);
    bool isDone() { return current_command >= commands.size(); }
    int command() { return current_command; }
    int password();
    Vector3 position(){ return pos3d; }
    bool newCommand(){ return new_c; }
    int side() { return _side; }
};