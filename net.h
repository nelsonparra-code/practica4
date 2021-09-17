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
    map<string,int>* ptrChanges = &changes;
    vector<string>* ptrRoutes = &routes;
protected:
    void deleteRoutes(vector<string>*,string);
    int calculateCost(vector<router>*,string);
    void possibleRoutes(vector<string>*,char,char);
public:
    void readFile();
    void addToChanges(string);
    void updateLocalData(vector<router>*);
    void calculateRoutes(vector<router>,char,char);

};

#endif // NET_H
