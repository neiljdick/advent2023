#pragma once
#include "advent.hpp"

class Day3 {
public:
	pair<int,int> p1(const string path) {
		auto adv = advent(path);
		set<pair<int, int>> valids;
		bool valid = false;
		map<pair<int,int>, int> parsed;
		vector<int> gears;
		pair<int, int> candidate = make_pair(-1,-1);

		for (int y = 0; y < adv.cmap.height; y++) {
			valid = false;
			for (int x = 0; x < adv.cmap.width; x++) {
				char cur = adv.cmap.get(x, y);
				if (!isdigit(cur)) {
					valid = false;
					candidate = make_pair(-1, -1);
					continue;
				}
				if (!valid && candidate == make_pair(-1,-1))
					candidate = make_pair(x, y);
				auto n = adv.cmap.neighbours(make_pair(x, y));
				for (auto const& coord : n) {
					char c = adv.cmap.get(coord);
					if (c != '.' && !isdigit(c)) {
						valid = true;
						valids.insert(candidate);
					}
				}
			}
		}
		for (auto const& coord : valids) {
			string s;
			int x = coord.first;
			int y = coord.second;
			char c;
			do {
				c = adv.cmap.get(x, y);
				if (isdigit(c)) s.push_back(c);
				x++;
			} while (isdigit(c) && x < adv.cmap.width);
			parsed[coord] = stoi(s);
		}


		// p2

		for (int y = 0; y < adv.cmap.height; y++) {
			for (int x = 0; x < adv.cmap.width; x++) {
				char cur = adv.cmap.get(x, y);
				if (cur == '*') {
					set<int> parts;
					auto n = adv.cmap.neighbours(make_pair(x, y));
					for (auto const& coord : n) {
						char search_c = adv.cmap.get(coord);
						if (isdigit(search_c)) {
							int search_x = coord.first;

							do {
								if (valids.find(make_pair(search_x, coord.second)) != valids.end()) {
									parts.insert(parsed[make_pair(search_x, coord.second)]);
									break;
								}
								search_c = adv.cmap.get(search_x, coord.second);
								search_x--;
							} while (search_x >= 0 && isdigit(search_c));

						}
					}
					if (parts.size() == 2) {
						int total = 1;
						for (auto& i : parts) {
							total *= i;
						}
						gears.push_back(total);
					}
				}
			}
		}
		int total = 0;
		for (auto& i : parsed) {
			total += i.second;
		}

		return make_pair(total, sum(gears));
	}
private:

};