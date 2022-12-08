#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

int problem_a(const vector<vector<int>> in){
  
  int R=in.size();
  int C=in[0].size();
  vector<vector<int>> vis(R,vector<int>(C,0));
  
  for(int r=0; r<R; r++ ){
    int maxtree=in[r][0];
    vis[r][0]=1;
    for(int c=1; c<C; c++){
      if(in[r][c] > maxtree){
        maxtree=in[r][c];
        vis[r][c]=1;
      }
    }
    maxtree=in[r][C-1];
    vis[r][C-1]=1;
    for(int c=C-2; c>=0; c--){
      if(in[r][c] > maxtree){
        maxtree=in[r][c];
        vis[r][c]=1;
      }
    }
  }
  for(int c=0; c<C; c++ ){
    int maxtree=in[0][c];
    vis[0][c]=1;
    for(int r=1; r<R; r++){
      if(in[r][c] > maxtree){
        maxtree=in[r][c];
        vis[r][c]=1;
      }
    }
    maxtree=in[R-1][c];
    vis[R-1][c]=1;
    for(int r=R-2; r>=0; r--){
      if(in[r][c] > maxtree){
        maxtree=in[r][c];
        vis[r][c]=1;
      }
    }
  }
  int sum=0;

  for(auto v : vis ){
    for( auto n : v ){
      cout << n << " ";
      sum+=n;
    }    
    cout << "\n";
  }
  return sum;
}

int problem_b(const vector<vector<int>> in){
  int R=in.size();
  int C=in[0].size();
  vector<vector<int>> vis(R,vector<int>(C,0));
  
  for(int r=1; r<R-1; r++ ){
    for(int c=1; c<C-1; c++){      
      vis[r][c]=1;
      int tmp=1;
      while( c+tmp<C-1 && in[r][c]>in[r][c+tmp]){        
        tmp++;
      }      
      vis[r][c]*=tmp;
      tmp=1;      
      while( c-tmp>0 && in[r][c]>in[r][c-tmp]){
        tmp++;
      }            
      vis[r][c]*=tmp;
      tmp=1;      
      while( r+tmp<R-1 && in[r][c]>in[r+tmp][c]){
        tmp++;        
      }      
      vis[r][c]*=tmp;
      tmp=1;      
      while( r-tmp>0 && in[r][c]>in[r-tmp][c]){
        tmp++;        
      }            
      vis[r][c]*=tmp;      
    }
  }
  int sum=0;
  for(auto v : vis ){
    for( auto n : v ){
      cout << n << " ";
      if( n > sum ){
        sum=n;
      }
    }    
    cout << "\n";
  }
  return sum;
}

int main(int argc, char** argv){
  vector<vector<int>> data;
  // Get data
  string s;
  while( getline(cin,s )){
    data.push_back(vector<int>(0));
    for( auto c : s ){
      int v = c-'0';
      if( v>=0 && v<=9 ){
        data.back().push_back(v);
      }
    }
  }

  cout << "Part 1:\n" << problem_a(data) << "\n";
  cout << "Part 2:\n " << problem_b(data) << "\n";
}