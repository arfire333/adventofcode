#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stdio.h>
#include <vector>
using namespace std;
string rtrim(const string &str);

pair<int, int> start;
pair<int, int> last;

int problem_a(vector<string> &in) {
    int R = in.size();
    int C = in[0].size();
    vector<vector<int>> visited(R, vector<int>(C, -1));

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (in[r][c] == 'S') {
                start = {r, c};                
                in[r][c] = 'a';
            }
            if (in[r][c] == 'E') {
                last = {r, c};
                in[r][c] = 'z';
            }
        }
    }
    queue<pair<int, int>> q;
    queue<int> depth;
    q.push(start);
    depth.push(0);
    
    visited[start.first][start.second] = 0;
    while (q.size() > 0) {
        auto curr = q.front();
        auto d = depth.front();
        q.pop();
        depth.pop();
        int r = curr.first;
        int c = curr.second;        

        if (r == last.first && c == last.second) {            
            return d;
        }

        if (r > 0 && in[r - 1][c] <= in[r][c] + 1 && visited[r - 1][c] < 0) {
            q.push({r - 1, c});
            depth.push(d + 1);
            visited[r - 1][c] = 0;
        }
        if (c > 0 && in[r][c - 1] <= in[r][c] + 1 && visited[r][c - 1] < 0) {
            q.push({r, c - 1});
            depth.push(d + 1);
            visited[r][c - 1] = 0;
        }
        if (r + 1 < R && in[r + 1][c] <= in[r][c] + 1 &&
            visited[r + 1][c] < 0) {
            q.push({r + 1, c});
            depth.push(d + 1);
            visited[r + 1][c] = 0;
        }
        if (c + 1 < C && in[r][c + 1] <= in[r][c] + 1 &&
            visited[r][c + 1] < 0) {
            visited[r][c + 1] = 0;
            depth.push(d + 1);
            q.push({r, c + 1});
        }
    }

    return 0;
}

int problem_b(const vector<string> in) {
    int R = in.size();
    int C = in[0].size();
    
    vector<pair<int,int>> starts;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (in[r][c] == 'a' ) {
              starts.push_back({r,c});                
            }           
        }
    }
    int minpath=INT_MAX;
    for(auto start : starts ){
        
      queue<pair<int, int>> q;
      queue<int> depth;
      q.push(start);
      depth.push(0);      
      vector<vector<int>> visited(R, vector<int>(C, -1));
      visited[start.first][start.second] = 0;
      while (q.size() > 0) {
          auto curr = q.front();
          auto d = depth.front();
          q.pop();
          depth.pop();
          int r = curr.first;
          int c = curr.second;        

          if (r == last.first && c == last.second) {              
              if( d < minpath ){
                minpath=d;
              }
              while(q.size() > 0 ) q.pop();
              continue;
          }

          if (r > 0 && in[r - 1][c] <= in[r][c] + 1 && visited[r - 1][c] < 0) {
              q.push({r - 1, c});
              depth.push(d + 1);
              visited[r - 1][c] = 0;
          }
          if (c > 0 && in[r][c - 1] <= in[r][c] + 1 && visited[r][c - 1] < 0) {
              q.push({r, c - 1});
              depth.push(d + 1);
              visited[r][c - 1] = 0;
          }
          if (r + 1 < R && in[r + 1][c] <= in[r][c] + 1 &&
              visited[r + 1][c] < 0) {
              q.push({r + 1, c});
              depth.push(d + 1);
              visited[r + 1][c] = 0;
          }
          if (c + 1 < C && in[r][c + 1] <= in[r][c] + 1 &&
              visited[r][c + 1] < 0) {
              visited[r][c + 1] = 0;
              depth.push(d + 1);
              q.push({r, c + 1});
          }
      }
    }
    return minpath;
}

int main(int argc, char **argv) {
    vector<string> data;
    // Get data
    string s;
    while (getline(cin, s)) {
        data.push_back(rtrim(s));
    }

    cout << "Part 1: " << problem_a(data) << "\n";
    cout << "Part 2: " << problem_b(data) << "\n";
}
string rtrim(const string &str) {
    string s(str);

    s.erase(find_if_not(s.rbegin(), s.rend(), [](char c) { return isspace(c); })
                .base(),
            s.end());

    return s;
}
