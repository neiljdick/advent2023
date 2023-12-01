
#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "day1.hpp"

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<pair<int, int>>(const pair<int,int>& p)
			{
				ostringstream ss;
				ss << "<" << p.first << ", " << p.second << ">" << endl;
				auto s = ss.str();
				return wstring(s.begin(), s.end());
			};
		}
	}
}

namespace advent2023
{
	TEST_CLASS(advent2023)
	{
	public:
		TEST_METHOD(sum_t)
		{
			vector<int> v1 = { 0, 1, 2, 3, 4, 5 };
			Assert::AreEqual(sum(v1), 15l);
		}
		TEST_METHOD(fmap_t)
		{
			vector<int> v1 = { 0, 1, 2, 3, 4, 5 };
			vector<int> expected = { 0, 1, 4, 9, 16, 25 };
			vector<int> res = fmap(v1, [](int i) {return i * i; });
			Assert::IsTrue(res == expected);
		}
		TEST_METHOD(day1_t)
		{
			auto d = Day1();
			
			Assert::AreEqual(d.mass(12), 2);
			Assert::AreEqual(d.mass(100756), 33583);
		}
		TEST_METHOD(day1)
		{
			auto d = Day1();
			auto p = d.day1("C:/users/neildick/source/repos/day1/1.txt");
			Assert::AreEqual(p, make_pair(3305115, 4954799));
		}
	};
}
