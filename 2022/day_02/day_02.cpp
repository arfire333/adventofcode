#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

const int ROCK=1;//A  X
const int PAPER=2;//C  Z
const int SCISSORS=3;//B Y

map<char,int> op={{'A',1},{'B',2},{'C',3}};
map<char,int> me={{'X',1},{'Y',2},{'Z',3}};

const int WIN=6;
const int DRAW=3;
const int LOSS=0;
int alt_problem_a(const vector<vector<char>> in){
  int score=0;
  for( auto g : in ){
      int m=me[g[1]];
      int o=op[g[0]];
      if( o==m )score+=o+3;
      else if( o%3+1 == m ) score+=m+6;
      else score+=m;    
  }
  return score;
}

int problem_a(const vector<vector<char>> in){
  int score=0;
  for( auto g : in ){
    char a=g[1];
    // cout << g[0] << " " << a << " = ";
    switch( g[0] ){
      case 'A': // ROCK     X
        if( a=='X' ) score+=ROCK+DRAW;
        if( a=='Y' ) score+=PAPER+WIN;
        if( a=='Z' ) score+=SCISSORS+LOSS;
        break;
      case 'B': // PAPER
        if( a=='X' ) score+=ROCK+LOSS;
        if( a=='Y' ) score+=PAPER+DRAW;
        if( a=='Z' ) score+=SCISSORS+WIN;
        break;
      case 'C': // SCISSORS
        if( a=='X' ) score+=ROCK+WIN;
        if( a=='Y' ) score+=PAPER+LOSS;
        if( a=='Z' ) score+=SCISSORS+DRAW;
        break;
      default:
      break;
    }
    // cout << score << "\n";
    
  }
  return score;
}

int problem_b(const vector<vector<char>> in){
  int score=0;
  for( auto g : in ){
    char a=g[1];
    // cout << g[0] << " " << a << " = ";
    switch( g[0] ){
      case 'A': // ROCK     X LOSE, Y DRAW, Z WIN
        if( a=='X' ) score+=SCISSORS+LOSS;
        if( a=='Y' ) score+=ROCK+DRAW;
        if( a=='Z' ) score+=PAPER+WIN;
        break;
      case 'B': // PAPER
        if( a=='X' ) score+=ROCK+LOSS;
        if( a=='Y' ) score+=PAPER+DRAW;
        if( a=='Z' ) score+=SCISSORS+WIN;
        break;
      case 'C': // SCISSORS
        if( a=='X' ) score+=PAPER+LOSS;
        if( a=='Y' ) score+=SCISSORS+DRAW;
        if( a=='Z' ) score+=ROCK+WIN;
        break;
      default:
      break;
    }
    // cout << score << "\n";
    
  }
  return score;  
}

int main(int argc, char** argv){
  vector<vector<char>> data;
  // Get data
  char i,j;
  
  while( cin >> i >> j ){
    data.push_back({i,j});
  }

  cout << "Part 1: " << problem_a(data) << "\n";
  cout << "AltPart 1: " << alt_problem_a(data) << "\n";
  cout << "Part 2: " << problem_b(data) << "\n";
}