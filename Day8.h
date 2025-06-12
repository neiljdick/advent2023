#pragma once

#include "advent.hpp"

namespace Day8 {

	
	class Day8 {
	public:
		Day8(string path) : adv(path) {
			instructions = adv.raw_vec[0];

			for (auto it = adv.raw_vec.begin() + 2; it != adv.raw_vec.end(); ++it) {
				string point, left, right;

				smatch sm;
				regex_search(*it, sm, regex("(\\w+) = \\((\\w+), (\\w+)\\)"));
				point = sm[1];
				left = sm[2];
				right = sm[3];
				desert[point] = make_pair(left, right);
			}

		};
		bool check(const vector<unordered_map<string, pair<string, string>>::iterator> &ghosts) {
			bool done = true;
			for (auto const& c : ghosts) {
				if (c->first[2] != 'Z') {
					done = false;
					break;
				}
			}
			return done;
		}
		int64_t p2() {
			vector<string> starts;
			for (auto const& p : desert) {
				if (p.first[2] == 'A') starts.push_back(p.first);
			}
			vector<unordered_map<string, pair<string, string>>::iterator> ghosts;
			for (auto const& p : starts) {
				ghosts.push_back(desert.find(p));
			}
			size_t idx = 0;
			int64_t count = 0;
			while (!check(ghosts)) {
				for (auto &g : ghosts) {
					if (instructions[idx] == 'L') g = desert.find(g->second.first);
					else g = desert.find(g->second.second);
				}
				idx = (idx + 1) % instructions.size();
				count++;
			}
			return count;
		}
		int p1() {
			auto it = desert.find("AAA");
			size_t idx = 0;
			int count = 0;
			while (it->first != "ZZZ") {
				if (instructions[idx] == 'L') it = desert.find(it->second.first);
				else it = desert.find(it->second.second);
				idx = (idx + 1) % instructions.size();
				count++;
			}
			return count;
		}
	private:
		string instructions;
		unordered_map<string, pair<string, string>> desert;
		advent adv;
	};
}