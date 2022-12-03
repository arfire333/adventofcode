#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int problem_a(const vector<vector<int>> in){
  int max_sum=0;
  for(auto v : in ){
    int sum=0;
    for(auto calories : v ){
      sum+=calories;
    }
    if( sum > max_sum ){
      max_sum=sum;
    }
  }
  return max_sum;
}

int problem_b(const vector<vector<int>> in){
  int N=in.size();
  vector<int> sum(N,0);
  for(auto i=0; i<N; i++ ){      
    for(auto calories : in[i] ){
      sum[i]+=calories;
    }        
  }
  sort(sum.begin(), sum.end());

  return sum[N-1]+sum[N-2]+sum[N-3];
}

int main(int argc, char** argv){
  vector<vector<int>> data;
  // Get data
  int i=0;
  string s;
  data.push_back(vector<int>());
  while( getline(cin, s)){
    if( s.size() == 0){
      data.push_back(vector<int>(0,0));      
    }else{
      data.back().push_back(atoi(s.c_str()));
    }    
  }

  cout << "Part 1: " << problem_a(data) << "\n";
  cout << "Part 2: " << problem_b(data) << "\n";
}