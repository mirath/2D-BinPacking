using namespace std;
#include "TabuSearch.h"

Packing TabuSearch(vector<Item> &items, int Wbin, int Hbin) {
  Packing opt = FBS(items, Hbin, Wbin);
  int z_star = opt.binNum;
  int nItems = items.size();
  int z = nItems;
  int lowb = lowerBound(nItems,items, Wbin, Hbin);
  if (opt.binNum == lowb) return opt;
  // Packing each item into a separate bin
  Packing fsol = initialPacking(items);
  // z = n tabu search solution ??
  // Target Bin
  int Tbin = targetBin(fsol, Hbin, Wbin);
  int d = 1;
  int max_iterations = MAX_IT; // diez mil
  bool diversify;
  int k_in;
  int k; // neighbourhood
  while(max_iterations >= 0) {
    diversify = false;
    k = 1;
    while(!diversify && z_star > lowb) {
      k_in = k;
      //      fsol = searchtabu(Tbin, k, diversify,z, fsol);
      fsol.binNum = z;
      z_star = min(z_star, z);
      if (k <= k_in) {
        // We determine the new target bin
        Tbin = targetBin(fsol, Hbin, Wbin);
      }
    }
    if (z_star == lowb) return fsol;
    else diversification(d, z, Tbin);
  }
}

Packing searchtabu(int &Tbin, int &k, bool &diversify,
                   int &z, Packing &fsol, int Hbin,
                   int Wbin, vector<Triple> &tenure,
                   vector<Triple> tlist) {

  int penalty_star = INFINITY;
  int penalty;
  int nPacks = fsol.packing.size();
  Packing candidate;
  // Outer loop, for each j in target bin.
  Item j;
  int nBins = fsol.binNum - 1; // Excluding Tbin
  long combs = comb(nBins,k);
  vector<Item> S;
  if (combs > 10000) 
    combs = combs * (long) (0.4);
  // Trivial combination 
  int * arr = new int[k];
  for(int c = 0; c < k; c++) {
    if (c >= Tbin) arr[c] = c + 1;
    else arr[c] = c;
  }
  for(int i = 0; i < nPacks; i++) {
    // We only want those j in target bin.
    if (fsol.packing[i].bin == Tbin) {
      S = buildS(fsol.packing[i].item,fsol,arr,k,nPacks);
      penalty = INFINITY;
      candidate = FBS(S, Hbin, Wbin);
      int evalH = fsol.binNum;
      if (evalH < k) {
        fsol = candidate;
        z = candidate.binNum;
        k = max(1, k-1);
        return fsol;
      }
      else if (evalH == k) {
        if (true) {
          fsol = candidate;
          return fsol;
        }
      }
    }
  }
}

void diversification(int d, int z, int Tbin) {
  return;
}

int lowerBound(int nItems, vector<Item> &items, int Wbin,
               int Hbin) {
  int x;
  int y;
  int tot1 = 0;
  int tot2 = Wbin;
  int value;
  int lb;
  for(int i = 0; i < nItems; i++) {
    y = items[i].width;
    y *= items[i].height;
    tot1 += y;
  }
  tot2 *= Hbin;
  value = tot1 / tot2;
  lb = (int) value;
  if (value - (double) lb > EPS) 
    lb++;
  return lb;
}

vector<Item> buildS(Item it, Packing fsol, int * arr, 
                    int k, int nPacks) {
  vector<Item> result;
  result.push_back(it);
  for(int bin = 0; bin < k; bin++) {
    for(int j = 0; j < nPacks; j++) {
      if (fsol.packing[j].bin == bin) 
        result.push_back(fsol.packing[j].item);
    }
  }
  return result;
}
