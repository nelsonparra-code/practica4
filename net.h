#ifndef NET_H
#define NET_H

#include <router.h>

#include <iostream>
#include <map>
using namespace std;

class net:protected router{
private:
    map<string,int> changes {};
    vector<string> routes {};
    vector<string>* ptrRoutes = &routes;
public:
    void readFile();
    void addToChanges(string);
    void updateLocalData(vector<router>*);
    void calculateRoutes(vector<router>,char,char);
    int calculateCost(vector<router>*,string);

    void possibleRoutes(vector<string>*,char,char);

    void printChanges();
    void printIndRoutes();
};

#endif // NET_H
