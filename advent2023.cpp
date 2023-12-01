
#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "day1.hpp"

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> std::wstring ToString<pair<int, int>>(const pair<int,int>& p)
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
		TEST_METHOD(day1)
		{
			Assert::Fail();
		}
		TEST_METHOD(day2)
		{
			Assert::Fail();
		}
		TEST_METHOD(day3)
		{
			Assert::Fail();
		}
		TEST_METHOD(day4)
		{
			Assert::Fail();
		}
		TEST_METHOD(day5)
		{
			Assert::Fail();
		}
		TEST_METHOD(day6)
		{
			Assert::Fail();
		}
		TEST_METHOD(day7)
		{
			Assert::Fail();
		}
		TEST_METHOD(day8)
		{
			Assert::Fail();
		}
		TEST_METHOD(day9)
		{
			Assert::Fail();
		}
		TEST_METHOD(day10)
		{
			Assert::Fail();
		}
		TEST_METHOD(day11)
		{
			Assert::Fail();
		}
		TEST_METHOD(day12)
		{
			Assert::Fail();
		}
		TEST_METHOD(day13)
		{
			Assert::Fail();
		}
		TEST_METHOD(day14)
		{
			Assert::Fail();
		}
		TEST_METHOD(day15)
		{
			Assert::Fail();
		}
		TEST_METHOD(day16)
		{
			Assert::Fail();
		}
		TEST_METHOD(day17)
		{
			Assert::Fail();
		}
		TEST_METHOD(day18)
		{
			Assert::Fail();
		}
		TEST_METHOD(day19)
		{
			Assert::Fail();
		}
		TEST_METHOD(day20)
		{
			Assert::Fail();
		}
		TEST_METHOD(day21)
		{
			Assert::Fail();
		}
		TEST_METHOD(day22)
		{
			Assert::Fail();
		}
		TEST_METHOD(day23)
		{
			Assert::Fail();
		}
		TEST_METHOD(day24)
		{
			Assert::Fail();
		}
		TEST_METHOD(day25)
		{
			Assert::Fail();
		}
	};
}
