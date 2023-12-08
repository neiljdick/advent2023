#pragma once
#include "advent.hpp"

class Day6 {
public:

	Day6(string path) : adv(path) {
		string t_s = split(adv.raw_vec[0], ":")[1];
		string d_s = split(adv.raw_vec[1], ":")[1];
		for (auto& s : split(t_s, " ")) {
			times.push_back(stoll(s));
		}
		for (auto& s : split(d_s, " ")) {
			distances.push_back(stoll(s));
		}
	}

	int64_t p1(void) {
		size_t len = times.size();
		int64_t res = 1;
		for (int i = 0; i < len; i++) {
			int64_t time = times[i];
			int64_t distance = distances[i];
			int64_t sum = 0;
			vector<int64_t> race;
			for (int64_t charge_time = 0; charge_time < time; charge_time++) {
				race.push_back((time - charge_time) * charge_time);
			}
			for (auto const& x : race) {
				if (x > distance) sum++;
			}
			res = res * sum;
		}
		return res;
	}

private:
	advent adv;
	vector<int64_t> times;
	vector<int64_t> distances;
};