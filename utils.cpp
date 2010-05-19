#include "utils.h"

bool compareHeight(Item a, Item b) {
  // We add the outer minus sign to get nonincreasing 
  // ordering.
  return (a.height >= b.height);
}

void init_visited(vector <Item> &items) {
  // Setting all items to not visited
  for(int i = 0; i < nItems; i++) 
    items[i].visited = false;
}

void init_coord(vector <Item> &items) {
  vector<Item>::iterator it;
  for(it = items.begin(); it != items.end(); it++) {
    (*it).coord.x = 0;
    (*it).coord.y = 0;
  }
}

void init_vi_strip(vector <Strip> &sset) {
  vector<vector<Item> > p = sset.strips;
  vector<Item>::iterator it;
}
