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
  Coord coord;
  Item item;
};

struct Packing {
  vector <Placement> packing;
  int binNum;
};

struct Item {
  int width;
  int height;
  int id;
  bool visited;
};

#endif
