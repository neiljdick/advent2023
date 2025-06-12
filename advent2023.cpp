
//#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include "advent.hpp"

#include "day1.hpp"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include "Day6.h"
#include "Day7.h"
#include "Day8.h"
#include "Day10.h"

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
			int64_t p = d.p1("../../5t.txt");
			Assert::AreEqual(35ll, p);
			p = d.p2("../../5t.txt");
			Assert::AreEqual(46ll, p);
		}
		TEST_METHOD(day5)
		{
			Day5 d = Day5();
			int64_t p = d.p1("../../5.txt");
			Assert::AreEqual(486613012ll, p);
			Day5 d2 = Day5();
			p = d2.p2("../../5.txt");
			Assert::AreEqual(56931769ll, p);
		}
		TEST_METHOD(day6t)
		{
			Day6 d = Day6("../../6t.txt");
			int64_t p = d.p1();
			Assert::AreEqual(288ll, p);
			d = Day6("../../6t-2.txt");
			p = d.p1();
			Assert::AreEqual(71503ll, p);

		}
		TEST_METHOD(day6)
		{
			Day6 d = Day6("../../6.txt");
			int64_t p = d.p1();
			Assert::AreEqual(5133600ll, p);
			d = Day6("../../6.2.txt");
			p = d.p1();
			Assert::AreEqual(40651271ll, p);
		}
		TEST_METHOD(day7t)
		{
			Day7 d = Day7("../../7t.txt");
			int64_t p1 = d.p1();
			//Assert::AreEqual(6440ll, p1);
			Assert::AreEqual(5905ll, p1); // part2 
			Assert::AreEqual(d.hand_score("AAAAA"), 7);
			Assert::AreEqual(d.hand_score("AA8AA"), 6);
			Assert::AreEqual(d.hand_score("23332"), 5);
			Assert::AreEqual(d.hand_score("TTT98"), 4);
			Assert::AreEqual(d.hand_score("23432"), 3);
			Assert::AreEqual(d.hand_score("A23A4"), 2);
			Assert::AreEqual(d.hand_score("23456"), 1);
			Assert::AreEqual(d.hand_score_fn(make_pair("33332", 0), make_pair("2AAAA", 0)), false);
			Assert::AreEqual(d.hand_score_fn(make_pair("77888", 0), make_pair("77788", 0)), false);
		}
		TEST_METHOD(day7)
		{
			Day7 d = Day7("../../7.txt");
			int64_t p1 = d.p1();
			//Assert::AreEqual(248396258ll, p1);
			Assert::AreEqual(246436046ll, p1);
		}
		TEST_METHOD(day8t)
		{
			Day8::Day8 d = Day8::Day8("../../8t.txt");
			int p1 = d.p1();
			Assert::AreEqual(2, p1);
			d = Day8::Day8("../../8t2.txt");
			p1 = d.p1();
			Assert::AreEqual(6, p1);
			Day8::Day8("../../8t3.txt");
			p1 = d.p2();
			Assert::AreEqual(6, p1);
		}
		TEST_METHOD(day8)
		{
			Day8::Day8 d = Day8::Day8("../../8.txt");
			int p1 = d.p1();
			Assert::AreEqual(16897, p1);
			int64_t p2 = d.p2();
			Assert::AreEqual(16897ll, p2);
		}
		TEST_METHOD(day9)
		{
			Assert::Fail();
		}
		TEST_METHOD(day10t)
		{
			Day10::Day10 d = Day10::Day10("../../10t.txt");
			int p1 = d.p1();
			Assert::AreEqual(8, p1);
			int64_t p2 = d.p2();
			// Assert::AreEqual(expected_value, p2);
		}
		TEST_METHOD(day10)
		{
			Day10::Day10 d = Day10::Day10("../../10.txt");
			int p1 = d.p1();
			// TODO: Update expected values when implementing solution
			Assert::AreEqual(6956, p1);
			int64_t p2 = d.p2();
			// Assert::AreEqual(expected_value, p2);
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
