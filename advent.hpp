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
    if (x < width)
      n.push_back(make_pair(x+1, y));
    if (y > 0)
      n.push_back(make_pair(x, y-1));
    if (y < height)
      n.push_back(make_pair(x,y+1));
    return n;
  }
  char get(int x, int y) {return cmap[make_pair(x,y)];}
  char get(pair<int,int> coord) {return cmap[coord];}
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