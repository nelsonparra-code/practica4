#include <router.h>

#include <iostream>
#include <vector>

using namespace std;

void enrutador::setCost(int newCost,int position){
    (*ptrVctr)[position] = newCost;
}
