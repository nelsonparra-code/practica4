#include <net.h>
#include <functions.h>

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template <class T>
bool notInArray(vector<T> vctr, T d){
    for(unsigned long long i=0;i<vctr.size();i++){
        if(vctr[i]==d) return false;
    }
    return true;
}

void net::readFile(){
    vector<string> vctr {};
    string data;

    ifstream rFile;
    rFile.open("../practica4/BD/routes.txt");
    if (!rFile.is_open())
       {
         cout << "Error abriendo el archivo." << endl;
         exit(1);
       }
    while(true){
        rFile>>data;
        if(notInArray(vctr,data)) vctr.push_back(data);
        else break;
    }
    rFile.close();

    int vctrSize = vctr.size();
    for(int i=0;i<vctrSize;i++){
        addToChanges(vctr[i]);
    }
}

void net::addToChanges(string str){
    int stringSize = str.length();

    string route="", auxCost="";
    bool identifier=false;
    for(int i=0;i<stringSize;i++){
        if(str[i]!=','&&identifier==false) route+=str[i];
        else if(str[i]!=','&&identifier==true) auxCost+=str[i];
        else identifier=true;
    }
    changes[route]=stoi(auxCost);
}

void net::updateLocalData(vector<router>* vctr){
    map<char,int> guide {{'A',0},{'B',1},{'C',2},{'D',3},{'E',4},{'F',5},{'G',6}};
    for(auto it = changes.cbegin(); it != changes.cend(); it++){
        char origin = (*it).first[0], end = (*it).first[1];
        if(origin!=end){

            int indexO = guide.find(origin)->second, indexE = guide.find(end)->second;
            (*vctr)[indexO].setCost((*it).second, indexE);
            (*vctr)[indexE].setCost((*it).second, indexO);

            if((*it).second>=0){
                (*vctr)[indexO].modifyConnection(end,indexE);
                (*vctr)[indexE].modifyConnection(origin,indexO);
                string toAddRoute="";
                bool sit=true;
                toAddRoute.push_back(origin);toAddRoute.push_back(end);
                for(unsigned long long i=0;i<routes.size();i++){
                    if(routes[i]==toAddRoute) sit=false;
                }
                if(sit==true) routes.push_back(toAddRoute);
            }
            else{
                (*vctr)[indexO].modifyConnection('x',indexE);
                (*vctr)[indexE].modifyConnection('x',indexO);
                string toDeleteRoute="";
                toDeleteRoute.push_back(origin);toDeleteRoute.push_back(end);
                for(unsigned long long i=0;i<routes.size();i++){
                    if(routes[i]==toDeleteRoute) routes.erase(routes.cbegin()+i);
                }
            }
        }
    }
}

void net::printChanges(){
    for(auto it = changes.cbegin(); it != changes.cend(); it++){
        cout<<(*it).first<<" -> "<<(*it).second<<endl;
    }
}

void net::printIndRoutes(){
    for(unsigned long long i=0;i<routes.size();i++){
        cout<<routes[i]<<endl;
    }
}

void net::calculateRoutes(vector<router> vctr, char o, char e){
    if(o==e){
        cout<<"El origen de la ruta es igual a la llegada de la misma. Cuesta 0."<<endl;
        return;
    }
    (*ptrRoutes).empty();
    vector<char> routers {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int vctrSize = (vctr).size();
    for(int i=0;i<7;i++){
        for(int j=0;j<vctrSize;j++){
            string route;
            route.push_back(routers[i]);
            if((vctr)[i].getConnectionsElement(j)!='x'){
                route.push_back((vctr)[i].getConnectionsElement(j));
                (*ptrRoutes).push_back(route);
            }
        }
    }
    vector<string> definitiveRoutes {};
    possibleRoutes(&definitiveRoutes, o, e);
    int actualCost=0, minCost=0;
    string minCostRoute="";
    for(unsigned long long i=0;i<definitiveRoutes.size();i++){
        if(i==0){
            minCost = calculateCost(&vctr,definitiveRoutes[i]);
            minCostRoute = definitiveRoutes[i];
        }
        else{
            actualCost = calculateCost(&vctr,definitiveRoutes[i]);
            if(actualCost<minCost){
                minCost = actualCost;
                minCostRoute = definitiveRoutes[i];
            }
        }
    }
    if(minCost==-1 || actualCost==-1) cout<<"La ruta destino: '"<<e<<"' no existe, o no se encuentra asociada al origen '"<<o<<"'."<<endl;
    else cout<<"La ruta mas eficiente es: "<<minCostRoute<<" y cuesta "<<minCost<<endl;
}

void net::possibleRoutes(vector<string>* defRoutes, char origin, char end){
    vector<string> routesModified {};
    vector<string> auxArray {};
    routesModified = routes;

    long routesQty = routes.size();

    for(long i=0;i<routesQty;i++){
        //routesQty = routesModified.size();
        string aux = routes[i];
        if(aux[0]==origin && aux[1]==end){
            (*defRoutes).push_back(aux);
            //routesModified.erase(routesModified.begin()+i);
            //i--;
        }
        else{
            auxArray = routesModified;
            string newRoute = "", start;
            if(aux[0]==origin){
                newRoute+=aux;
                deleteRoutes(&auxArray, aux);
            }
            routesModified = auxArray;
            if(newRoute!=""){
                for(long j=0;j<routesQty;j++){

                    routesQty = auxArray.size();
                    string aux2 = auxArray[j];
                    int newRouteLength = newRoute.length();
                    if(newRoute[newRouteLength-1]==aux2[0] && newRoute[newRouteLength-2]!=aux2[1]){
                        newRoute+=aux2;
                        deleteRoutes(&auxArray, aux2);
                        j=-1;
                        newRouteLength = newRoute.length();
                        if(newRoute[0]==origin && newRoute[newRouteLength-1]==end){
                            if(!notInArray((*defRoutes), newRoute)) newRoute=newRoute[0]+newRoute[1];
                            else{
                                (*defRoutes).push_back(newRoute);
                                auxArray = routes;
                                routesQty = auxArray.size();
                                break;
                            }
                        }
                        else if(auxArray.size()==0){
                            routesModified.erase(routesModified.begin());
                            auxArray=routesModified;
                            j=-1;
                            newRoute = aux;
                        }
                    }
                }
            }
        }
    }
}

int net::calculateCost(vector<router>* vctr, string cad){
    map<char,int> guide {{'A',0},{'B',1},{'C',2},{'D',3},{'E',4},{'F',5},{'G',6}};

    string auxCad;
    int totalCost=0;

    for(unsigned long long i=0;i<cad.size();i+=2){
        char o = cad[i];
        char e = cad[i+1];
        if((*vctr)[guide.find(o)->second].getCost(guide.find(e)->second)==-1) return -1;
        totalCost+=(*vctr)[guide.find(o)->second].getCost(guide.find(e)->second);
    }

    return totalCost;
}
