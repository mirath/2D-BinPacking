#include "LocalSearch.h"
#include <limits>
#include <list>

Packing LocalSearch(vector<Item> items, int Hbin, int Wbin){
  int Tbin;
  Packing pack;
  Packing bestPack;
  pack = initialPacking(items);
  bestPack = pack;

  long max_iterations = 10000; //diez mil
  long i = 0;

  register int k_in = 1;
  int k_out = 1;
  register int done = 0;
  register int useless = 0;
  register int div = 1;

  while (i<max_iterations && done != 4){
    if (k_in == pack.binNum){

      Tbin = nthFilledBin(pack, Hbin, Wbin, div);
      if (div == pack.binNum-1)
	div = 1; 
      else
	div += 1;

      if (useless == (k_in-1)){
    	done += 1;
      }
      else{
    	done = 0;
      }
      useless = 0;
      k_in = 1;
    }
    else
      Tbin = targetBin(pack, Hbin, Wbin);
    k_out = HFirstBest(Tbin,&pack,Hbin,Wbin,k_in);
    if (k_out > k_in){
      if (k_in < pack.binNum)
	k_in += 1;
      useless += 1;
    }
    else{
      bestPack = pack;
      if (k_in != 1)
	k_in -= 1;
      useless = 0;
    }
    ++i;
  }
  return bestPack;
}



int targetBin(Packing pack, int Hbin, int Wbin){
  int bin;
  int nbins = pack.binNum;
  double temp;

  double min = numeric_limits<double>::max();
  int minBin;

  //Por cada bin
  for(bin=0; bin<nbins; bin++){
    temp = filling(pack,bin,Hbin,Wbin);
    if (min > temp){
      minBin = bin;
      min = temp;
    }
  }

  //cout << minBin<<"\n";
  return minBin;
}

int nthFilledBin(Packing pack, int Hbin, int Wbin, int N){
  int bin;
  int nbins = pack.binNum;
  list<double> bins;
  list<double> bins_toBeDestroyed;
  double fill;
  double nthBinFill;

  //Se crea una lista con los filling de los bins
  for(bin=nbins-1; bin>=0; bin--){
    fill = filling(pack,bin,Hbin,Wbin);
    bins.push_front(fill);
    bins_toBeDestroyed.push_front(fill);
  }

  nthBinFill = nth(&bins_toBeDestroyed,N);

  return linSlist(bins,nthBinFill);
}

double filling(Packing pack, int bin, int Hbin, int Wbin){
  double sigmaItems = 0;
  double sigmaItemsArea = 0;
  double alpha = 3.5;
  double V = Hbin*Wbin;

  Item* it;
  double nitems = pack.packing.size();
  int i;

  //Por cada item
  for(i=0; i<nitems; i++){
    if (pack.packing[i].bin == bin){
      it = &(pack.packing[i].item);
      sigmaItems += 1;
      sigmaItemsArea += (it->width)*(it->height);
    }
  }

  //cout << sigmaItemsArea/V - sigmaItems/nitems <<"\n";
  return sigmaItemsArea/V - sigmaItems/nitems;
}

Packing initialPacking(vector<Item> items){
  Packing pack;
  Placement p;
  int i;
  int N = items.size();

  pack.binNum = N;
  for(i=0 ; i<N ; ++i){
    p = (Placement) {i,{0,0},items[i]};
    pack.packing.push_back(p);
  }

  return pack;
}
