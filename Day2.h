#pragma once
#include "advent.hpp"
class Day2
{
public:
	Day2()  {
		try {
			game_R = regex(R"(([\d+])([\w+])([,?]))");
		}
		catch (exception const& e) {
			cerr << e.what() << endl;
		}
	}
	int p1(string path) {
		auto adv = advent(path);
		int id = 1;
		for (auto& l : adv.raw_vec) {
			// parse lines
			size_t start = l.find(":");
			assert(start != string::npos);
			auto line = l.substr(start+1);
			// now try to split on ;
			string sub(line);
			size_t next;
			do {
				next = sub.find(";");
				if (next != string::npos) {
					sub = sub.substr(next+1);
				}

				
			} while (next != string::npos);
		}
		return 0;
	}
private:
	regex game_R;
};

