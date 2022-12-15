#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>
#include <numeric>
using namespace std;

/* Thanks to https://www.twitch.tv/qiqi_impact for helping get past a hurdle
 * on the part a.  
 */
int node_count = 0;
struct list {
    vector<list *> lists;
    int val;
    bool islist = false;
    list() : val(110), islist(true){};
    list(int val) : val(val), islist(false){};
    void populate(string s, int &si) {
        si++;
        stringstream ss;
        while (si < s.size()) {
            if (s[si] == ']') {
                if (ss.str().size() > 0) {
                    lists.push_back(new list(std::stoi(ss.str())));
                    ss.str("");
                }
                return;
            } else if (s[si] == '[') {
                lists.push_back(new list());
                lists.back()->populate(s, si);
            } else if (s[si] == ',') {
                if (ss.str().size() > 0) {                    
                    lists.push_back(new list(std::stoi(ss.str())));
                    ss.str("");
                }
            } else {
                ss << s[si];
            }
            si++;
        }
    }

    void print(int level = 0) {
        stringstream ss;
        for (int i = 0; i < level * 2; i++) {
            ss << " ";
        }
        for (int i = 0; i < lists.size(); i++) {
            auto n = lists[i];
            if (n->islist) {
                cout << ss.str() << "x\n";
                n->print(level + 1);
            } else {
                cout << ss.str() << n->val << "\n";
            }
        }
    }
};
int compare(list *l, list *r) {
    int lsize = l->lists.size();
    int rsize = r->lists.size();
    int retVal = 0;

    for (int i = 0; i < lsize; i++) {
        if (i >= rsize) {
            return 1;
        }
        auto llist=l->lists[i];
        auto rlist=r->lists[i];

        if (!llist->islist && !rlist->islist) {
            if (llist->val - rlist->val) {
                return llist->val - rlist->val;
            }
        } else if (!llist->islist && rlist->islist) {
            list *tmp = new list();
            tmp->lists.push_back(llist);
            auto result = compare(tmp, rlist);
            delete tmp;
            if (result != 0) {
                return result;
            }
        } else if (llist->islist && !rlist->islist) {
            list *tmp = new list();
            tmp->lists.push_back(rlist);
            auto result = compare(llist, tmp);
            delete tmp;
            if (result != 0) {
                return result;
            }
        } else {
            retVal = compare(llist, rlist);
            if (retVal != 0) {
                return retVal;
            }
        }
    }

    if (retVal == 0) {
        if (lsize < rsize) {
            return -1;
        } else if (lsize > rsize) {
            return 1;
        }
    }
    return retVal;
}

int problem_a(vector<pair<string, string>> packets) {
    int sum = 0;

    vector<int> valids;
    for (auto i = 0; i < packets.size(); i++) {
        auto p = packets[i];
        list n1, n2;        
        int start = 0;
        n1.populate(p.first, start);               
        start = 0;
        n2.populate(p.second, start);                
        auto result = compare(&n1, &n2);

        if (result < 0) {
            valids.push_back(i + 1);
            sum += (i + 1);
        }
        cout << "Index: " << i + 1 << " : " << (result < 0 ? "GOOD" : "bad")
             << "\n\t" << p.first << "\n\t" << p.second << "\n";
    }

    return sum;
}

int problem_b(vector<pair<string, string>> packets) { 
    vector<list> l;
    int start=0;
    for(auto p : packets ){
        start=0;
        l.push_back(list());        
        l.back().populate(p.first,start);
        start=0;
        l.push_back(list());        
        l.back().populate(p.second,start);
    }
    start=0;
    l.push_back(list());
    l.back().populate("[[2]]",start);
    start=0;
    l.push_back(list());
    l.back().populate("[[6]]",start);
    vector<int> idx(l.size(),0);
    iota(idx.begin(),idx.end(),0);
    for(int i=0; i<l.size(); i++){
        for(int j=i; j < l.size(); j++){
            if( compare(&l[i],&l[j]) > 0 ){
                swap(l[i],l[j]);
                swap(idx[i],idx[j]);
            }
        }
    }
    int product=1;
    for(int i=0; i<idx.size(); i++){        
        if( idx[i] == packets.size()*2 || idx[i]== packets.size()*2+1 ){            
            product*=(i+1);
        }
    }

    return product; 
    
}

int main(int argc, char **argv) {
    vector<int> data;
    // Get data
    vector<pair<string, string>> packets;
    string one;
    string two;
    while (getline(cin, one)) {
        getline(cin, two);
        packets.push_back({one, two});
        getline(cin, one);
    }

    int64_t ans1 = problem_a(packets);
    int64_t ans2 = problem_b(packets);
    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
}
