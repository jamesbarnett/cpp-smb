#include <iostream>
#include "sound.hpp"

using namespace std;

ostream& operator<<(ostream& os, const Sound& rhs)
{
  os << "Sound { name: " << rhs.name_
     << " res: " << rhs.res_
     << " } ";

  return os;
}
