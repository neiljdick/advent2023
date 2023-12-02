#include "advent.hpp"
//#include "pch.h"

class Day1 {
public:
    Day1() {
        vals["one"] = "1";
        vals["two"] = "2";
        vals["three"] = "3";
        vals["four"] = "4";
        vals["five"] = "5";
        vals["six"] = "6";
        vals["seven"] = "7";
        vals["eight"] = "8";
        vals["nine"] = "9";
    }
    map<string, string> vals;

    int p1(string line) {
        string s;
        string digits;

        copy_if(line.begin(), line.end(), back_inserter(digits), isdigit);

        s.push_back(digits.front());
        s.push_back(digits.back());
        return stoi(s);
    }
    int p2(string path) {
        auto adv = advent(path);

        // p2 
        vector<int> parsed2;

        for (auto& line : adv.raw_vec) {
            string s = string(line);
            vector<pair<size_t, string>> matches;
            bool done = false;
            while (!done) {
                for (auto it = vals.begin(); it != vals.end(); ++it) {
                    string key = it->first;
                    auto m = s.find(key);
                    if (m != string::npos) {
                        matches.push_back(make_pair(m, key));
                    }
                }

                if (!matches.empty()) {
                    sort(matches.begin(), matches.end());
                    for (auto& m : matches)
                        s.replace(m.first, 1, vals[m.second]);
                    matches.clear();
                }
                else {
                    done = true;
                }
            }
            parsed2.push_back(p1(s));
        }
  
        return sum(parsed2);
    }
    int do_p1(string path)
    {
       
        auto adv = advent(path);
        vector<int> parsed;
        for (auto& line : adv.raw_vec) {
            int i = p1(line);
            parsed.push_back(i);
        }

        return sum(parsed);
    }
};
