#ifndef dataStructs
#define dataStructs
#include <vector>
using namespace std;

struct Item {
  int width;
  int height;
  int id;
  bool visited;
};

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
  vector<Placement> packing;
  int binNum;
};

struct Bins {
  vector<vector<Item>*> bins;
};

struct Strip {
  vector<Item> strip;
  bool visited;
};
#endif
