#include "LocalSearch.h"
#include <limits>

Packing LocalSearch(vector<Item> items, int Hbin, int Wbin){
  int Tbin;
  Packing pack;
  pack = initialPacking(items);

  long max_iterations = 100000000; //cien millones
  long i = 0;

  register int k_in = 1;
  int k_out = 1;
  register int done = 0;
  register int useless = 0;

  while (i<max_iterations && done != 4){
    if (k_in == pack.binNum){
      if (useless == (k_in-1)){
    	done += 1;
      }
      else{
    	done = 0;
      }
      useless = 0;
      k_in = 1;
    }
    Tbin = targetBin(pack, Hbin, Wbin);
    k_out = HFirstBest(Tbin,&pack,Hbin,Wbin,k_in);
    if (k_out > k_in){
      if (k_in < pack.binNum)
	k_in += 1;
      useless += 1;
    }
    else{
      if (k_in != 1)
	k_in -= 1;
      useless = 0;
    }
    ++i;
  }
  cout << i <<"\n";
  return pack;
}

int targetBin(Packing pack, int Hbin, int Wbin){
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

  //Filling function
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

Packing initialPacking(vector<Item> items){
  Packing pack;
  Placement p;
  int i;
  int N = items.size();

  pack.binNum = N;
  for(i=0 ; i<N ; ++i){
    p = {i,{0,0},items[i]};
    pack.packing.push_back(p);
  }

  return pack;
}
