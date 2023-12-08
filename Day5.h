#pragma once

#include "advent.hpp"
#include <optional>
class comp_obj {
public:
	comp_obj(vector<int64_t> in) {
		start = in[1];
		end = start + in[2];
		offset = start - in[0];
	}

	optional<int64_t> find(int64_t in) {
		if (in >= start && in < end) return in - offset;
		else return {};
	}


private:
	int64_t start;
	int64_t end;
	int64_t offset;
};

class Day5 {
public:
	Day5() {
		for (int m = 0; m < 7; m++) {
			maps.push_back(vector<comp_obj>());
		}
	}

	int64_t p2(string path) {
		auto adv = advent(path);
		auto seeds_s = split(split(adv.raw_vec[0], ":")[1], " ");
		vector<int64_t> seeds;
		int map = -1;
		for (auto& s : seeds_s)
			try {
			seeds.push_back(stoll(s));
		}
		catch (const exception e) {
			cout << e.what();
		}
		for (int i = 1; i < adv.raw_vec.size(); i++) {
			string& line = adv.raw_vec[i];
			if (line.find("map") != string::npos) {
				map++;
				continue;
			}
			if (isdigit(line[0])) {
				auto nums_s = split(line, " ");
				vector<int64_t> nums;
				for (auto& n : nums_s) nums.push_back(stoll(n));
				assert(nums.size() == 3);
				maps[map].push_back(comp_obj(nums));
			}
		}

		// try to do the walk
		vector<int64_t> locations;
		for (int pair = 0; pair < seeds.size(); pair += 2) {
			Logger::WriteMessage("finished seed\n");
			for (int64_t seed = seeds[pair]; seed < seeds[pair + 1] + seeds[pair]; seed++) {
				int64_t next = seed;
				for (int i = 0; i < 7; i++) {
					optional<int64_t> match;
					for (auto& c : maps[i]) {
						match = c.find(next);
						if (match.has_value()) break;
					}
					next = match.has_value() ? match.value() : next;
				}
				locations.push_back(next);
			}
		}
		return *min_element(locations.begin(), locations.end());
	}

	int64_t p1(string path) {
		auto adv = advent(path);
		auto seeds_s = split(split(adv.raw_vec[0], ":")[1], " ");
		vector<int64_t> seeds;
		int map = -1;
		for (auto& s : seeds_s) 
			try {
			seeds.push_back(stoll(s));
		}
		catch (const exception e) {
			cout << e.what();
		}
		for (int i = 1; i < adv.raw_vec.size(); i++) {
			string& line = adv.raw_vec[i];
			if (line.find("map") != string::npos) {
				map++;
				continue;
			}
			if (isdigit(line[0])) {
				auto nums_s = split(line, " ");
				vector<int64_t> nums;
				for (auto& n : nums_s) nums.push_back(stoll(n));
				assert(nums.size() == 3);
				maps[map].push_back(comp_obj(nums));
			}
		}

		// try to do the walk
		vector<int64_t> locations;
		for (auto const& seed : seeds) {
			int64_t next = seed;
			for (int i = 0; i < 7; i++) {
				optional<int64_t> match;
				for (auto& c : maps[i]) {
					match = c.find(next);
					if (match.has_value()) break;
				}
				next = match.has_value() ? match.value() : next;
			}
			locations.push_back(next);
		}
		return *min_element(locations.begin(), locations.end());
	}

private:
	vector<vector<comp_obj>> maps;
};