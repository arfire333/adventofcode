#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
// not 945240480
// not 3162302936738425475 (even though it works ;)
// not 3162302936738425476 (even though it works ;)
// not 3162302936738425477 (now i'm confused. :(
/* 
 * Thanks to https://www.twitch.tv/qiqi_impact providing a means
 * to check partb.  
 * 
 * There may be a bug in this or the answer assumes a particular 
 * solution.  Comments on identifying the bug, if any, are welcome.
 */

vector<string> split(const string &str);
struct Node {
    string left;
    string right;
    char op = ' ';
    bool valset = false;
    int64_t val;
};

int64_t dfs(map<string, Node> &monkeys, string next) {
    auto curr = monkeys[next];
    if (curr.valset) {
        return curr.val;
    }

    int64_t left = 0;
    int64_t right = 0;
    if (!monkeys[curr.left].valset) {
        dfs(monkeys, curr.left);
    }
    if (!monkeys[curr.right].valset) {
        dfs(monkeys, curr.right);
    }
    left = monkeys[curr.left].val;
    right = monkeys[curr.right].val;
    monkeys[next].valset = true;

    switch (curr.op) {
    case '+':
        monkeys[next].val = left + right;
        // cout << next << " yells " << monkeys[next].val << "\n";
        return monkeys[next].val;
    case '-':
        monkeys[next].val = left - right;
        // cout << next << " yells " << monkeys[next].val << "\n";
        return monkeys[next].val;
    case '*':
        monkeys[next].val = left * right;
        // cout << next << " yells " << monkeys[next].val << "\n";
        return monkeys[next].val;
    case '/':
        monkeys[next].val = left / right;
        // cout << next << " yells " << monkeys[next].val << "\n";
        return monkeys[next].val;
    default:
        break;
    }
    assert(false);
    return 0;
}

int64_t problem_a(map<string, Node> monkeys) {
    cout << "root: " << dfs(monkeys, "root") << "\n";
    return monkeys["root"].val;
}

int bcheck(map<string, Node> monkeys, int64_t &diff) {
    dfs(monkeys, "root");
    auto left = monkeys["root"].left;
    auto right = monkeys["root"].right;
    cout << monkeys[left].val << " =?= " << monkeys[right].val << " ";
    diff=monkeys[right].val - monkeys[left].val;
    if (monkeys[left].val < monkeys[right].val) {
        return -1;
    } else if (monkeys[left].val > monkeys[right].val) {
        return 1;
    }
    return 0;
}

int64_t problem_b(map<string, Node> monkeys) {
    int64_t maxval = INT64_MAX>>4;
    int check = -1;
    int64_t minval = 0;
    int64_t diff1=0;
    int64_t diff2=0;
    cout << "\n";
    monkeys["humn"].val=0;
    bcheck(monkeys,diff1);    
    monkeys["humn"].val=100;
    bcheck(monkeys,diff2);
    int check_multiplier=1;
    if( diff1 < diff2 ){
      check_multiplier = -1;
    }


    cout << "MAX: " << maxval << "\n";    
    while (check != 0) {        
        // monkeys["humn"].val = val;
        cout << "Trying " << monkeys["humn"].val << " : ";
        check = bcheck(monkeys,diff1);
        check =check * check_multiplier;
        if (check > 0) {
            cout << " > \n";
            maxval = monkeys["humn"].val-1 ;
        } else if (check < 0) {
            cout << " < \n";
            minval = monkeys["humn"].val+1 ;
        } else {
            cout << "hit\n";
            break;
        }
        monkeys["humn"].val = (maxval + minval) >> 1LL;        
    }
    int64_t save=monkeys["humn"].val;
    for( int64_t i=save-5LL; i<=save+5LL; i++ ){        
      monkeys["humn"].val = i;
      check = bcheck(monkeys, diff1);
      if( check == 0 ){
        cout << i << " works!\n";
        break;
      }else{
        cout << i << " does not!\n";
      }
    }
    return monkeys["humn"].val;
}

int main(int argc, char **argv) {

    map<string, Node> monkeys;
    string s;
    map<string, int> name_count;
    while (getline(cin, s)) {
        string key = s.substr(0, 4);
        if (name_count.find(key) == name_count.end()) {
            name_count[key] = 1;
        } else {
            name_count[key]++;
        }

        Node val;
        auto ss = split(s);
        if (ss.size() > 2) {
            val.left = ss[1];
            val.right = ss[3];
            val.op = ss[2][0];
            if (name_count.find(val.left) == name_count.end()) {
                name_count[val.left] = 1;
            } else {
                name_count[val.left]++;
            }
            if (name_count.find(val.right) == name_count.end()) {
                name_count[val.right] = 1;
            } else {
                name_count[val.right]++;
            }
        } else {
            val.val = stoi(ss[1]);
            val.valset = true;
        }
        monkeys[key] = val;
    }
    for (auto n : name_count) {
        if (n.second > 2)
            cout << n.first << " count " << n.second << "\n";
    }
    int64_t ans1 = problem_a(monkeys);
    int64_t ans2 = problem_b(monkeys);

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
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