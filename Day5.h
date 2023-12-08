#pragma once

#include "advent.hpp"
#include <optional>

namespace Day5 {
	struct Node {
		struct Node* next;
		int offset;
		unsigned int value;
		Node(unsigned int value, int offset) { this->value = value; this->offset = offset; next = nullptr; }
		Node() { next = nullptr; offset = 0; value = 0; }

	};

	unsigned int find(struct Node* head, unsigned int seed) {
		unsigned int val = 0;
		while (head) {
			if (seed >= head->value && seed < head->next->value) {
				val = seed - head->offset;
				break;
			}
			head = head->next;
		}
		return val;
	}
	void insert(struct Node* head, unsigned int begin, unsigned int end, int offset) {
		unsigned int search[2] = { begin, end };
		size_t idx = 0;
		while (head && idx < 2) {

			if (begin >= head->value && begin < head->next->value && end < head->next->value) {
				// they both fit..
				struct Node* n_begin;
				struct Node* n_end;
				if (head->value == begin) {
					n_begin = head;
				}
				else {
					n_begin = new Node(begin, head->offset);
				}
				if (head->next->value == end) {
					n_end = head->next;
				}
				else {
					n_end = new Node(end, head->offset);
				}
				n_end->offset = head->offset;
				n_begin->offset += offset;

				n_end->next = head->next;
				head->next = n_begin;
				n_begin->next = n_end;

				idx = 2;
				break;
			}
			else if (head->value == begin && idx == 0) {
				// collision on begin 
				head->offset += offset;
			}
			else if (head->value == end && idx == 1) {
				//collision on the end 
				// actually do nothing..
				break;
			}
			else if (search[idx] > head->value && search[idx] < head->next->value) {
				struct Node* n = new Node(search[idx], head->offset + offset);
				if (idx == 1) {
					n->offset = head->offset;
					head->offset += offset;
				}
				n->next = head->next;
				head->next = n;
				if (idx == 0)
					head = head->next;

				idx += 1;
			}
			else if (search[idx] > head->value && idx == 1 && search[idx] > head->next->value) {
				head->offset += offset;
			}
			head = head->next;
		}
	}
	/*
	class comp_obj {
	public:
		comp_obj(unsigned int start, unsigned int end, int offset) {
			this->start = start;
			this->end = end;
			this->offset = offset;
		}

		comp_obj(vector<unsigned int> in) {
			start = in[1];
			end = start + in[2];
			offset = start - in[0];
		}

		optional<unsigned int> find(unsigned int in) {
			if (in >= start && in < end) return in - offset;
			else return {};
		}

		unsigned int start;
		unsigned int end;
		int offset;
	};
	*/

	class Day5 {
	public:
		Day5() {
			Node* n = new Node(-1, 0);
			maps.next = n;
		}
		/*
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
		*/

		/*
		vector<comp_obj> merge(comp_obj c, vector<comp_obj> line) {
			vector<comp_obj> finals;
			for (auto const& first : line) {
				if (c.start >= first.start) {
					if (c.end <= first.end) {
						// fully contained..

						if (c.start != first.start)
							finals.push_back(comp_obj(c.start, c.end, first.offset + c.offset));
						if (c.end != first.end)
							finals.push_back(comp_obj(c.end, first.end, first.offset));
						finals.push_back(comp_obj(first.start, c.start, first.offset));
					}
					else {
						// overlap front side
						if (first.start != c.start)
							finals.push_back(comp_obj(first.start, c.start, first.offset));
						if (c.start != first.end)
							finals.push_back(comp_obj(c.start, first.end, c.offset + first.offset));
						finals.push_back(comp_obj(first.end, c.end, first.offset));

					}
				}
				else if (c.end <= first.end && c.start >= first.start) {
					// overlap at end side
					finals.push_back(comp_obj(c.start, first.start, c.offset));
					finals.push_back(comp_obj(first.start, c.end, first.offset + c.offset));
					finals.push_back(comp_obj(c.end + 1, first.end, first.offset));

				}
				else {
					finals.push_back(first);
				}
			}
			sort(finals.begin(), finals.end(), [](const comp_obj& a, const comp_obj& b) {return a.start < b.start; });
			return finals;
		}
		*/

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
					if (map == 3) break;
					continue;
				}
				if (isdigit(line[0])) {
					auto nums_s = split(line, " ");
					vector<unsigned int> nums;
					for (auto& n : nums_s) nums.push_back(stoul(n));
					assert(nums.size() == 3);
					unsigned int begin = nums[1];
					unsigned int end = nums[1] + nums[2];
					int offset = nums[1] - nums[0];

					insert(&maps, begin, end, offset);
				}
			}

			/*
			for (int i = 0; i < maps.size(); i++) {
				size_t len = finals.size();
				for (int j = 0; j < len; j++) {
					comp_obj &first = finals[j];
					for (auto& c : maps[i]) {
						if (c.start >= first.start) {
							if (c.end <= first.end) {
								// fully contained..

								if (c.start != first.start)
									finals.push_back(comp_obj(c.start, c.end,  first.offset + c.offset));
								if (c.end != first.end)
									finals.push_back(comp_obj(c.end, first.end, first.offset));
								first.end = c.start;
							}
							else {
								// overlap front side

								finals.push_back(comp_obj(first.start, c.start, first.offset));
								finals.push_back(comp_obj(c.start, c.end, c.offset + first.offset));
								first.start = c.end;

							}
						}
						else if (c.end <= first.end && c.start >= first.start) {
							// overlap at end side
							finals.push_back(comp_obj(c.start, first.start, c.offset));
							finals.push_back(comp_obj(first.start, c.end, first.offset + c.offset));
							first.start = c.end + 1;

						}
					}
				}
			}
			*/
			// try to do the walk
			vector<unsigned int> locations;
			for (auto const& seed : seeds) {
				unsigned int next = find(&maps, seed);
				locations.push_back(next);
			}
			return *min_element(locations.begin(), locations.end());
		}

	private:
		Node maps;
	};
}