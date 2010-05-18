using namespace std;
#include <cstdlib>
#include "dataStructs.h"
#include "utils.h"

// Finite Best Strip

Packing FBS(vector <Item> &items, int Hbin, int Wbin) {

  // Sorting the items by nonincreasing height
  qsort(items, nItems, sizeof(Item), compareHeight);
  
  // Number of bins used so far
  int nbin = 0;
  // leftover width used to fit figure
  int wleft = Wbin;

  list <list <pair <Item, Coord> > > strips;

  for(int i = 0; i < nItems; i++) {
    if (!items[i].visited) {
      if items[i].
    }
      
              
  }

  
  
  
  
  
  
  
  
  
  
  
  return; 
}
