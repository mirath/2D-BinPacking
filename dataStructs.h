#ifndef dataStructs
#define dataStructs
using namespace std;
#include <vector>

struct Coord {
  int x;
  int y;
};

struct Placement {
  int bin;
  Coord z;
};

struct Packing {
  vector <Placement> p;
};

struct Item {
  int width;
  int height;
};

#endif
