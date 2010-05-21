#include "dataStructs.h"
#include "utils.h"
#include "FiniteBestStrip.h"
#include <iostream>
#include <vector>
using namespace std;

//IN: - Packing
//    - int*: arreglo de bins
//    - int: bin prohibido
//OUT: - Vector<Item>: items del Packing que estan
//                     en los bins del arreglo
vector<Item>* getItems(int*,int,int,Packing*);


//Sincroniza la informacion de los items del
//segundo packing con los del primero
Packing * update(Packing,Packing*,int*,int,int);


//Decide que packing es "mejor" dado que ambos
//usan el mismo numero de bins
Packing* breakTie(Packing*,Packing*,int,int);

//Busqueda Primer Mejor
int HFirstBest(int,Packing*,int,int,int);

//Busqueda Mejor Mejor
int HBestBest(int,Packing*,int,int,int);
