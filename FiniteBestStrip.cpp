using namespace std;
#include <cstdlib>
#include <utility>
#include <iostream>
#include <algorithm>
#include "utils.h"
#include "FiniteBestStrip.h"

// Finite Best Strip

Packing FBS(vector <Item> & items, int Hbin, int Wbin) {
  
  // Sorting the items by nonincreasing height
  sort(items.begin(), items.end(), compareHeight);

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
        pair<int,bool> search = search4others(items,wleft,
                                              i,nItems);
        if (search.second) {  // We found a candidate
          sset[nstrip].strip.push_back(items[search.first]);
          wleft -= items[search.first].width;
          items[search.first].visited = true;
          i -= 1; // We still need to allocate the ith
                  // element !.
        }
        else {
          // None of the elements fit, so we need 
          // to open up a new strip
          nstrip++;
          sset.push_back((Strip) {vector <Item>(), false});
          sset[nstrip].strip.push_back(items[i]);
          wleft = Wbin - items[i].width;
        }
      }
    }
  }

  Packing result = merge_strips(&sset, Hbin, Wbin);
  return result;
}

Packing merge_strips(vector<Strip>* sset, 
                     int Hbin, int Wbin) {

  int currBin = 0;
  vector<Placement> total;

  // for(int i = 0; i < sset.size(); i++) {
  //   cout << "strip " << i << endl;
  //   for(int k = 0; k < sset->at(i).strip.size(); k++) {
  //     cout << "id " << sset->at(i).strip[k].id;
  //   }
  // }
  
  int setSize = sset->size();
  total.reserve(setSize);
  int it = 0;
  genBin(currBin,&(sset->at(it).strip),&total);
  int currH = sset->at(it).strip[0].height; 
  it++;
  for(it; it < setSize ; it++) {
    if (!sset->at(it).visited) {
    // See if the strip fits
      if (sset->at(it).strip[0].height + currH > Hbin) {
        pair<int,bool> search;
        search = search4strips(it + 1, sset, currH, Hbin,setSize);
        if (! search.second) { // We found a candidate
          // No choice left, we have to open up a new bin
          currBin++;
          //total = total + genBin(currBin,&(sset->at(it).strip));
	  genBin(currBin,&(sset->at(it).strip),&total);
          currH = sset->at(it).strip[0].height;
        }
        else {
          int index = search.first;
          //total = total + 
	  putAbove(sset->at(index),currH, currBin, &total);
          currH += sset->at(index).strip[0].height;
          sset->at(index).visited = true;
          it--; // We still need to allocate the ith strip
        }
      }
      else { // We have to check for the others strips
        // The strip fits
        //total = total + putAbove(sset->at(it), currH, currBin);
	putAbove(sset->at(it), currH, currBin, &total);
        currH += sset->at(it).strip[0].height;
      }
    }
  }
  Packing result = {total, currBin + 1};
  return result;
}

vector<Placement>* genBin(int newBin, vector <Item>* bottom, vector<Placement>* total) {

  //vector<Placement> result;
  // Accumulated width
  int wacc = 0;
  vector<Item>::iterator it;
  for(it = bottom->begin(); it != bottom->end(); it++) {
    total->push_back((Placement) {newBin, {wacc ,0}, *it});
    wacc += (*it).width;
  }
  return total;
}

vector<Placement>* putAbove(Strip &s, int currH, 
                           int currBin, vector<Placement>* total) {
  vector<Item>::iterator it;
  vector<Placement> result;
  int wacc = 0; // Accumulated width
  for(it = s.strip.begin(); it != s.strip.end(); it++) {
    total->push_back((Placement) {currBin, {wacc, currH}, *it});
    wacc += (*it).width;
  }
  return total;
}

// Merges two Placement vectors.
vector<Placement> operator+(vector<Placement> a,
                                   vector<Placement> b) {
  vector<Placement>::iterator it;
  
  for(it = b.begin(); it != b.end(); it++)
    a.push_back(*it);
  
  return a;
}

pair<int, bool> search4others(vector<Item> items,
                              int wleft, int i, int nItems)
{
  for(int k = i + 1; k < nItems; k++) {
    if (!items[k].visited) {
      if (items[k].width <= wleft) {
        pair<int, bool> response(k, true);
        return response;
      }
    }
  }
  pair<int, bool> none(-1, false);
  return none;
}

pair<int,bool> search4strips(int k, vector<Strip>* sset,
                             int currH, int Hbin,
                             int setSize) {
  
  for(k; k < setSize; k++) {
    if (!sset->at(k).visited) {
      if (sset->at(k).strip[0].height + currH <= Hbin) {
        pair<int,bool> result;
        result.first = k;
        result.second = true;
        return result;
      }
    }
  }
  pair<int,bool> none;
  none.first = -1;
  none.second = false;
  return none;
}
