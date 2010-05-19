#include "LocalSearch.h"
#include <limits>

Packing LocalSearch(vector<Item> items, int Hbin, int Wbin){
  int Tbin;
  Packing pack;
  pack = initialPacking();

  while (parate()){
    Tbin = targetBin();
    HFirstBest(Tbin,pack,Hbin,Wbin);
  }
}

int filling(Packing pack, int Hbin, int Wbin){
  Item* it;
  int sigmaItems = 0;
  int sigmaItemsArea = 0;
  int i;
  int nitems = pack.packing.size();
  int j;
  int nbins = pack.binNum;

  int min = numeric_limits<int>::min();
  int alpha = 1;
  int V = Hbin*Wbin;
  int minBin;

  for(j=0; j<nbins; j++){
    for(i=0; i<nitems; i++){
      if (pack.packing[i].bin == j){
	it = &(pack.packing[i].item);
	sigmaItems += 1;
	sigmaItemsArea += (it->width)*(it->height);
      }
    }
    if (min > sigmaItemsArea/V - sigmaItems/nitems){
      minBin = j;
    }
    sigmaItems = 0;
    sigmaItemsArea = 0;
  }

  return j;
}

int targetBin(Packagin pack){
  

}
