#include <iostream>
#include "level_data.hpp"

ostream& operator<<(ostream& os, const LevelData& rhs)
{
  os << "LevelData { id: " << rhs.id_
     << " rows: " << rhs.rows_
     << " cols: " << rhs.columns_
     << " }";

  return os;
}
