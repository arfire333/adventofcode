#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;
map<char,int> priorities;

void build_priorities(){
  int i=1;
  for(auto l='a'; l<='z'; l++){
    priorities[l]=i++;
  }
  for(auto l='A'; l<='Z'; l++){
    priorities[l]=i++;
  }
}

int problem_a(const vector<string> in){
  int sum=0;
  set<char> first_sack;
  for( auto word : in ){
    first_sack.clear();
    int i=0;
    for(; i<word.size()/2; i++){
      first_sack.insert(word[i]);
      
    }
    for(;i<word.size(); i++){
      if( first_sack.find(word[i]) != first_sack.end() ){
        cout << priorities[word[i]] << word[i] << "\n";
        sum+=priorities[word[i]];
        first_sack.erase(word[i]);
      }
    }
  }
  
  return sum;
}

int problem_b(const vector<string> in){
  int sum=0;
  int i=0;
  for( int i=0; i< in.size() ;i+=3){
    vector<vector<int>> freq('z'+1,vector<int>(3,0));
    for( int j=0; j<3; j++){
      for( auto l : in[i+j] ){
        freq[l][j]=1;
      }      
    } 

    for( int j=0; j<freq.size(); j++){
      auto v=freq[j];
      if( v[0]+v[1]+v[2] == 3 ){
        sum+=priorities[j];
      }          
    }
    
    if( i%3==0 && i!=0 ){
    }
   
  }
  return sum;
}

int main(int argc, char** argv){
  vector<string> data;
  // Get data
  string i;
  while( cin >> i ){
    data.push_back(i);
  }

  build_priorities();
  cout << "Part 1: " << problem_a(data) << "\n";
  cout << "Part 2: " << problem_b(data) << "\n";
}