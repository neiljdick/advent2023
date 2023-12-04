#pragma once
#include "advent.hpp"
class Day2
{
public:
	Day2()  {
		try {
			game_R = regex(R"((\d+) (\w+))");
		}
		catch (exception const& e) {
			cerr << e.what() << endl;
		}
		limit_red = 12;
		limit_green = 13;
		limit_blue = 14;
	}
	pair<int, int> p1(string path) {
		
	
		auto adv = advent(path);
		int id = 1;
		int sum = 0;
		int sum_power = 0;
		for (auto& l : adv.raw_vec) {
			auto _tmp = split(l, ":");
			string line = _tmp[1];
			auto hands = split(line, ";");
			smatch sm;
			bool valid = true;
			int min_blue = 0;
			int min_red = 0;
			int min_green = 0;
			int power = 0;
			for (auto const& hand : hands) {
				string::const_iterator search_start(hand.cbegin());
				while (regex_search(search_start, hand.cend(), sm, game_R)) {
					search_start = sm.suffix().first;
					int val = stoi(sm[1]);
					if (sm[2] == "green") {
						if (val > limit_green) valid = false;
						if (val > min_green) min_green = val;
					} else if (sm[2] == "red") {
						if (val > limit_red) valid = false;
						if (val > min_red) min_red = val;
					}
					else {
						if (val > limit_blue) valid = false;
						if (val > min_blue) min_blue = val;
					}
				}
			}
			if (valid)
				sum += id;
			power = min_blue * min_red * min_green;
			sum_power += power;
			id++;

		}
		return make_pair(sum, sum_power);
	}

private:
	int limit_red;
	int limit_green;
	int limit_blue;
	regex game_R;
};

