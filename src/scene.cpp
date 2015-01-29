#include <iostream>
#include "scene.hpp"

using namespace std;

ostream& operator<<(ostream& os, const Scene& rhs)
{
  os << "Scene { name: " << rhs.name()
     << " }";

  return os;
}

