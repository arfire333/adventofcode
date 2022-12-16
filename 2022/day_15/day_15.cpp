#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;

int64_t distance(int64_t sx, int64_t sy, int64_t bx, int64_t by) {
    return abs(sx - bx) + abs(sy - by);
}

pair<int64_t, int64_t> taken(int row, int64_t sx, int64_t sy, int64_t bx,
                             int64_t by, int64_t lower_limit = INT_MIN,
                             int64_t upper_limit = INT_MAX) {
    pair<int64_t, int64_t> minmax = {INT_MAX, INT_MIN};
    int64_t max_offset = distance(sx, sy, bx, by) - abs(sy - row);
    if (max_offset >= 0) {
        if (sx - max_offset < minmax.first) {
            minmax.first = max(lower_limit, sx - max_offset);
        }
        if (sx + max_offset > minmax.second) {
            minmax.second = min(upper_limit, sx + max_offset);
        }
    }
    return minmax;
}
int64_t freq(int64_t x, int64_t y) { return x * 4000000 + y; }

int problem_a(int64_t row, const vector<pair<int64_t, int64_t>> &sensors,
              const vector<pair<int64_t, int64_t>> &beacons) {
    vector<pair<int64_t, int64_t>> minmax;
    for (auto i = 0; i < sensors.size(); i++) {
        auto sensor = sensors[i];
        auto beacon = beacons[i];

        auto newrange = taken(row, sensor.first, sensor.second, beacon.first,
                              beacon.second);
        if (newrange.second >= newrange.first) {
            minmax.push_back(newrange);
        }
    }
    sort(minmax.begin(), minmax.end());
    int start = 0;
    int end = 1;
    while (end < minmax.size()) {
        if (minmax[start].second >= minmax[end].second) {
            end++;
        } else if (minmax[start].second >= minmax[end].first - 1) {
            minmax[start].second = minmax[end].second;
            end++;
        } else {
            start++;
            end++;
        }
    }
    minmax.resize(start + 1);
    int sum = 0;
    int toremove = 0;
    for (auto v : minmax) {
        sum += v.second - v.first;    
    }
    
    return sum;
}

int64_t problem_b( const vector<pair<int64_t, int64_t>> &sensors,
              const vector<pair<int64_t, int64_t>> &beacons) {
    int64_t distress_freq = 0;
    for (int64_t y = 0; y <= 4000000; y++) {
        vector<pair<int64_t, int64_t>> minmax;
        for (auto i = 0; i < sensors.size(); i++) {
            auto sensor = sensors[i];
            auto beacon = beacons[i];

            auto newrange = taken(y, sensor.first, sensor.second,
                                  beacon.first, beacon.second,0,4000000);
            if (newrange.second >= newrange.first) {
                minmax.push_back(newrange);
            }
        }
        sort(minmax.begin(), minmax.end());
        int start = 0;
        int end = 1;
        while (end < minmax.size()) {
            if (minmax[start].second >= minmax[end].second) {
                minmax.erase(minmax.begin()+end); 
            } else if (minmax[start].second >= minmax[end].first - 1) {
                minmax[start].second = minmax[end].second;
                minmax.erase(minmax.begin()+end);                
            } else {
                start++;
                end++;
            }
        }
        minmax.resize(start + 1);
        if( minmax.size() > 1  || minmax[0].first>0 || minmax[0].second<4000000)
        {          
          distress_freq=(minmax[0].second+1)*4000000+y;
        }
    }
    return distress_freq;
}

int main(int argc, char **argv) {
    vector<int> data;
    vector<pair<int64_t, int64_t>> sensors;
    vector<pair<int64_t, int64_t>> beacons;

    string s;
    int row = 0;
    getline(cin, s);
    row = std::stoi(s);
    while (getline(cin, s)) {
        int sx, sy, bx, by;
        // cout << s << "\n";
        sscanf(s.c_str(),
               "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sx,
               &sy, &bx, &by);

        sensors.push_back({sx, sy});
        beacons.push_back({bx, by});        
    }

    int64_t ans1=problem_a(row, sensors, beacons);    
    int64_t ans2=problem_b(sensors, beacons);    
    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";    
}