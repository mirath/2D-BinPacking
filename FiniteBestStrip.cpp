using namespace std;
#include <cstdlib>
#include <utility>
#include "dataStructs.h"
#include "utils.h"

// Finite Best Strip

Packing FBS(vector <Item> &items, int Hbin, int Wbin) {

  // Sorting the items by nonincreasing height
  sort(items.begin(), items.end(), compareHeight);
  
  // Number of bins used so far
  int nbin = 0;
  // leftover width used to fit figure
  int wleft = Wbin;
  int nItems = items.size();

  vector <vector <Item > > strips;

  int nstrip = 0; // Number of strips used 

  // Setting all items to not visited
  for(int i = 0; i < nItems; i++) 
    items[i].visited = false;

  // At least one strip will have to be used
  strips.push_back(vector <Item>());

  bool assig = false;
  for(int i = 0; i < nItems; i++) {
    if (!items[i].visited) {
      if (items[i].width <= wleft) {
        // We add the item to the strip
        strips[nstrip].push_back(items[i]);
        wleft -= items[i].width;
      }
      else {
        // We need to look for other elements 
        // that might fit
        for(int k = i + 1; k < nItems; k++) {
          if (!items[k].visited) {
            if (items[k].width <= wleft) {
              // We add the item to the strip
              strips[nstrip].push_back(items[k]);
              wleft -= items[k].width;
              items[k].visited = true;
              assig = true;
              break;
            }
            continue; // We keep on checking til the end
          }
        }
        if (!assig) {
          // None of the elements fit, so we need 
          // to open up a new strip
          nstrip++;
          strips.push_back(vector <Item>());
          strips[nstrip].push_back(items[i]);
          wleft = Wbin;
          assig = false;
        }
      }
      
    }
  }
  Packing b = {1, {4,5},{4,5,6,false}};
  return; 
}
