#include "utils.h"
#include <iostream>
using namespace std;

bool compareHeight(Item a, Item b) {
  // We add the outer minus sign to get nonincreasing 
  // ordering.
  return (a.height >= b.height);
}

void init_visited(vector <Item> &items) {
  // Setting all items to not visited
  for(int i = 0; i < nItems; i++) 
    items[i].visited = false;
}

void init_coord(vector <Item> &items) {
  vector<Item>::iterator it;
  for(it = items.begin(); it != items.end(); it++) {
    (*it).coord.x = 0;
    (*it).coord.y = 0;
  }
}

void init_vi_strip(vector <Strip> &sset) {
  vector<vector<Item> > p = sset.strips;
  vector<Item>::iterator it;
}

int * combinations(int k, int n, int* arr){
  int i = k-1;

  if (arr[i] < n-1)
    arr[i] += 1;
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
