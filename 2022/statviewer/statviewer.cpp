#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json/json.h>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;
/*
* Try not to judge, it's quick and dirty.
*/
const string DEFAULT_FILENAME = "example.json";
/**
 * https://stackoverflow.com/questions/7960318/math-to-convert-seconds-since-1970-into-date-and-vice-versa/32158604#32158604
 */
int days_from_civil(int y, unsigned m, unsigned d) noexcept {
    y -= m <= 2;
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400); // [0, 399]
    const unsigned doy =
        (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;         // [0, 365]
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]
    return era * 146097 + static_cast<int>(doe) - 719468;
}

int main(int argc, char **argv) {
    Json::Value root;

    std::ifstream ifs;
    if (argc > 1) {
        cout << "Opening: " << argv[1] << "\n";
        ifs.open(argv[1]);
    } else {
        cout << "Opening: " << DEFAULT_FILENAME << "\n";
        ifs.open(DEFAULT_FILENAME);
    }

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;

    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        cout << "Parse Error!\n";
        cout << errs << endl;
        return EXIT_FAILURE;
    }
    cout << "Event: " << root["event"] << "\n";
    auto members_node = root["members"];

    int i = 0;
    vector<string> members;
    vector<string> member_id;
    vector<vector<int>> timestamp(51);
    for (auto a : members_node) {
        if (a["name"].isNull()) {
            members.push_back(a["id"].asString());
        } else {
            members.push_back(a["name"].asString());
        }
        member_id.push_back(a["id"].asString());    
    }
    
    for( auto i=0; i<timestamp.size(); i++){
      timestamp[i].resize(members.size(),INT_MAX);
    }
        
    for (auto j=0; j<members.size(); j++) {
      auto a = members_node[member_id[j]];    
      auto days = a["completion_day_level"];      
      for (auto day : days.getMemberNames() ) {
          int dayval = atoi(day.c_str());
          int i=0;
          for (auto problem : days[day]) {
              int idx = (dayval - 1) * 2 + i + 1;              
              timestamp[idx][j]=problem["get_star_ts"].asInt();
              i++;
          }
      }      
    }
  
    int problem_number=3;
    for(int problem_number=1; problem_number < 51; problem_number++){
      int problem_day = (problem_number-1)/2+1;
      cout << "Problem Number: " << problem_day << ( problem_number % 2 ? "A" : "B" ) << "\n";
      vector<int> idx(members.size(), 0);
      iota(idx.begin(), idx.end(), 0);    
      sort(idx.begin(), idx.end(), [&](int a, int b) { return timestamp[problem_number][a] < timestamp[problem_number][b]; });
      int rank=1;
      int start =
                days_from_civil(2022, 12, problem_day) * 60 * 60 * 24 + 5 * 60 * 60;
      for (auto i : idx) {        
          
          int delta = timestamp[problem_number][i] - start;
          int hours = delta / (60 * 60);
          int minutes = (delta - hours * 60 * 60) / 60;
          if( hours < 24 ){
            cout << rank++ << " " << setfill('0') << setw(2) << hours 
                << ":" << setfill('0') << setw(2) << minutes
                << ":" << setfill('0') << setw(2) << (delta % 60)   
                << " " << members[i] <<"\n";
          }
      }
    }
    return EXIT_SUCCESS;
}