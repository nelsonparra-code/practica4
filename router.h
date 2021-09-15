#ifndef ROUTER_H
#define ROUTER_H

#include <vector>
using namespace std;

class enrutador{
public:
    vector<int> costs {-1, -1, -1, -1, -1, -1, -1};
    vector<int>* ptrVctr = &costs;

    void setCost(int,int);
};

#endif // ROUTER_H
