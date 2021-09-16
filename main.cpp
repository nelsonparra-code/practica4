#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <router.h>
#include <net.h>

using namespace std;

int main()
{
    router A, B, C, D, E, F, G;
    vector<router> enrutadores {A,B,C,D,E,F,G};

    net red;
    red.readFile();
    //red.printChanges();
    red.updateLocalData(&enrutadores);

    red.calculateRoutes(enrutadores);
    red.printIndRoutes();


    return 0;
}
