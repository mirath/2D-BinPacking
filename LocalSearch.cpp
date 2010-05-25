#include "LocalSearch.h"
#include <limits>
#include <list>


Packing LocalSearch(vector<Item> items, int Hbin, int Wbin, int which){
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
      if (div >= pack.binNum-1)
	div = 1; 
      else
	div += 1;
      Tbin = nthFilledBin(pack, &bins, Hbin, Wbin, div);

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
      Tbin = targetBin(pack, &bins, Hbin, Wbin);

    //===== para mejor mejor, cambiar HFirsBest por HBestBest ======//
    if (which == 0) 
      k_out = HFirstBest(Tbin,&pack,&bins,Hbin,Wbin,k_in);
    else 
      k_out = HBestBest(Tbin,&pack,&bins,Hbin,Wbin,k_in);
    //Si la cantidad de bins de salida es mayor a la de entrada
    //aumento la vecindad
    if (k_out > k_in) {
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



int targetBin(Packing pack, Bins* bins, int Hbin, int Wbin){
  int bin;
  int nbins = pack.binNum;
  double temp;

  double min = numeric_limits<double>::max();
  int minBin;

  //Por cada bin
  for(bin=0; bin<nbins; bin++){
    temp = filling(pack,bins,bin,Hbin,Wbin);
    if (min > temp){
      minBin = bin;
      min = temp;
    }
  }

  return minBin;
}

int nthFilledBin(Packing pack, Bins* bins, int Hbin, int Wbin, int N){
  int bin;
  int nbins = pack.binNum;
  list<double> binsFilling;

  //La funcion nthBinFill destruye la lista que recibe
  list<double> bins_toBeDestroyed;

  double fill;
  double nthBinFill;

  //Se crea una lista con los filling de los bins
  for(bin=nbins-1; bin>=0; bin--){
    fill = filling(pack,bins,bin,Hbin,Wbin);
    binsFilling.push_front(fill);
    bins_toBeDestroyed.push_front(fill);
  }

  //Calculo el valor del nth bin
  nthBinFill = nth(&bins_toBeDestroyed,N);
  
  //Debo buscar el valor del nth bin para devolver
  //su numero
  bin = linSlist(binsFilling,nthBinFill);

  return bin;
}

double filling(Packing pack, Bins* bins, int bin, int Hbin, int Wbin){
  double sigmaItems = 0;
  double sigmaItemsArea = 0;
  double alpha = 3.5;
  double V = Hbin*Wbin;

  Item* it;
  //double nitems = pack.packing.size();
  double nitems = bins->bins[bin]->size();
  int i;

  //cout << nitems<<"\n";
  //cout << "=========\n";
  //Por cada item
  // for(i=0; i<nitems; i++){
  //   //Si el item esta en el bin que se esta procesando
  //   if (pack.packing[i].bin == bin){
  //     it = &(pack.packing[i].item);
  //     cout << it->id <<"\n";
  //     sigmaItems += 1;
  //     sigmaItemsArea += (it->width)*(it->height);
  //   }
  // }

  // cout << sigmaItemsArea/V - sigmaItems/pack.packing.size() <<"\n"; 
  // cout << sigmaItemsArea <<"\n";
  //cout << "---------\n";

  //nitems = bins->bins[bin]->size();
  //sigmaItemsArea = 0;
  //Por cada item
  for(i=0; i<nitems; i++){
    it = &(bins->bins[bin]->at(i));
    //sigmaItems += 1;
    //cout << it->id <<"\n";
    sigmaItemsArea += (it->width)*(it->height);
  }

  // cout << sigmaItemsArea/V - nitems/pack.packing.size() <<"\n"; 
  // cout << sigmaItemsArea <<"\n";
  //cout << "=========\n";
  return sigmaItemsArea/V - nitems/pack.packing.size();
}

Packing* initialPacking(vector<Item> items, Packing* pack, Bins* bins){
  Placement p;
  vector<Item>* contents;
  int i;
  int N = items.size();

  pack->binNum = N;
  pack->packing.clear();
  bins->bins.resize(N);
  for(i=0 ; i<N ; ++i){
    contents = new vector<Item>;
    p = (Placement) {i,{0,0},items[i]};
    pack->packing.push_back(p);

    contents->push_back(items[i]);
    bins->bins[i] = contents;
  }

  return pack;
}
