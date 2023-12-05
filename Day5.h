#pragma once

#include "advent.hpp"
#include <optional>
class comp_obj {
public:
	comp_obj(vector<unsigned int> in) {
		start = in[1];
		end = start + in[2];
		offset = start - in[0];
	}

	optional<unsigned int> find(unsigned int in) {
		if (in >= start && in < end) return in - offset;
		else return {};
	}


private:
	unsigned int start;
	unsigned int end;
	int offset;
};

class Day5 {
public:
	Day5() {
		for (int m = 0; m < 7; m++) {
			maps.push_back(vector<comp_obj>());
		}
	}

	unsigned int p2(string path) {
		auto adv = advent(path);
		auto seeds_s = split(split(adv.raw_vec[0], ":")[1], " ");
		vector<unsigned int> seeds;
		int map = -1;
		for (auto& s : seeds_s)
			try {
			seeds.push_back(stoul(s));
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
				vector<unsigned int> nums;
				for (auto& n : nums_s) nums.push_back(stoul(n));
				assert(nums.size() == 3);
				maps[map].push_back(comp_obj(nums));
			}
		}

		// try to do the walk
		vector<unsigned int> locations;
		for (int pair = 0; pair < seeds.size(); pair += 2) {
			Logger::WriteMessage("finished seed\n");
			for (int seed = seeds[pair]; seed < seeds[pair + 1] + seeds[pair]; seed++) {
				unsigned int next = seed;
				for (int i = 0; i < 7; i++) {
					optional<unsigned int> match;
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

	unsigned int p1(string path) {
		auto adv = advent(path);
		auto seeds_s = split(split(adv.raw_vec[0], ":")[1], " ");
		vector<unsigned int> seeds;
		int map = -1;
		for (auto& s : seeds_s) 
			try {
			seeds.push_back(stoul(s));
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
				vector<unsigned int> nums;
				for (auto& n : nums_s) nums.push_back(stoul(n));
				assert(nums.size() == 3);
				maps[map].push_back(comp_obj(nums));
			}
		}

		// try to do the walk
		vector<unsigned int> locations;
		for (auto const& seed : seeds) {
			unsigned int next = seed;
			for (int i = 0; i < 7; i++) {
				optional<unsigned int> match;
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