#ifndef PLAYER_HPP__
#define PLAYER_HPP__

#include <iostream>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;

class Player
{
private:
  int startRow_;
  int startCol_;
  string facing_;

public:
  Player(int startRow, int startCol, string facing) : startRow_(startRow)
    , startCol_(startCol)
    , facing_(facing) {}

  static Player parse(boost::property_tree::ptree::value_type value)
  {
    return Player(value.second.get<int>("<xmlattr>.startrow"),
                  value.second.get<int>("<xmlattr>.startcol"),
                  value.second.get<string>("<xmlattr>.facing"));
  }

  void print()
  {
    cout << "Player { startRow: " << startRow_
         << ", startCol: " << startCol_
         << ", facing: " << facing_
         << " }" << endl;
  }
};

#endif
