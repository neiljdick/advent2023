#include "pch.h"

class Day1 {
public:
    int mass(int i) { return i / 3 - 2; }
    int p1(vector<int>& data) {
        vector<int> res = fmap(data, [this](int i) {return mass(i); });
        return sum(res);
    }

    int p2_worker(int i, int sum) {
        i = mass(i);
        if (i <= 0)
            return sum;
        return p2_worker(i, sum + i);
    }

    int p2_f(int i) {
        return p2_worker(i, 0);
    }

    int p2(std::vector<int>& data) {
        for_each(data.begin(), data.end(), [this](int& i) { i = p2_f(i); });
        return sum(data);
    }

    pair<int,int> day1(string path)
    {
       
        auto adv = advent(path);
        auto data = vector<int>(adv.int_vec);

        int r1 = p1(data);
        int r2 = p2(adv.int_vec);

        std::cout << "p1 " << r1 << std::endl;
        std::cout << "p2 " << r2 << std::endl;
        return make_pair(r1,r2);
    }
};
