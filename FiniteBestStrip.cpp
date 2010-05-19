using namespace std;
#include <cstdlib>
#include <utility>
#include <algorithm>
#include "utils.h"
#include "FiniteBestStrip.h"

// Finite Best Strip

Packing FBS(vector <Item> &items, int Hbin, int Wbin) {
  
  // Sorting the items by nonincreasing height
  //  sort(items.begin(), items.end(), compareHeight);

  // Number of bins used so far
  int nbin = 0;
  // leftover width used to fit figure
  int wleft = Wbin;
  int nItems = items.size();

  vector<Strip> sset; // Strip set 

  int nstrip = 0; // Number of strips used 

  // Structure initialization
  init_visited(items);

  // At least one strip will have to be used
  sset.push_back((Strip){vector<Item>(), false});

  bool assig = false;
  for(int i = 0; i < nItems; i++) {
    if (!items[i].visited) {
      if (items[i].width <= wleft) {
        // We add the item to the strip
        sset[nstrip].strip.push_back(items[i]);
        wleft -= items[i].width;
      }
      else {
        // We need to look for other elements 
        // that might fit
        for(int k = i + 1; k < nItems; k++) {
          if (!items[k].visited) {
            if (items[k].width <= wleft) {
              // We add the item to the strip
              sset[nstrip].strip.push_back(items[k]);
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
          sset.push_back((Strip) {vector <Item>(), false});
          sset[nstrip].strip.push_back(items[i]);
          wleft = Wbin;
          assig = false;
        }
      }
    }
  }

  Packing result = merge_strips(sset, Hbin, Wbin);
  return result;
}

Packing merge_strips(vector<Strip> &sset, 
                     int Hbin, int Wbin) {

  int currBin = 0;
  vector<Placement> total; 
  vector<Strip>::iterator it;
  it = sset.begin();
  total = total + genBin(currBin,(*it).strip);
  int currH = (*it).strip[0].height; 
  it++;
  bool assig = false;
  for(it; it != sset.end(); it++) {
    if (!(*it).visited) {
    // See if the strip fits
      if ((*it).strip[0].height + currH <= Hbin) {
        // The strip fits
        total = total + putAbove(*it, currH, currBin);
        currH += (*it).strip[0].height;
      }
      else { // We have to check for the others strips
        vector<Strip>::iterator k;
        for(k = it; k != sset.end(); it++) {
          if (!(*k).visited) {
            if ((*k).strip[0].height + currH <= Hbin) {
              total = total + putAbove(*k,currH, currBin);
              currH += (*k).strip[0].height;
              assig = true;
              break;
            }
            else continue;
          }
        }
        if (!assig) {
          // No choice left, we have to open up a new bin
          currBin++;
          total = total + genBin(currBin,(*it).strip);
          currH = (*it).strip[0].height;
          assig = false;
        }
      }
    }
  }
  Packing result = {total, currBin + 1};
  return result;
}

vector<Placement> genBin(int newBin, vector <Item> bottom) {

  vector<Placement> result;
  // Accumulated width
  int wacc = 0;
  vector<Item>::iterator it;
  for(it = bottom.begin(); it != bottom.end(); it++) {
    result.push_back((Placement) {newBin, {wacc ,0}, *it});
    wacc +=  (*it).width;
  }
  return result;
}

vector<Placement> putAbove(Strip &s, int currH, 
                           int currBin) {
  vector<Item>::iterator it;
  vector<Placement> result;
  int wacc = 0; // Accumulated width
  for(it = s.strip.begin(); it != s.strip.end(); it++) {
    result.push_back((Placement) {currBin, {wacc, currH}, *it});
    wacc += (*it).width;
  }
  return result;
}

// Merges two Placement vectors.
vector<Placement> operator+(vector<Placement> a,
                                   vector<Placement> b) {
  vector<Placement>::iterator it;
  
  for(it = b.begin(); it != b.end(); it++)
    a.push_back(*it);
  
  return a;
}

