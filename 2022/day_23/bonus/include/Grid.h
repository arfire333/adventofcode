#include <algorithm>
#include <map>
#include <raylib.h>
#include <string>
#include <vector>

class Grid {
    std::map<std::pair<int, int>, std::vector<int>> proposed_positions;
    int64_t tick = 0;
    std::vector<std::pair<int, int>> elves;
    std::map<std::pair<int, int>, int> pos2elf;
    int no_move_count = 0;
    int minx, maxx, miny, maxy;
    Texture2D elftext;
    int scale = 1;

  public:
    void init(std::vector<std::pair<int, int>> elves,
              std::map<std::pair<int, int>, int> pos2elf);
    void setElfText(const Image &elfImage) {
        elftext = LoadTextureFromImage(elfImage);
    }
    void setScale(int scale){ this->scale = scale; };
    void update();
    void draw();
    Vector3 getCenter() {
        int z = 5* std::max(maxx-minx, maxy-miny);
        return Vector3(scale * (maxy + miny) / 2, scale * (maxx + minx) / 2,z);
    }
};