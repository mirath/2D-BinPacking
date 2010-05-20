#include "HFirstBest.h"

Packing _FBS(vector<Item>* i, int h, int w, Packing items){
  return items;
}

int HFirstBest(int Tbin, Packing items, int Hbin, int Wbin){
  //Parametros de la heuristica
  int n = items.binNum;
  int k = 1;
  long combs = comb((n-1),k);
  cout<<"combs:"<<combs<<"\n";
  if (combs > 100000)
    combs = combs* (long) (0.4);
  
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
  while ( i < items.packing.size() ) {
    //Inicializo las combinaciones de bins
    for(j=0;j<k;++j){
      arr[j]=j;
    }
    j = 0;
    //Ciclo a traves de las combinaciones
    while ((j < combs) && (items.packing[i].bin == Tbin)){
      //Solo si el objeto esta en el "target bin" lo proceso
      itemsToPack = getItems(arr,k,Tbin,items);
      itemsToPack->push_back(items.packing[i].item);
      pack = _FBS(itemsToPack,Hbin,Wbin,items);
      if (pack.binNum <= k){
	update(pack,items);
	return pack.binNum;
      }
      combinations(k,(n-1),arr);//Actualizo la combinacion
      j += 1;
    }
    i += 1;
  }
  return 0;
}

vector<Item>* getItems(int * b, int N, int forbiddenBin, Packing items){
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
  for(i=0;i<items.packing.size();++i){
    //Si esta dentro de las seleccionadas lo inserto
    if (linS(bins,N,items.packing[i].bin)){
      selectedItems->push_back(items.packing[i].item);
    }
  }

  delete bins;
  return selectedItems;
}

Packing update(Packing newPacking, Packing items){
  int i;
  int j;

  //Recorro los items
  for(i=0;i<items.packing.size();++i){
    if ((j=searchItem(newPacking.packing,items.packing[i].item.id)) != -1){
      items.packing[i].coord = newPacking.packing[j].coord;
      items.packing[i].bin = newPacking.packing[j].bin;
    }
  }

  return items;
}
