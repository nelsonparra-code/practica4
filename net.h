#ifndef NET_H
#define NET_H

#include <router.h>

#include <iostream>
#include <map>
using namespace std;

class red:protected enrutador{
private:
    map<string,int> changes {};
public:
    void readFile();
    void addToChanges(string);
    void updateLocalData(vector<enrutador>*);

    void printChanges();
};

#endif // NET_H
