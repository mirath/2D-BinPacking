#ifndef dataStructs
#define dataStructs
#include <vector>

struct Coord {
  int x;
  int y;
};

struct Item {
  int width;
  int height;
  int id;
  bool visited;
};

struct Placement {
  int bin;
  Coord coord;
  Item item;
};

struct Packing {
  vector<Placement> packing;
  int binNum;
};

struct Strip {
  vector<Item> strip;
  bool visited;
};

#endif
