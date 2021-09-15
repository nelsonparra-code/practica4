#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <router.h>
#include <net.h>

using namespace std;

int main()
{
    enrutador A, B, C, D, E, F, G;
    vector<enrutador> enrutadores {A,B,C,D,E,F,G};

    red red;
    red.readFile();
    //red.printChanges();
    red.updateLocalData(&enrutadores);

    return 0;
}
