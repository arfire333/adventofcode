#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

bool contained( vector<int> l, vector<int> r){  
  if( l[0] <= r[0] && l[1] >=r[1] ){    
    return true;
  }else
  if( r[0] <= l[0] && r[1] >=l[1] ){
    return true;
  }
  return false;
}

bool overlap(vector<int>l, vector<int> r){
  if( l[0] <= r[1] && l[1] >=r[0] ){        
    return true;
  }else  if( r[0] <= l[1] && r[1] >=l[0] ){    
    return true;
  }
  return false;
}

int problem_a(const vector<vector<int>> in){
  int count=0;
  for(int  i=0; i< in.size(); i+=2){
    count += (contained(in[i],in[i+1])? 1: 0 ) ;
  }
  return count;
}

int problem_b(const vector<vector<int>> in){
  int count=0;
  for(int  i=0; i< in.size(); i+=2){
    count += (overlap(in[i],in[i+1])? 1: 0 ) ;
  }
  return count;  
}

int main(int argc, char** argv){
  vector<vector<int>> data;
  // Get data 
  string s;
  int i,j,k,l=0;
  while( cin >> s ){
    sscanf( s.c_str(),"%d-%d,%d-%d",&i,&j,&k,&l );
    cout << i << " " << j << " " << k << " " << l << "\n";
    data.push_back({i,j});
    data.push_back({k,l});
  }

  cout << "Part 1: " << problem_a(data) << "\n";
  cout << "Part 2: " << problem_b(data) << "\n";
}