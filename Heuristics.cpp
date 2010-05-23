#include "Heuristics.h"

vector<Item>* getItems(int * b, int N, int forbiddenBin, Packing* items,Bins* bins){
  int * selectedBins = new int[N];
  vector<Item>* selectedItems = new vector<Item>;
  int binSize;
  int i;
  int j;

  // Debo quitar el forbiddenBin
  //si quedo seleccionado 
  for(i=0;i<N;i++){
    selectedBins[i] = b[i];
    if (selectedBins[i] >= forbiddenBin)
      selectedBins[i] += 1;
  }
  

  //Recorro los bins
  for(i=0;i<N;++i){
    binSize = bins->bins.size();
    for(j=0;j<binSize;++j) 
      selectedItems->push_back(bins->bins[i][j]);
  }
  // //Recorro los items
  // for(i=0;i<items->packing.size();++i){
  //   //Si esta dentro de las seleccionadas lo inserto
  //   if (linS(selectedBins,N,items->packing[i].bin)){
  //     selectedItems->push_back(items->packing[i].item);
  //   }
  // }

  delete [] selectedBins;
  return selectedItems;
}

Packing* update(Packing newPacking, Packing* items, Bins* bins, int * b, int N, int Tbin){
  int i;
  int j;
  int bin;

  int * selectedBins = new int[N];
  // Debo quitar el Tbin
  //si quedo seleccionado 
  for(i=0;i<N;i++){
    selectedBins[i] = b[i];
    if (selectedBins[i] >= Tbin)
      selectedBins[i] += 1;

    bins->bins[selectedBins[i]].clear();
  }

  // //Recorro los items
  // for(i=0;i<items->packing.size();++i){
  //   if ((j=searchItem(newPacking.packing,items->packing[i].item.id)) != -1){
  //     items->packing[i].coord = newPacking.packing[j].coord;
  //     items->packing[i].bin = bins[newPacking.packing[j].bin];
  //   }
  // }

  for(i=0;i<items->packing.size();++i){
    if ((j=searchItem(newPacking.packing,items->packing[i].item.id)) != -1){
      bin = selectedBins[newPacking.packing[j].bin];

      items->packing[i].coord = newPacking.packing[j].coord;
      items->packing[i].bin = bin;
      bins->bins[bin].push_back(newPacking.packing[j].item);
    }
  }

  //Reviso si el Tbin todavia tiene elementos
  if (searchBin(items->packing,Tbin) == -1){
    items->binNum -= 1;

    for(i=0;i<items->packing.size();++i){
      if (items->packing[i].bin > Tbin){
	items->packing[i].bin -= 1;
      }
    }
  }

  delete [] selectedBins;
  return items;
}

Packing* breakTie(Packing* a, Packing* b, int Hbin, int Wbin){
  int binsArea = Hbin*Wbin;
  int itemsAreaA = 0;
  int itemsAreaB = 0;
  vector<Placement> itemsA = a->packing;
  vector<Placement> itemsB = b->packing;
  int nItemsA = a->packing.size();
  int nItemsB = b->packing.size();

  int i;
  Item* it;
  
  for(i=0; i<nItemsA; i++){
    it = &(itemsA[i].item);
    itemsAreaA += (it->width)*(it->height);
  }

  for(i=0; i<nItemsB; i++){
    it = &(itemsB[i].item);
    itemsAreaB += (it->width)*(it->height);
  }

  if (binsArea/itemsAreaB < binsArea/itemsAreaA)
    return b;
  else
    return a;
} 
