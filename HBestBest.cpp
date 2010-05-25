#include "Heuristics.h"
#include <limits>

int HBestBest(int Tbin, Packing* items,Bins* bins, int Hbin, int Wbin, int k){
  //Parametros de la heuristica
  int n = items->binNum;
  long combs = comb((n-1),k);
  if (combs > 100000)
    combs = combs*(0.4);
  
  //Variables temporales de la heuristica
  Packing pack; //Packing actual
  Packing* bestPack = new Packing;//Mejor packing hasta el momento
  vector<Item> *itemsToPack;
  bestPack->binNum = numeric_limits<int>::max();
  
  //Parametros de control
  int i = 0;
  long j = 0;
  int l = 0;
  int* arr = new int[k]; //combinaciones de bins
  int bestBinNum;
  int binNum;

  i=0;
  //Mientras me queden objetos
  while ( i < items->packing.size() ) {
    //Solo si el objeto esta en el "target bin" lo proceso
    if (items->packing[i].bin == Tbin){
      //Inicializo las combinaciones de bins
      for(j=0;j<k;++j){
        arr[j]=j;
      }
      j = 0;
      //Ciclo a traves de las combinaciones
      while (j < combs){
        itemsToPack = getItems(arr,k,Tbin,items,bins);
        itemsToPack->push_back(items->packing[i].item);
        pack = FBS(*itemsToPack,Hbin,Wbin);
        
        bestBinNum = bestPack->binNum;
        binNum = pack.binNum;

        //Si consegui una mejor solucion la guardo en
        //bestPack
        if (bestBinNum > binNum){
          bestPack = &pack;
        }
        //En caso de emptate, se debe romper el empate
        else if (bestBinNum == binNum){
          bestPack = breakTie(bestPack,&pack,Hbin,Wbin);
        }
        
        combinations(k,(n-1),arr);//Actualizo la combinacion
        j += 1;
      }
    }
    i += 1;
  }
  
  //Si logre mejorar, devuelvo bestPack
  if (bestPack->binNum <= k){
    update(*bestPack,items,bins,arr,k,Tbin);

    delete arr;
    return bestPack->binNum;
  }
  else{
    delete arr;

    //Falle en hallar algo mejor, k+1 se asegura que
    //el valor de retorno sea mayor que el de 
    return k+1;
  }
}
