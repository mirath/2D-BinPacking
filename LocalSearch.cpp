#include "LocalSearch.h"
#include <limits>
#include <list>


Packing LocalSearch(vector<Item> items, int Hbin, int Wbin){
  int Tbin;
  Packing pack;
  Bins bins;
  Packing bestPack;
  initialPacking(items,&pack,&bins);
  bestPack = pack;

  long max_iterations = 10000; //diez mil
  long i = 0;

  register int k_in = 1;
  int k_out = 1;

  //Cuando esto llegue a 4, me salgo.
  register int done = 0;

  //Numero de veces seguidas que no se
  //se ha logrado mejorar la solucion
  register int useless = 0;

  register int div = 1; //Parametro de diversificacion

  //Ciclo principal
  while (i<max_iterations && done != 4){
    //Si la vecindad ya es muy grande
    if (k_in == pack.binNum){
      //Diversifico
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

    //===== para mejor mejor, cambiar HFirsBest por HBestBest ======//
    k_out = HFirstBest(Tbin,&pack,&bins,Hbin,Wbin,k_in);
    //Si la cantidad de bins de salida es mayor a la de entrada
    //aumento la vecindad
    if (k_out > k_in){
      if (k_in < pack.binNum)
	k_in += 1;
      useless += 1;
    }
    //Si la cantidad de bins de salida es menor o igua a la de entrada
    //la tomo
    else{
      bestPack = pack; //Actualizo mejor hasta el momento
      if (k_in != 1)
	k_in -= 1;
      useless = 0;
    }
    ++i;
  }

  cout << "Iteraciones: " << i << "\n";
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

  return minBin;
}

int nthFilledBin(Packing pack, int Hbin, int Wbin, int N){
  int bin;
  int nbins = pack.binNum;
  list<double> bins;

  //La funcion nthBinFill destruye la lista que recibe
  list<double> bins_toBeDestroyed;

  double fill;
  double nthBinFill;

  //Se crea una lista con los filling de los bins
  for(bin=nbins-1; bin>=0; bin--){
    fill = filling(pack,bin,Hbin,Wbin);
    bins.push_front(fill);
    bins_toBeDestroyed.push_front(fill);
  }

  //Calculo el valor del nth bin
  nthBinFill = nth(&bins_toBeDestroyed,N);
  
  //Debo buscar el valor del nth bin para devolver
  //su numero
  bin = linSlist(bins,nthBinFill);

  return bin;
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
    //Si el item esta en el bin que se esta procesando
    if (pack.packing[i].bin == bin){
      it = &(pack.packing[i].item);
      sigmaItems += 1;
      sigmaItemsArea += (it->width)*(it->height);
    }
  }

  return sigmaItemsArea/V - sigmaItems/nitems;
}

Packing* initialPacking(vector<Item> items, Packing* pack, Bins* bins){
  Placement p;
  vector<Item> contents;
  int i;
  int N = items.size();

  pack->binNum = N;
  pack->packing.clear();
  bins->bins.reserve(N);
  for(i=0 ; i<N ; ++i){
    p = (Placement) {i,{0,0},items[i]};
    pack->packing.push_back(p);

    contents.push_back(items[i]);
    bins->bins[i] = contents;
    contents.clear();
  }

  return pack;
}
