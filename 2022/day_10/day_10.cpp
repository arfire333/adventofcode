#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;
vector<string> split(const string &str);
set<int> cycles;

enum opcode { NOOP = 0, ADDX = 1 };

int signal_strength(int cycle, int X) { return cycle * X; }

void print_pixel(int cycle, int sprite) {
    int pixel = (cycle - 1) % 40;
    if (pixel == 0 && cycle != 1) {
        cout << "\n";
    }
    if (pixel <= sprite + 1 && pixel >= sprite - 1) {
        cout << "#";
    } else {
        cout << " ";
    }
}

int problem_a(const vector<pair<int, int>> &in) {
    // cycles to save
    for (int i = 20; i <= 220; i += 40) {
        cycles.insert(i);
    }
    int cycle = 0;
    int X = 1;
    int sum = 0;
    for (auto op : in) {
        switch (op.first) {
        case ADDX:
            cycle++;
            if (cycles.find(cycle) != cycles.end()) {
                sum += signal_strength(cycle, X);
            }
            cycle++;
            if (cycles.find(cycle) != cycles.end()) {
                sum += signal_strength(cycle, X);
            }
            X += op.second;
            break;
        case NOOP:
        default:
            cycle++;
            if (cycles.find(cycle) != cycles.end()) {
                sum += signal_strength(cycle, X);
            }
            break;
        }
    }

    return sum;
}

void problem_b(const vector<pair<int, int>> &in) {
    int cycle = 0;
    int X = 1;
    int sum = 0;
    for (auto op : in) {
        switch (op.first) {
        case ADDX:
            cycle++;
            print_pixel(cycle, X);
            cycle++;
            print_pixel(cycle, X);
            X += op.second;
            break;
        case NOOP:
        default:
            cycle++;
            print_pixel(cycle, X);
            break;
        }
    }
    cout << "\n";
}

int main(int argc, char **argv) {
    vector<pair<int, int>> data;
    // Get data
    string s;
    int i = 0;
    while (getline(cin, s)) {
        auto s2 = split(s);
        if (s2.size() > 1) {
            data.push_back({ADDX, std::stoi(s2[1])});
        } else {
            data.push_back({NOOP, 0});
        }
    }
    int part1 = problem_a(data);
    cout << "Part 1: " << part1 << "\n";
    cout << "----------------------------------------\n";
    problem_b(data);
    cout << "----------------------------------------\n";
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