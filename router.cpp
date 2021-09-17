#include <router.h>

#include <iostream>
#include <vector>
#include <map>

using namespace std;

void router::setCost(int newCost,int position){
    (*ptrCosts)[position] = newCost;
}

int router::getCost(int position){
    return (*ptrCosts)[position];
}

void router::modifyConnection(char end,int position){
    (*ptrConnections)[position] = end;
}

char router::getConnectionsElement(int position){
    return (*ptrConnections)[position];
}
