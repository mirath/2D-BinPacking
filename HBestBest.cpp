#include "Heuristics.h"
#include <limits>

int HBestBest(int Tbin, Packing* items, int Hbin, int Wbin, int k){
  //Parametros de la heuristica
  int n = items->binNum;
  long combs = comb((n-1),k);
  if (combs > 100000)
    combs = combs*(0.4);
  
  //Variables temporales de la heuristica
  Packing pack;
  Packing* bestPack;
  vector<Item> *itemsToPack;
  bestPack->binNum = numeric_limits<int>::max();
  int itemsArea = 0;
  int binsArea = Hbin*Wbin;
  int bestBinNum;
  int binNum;
  
  //Parametros de control
  int i = 0;
  long j = 0;
  int l = 0;
  int* arr = new int[k]; //combinaciones de bins
    
  i=0;
  //Mientras me queden objetos
  while ( i < items->packing.size() ) {
    //Inicializo las combinaciones de bins
    for(j=0;j<k;++j){
      arr[j]=j;
    }
    j = 0;
    //Ciclo a traves de las combinaciones
    while ((j < combs) && (items->packing[i].bin == Tbin)){
      //Solo si el objeto esta en el "target bin" lo proceso
      itemsToPack = getItems(arr,k,Tbin,items);
      itemsToPack->push_back(items->packing[i].item);
      pack = _FBS(itemsToPack,Hbin,Wbin,*items);
      
      bestBinNum = bestPack->binNum;
      binNum = pack.binNum;

      if (bestBinNum > binNum){
	bestPack = &pack;
      }
      else if (bestBinNum == binNum){
	bestPack = breakTie(bestPack,&pack,Hbin,Wbin);
      }

      combinations(k,(n-1),arr);//Actualizo la combinacion
      j += 1;
    }
    i += 1;
  }

  delete arr;
  if (bestPack->binNum <= k){
    update(*bestPack,items);
    return bestPack->binNum;
  }
  else
    return k+1;
}
