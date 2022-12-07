#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>

using namespace std;
vector<string> split(const string &str);

struct File {    
    string name;
    File *parent=nullptr;
    map<string, File *> files;
    bool isDirectory = false;
    int64_t size;
    File(string name, bool isDirectory = true, int64_t size = 0)
        : name(name), size(size), isDirectory(isDirectory){};
    static void print(File *root, int depth=0){
      if( root == nullptr ){
        return ;
      }
      for(int i=0; i<depth*2; i++){
        cout << " ";
      }
      cout << root->name << " " << root->size <<  "\n";
      for( auto [k,f] : root->files ){
        print( f, depth + 1);    
      }

    }
    static int64_t sumMax100k(File *root, int64_t &sum, priority_queue<pair<int64_t,string>> &q){
      if( root == nullptr ){
        return 0;
      }
      if( !root->isDirectory ){        
          return root->size;     
      }
      int64_t val=0;
      for( auto [k,f] : root->files ){        
        val+=sumMax100k(f,sum,q);
      }
      if( val <= 100000){                        
        sum+=val;
      }
      cout << root->name << " uses " << val << "\n";
      q.push({val,root->name});
      return val;
    }
};

int problem_a(File *root) { 
  int64_t sum=0;
   priority_queue<pair<int64_t,string>> q;
  int64_t top=File::sumMax100k(root,sum, q);
  if( top <=100000 ){
    sum+=top;
  }
  return sum; 
}

int problem_b(File *root) {  
  int64_t sum=0;
   priority_queue<pair<int64_t,string>> q;
  int64_t top=File::sumMax100k(root,sum, q);
  if( top <=100000 ){
    sum+=top;
  }
  int64_t last=top;
  string last_name="/";
  int64_t used_space=q.top().first;
  int64_t free_space=70000000-q.top().first;
  q.pop();
  while(free_space+q.top().first >= 30000000 ){
    last=q.top().first;
    last_name=q.top().second;
    q.pop();
  }
  
  cout << "Delete the " << last_name << " directory to save " << last << ".\n";
  return last; 
   
}


int main(int argc, char **argv) {
    File root("/");
    // Get data
    string s;
    string current_directory="/";
    File *curr=&root;
    curr->files.find("/");
    while (getline(cin, s)) {
        cout << s << "\n";
        auto tokens = split(s);
        if (tokens[0] == "$") {            
            if (tokens[1] == "cd") {
              if( tokens[2] == "/" ){
                //
              }else if ( tokens[2] == ".." ){
                curr=curr->parent;
              }else{
                 curr=curr->files[tokens[2]];
              }
              cout << "changed to " << tokens[2] << " directory\n";
            }             
        } else if (tokens[0] == "dir") {
          printf("%x : ", curr );
          cout << curr->name << " " << tokens[1] << "\n";
          
          if( curr->files.find(tokens[1]) == curr->files.end() ){
            curr->files[tokens[1]]=new File(tokens[1]);
            curr->files[tokens[1]]->parent = curr;;
          }
        } else {
          cout << tokens[1] << "\n";
          if( curr->files.find(tokens[1]) != curr->files.end() ){
            curr->files[tokens[1]]->size=stoi(tokens[0]);            
          }else{            
            curr->files[tokens[1]]=new File(tokens[1],false,stoi(tokens[0]));
            curr->files[tokens[1]]->parent=curr;
          }            
        }
    }
    // File::print(&root);

    cout << "Part 1: " << problem_a(&root) << "\n";
    cout << "Part 2: " << problem_b(&root) << "\n";
    return 0;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(' ', start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}