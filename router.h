#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <vector>
using namespace std;

class router{
    friend class net;
protected:
    vector<int> costs          {-1,   -1,  -1,  -1,  -1,  -1,  -1};
    vector<char> connectionsAv {'x', 'x', 'x', 'x', 'x', 'x', 'x'};
    vector<int>* ptrCosts = &costs;
    vector<char>* ptrConnections = &connectionsAv;

    void setCost(int,int);
    int getCost(int);
    void modifyConnection(char,int);
    char getConnectionsElement(int);
};

#endif // ROUTER_H
