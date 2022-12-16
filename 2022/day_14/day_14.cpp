#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

enum TYPE { AIR, GROUND, SAND };
map<int,char> t2c={{AIR,' '},{GROUND,'#'},{SAND,'O'}};
int X_SHIFT=0;

void print_grid(const vector<vector<int>> &grid){
  for( auto r : grid){
    for( auto c : r ){
      cout << t2c[c];
    }
    cout << "\n";
  }
}

int problem_a(vector<vector<int>> grid, int minx, int maxx){
  int Y=grid.size();
  int X=grid[0].size();
  int starty=0;
  int startx=500+X_SHIFT;
  int count=0;
  int lastx=startx;
  int lasty=starty;
  while( lastx >minx && lastx < maxx ){
    int x=startx;
    int y=starty;
    bool dropped=true;
    while( dropped && x > minx && x < maxx ){
      if( grid[y+1][x] == AIR ){
        y=y+1;
      }else if( grid[y+1][x-1] == AIR ){
        y++;
        x--;
      }else if( grid[y+1][x+1] == AIR ){
        y++;
        x++;
      }else{
        grid[y][x]=SAND;
        count++;
        dropped=false;
      }
      lastx=x;
      lasty=y;
    }
  }
  print_grid(grid);
  return count;
}

int problem_b(vector<vector<int>> grid, int minx, int maxx){
  int Y=grid.size();
  int X=grid[0].size();
  int starty=0;
  int startx=500+X_SHIFT;
  int count=0;
  int lastx=0;
  int lasty=1;
  while( lasty != starty ){
    int x=startx;
    int y=starty;
    bool dropped=true;
    while( dropped ){
      if( grid[y+1][x] == AIR ){
        y=y+1;
      }else if( grid[y+1][x-1] == AIR ){
        y++;
        x--;
      }else if( grid[y+1][x+1] == AIR ){
        y++;
        x++;
      }else{
        grid[y][x]=SAND;
        count++;
        dropped=false;
      }
      lastx=x;
      lasty=y;
    }
  }
  print_grid(grid);
  return count;
}

int main(int argc, char** argv){
  vector<vector<pair<int,int>>> scans;
  // vector<vector<int>> map;
  // Get data
  string s;
  int minx=INT_MAX;
  int miny=INT_MAX;
  int maxx=INT_MIN;
  int maxy=INT_MIN;
  while( getline(cin, s)){
    int x=0;
    int y=0;
    int start=0;
    int end=0;
    vector<pair<int,int>> scan;
    
    while (start <s.size()){
      while(end < s.size() && s[end]!='-' ){
        end++;
      }
      sscanf(s.substr(start,end-start).c_str(),"%d,%d",&x,&y);
      maxx=max(maxx,x);
      maxy=max(maxy,y);
      minx=min(minx,x);
      miny=min(miny,y);
      start=end+2;
      end=start+1;
      scan.push_back({x,y});
    }

    scans.push_back(scan);
  }
  cout << minx << "," << miny << " " << maxx <<"," << maxy <<"\n";
  int Y=maxy+3;
  int X=Y+(maxx-minx+1)+Y;
  
  X_SHIFT=Y-minx;
  vector<vector<int>> grid(Y,vector<int>(X,AIR));

  for(int x=0; x<X; x++){
    grid[maxy+2][x]=GROUND;
  }
  for(auto scan : scans ){
    for( auto i=1; i<scan.size(); i++){
      int startx=scan[i-1].first;
      int starty=scan[i-1].second;
      int endx=scan[i].first;
      int endy=scan[i].second;
      if( startx == endx ){
        if( starty<endy ){
          for(int y=starty; y<=endy; y++){
            grid[y][startx+X_SHIFT]=GROUND;
          }
        }else{
          for(int y=endy; y<=starty; y++){
            grid[y][startx+X_SHIFT]=GROUND;
          }
        }
      }else{
        if( startx < endx ){
          for(int x=startx; x<=endx; x++){
             grid[starty][x+X_SHIFT]=GROUND;
          }
        }else{
          for(int x=endx; x<=startx; x++){
            grid[starty][x+X_SHIFT]=GROUND;
          }
        }
      }
    }
  }
  int ans1=problem_a(grid,minx+X_SHIFT, maxx+X_SHIFT);
  int ans2=problem_b(grid,minx+X_SHIFT, maxx+X_SHIFT);
  cout <<"\n";
  cout << "Part 1: " << ans1 << "\n";
  cout << "Part 2: " << ans2 << "\n";
}