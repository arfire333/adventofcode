#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
enum operation { NONE, ADD, MULT, MULTSELF };
struct Monkey {
    queue<int64_t> items;
    operation op;
    int64_t operand = 0;
    int64_t divis = 0;
    int trueMonkey = 0;
    int falseMonkey = 0;
    uint64_t inspects = 0;
};

vector<string> split(const string &str);

int problem_a(vector<Monkey> monkeys) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < monkeys.size(); j++) {
            Monkey &m = monkeys[j];
            int K = m.items.size();
            for (int k = 0; k < K; k++) {
                int current = m.items.front();
                m.items.pop();
                m.inspects++;
                switch (m.op) {
                case ADD:
                    current += m.operand;
                    break;
                case MULT:
                    current *= m.operand;
                    break;
                case MULTSELF:
                    current = current * current;
                    break;
                default:
                    break;
                }
                current = current / 3;
                if (current % m.divis == 0) {
                    monkeys[m.trueMonkey].items.push(current);
                } else {
                    monkeys[m.falseMonkey].items.push(current);
                }
            }
        }

        // cout << "Round " << i << "\n";
        // for (int j = 0; j < monkeys.size(); j++) {
        //     cout << "Monkey " << j << ": "
        //          << " ";
        //     auto tmp = monkeys[j].items;
        //     while (tmp.size() > 0) {
        //         cout << tmp.front() << ", ";
        //         tmp.pop();
        //     }
        //     cout << "\n";
        // }
        // cout << "---------------------\n";
    }
    vector<int> inspects;
    for (int i = 0; i < monkeys.size(); i++) {
        cout << i << " " << monkeys[i].inspects << "\n";
        inspects.push_back(monkeys[i].inspects);
    }
    sort(inspects.rbegin(), inspects.rend());

    return inspects[0] * inspects[1];
}

int64_t problem_b(vector<Monkey> monkeys) {
    int64_t M = 1;
    for (int i = 0; i < monkeys.size(); i++) {
        M = M * monkeys[i].divis;
    }
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < monkeys.size(); j++) {
            Monkey &m = monkeys[j];
            int K = m.items.size();
            for (int k = 0; k < K; k++) {
                int64_t current = m.items.front();
                m.items.pop();
                m.inspects++;
                switch (m.op) {
                case ADD:
                    current = ((current % M + m.operand % M)) % M;
                    break;
                case MULT:
                    current = ((current % M) * (m.operand % M)) % M;
                    break;
                case MULTSELF:
                    current = ((current % M) * (current % M)) % M;
                    break;
                default:
                    break;
                }

                if (current % m.divis == 0) {
                    monkeys[m.trueMonkey].items.push(current);
                } else {
                    monkeys[m.falseMonkey].items.push(current);
                }
            }
        }
    }
    vector<int64_t> inspects;
    for (int i = 0; i < monkeys.size(); i++) {
        cout << i << " " << monkeys[i].inspects << "\n";
        inspects.push_back(monkeys[i].inspects);
    }
    sort(inspects.rbegin(), inspects.rend());

    return inspects[0] * inspects[1];
}

int main(int argc, char **argv) {

    vector<Monkey> data;
    // Get data
    string s;
    int i = 0;

    while (getline(cin, s)) {
        Monkey m;

        for (auto v : split(s)) {
            m.items.push(std::stoi(v));
        }
        getline(cin, s);

        if (s[0] == '*')
            m.op = MULT;
        if (s[0] == '+')
            m.op = ADD;
        if (s[0] == 'o')
            m.op = MULTSELF;
        getline(cin, s);

        m.operand = std::stoi(s);
        getline(cin, s);

        m.divis = std::stoi(s);
        getline(cin, s);

        m.trueMonkey = std::stoi(s);
        getline(cin, s);

        m.falseMonkey = std::stoi(s);

        data.push_back(m);
    }
    int ans1 = problem_a(data);
    int64_t ans2 = problem_b(data);
    cout << "\nPart 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
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
