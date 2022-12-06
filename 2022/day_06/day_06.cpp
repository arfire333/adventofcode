#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>

/**
 * This was originally coded on godbolt.org.  I was away from my primary
 * computer at the time.  It was edited after completion to match the
 * format of the other programs and cleanup the output a bit.
 */
#include <iostream>
#include <set>
#include <string>
using namespace std;
int find_start(const string b, int length){
  int i = 0;
    set<char> s;
    int lastsize = 0;
    int count = 0;
    for (i = 0; i < b.size(); i++) {
        s.insert(b[i]);        
        if (s.size() == lastsize) {
            s.clear();
            lastsize = 0;
            i = i - count;
            count = 0;
        } else {
            lastsize = s.size();
            count++;
        }
        if (s.size() >= length) {
            break;
        }
    }
    return i+1;
}
int problem_a(const string b) {
  return find_start(b,4);
}
int problem_b(const string b) {
  return find_start(b,14);
}

int main(int argc, char **argv) {
    string a;
    while (getline(cin, a)) {
        cout << "Text: " << a << "\n";
        cout << "start-of-packet=" << problem_a(a) << "\n";
        cout << "start-of-message=" << problem_b(a) << "\n";
    }    
    return 0;
}
/******************************************************************
 * Below here was not used
 ******************************************************************/

string ltrim(const string &str) {
    string s(str);

    s.erase(s.begin(),
            find_if_not(s.begin(), s.end(), [](char c) { return isspace(c); }));

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(find_if_not(s.rbegin(), s.rend(), [](char c) { return isspace(c); })
                .base(),
            s.end());

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
