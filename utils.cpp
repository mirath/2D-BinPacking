#include "utils.h"
#include <iostream>
using namespace std;

int compareHeight(const void *a, const void *b) {
  // We add the outer minus sign to get nonincreasing 
  // ordering.
  return ( -((*(Item *)a).height - (*(Item*)b).height) );
}

int * combinations(int k, int n, int* arr){
  int i = k-1;

  if (arr[i] < n-1)
    arr[i] += 1;
  else if (arr[0] == n-1)
    return 0;
  else{
    while(arr[i] >= n-1){
      arr[i-1] += 1;
      i -= 1;
    }

    while(i < k-1){
      arr[i+1] = arr[i]+1;
      i += 1;
    }
  }

  return arr;
}

bool linS(int* arr, int N, int elem){
  bool is = false;
  int i = 0;

  while (i<N){
    is = is | arr[i]==elem;
    i += 1;
  }

  return is;
}

int searchItem(vector<Placement> vect, int item){
  int where = -1;
  int i = 0;

  while (i < vect.size()){
    if (vect[i].item.id == item)
      where = i;
    i += 1;
  }

  return where;
}

long factorial(int i){
  long fac = 1;

  while(i > 1){
    fac = fac*i;
    i -=1;
  }

  return fac;
}

long comb(int n, int k){
  long comb;

  comb = factorial(n)/(factorial(n-k)*factorial(k));
  
  return comb;
}

void printPack(Packing p){
  int i = 0;

  cout<<"Total bins: ";
  cout<<p.binNum;
  cout<<"\n";
  
  for(i=0;i<p.packing.size();++i){
    cout<<"------------\n";
    cout<<"Item: " << p.packing[i].item.id << "\n";
    cout<<"Bin: " << p.packing[i].bin << "\n";
    cout<<"Coor: " << p.packing[i].coord.x << "," << p.packing[i].coord.y << "\n";
    cout<<"Height: " << p.packing[i].item.height << "\n";
    cout<<"Width: " << p.packing[i].item.width << "\n";
  }
}
