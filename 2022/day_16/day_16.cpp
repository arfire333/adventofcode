#include <bitset>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stdio.h>
#include <unordered_set>
#include <vector>
using namespace std;
vector<string> split(const string &str);
// Don't try this at home.  The code equivalent of an ugly Christmas sweater
map<string, int> idx;
vector<int> flow_rates;
vector<string> valves;
vector<vector<string>> adj_lists;
vector<vector<int>> n_adj_lists;
vector<vector<int64_t>> travel_times;
set<pair<int, string>> complete_set;

set<pair<int, int64_t>> complete_set_n;
int64_t count = 0;

stringstream ss, ss2;
int maxgain = 0;
void fastflow(int64_t curr, vector<int> opened, string s, int64_t si,
              int total_vented = 0, int vent_rate = 0,
              int time_remaining = 30) {
    if (time_remaining < 0) {
        cerr << "Negative Time Remaining: " << time_remaining << " with path "
             << s << "\n";
        assert(false);
        return;
    }
    if (time_remaining == 0) {
        complete_set.insert({total_vented, s});
        complete_set_n.insert({total_vented, si});
        if (total_vented > maxgain) {
            maxgain = total_vented;            
        }
        return;
    }
    int64_t gain = 0;

    for (int64_t i = 0; i < valves.size(); i++) {
        if (opened[i] > 0 || flow_rates[i] == 0) {
            continue;
        }

        auto nextopened = opened;
        nextopened[i]++;
        ss.str("");
        int64_t ssi = si;
        int travel_time = travel_times[curr][i];
        ss << s;

        int new_vent_rate = vent_rate;
        if (time_remaining - travel_time > 1) {
            for (int k = 0; k < travel_time; k++) {
                ss << "__";
            }

            new_vent_rate = vent_rate + flow_rates[i];
            ss << valves[i];

            ssi = ssi | (1LL << i); // Very important to use LL

            travel_time++;
        } else {

            travel_time = time_remaining;
            for (int k = 0; k < travel_time; k++) {
                ss << "__";
            }
        }
        int travel_gain = travel_time * vent_rate;
        fastflow(i, nextopened, ss.str(), ssi, total_vented + travel_gain,
                 new_vent_rate, time_remaining - travel_time);
    }

    int travel_time = time_remaining;
    int travel_gain = travel_time * vent_rate;
    ss.str("");
    ss << s;
    for (int i = 0; i < travel_time; i++) {
        ss << "__";
    }
    fastflow(curr, opened, ss.str(), si, total_vented + travel_gain, vent_rate,
             time_remaining - travel_time);
}

int64_t problem_a() {
    string s;
    int64_t si = 0;
    vector<int> opened(flow_rates.size(), 0);

    fastflow(idx["AA"], opened, s, si);

    return maxgain;
}
string valves_visited(int64_t v) {
    stringstream ss;
    int c = 0;
    while (v > 0) {
        if (v & 1 == 1) {
            ss << valves[c] << "(" << flow_rates[c] << ") ";
        }
        c++;
        v = v >> 1;
    }
    return ss.str();
}

int problem_b() {
    string s;
    int64_t si = 0;
    complete_set.clear();
    complete_set_n.clear();
    vector<int> opened(flow_rates.size(), 0);

    fastflow(idx["AA"], opened, s, si, 0, 0, 26);
    
    vector<pair<int, int64_t>> complete_set_v(complete_set_n.begin(),
                                              complete_set_n.end());
    cout << "complete_set: " << complete_set_v.size() << "\n";
    vector<pair<int, string>> cs(complete_set.begin(), complete_set.end());
    int64_t maxme = 0, maxele = 0;
    for (int i = 0; i < complete_set_v.size() - 1; i++) {
        for (int j = i; j < complete_set_v.size(); j++) {
            auto l = complete_set_v[i];
            auto r = complete_set_v[j];

            if ((l.second & r.second) == 0) {

                int gain = l.first + r.first;
                if (gain > maxgain) {
                    maxgain = gain;
                    maxme = l.first;
                    maxele = r.first;
                    cout << maxgain << " " << maxme << " " << maxele << "\n";
                    cout << std::bitset<60>(l.second) << " : "
                         << valves_visited(l.second) << " : " << cs[i].first
                         << " = " << cs[i].second << "\n";
                    cout << std::bitset<60>(r.second) << " : "
                         << valves_visited(r.second) << " : " << cs[j].first
                         << " = " << cs[j].second << "\n";
                }
            }
        }
    }
    return maxgain;
}

int64_t get_travel_time(int64_t start, int64_t stop) {
    vector<bool> visited(valves.size());
    queue<pair<int64_t, int64_t>> q;
    q.push({start, 0});

    while (q.size() > 0) {
        auto curr = q.front();

        q.pop();
        if (curr.first == stop) {
            return curr.second;
        }
        for (auto next : n_adj_lists[curr.first]) {
            if (visited[next])
                continue;
            visited[next] = true;
            q.push({next, curr.second + 1});
        }
    }
    return -1;
}
void gen_travel_times() {
    int N = valves.size();
    travel_times = vector<vector<int64_t>>(N, vector<int64_t>(N, INT_MAX));
    cout << "   ";
    for (int i = 0; i < N; i++) {
        cout << valves[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << valves[i] << " ";
        for (int j = 0; j < N; j++) {
            travel_times[i][j] = get_travel_time(i, j);
            if (flow_rates[j] == 0 || (flow_rates[i] == 0 && i != idx["AA"])) {
                cout << "."
                     << "  ";
            } else if (travel_times[i][j] > 9) {
                cout << char(travel_times[i][j] + 'a' - 10) << "  ";
            } else {
                cout << travel_times[i][j] << "  ";
            }
        }
        cout << "\n";
    }
}

int main(int argc, char **argv) {

    string s;
    vector<vector<string>> input;

    while (getline(cin, s)) {
        auto slist = split(s);
        input.push_back(slist);
    }
    int count = 0;
    for (auto list : input) {
        valves.push_back(list[0]);
        flow_rates.push_back(std::stoi(list[1]));
        idx[list[0]] = count++;
    }

    for (auto list : input) {
        adj_lists.push_back(vector<string>(list.begin() + 2, list.end()));
        n_adj_lists.push_back(vector<int>());
        for (auto item = list.begin() + 2; item != list.end(); item++) {
            n_adj_lists.back().push_back(idx[*item]);
        }
    }
    gen_travel_times();

    for (int i = 0; i < valves.size(); i++) {
        cout << i << " " << valves[i] << " " << flow_rates[i] << " \n";
    }

    int ans1 = problem_a();
    cout << "Part 1: " << ans1 << "\n";

    int64_t ans2 = problem_b();

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(",", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
