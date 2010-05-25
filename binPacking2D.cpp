#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <istream>
#include "utils.h"
#include "FiniteBestStrip.h"
#include "LocalSearch.h"
#include "dataStructs.h"
#include "time.h"
using namespace std;

int main(int argc, char *argv[]) {
  ifstream instance(argv[1]);
  char * line = (char *) malloc(sizeof(char)*60);
  if (instance.is_open()) {
    int clase;
    int nItems;
    vector<Item> items;
    int Hbin;
    int Wbin;
    int width;
    int height;
    Packing result;
    time_t time1, time2;
    clock_t ctime1, ctime2;
    while (!instance.eof()) {
      // Problem class 
      instance.getline(line, 60);
      sscanf(line," %d", &clase);
      // Number of items
      instance.getline(line, 60);
      sscanf(line," %d", &nItems);
      // Non useful parameter
      instance.getline(line, 60);
      // Height and Width of bin
      instance.getline(line, 60);
      sscanf(line," %d %d", &Hbin, &Wbin);
      // Starting to loop over items
      for(int i = 0; i < nItems; i++) {
        instance.getline(line, 60);
        sscanf(line," %d %d", &height, &width);
        items.push_back((Item) {width, height, i, false});
      }
      // Whiteline after reading last Item
      instance.getline(line, 60);

      //time(&time1);
      ctime1 = clock();
      result = LocalSearch(items, Hbin, Wbin);
      ctime2 = clock();
      //time(&time2);

      cout << "Tamano: " << nItems << "\n";
      printPack(result);
      cout << "Tiempo: "<< (double)(ctime2-ctime1)/((CLOCKS_PER_SEC)*1000)/*((double)difftime(time2,time1))*/ <<"\n";      
      cout << "==============\n";
      items.clear();
    }
    instance.close();
  }
  else {
    cout << "Error leyendo instacia" << endl;
    exit(0);
  }
  free(line);

}
