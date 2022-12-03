#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int depth_increases(const vector<int> soundings){
  int count=0;
  
  for( int i=1; i<soundings.size(); i++){
    if(soundings[i]>soundings[i-1]){
      count++;
    }
  }
  return count;
}
int avg_depth_increases(const vector<int> soundings){
  int count=0;
  int last=soundings[0]+soundings[1]+soundings[2];  
  for( int i=2; i+1<soundings.size(); i++){    
    int curr=soundings[i-1]+soundings[i]+soundings[i+1];
    if(curr > last){
      count++;
    }
    last=curr;
  }
  return count;
}


int main(int argc, char** argv){

  vector<int> soundings;

  int i=0;

  while( cin >> i ){
    soundings.push_back(i);
  }

  cout << "Part 1: " << depth_increases(soundings) << "\n";
  cout << "Part 2: " << avg_depth_increases(soundings) << "\n";
}