#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

int problem_a(const vector<int> in){

  return 0;
}

int problem_b(const vector<int> in){

  return 0;
}

int main(int argc, char** argv){
  vector<int> data;
  // Get data
  int i=0;
  while( cin >> i ){
    data.push_back(i);
  }

  cout << "Part 1: " << problem_a(data) << "\n";
  cout << "Part 2: " << problem_b(data) << "\n";
}