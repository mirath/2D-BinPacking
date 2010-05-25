using namespace std;
#include "TabuSearch.h"

Packing TabuSearch(vector<Item> &items, int Wbin, int Hbin) {
  Packing opt = FBS(items, Hbin, Wbin);
  int z_star = opt.binNum;
  int nItems = items.size();
  int z = nItems;
  int lowb = lowerBound(nItems,items, Wbin, Hbin);
  lowb++;
  if (opt.binNum == lowb) return opt;
  // Packing each item into a separate bin
  Packing fsol = initialPacking(items);
  // Target Bin
  int Tbin = targetBin(fsol, Hbin, Wbin);
  int d = 0;
  int max_iterations = MAX_IT; // diez mil
  bool diversify;
  int k_in;
  // At least one element in tabulist
  int k; // neighbourhood
  vector<vector<Triple> > tlist(3); // TabuList
  while(max_iterations >= 0) {
    diversify = false;
    k = 1;
    while(!diversify && z_star > lowb) {
      k_in = k;
      searchtabu(Tbin, k, diversify,z, fsol,
                 Hbin, Wbin, tlist);
      z_star = min(z_star, z);
      if (k <= k_in) {
        // We determine the new target bin
        Tbin = targetBin(fsol, Hbin, Wbin);
      }
    }

    if (z_star == lowb) return fsol;
    else diversification(d, z, Tbin, fsol,
                                Hbin, Wbin, tlist);
    max_iterations--;
  }
  return fsol;
}

void searchtabu(int &Tbin, int &k, bool &diversify,
                int &z, Packing &fsol, int Hbin,
                int Wbin, 
                vector<vector<Triple> > &tlist) {
  
  int penalty_star = INFINITY;
  int penalty;
  int nPacks = fsol.packing.size();
  Packing candidate;
  // Outer loop, for each j in target bin.
  Item j;
  int nBins = fsol.binNum - 1; // Excluding target bin
  long combs = comb(nBins,k);
  vector<Item> S;
  if (combs > 10000) 
    combs = combs * (long) (0.4);
  // Trivial combination 
  int * arr = new int[k];
  for(int c = 0; c < k; c++)
    arr[c] = c;
  
  Triple move; // Move that goes in tabu list

  for(int i = 0; i < nPacks; i++) {
    // We only want those j in target bin.
    if (fsol.packing[i].bin == Tbin) {
      // We generate all possible combinations
      // for each k tuple K bins not including targetBin
      while(combs >= 0) {
        S = buildS(fsol.packing[i].item,fsol,arr,k,nPacks,
                   Tbin);
        penalty = INFINITY;
        candidate = FBS(S, Hbin, Wbin);
        int evalH = candidate.binNum;
        if (evalH < k) {
          // Delete j from fsol.
          fsol.packing.erase(fsol.packing.begin() + i);
          int size = fsol.packing.size();
          fsol = updateSol(candidate, fsol, arr, Tbin, k,size);
          z = fsol.binNum;
          k = max(1, k-1);
          // Adding move to tabuList
          move = (Triple) {Tbin, penalty, fsol};
          tlist[k-1].push_back(move);
          return;
        }
        else if (evalH == k) {
          bool single = singleSet(fsol.packing[i].item, S); 
          bool not_tab = not_tabu(tlist, candidate,k-1,Tbin,penalty);
          if (not_tab
              || single) {
            // Delete j from fsol
            fsol.packing.erase(fsol.packing.begin() + i);
            int size = fsol.packing.size();
            fsol = updateSol(candidate, fsol, arr, Tbin, k,size);
            z = fsol.binNum;
            move = (Triple) {Tbin, penalty, fsol};
            tlist[k-1].push_back(move);
            if (single) k = max(1,k-1);
            return;
          }
        }
        else {
          if (evalH = k + 1 && k > 1) {
            int new_target = targetBin(candidate, Hbin, Wbin);
            vector<Item> S_roof = buildS_target(new_target, candidate);
            vector<Item> S_t = buildS_target(Tbin, candidate);
            extract_item(S_t, fsol.packing[i].item);
            vector<Item> T = S_t + S_roof;
            Packing new_candidate = FBS(T, Hbin, Wbin);
            int new_eval = new_candidate.binNum;
            if (new_eval == 1 && not_tabu(tlist, new_candidate, 0, new_target, penalty)) {
              penalty = min((int) filling(new_candidate, new_target, Hbin, Wbin),
                            targetBin_minus(candidate, Hbin, Wbin, new_target));
              tlist[0].push_back((Triple) {new_target, penalty, new_candidate});
            }
          }
        }
        penalty_star = min(penalty_star, penalty);
        combs--;
        // Nueva combinación
        arr = combinations(k,nBins,arr);
      }
    }
  }
  if (penalty_star != INFINITY) {
    vector<Triple>::iterator it;
    for(it = tlist[k-1].begin(); it < tlist[k-1].end(); ++it) {
      if ((*it).penalty == penalty_star) {
        z = (*it).sol.binNum;
        move = (Triple) {(*it).binchosen, (*it).penalty, (*it).sol};
        tlist[k-1].push_back(move);
        fsol = (*it).sol;
        return;
      }
    }
  }
  else {
    if (k == KMAX) diversify = true; 
    else k++;
  }
  return;
}

void diversification(int &d, int z, int &Tbin, Packing &fsol,
                     int Hbin, int Wbin, vector<vector<Triple> > tlist) {
  int k;
  if (d <= z && d < DMAX) {
    d++;
    vector<int> new_target;
    for(int i = 0; i < z; i++) {
      k = (int) filling(fsol, i, Hbin, Wbin);
      new_target.push_back(k);
    }
    sort(new_target.begin(), new_target.end());
    Tbin = new_target[d];
  }
  else {
    vector<int> elements;
    for(int i = 0; i < z; i++) {
      k = (int) filling(fsol,i, Hbin, Wbin);
      elements.push_back(k);
    }
    sort(elements.begin(), elements.end());
    vector<Placement>::iterator it;
    vector<Placement> modifiedSol;
    int newBins = fsol.binNum - z/2;
    for(int i = 0; i < z/2; i++)  {
      for(it = fsol.packing.begin(); it < fsol.packing.end(); it++) {
        if (elements[i] == (*it).bin) {
          vector<Item> dummy;
          dummy.push_back((*it).item);
          modifiedSol = modifiedSol+genBin(newBins,dummy); 
          //          fsol.packing.erase(it);
          newBins++;
        }
      }
    }
    // Ahora borramos todos los elementos 
    // que consideramos anteriormente
    int control;
    for(int i = 0; i < z/2; i++) {
      control = deleteItem(fsol, elements[i]);
      while(control) 
        control = deleteItem(fsol, elements[i]);
    }
    fsol.packing = fsol.packing + modifiedSol;
    tlist.clear();
    d = 0;
  }
  return;
}

int lowerBound(int nItems, vector<Item> &items, int Wbin,
               int Hbin) {
  int x;
  int y;
  int tot1 = 0;
  int tot2 = Wbin;
  int value;
  int lb;
  for(int i = 0; i < nItems; i++) {
    y = items[i].width;
    y *= items[i].height;
    tot1 += y;
  }
  tot2 *= Hbin;
  value = tot1 / tot2;
  lb = (int) value;
  if (value - (double) lb > EPS) 
    lb++;
  return lb;
}

vector<Item> buildS(Item it, Packing fsol, int * arr, 
                    int k, int nPacks, int Tbin) {
  vector<Item> result;
  result.push_back(it);
  int bin;
  for(int i = 0; i < k; i++) {
    bin = arr[i];
    if (bin >= Tbin) bin++;  // Skip target bin
    for(int j = 0; j < nPacks; j++) {
      if (fsol.packing[j].bin == bin) 
        result.push_back(fsol.packing[j].item);
    }
  }
  return result;
}

bool singleSet(Item j, vector<Item> S) {
  int size = S.size();
  if (size == 1) {
    if (S.front().id == j.id) return true;
  }
  return false;
}

bool not_tabu(vector<vector <Triple> > tlist, 
              Packing candidate, int k, int Tbin,
              int penalty) {
  if (tlist.empty())
    return true;

  vector<Triple>::iterator it;
  it = tlist[k].begin();
  for(it; it < tlist[k].end(); ++it) {
    if (Tbin == (*it).binchosen &&
        penalty == (*it).penalty &&
      check_sol((*it).sol, candidate)) {
      return false;
    }
  }
  return true;
}

bool check_sol(Packing sol, Packing candidate) {
  vector<Placement>::iterator sl;  // Sol
  vector<Placement>::iterator cd;  // Candidate
  Placement dummySL;
  Placement dummyCD;
  for(sl = sol.packing.begin(); sl < sol.packing.end();++sl) {
    dummySL = (*sl);
    for(cd = candidate.packing.begin(); cd < candidate.packing.end(); ++cd) {
      dummyCD = (*cd);
      if (!(dummySL.item.id == dummyCD.item.id &&
          dummySL.bin == dummyCD.bin && 
            dummySL.coord == dummyCD.coord))
        return false;
    }
  }
  return true; // All items proved to be equal
}

vector<Item> buildS_target(int target, Packing fsol) {
  vector<Item> result;
  vector<Placement>::iterator it;
  for(it = fsol.packing.begin(); it < fsol.packing.end(); ++it) {
    if ((*it).bin == target) 
      result.push_back((*it).item);
  }
  return result;
}

void extract_item(vector<Item> &items, Item to_delete) {
  vector<Item>::iterator it;
  for(it = items.begin(); it < items.end(); ++it) {
    if ((*it).id == to_delete.id)  {
      items.erase(it);
      return;
    }
  }
}

vector<Item> operator+(vector<Item> a, vector<Item> b) {
  vector<Item>::iterator it;
  for(it = b.begin(); it < b.end(); ++it) {
    a.push_back(*it);
  }
  return a;
}

int targetBin_minus(Packing pack, int Hbin, int Wbin, 
                    int minus){
  int bin;
  int nbins = pack.binNum;
  double temp;

  double min = numeric_limits<double>::max();
  int minBin;

  //Por cada bin
  for(bin=0; bin<nbins; bin++){
    if (bin == minus) 
      continue;
    else {
      temp = filling(pack,bin,Hbin,Wbin);
      if (min > temp){
        minBin = bin;
        min = temp;
      }
    }
  }
  return minBin;
}

Packing updateSol(Packing & candidate, Packing & fsol,
               int * arr, int Tbin, int k, int size) {
  // Eliminación de soluciones en la solución
  // vieja.
  int control;
  for(int i = 0; i < k; i++) {
    control = deleteItem(fsol, arr[i]);
    while(control) {
      control = deleteItem(fsol, arr[i]);
    }
  }
  // Arreglo de elementos que quedan
  vector<int> leftover;
  for(int i = 0; i < size; i++) {
    if (!linS(arr, k, i))
      leftover.push_back(i);
  }
  int csize = candidate.binNum;

  // Se verifica si target bin quedó vació
  int vacio = 1;
  for(int i = 0; i < fsol.packing.size(); i++) {
    if (fsol.packing[i].bin == Tbin) 
      vacio = vacio && 0;
  }
  
  // Busco todos los elementos que están en leftover 
  // y les pongo nueva numeración
  int target;
  vector<Placement>::iterator it;
  for(int i = 0; i < leftover.size(); i++) {
    target = leftover[i];
    for(it = fsol.packing.begin(); it < fsol.packing.end();
        it++) {
      if ((*it).bin == target) {
        if (target >= Tbin && vacio)
          (*it).bin = csize - 1;
        else  (*it).bin = csize;
      }
    }
    csize++;
  }
  // Finalmente hacemos la unión de los Packings para 
  // obtener la solución actualizada
  vector<Placement> new_plm = candidate.packing + fsol.packing;
  int new_sol_size = candidate.binNum + leftover.size();
  Packing new_packing = {new_plm, new_sol_size };
  return new_packing;
}

// Operador para unir dos Packings


// Find the first occurence of element in a given bin
int deleteItem(Packing & fsol, int bin) {
  vector<Placement>::iterator it;
  for(it = fsol.packing.begin(); it < fsol.packing.end();
      it++) {
    if ((*it).bin == bin) {
      fsol.packing.erase(it);
      return 1;
    }
  }
  return 0; // No elements left 
}

