//#ifndef utils
//#define utils
#include "dataStructs.h"
#include <list>

//Strip packing

bool compareHeight(Item, Item);

void init_visited(vector <Item> &);

//void init_coord(vector <Item> &);

void init_vi_strip(vector <Strip> &);


/*===Heuristics===*/

//Devuelve la posicion de un item en un 
//vector de Placement
int searchItem(const vector<Placement>,int);

//Devuelve la posicion de un bin en un 
//vector de Placement
int searchBin(const vector<Placement>,int);

//Busqueda lineal
bool linS(int*,int,int);

//Devuelve la posicion de un double en
//una lista de double
int linSlist(list<double>,double);

long factorial(int i);


//Factorial superior
long factorial_n(int i,int n);

//Calcula el numero de combinaciones (n en k)
long comb(int n, int k);

//Dado un arreglo con una combinacion, devuelve la
//proxima combinacion
int * combinations(int,int,int*);

//Dada un alista de doubles, devueve el valor
//del elemento que estaria en la nth posicion
//si la lista estuviera ordenada
double nth(list<double>*,int);

//Others
void printPack(const Packing);

//#endif
