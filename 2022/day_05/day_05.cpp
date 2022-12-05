#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <sstream>

using namespace std;

string problem_a(vector<vector<int>> commands, vector<stack<char>> stack){
  for(auto c : commands ){
    int count=c[0];
    cout << "move " << c[0] << " from " << c[1] << " " << c[2] << "\n"; 
    cout << stack[c[1]].size() << " " << stack[c[2]].size() << "\n";
    while( count>0 ){      
      stack[c[2]].push(stack[c[1]].top());
      stack[c[1]].pop();
      count--;      
    }
    cout << stack[c[1]].size() << " " << stack[c[2]].size() << "\n";
  }
  stringstream ss;
  for( auto s : stack ){
    ss << s.top();
  }
  return ss.str();
}

string problem_b(vector<vector<int>> commands, vector<stack<char>> mystack){
  
  for(auto c : commands ){
    int count=c[0];
    cout << "move " << c[0] << " from " << c[1] << " " << c[2] << "\n"; 
    cout << mystack[c[1]].size() << " " << mystack[c[2]].size() << "\n";
    stack<char> tmpstack;  
    while( count>0 ){      
      tmpstack.push(mystack[c[1]].top());
      mystack[c[1]].pop();
      count--;      
    }
    count = c[0];
    while( count>0 ){      
      mystack[c[2]].push(tmpstack.top());
      tmpstack.pop();
      count--;      
    }
    cout << mystack[c[1]].size() << " " << mystack[c[2]].size() << "\n";
  }
  stringstream ss;
  for( auto s : mystack ){
    ss << s.top();
  }
  return ss.str();
  return 0;
}

int main(int argc, char** argv){
  vector<vector<int>> commands;
  
  // Get commands
  int i=0;
  int R=0;
  int C=0;
  char line[1000];
  
  gets(line);
  sscanf(line, "%d %d", &R, &C );
  
  cout << R << ", " << C << "\n";
  vector<stack<char>> tmpstack(C);
  vector<stack<char>> stacks(C);
  for(int r=0; r<R; r++){
    gets(line);
    for(int c=0; c<C; c++){      
      if( line[c*4+1] != ' ' ){
        tmpstack[c].push(line[c*4+1]);
      }      
    }    
  }
  for(int c=0; c<C; c++){
    while( tmpstack[c].size() > 0 ){
      stacks[c].push(tmpstack[c].top());
      tmpstack[c].pop();
    }    
  }

  int val, from, to;
  gets(line);
  gets(line);
  while( gets(line) ){        
    sscanf(line,"move %d from %d to %d",&val, &from, &to); 
    cout << val << " " << from << " " << to << "\n";
    commands.push_back({val,from-1,to-1});
  }

  cout << "Part 1: " << problem_a(commands,stacks) << "\n";
  cout << "Part 2: " << problem_b(commands,stacks) << "\n";
}