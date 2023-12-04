#pragma once
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <set>
#include <numeric>
#include <sstream>
#include <cassert>
#include <regex>
using namespace std;

template <typename T>
long int sum(vector<T> x)
{
  return accumulate(x.begin(), x.end(), 0);
}

template <typename Container, typename Function>
Container fmap(const Container& c, Function f) {
    // Create a new container of the same type as the original
    Container result;
    // Reserve enough space for the result
    result.reserve(c.size());
    // Use std::transform to apply the function to each element
    // and insert the result into the new container
    std::transform(c.begin(), c.end(), std::back_inserter(result), f);
    // Return the new container
    return result;
}

static vector<string> split(string s, string tok) {
    // splits a string on a sub string and returns a vector of substrings
    vector<string> results;
    auto next = s.find(tok);
    while (next != string::npos) {
        auto ss = s.substr(0, next);
        results.push_back(ss);
        s = s.substr(next+1);
        next = s.find(tok);
    }
    results.push_back(s);
    return results;
}

class char_map
{
public:
  char_map() : width(0), height(0){};
  char_map(vector<string> &data) : width(0), height(0)
  {
    if (!data.empty())
    {
      width = data[0].size();
      height = data.size();
    }
    for (auto y_it = data.begin(); y_it != data.end(); ++y_it)
    {
      size_t y = distance(data.begin(), y_it);
      for (auto x_it = (*y_it).begin(); x_it != (*y_it).end(); ++x_it)
      {
        size_t x = distance((*y_it).begin(), x_it);

        cmap[make_pair(x, y)] = *x_it;
      }
    }
  }
  vector<pair<int,int>> neighbours(pair<int, int> coord) {
    // given a coord, return the neighbours
    int x = coord.first;
    int y = coord.second;
    vector<pair<int, int>> n;
    if (x > 0)
      n.push_back(make_pair(x-1, y));
    if (x + 1 < width)
      n.push_back(make_pair(x+1, y));
    if (y > 0)
      n.push_back(make_pair(x, y-1));
    if (y + 1 < height)
      n.push_back(make_pair(x,y+1));
    if (y > 0 && x > 0)
        n.push_back(make_pair(x-1, y - 1));
    if (y + 1 < height && x + 1 < width)
        n.push_back(make_pair(x + 1, y + 1));
    if (y + 1 < height && x > 0)
        n.push_back(make_pair(x - 1, y + 1));
    if (y > 0  && x + 1< width)
        n.push_back(make_pair(x + 1, y - 1));
    return n;
  }
  char get(int x, int y) {return cmap.at(make_pair(x,y));}
  char get(pair<int,int> coord) {return cmap.at(coord);}
  void pretty_print(void)
  {
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        char c = cmap[make_pair(x, y)];
        cout << c;
      }
      cout << endl;
    }
  }

  map<pair<size_t, size_t>, char> cmap;
  size_t width;
  size_t height;
};

class advent
{
public:

  advent(std::string path, const char delim = '\n') : f(path)
  {
    if (!f)
    {
      cout << "File not found : " << path << endl;
      exit(-1);
    }
    string s;
    while (getline(f, s, delim))
    {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
      raw_vec.push_back(s);
      try
      {
        int_vec.push_back(stoi(s));
      }
      catch (...)
      {
      }
    }
    vector<string> tmp;
    vector<int> tmp_i;
    auto last_it = prev(raw_vec.end());
    for (auto it = raw_vec.begin(); it != raw_vec.end(); ++it)
    {
      if (!it->empty())
        tmp.push_back(*it);
      if (it->empty() || it == last_it)
      {
        raw_multi.push_back(tmp);
        try
        {
          for (auto &i : tmp)
          {
            tmp_i.push_back(stoi(i));
          }
          int_multi.push_back(tmp_i);
          tmp_i.clear();
        }
        catch (...)
        {
        }
        tmp.clear();
      }
    }
    cmap = char_map(raw_vec);
  }

  vector<string> raw_vec;
  vector<int> int_vec;
  vector<vector<string>> raw_multi;
  vector<vector<int>> int_multi;
  char_map cmap;

private:
  ifstream f;
};

class UF {
	int* id, cnt, * sz;
public:
	// Create an empty union find data structure with N isolated sets.
	UF(int N) {
		cnt = N; id = new int[N]; sz = new int[N];
		for (int i = 0; i < N; i++)  id[i] = i, sz[i] = 1;
	}
	~UF() { delete[] id; delete[] sz; }

	// Return the id of component corresponding to object p.
	int find(int p) {
		int root = p;
		while (root != id[root])    root = id[root];
		while (p != root) { int newp = id[p]; id[p] = root; p = newp; }
		return root;
	}
	// Replace sets containing x and y with their union.
	void merge(int x, int y) {
		int i = find(x); int j = find(y); if (i == j) return;
		// make smaller root point to larger one
		if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
		else { id[j] = i, sz[i] += sz[j]; }
		cnt--;
	}
	// Are objects x and y in the same set?
	bool connected(int x, int y) { return find(x) == find(y); }
	// Return the number of disjoint sets.
	int count() { return cnt; }
};