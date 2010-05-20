#include "Heuristics.h"

Packing _FBS(vector<Item>* i, int h, int w, Packing items){
  return items;
}

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

  if (binsArea-itemsAreaB < binsArea-itemsAreaA)
    return b;
  else
    return a;
} 
