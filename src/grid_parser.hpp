#ifndef GRID_PARSER_HPP__
#define GRID_PARSER_HPP__

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

class GridParser
{
private:
  size_t rowIndex_;
  vector<vector<int>> grid_;

public:
  GridParser() : rowIndex_(0), grid_(vector<vector<int>>()) {}

private:
  vector<int> parseRow(const vector<string>& ids)
  {
    // cout << "grid size: " << grid_.size() << endl;
    if (grid_.size() <= rowIndex_)
    {
      grid_.push_back(vector<int>());

      // for (auto id : grid_[rowIndex_])
      // {
      //   grid_[rowIndex_].push_back(parseElement(id));
      // }

      ++rowIndex_;
    }

    return vector<int>();
  }
  
  int parseElement(const string& el)
  {
    return boost::lexical_cast<int>(el);
  }
};

#endif
