
#include "Adder.h"
#include "Data.h"
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

map<char, int64_t> c2i = {{'2', 2}, {'1', 1}, {'0', 0}, {'-', -1}, {'=', -2}};

int64_t snafu2decimal(string in) {
    int64_t val = 0;
    int place = 0;
    for (int i = static_cast<int>(in.size()) - 1; i >= 0; i--) {
        int64_t digit_val = static_cast<int64_t>(std::powl(5, place));
        char c = in[i];
        val = val + digit_val * c2i[c];
        place++;
    }
    return val;
}

void validate_adder() {
    string digits = "=-012";
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            for (int k = -2; k <= 2; k++) {
                int ans = i + j + k;
                string addsans =
                    adder[{digits[i + 2], digits[j + 2]}][digits[k + 2]];
                int64_t addans = snafu2decimal(addsans);
                assert(ans == addans);
            }
        }
    }
}
string add(string a, string b) {
    stringstream ss;
    if (a.size() > b.size()) {
        swap(a, b);
    }
    if (a.size() < b.size()) {
        for (int i = 0; i < b.size() - a.size(); i++) {
            ss << '0';
        }
        ss << a;
        a = ss.str();
        ss.str("");
    }
    char d1;
    char d2;
    char c = '0';
    stack<char> sumdigits;
    for (int i = static_cast<int>(a.size()) - 1; i >= 0; i--) {
        d1 = a[i];
        d2 = b[i];
        string cs = adder[{d1, d2}][c];
        sumdigits.push(cs[1]);
        c = cs[0];
    }
    bool waitingForFirstNonZero=true;
    if( c !='0' ){
        waitingForFirstNonZero=false;
        ss << c;
    }
    while (sumdigits.size() > 0) {
        char d=sumdigits.top();
        sumdigits.pop();
        if( d=='0' && waitingForFirstNonZero ){
            continue;
        }
        waitingForFirstNonZero=false;
        ss << d;        
    }

    return ss.str();
}

int main(int argc, char **argv) {
    validate_adder();

    int64_t sum = 0;
    string ssum = "0";
    for (auto s : MINE_IN) {
        int64_t sval = snafu2decimal(s);
        sum += snafu2decimal(s);
        ssum = add(s, ssum);
    }
    cout << "Decimal sum=" << sum << "\n";
    cout << "Snafu sum=" << ssum << "\n";
    cout << "Snafu converted to decimal sum=" << snafu2decimal(ssum) << "\n";
    return 0;
}
