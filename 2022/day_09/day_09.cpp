#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;
pair<int, int> amount2Shift(pair<int, int> head, pair<int, int> tail) {
    int dy = head.first - tail.first;
    int dx = head.second - tail.second;
    int ygrid[5][5] = {{-1, -1, -1, -1, -1},
                       {-1, 0, 0, 0, -1},
                       {0, 0, 0, 0, 0},
                       {1, 0, 0, 0, 1},
                       {1, 1, 1, 1, 1}};

    int xgrid[5][5] = {{-1, -1, 0, 1, 1},
                       {-1, 0, 0, 0, 1},
                       {-1, 0, 0, 0, 1},
                       {-1, 0, 0, 0, 1},
                       {-1, -1, 0, 1, 1}};
    return {ygrid[dy + 2][dx + 2], xgrid[dy + 2][dx + 2]};
}

int problem_a(const vector<pair<char, int>> in) {
    set<pair<int, int>> stops;
    pair<int, int> head = {0, 0};
    pair<int, int> tail = {0, 0};
    stops.insert(tail);
    int N = in.size();
    for (auto [direction, i] : in) {
        while (i > 0) {
            switch (direction) {
            case 'U':
                head.first++;
                break;
            case 'D':
                head.first--;
                break;
            case 'L':
                head.second--;
                break;
            case 'R':
                head.second++;
                break;
            default:
                break;
            }
            pair<int, int> shift = amount2Shift(head, tail);
            tail.first += shift.first;
            tail.second += shift.second;
            stops.insert(tail);
            i--;
        }
    }

    return stops.size();
}

void print_knots(const vector<pair<int, int>> &knots) {
    int maxx = 6;
    int maxy = 6;
    int minx = 0;
    int miny = 0;
    for (int j = 0; j < 10; j++) {
        if (knots[j].first > maxy) {
            maxy = knots[j].first;
        }
        if (knots[j].first < miny) {
            miny = knots[j].first;
        }
        if (knots[j].second > maxx) {
            maxx = knots[j].second;
        }
        if (knots[j].second < minx) {
            minx = knots[j].second;
        }
    }
    for (int j = maxy; j >= miny; j--) {
        for (int k = minx; k <= maxx; k++) {
            bool hit = false;
            for (int l = 0; l < 10; l++) {
                if (knots[l].first == j && knots[l].second == k) {
                    hit = true;
                    cout << l;
                    break;
                }
            }
            if (!hit) {
                cout << ".";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_tail(const set<pair<int, int>> &stops) {
    int maxx = 6;
    int maxy = 6;
    int minx = 0;
    int miny = 0;
    for (auto p : stops) {
        if (p.first > maxy) {
            maxy = p.first;
        }
        if (p.first < miny) {
            miny = p.first;
        }
        if (p.second > maxx) {
            maxx = p.second;
        }
        if (p.second < minx) {
            minx = p.second;
        }
    }
    for (int j = maxy; j >= miny; j--) {
        for (int k = minx; k <= maxx; k++) {
            if (stops.find({j, k}) != stops.end()) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int problem_b(const vector<pair<char, int>> in) {
    set<pair<int, int>> stops;
    vector<pair<int, int>> knots(10, pair<int, int>({0, 0}));
    pair<int, int> head = {0, 0};
    pair<int, int> tail = {0, 0};
    stops.insert(knots[9]);

    for (auto [direction, i] : in) {
        while (i > 0) {
            switch (direction) {
            case 'U':
                knots[0].first++;
                break;
            case 'D':
                knots[0].first--;
                break;
            case 'L':
                knots[0].second--;
                break;
            case 'R':
                knots[0].second++;
                break;
            default:
                break;
            }
            for (int j = 0; j < 9; j++) {
                pair<int, int> shift = amount2Shift(knots[j], knots[j + 1]);
                knots[j + 1].first += shift.first;
                knots[j + 1].second += shift.second;
            }
            stops.insert(knots[9]);
            i--;
        }
        
    }
    print_tail(stops);
    return stops.size();
}

int main(int argc, char **argv) {
    vector<pair<char, int>> data;
    // Get data
    char c = ' ';
    int i = 0;
    while (cin >> c >> i) {
        data.push_back({c, i});
    }

    cout << "Part 1: " << problem_a(data) << "\n";
    cout << "Part 2: \n" << problem_b(data) << "\n";
}