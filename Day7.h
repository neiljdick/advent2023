#pragma once

#include "advent.hpp"


class Day7 {
public:
	Day7(string path) : adv(path) {
		value['2'] = 2;
		value['3'] = 3;
		value['4'] = 4;
		value['5'] = 5;
		value['6'] = 6;
		value['7'] = 7;
		value['8'] = 8;
		value['9'] = 9;
		value['T'] = 10;
		value['J'] = 1;
		value['Q'] = 12;
		value['K'] = 13;
		value['A'] = 14;
	}

	int hand_score(const string& hand) {
		map<char, int> symbols_map;
		vector<pair<char, int>> symbols;
		int wild = 0;
		for (auto& c : hand) {
			symbols_map[c]++;
		}
		auto jit = symbols_map.find('J');
		if (jit != symbols_map.end()) {
			if (jit->second != 5) {
				wild = jit->second;
				symbols_map.erase('J');
			}
		}

		for (auto& p : symbols_map) symbols.push_back(p);
		
		sort(symbols.begin(), symbols.end(), [](const pair<const char, int>& a, const pair<const char,int>& b) {return a.second > b.second; });
		symbols[0].second += wild;
		for (auto it = symbols.begin(); it != symbols.end(); ++it) {
			if (it->second == 5) return 7;
			if (it->second == 4) return 6;
			if (it->second == 3) {
				auto tmp = it;
				tmp++;
				if (tmp->second == 2) return 5;
				else return 4;
			}
			if (it->second == 2) {
				auto tmp = it;
				tmp++;
				if (tmp->second == 2) return 3;
				else return 2;
			}
			else {
				return 1;
			}
		}
		return 0;
	}

	bool hand_score_fn(const pair<string, long> &a, const pair<string, long> &b) {
		const string &sa = a.first;
		const string &sb = b.first;
		int ha = hand_score(sa);
		int hb = hand_score(sb);

		if (ha > hb) return false;
		if (hb > ha) return true;
		for (int i = 0; i < sa.size(); i++) {
			if (value[sa[i]] > value[sb[i]]) return false;
			else if (value[sb[i]] > value[sa[i]]) return true;
		}
		return false;
	}

	int64_t p1() {
		vector<pair<string, long>> hands;
		for (auto const& line : adv.raw_vec) {
			auto s = split(line, " ");
			auto hand = s[0];
			auto bet = stol(s[1]);
			//sort(hand.begin(), hand.end(), [this](const char& a, const char& b) {return value[a] > value[b]; });
			hands.push_back(make_pair(hand, bet));
		}
		sort(hands.begin(), hands.end(), [this](const pair<string, long> &a, const pair<string, long> &b) { return hand_score_fn(a, b); });
		int64_t score = 0;
		for (int i = 0; i < hands.size(); i++) {
			score += (i + 1) * hands[i].second;
		}
		return score;
	}
private:
	advent adv;
	map<char, int> value;
};