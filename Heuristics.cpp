#include "Heuristics.h"

vector<Item>* getItems(int * b, int N, int forbiddenBin, Packing* items){
  int * bins = new int[N];
  vector<Item>* selectedItems = new vector<Item>;
  int i;

  // Debo quitar el forbiddenBin
  //si quedo seleccionado 
  for(i=0;i<N;i++){
    bins[i] = b[i];
    if (bins[i] >= forbiddenBin)
      bins[i] += 1;
  }
  

  //Recorro los items
  for(i=0;i<items->packing.size();++i){
    //Si esta dentro de las seleccionadas lo inserto
    if (linS(bins,N,items->packing[i].bin)){
      selectedItems->push_back(items->packing[i].item);
    }
  }

  delete bins;
  return selectedItems;
}

Packing* update(Packing newPacking, Packing* items){
  int i;
  int j;

  //Recorro los items
  for(i=0;i<items->packing.size();++i){
    if ((j=searchItem(newPacking.packing,items->packing[i].item.id)) != -1){
      items->packing[i].coord = newPacking.packing[j].coord;
      items->packing[i].bin = newPacking.packing[j].bin;
    }
  }

  return items;
}
