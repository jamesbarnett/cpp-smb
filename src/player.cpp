#include "player.hpp"

ostream& operator<<(ostream& os, const Player& rhs)
{
  os << "Player { startRow: " << rhs.startRow_
     << ", startCol: " << rhs.startCol_
     << ", facing: " << rhs.facing_
     << " }";

  return os;
}
