#include <algorithm>
#include <raylib.h>
#include <vector>

struct Sand {
    static const int STARTING_X = 500;
    static const int STARTING_Y = 0;    
    static int64_t last_id;

    int64_t id = 0;
    int x = STARTING_X;
    int y = STARTING_Y;
    Color color = GREEN;
    Sand() {
        id = last_id + 1;
        last_id = id;
        int r = rand() % 3;
        if (r == 0) {
            color = RED;
        } else if (r == 1) {
            color = GREEN;
        } else {
            color = BLUE;
        }
    };
};
class Grid {
    enum TYPE { AIR, GROUND, SAND };
    
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<std::pair<int, int>>> scans;
    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;
    int X_SHIFT = 0;
    int SCALE=1;
    std::vector<Sand> dropping;
    std::vector<Sand> stopped;

  public:
    void init(const std::vector<std::vector<std::pair<int, int>>> &scans, int scale);

    void update();

    void draw();

    std::pair<int, int> size();
};