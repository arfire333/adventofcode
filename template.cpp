#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

int problem_a(const vector<vector<int>> in){

  return in.size();
}

int problem_b(const vector<vector<int>> in){

  return in.size();
}

int main(int argc, char** argv){
  vector<vector<int>> data;
  // Get data
  int i=0;
  int j=0;
  while( cin >> i >> j ){
    data.push_back({i,j});
  }

  cout << "Part 1: " << problem_a(data) << "\n";
  cout << "Part 2: " << problem_b(data) << "\n";
}
