#pragma once
#include <math.h>
#include "advent.hpp"

class Day4 {

public:

	int p2(string path) {
		auto adv = advent(path);

		map<int, int> scores;
		map<int, int> counts;
		for (int i =  0; i < adv.raw_vec.size(); i++) {
			counts[i+1] = 1;
		}
		for (auto const& line : adv.raw_vec) {
			set<int> a, b, res;
			int id;
			auto game = split(line, ":");
			int score = 0;
			sscanf_s(game[0].c_str(), "Card %d", &id);
			auto g = split(game[1], " | ");
			auto first = split(g[0], " ");
			auto second = split(g[1], " ");
			for (auto const& num : first) {
				if (num.empty()) continue;
				a.insert(stoi(num));
			}
			for (auto const& num : second) {
				if (num.empty()) continue;
				b.insert(stoi(num));
			}
			set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
			score = res.size();
			scores[id] = score;
			for (int j = 0; j < score; j++) {
				counts[id + 1 + j]+=counts[id];
			}

		}
		int total = 0;
		for (auto& p : counts) {
			total += p.second;
		}
		return total;
	}

	int p1(string path) {
		auto adv = advent(path);
		
		int ans = 0;

		for (auto const& line : adv.raw_vec) {
			set<int> a, b, res;
			auto g = split(split(line, ":")[1], " | ");
			auto first = split(g[0], " ");
			auto second = split(g[1], " ");
			for (auto const& num : first) {
				a.insert(stoi(num));
			}
			for (auto const& num : second) {
				b.insert(stoi(num));
			}
			set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
			if (res.size() > 0)
				ans += pow(2, res.size() - 1);
		}
		return ans;
	}
};