#include "Heuristics.h"

int HFirstBest(int Tbin, Packing* items, Bins* bins, int Hbin, int Wbin, int k){
  //Parametros de la heuristica
  int n = items->binNum;
  long combs = comb((n-1),k);
  if (combs > 100000)
    combs = (long)combs*(0.4);
  
  //Variables temporales de la heuristica
  Packing pack;
  vector<Item> *itemsToPack;
  
  //Parametros de control
  int i = 0;
  long j = 0;
  int l = 0;
  int* arr = new int[k]; //combinaciones de bins
    
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
	//Si logre poner todos los objetos en k bins o menos
	//tomo la solucion
	delete itemsToPack;
	if (pack.binNum <= k){
	  update(pack,items,bins,arr,k,Tbin);
	  delete [] arr;
	  return pack.binNum;
	}
	combinations(k,(n-1),arr);//Actualizo la combinacion
	j += 1;
      }
    }
    i += 1;
  }
  
  delete [] arr;

  //Falle en hallar algo mejor, k+1 se asegura que
  //el valor de retorno sea mayor que el de entrada
  return k+1;
}
