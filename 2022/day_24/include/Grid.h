#include <algorithm>
#include <raylib.h>
#include <string>
#include <vector>
#include <set>
class Grid {
    std::vector<std::string> grid;
    std::vector<std::pair<int,int>> walls;
    std::vector<std::vector<std::pair<char,std::pair<int,int>>>> blizzards;
    std::vector<std::set<std::pair<int,int>>> occupied_spaces;
    int width=0;
    int height=0;
    int scale = 1;
    std::pair<int,int> start;
    std::pair<int,int> curr;
    std::pair<int,int> dest;
    std::vector<std::pair<int,int>> path;   
    int min_path_length = 0; 
    Texture2D elf;
    
  public:
    void init(const std::vector<std::string> &in, int scale);
    void setElf(Texture2D elf);
    void update();
    void draw(int tick);
    Vector2 windowSize();
    int minPathLength(){ return min_path_length; }

  private:    
    int findPathBFS(std::pair<int,int> cstart, std::pair<int,int> cdest, int startt) ;
    void updateBlizzards(std::vector<std::pair<char,std::pair<int,int>>> &blizzards);
    int64_t spaceTimeId( std::pair<int,int>, int b_idx );
};