
//#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include "advent.hpp"

#include "day1.hpp"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
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
		TEST_METHOD(uf_t)
		{
			auto uf = UF(16);
			Assert::AreEqual(uf.count(), 16);
			uf.merge(5, 11);
			Assert::AreEqual(uf.count(), 15);
			uf.find(5);
			Assert::IsTrue(uf.connected(5, 11));
			
		}

		TEST_METHOD(fmap_t)
		{
			vector<int> v1 = { 0, 1, 2, 3, 4, 5 };
			vector<int> expected = { 0, 1, 4, 9, 16, 25 };
			vector<int> res = fmap(v1, [](int i) {return i * i; });
			Assert::IsTrue(res == expected);
		}
		TEST_METHOD(day1t)
		{
			auto d = Day1();
			auto p = d.do_p1("../../1t.txt");
			Assert::AreEqual(142, p);
		}
		TEST_METHOD(day1t2)
		{
			auto d = Day1();
			auto p = d.p2("../../1t2.txt");
			Assert::AreEqual(281, p);
		}
		TEST_METHOD(day1)
		{
			auto d = Day1();
			//int p = d.do_p1("../../1.txt");
			//Assert::AreEqual(54388, p);

			auto p = d.p2("../../1.txt");
			Assert::AreEqual(53515, p);

		}
		TEST_METHOD(day2)
		{
			auto d2 = Day2();
			auto res = d2.p1("../../2.txt");
			Assert::AreEqual(3059, res.first);
			Assert::AreEqual(65371, res.second);
		}
		TEST_METHOD(string_split) {
			string s("This is a string");
			auto res = split(s, " ");
			Assert::AreEqual(res[0], string("This"));
			Assert::AreEqual(res[1], string("is"));
			Assert::AreEqual(res[2], string("a"));
			Assert::AreEqual(res[3], string("string"));
		}
		TEST_METHOD(day2t)
		{
			auto d2 = Day2();
			auto res = d2.p1("../../2t.txt");
			Assert::AreEqual(8, res.first);
			Assert::AreEqual(2286, res.second);
		}
		TEST_METHOD(day3t) {
			auto d3 = Day3();
			auto r = d3.p1("../../3t.txt");
			Assert::AreEqual(4361, r.first);
			Assert::AreEqual(467835, r.second);

		}
		
		TEST_METHOD(day3)
		{
			auto d3 = Day3();
			auto r = d3.p1("../../3.txt");
			Assert::AreEqual(525119, r.first);
			Assert::AreEqual(76504829, r.second);
		}
		TEST_METHOD(day4)
		{
			Day4 d = Day4();
			int r = d.p1("../../4.txt");
			Assert::AreEqual(25010, r);
			r = d.p2("../../4.txt");
			Assert::AreEqual(9924412, r);

		}
		TEST_METHOD(day4t)
		{
			Day4 d = Day4();
			int r = d.p1("../../4t.txt");
			Assert::AreEqual(13, r);
			r = d.p2("../../4t.txt");
			Assert::AreEqual(30, r);

		}
		TEST_METHOD(day5t)
		{
			Day5 d = Day5();
			unsigned int p = d.p1("../../5t.txt");
			Assert::AreEqual(35u, p);
			p = d.p2("../../5t.txt");
			Assert::AreEqual(46u, p);
		}
		TEST_METHOD(day5)
		{
			Day5 d = Day5();
			unsigned int p = d.p1("../../5.txt");
			Assert::AreEqual(486613012u, p);
			p = d.p2("../../5.txt");
			Assert::AreEqual(0u, p);
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
