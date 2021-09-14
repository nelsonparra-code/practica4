#include <iostream>
#include <vector>
#include <map>

using namespace std;

int deleteRoutes(vector<string>*,string);
bool notInArray(vector<string>,string);

int main(){
    map<string,int> costs {{"AC", 1},{"CD", 2},{"DB", 3},{"BE", 4}};
    string cad = "ACCDDBBE", auxCad;
    int totalCost=0;

    for(unsigned long long i=0;i<cad.size();i+=2){
        auxCad = cad[i];
        auxCad += cad[i+1];
        totalCost+=costs.find(auxCad)->second;
    }

    cout<<totalCost<<endl;

    return 0;
}

/*int main()
{

    //possibleRoutes()
    vector<char> routers {'A','B','C','D'};
    vector<string> routes {"AB","AC","AE","BA","BD","BE","CA","CD","DB","DC","EA","EB"};
    vector<string> routesModified {};
    vector<string> auxArray {};
    routesModified = routes;
    vector<string> defRoutes {};

    char origin = 'B', end = 'E';
    long routesQty = routes.size();

    for(long i=0;i<routesQty;i++){
        //routesQty = routesModified.size();
        string aux = routes[i];
        if(aux[0]==origin && aux[1]==end){
            defRoutes.push_back(aux);
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
                            if(!notInArray(defRoutes, newRoute)) newRoute=newRoute[0]+newRoute[1];
                            else{
                                defRoutes.push_back(newRoute);
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

    for(unsigned long long i=0;i<defRoutes.size();i++){
        cout<<defRoutes[i]<<endl;
        //return defRoutes;
    }

    return 0;
}*/

int deleteRoutes(vector<string>* vctor, string route){
    char letter = route[0];
    int deleted=0, position=0;
    long vectorSize = (*vctor).size(), iterations=0;
    for(long i=0;i<vectorSize;i++){
        if((*vctor)[i]==route){
            position=i;
            break;
        }
    }
    for(long i=0;i<vectorSize;i++){
        iterations++;
        if((*vctor)[i][0]==letter||(*vctor)[i][1]==letter){
            (*vctor).erase((*vctor).begin()+i);
            if(iterations<=position) deleted++;
            i--;
            vectorSize = (*vctor).size();
        }
    }
    return deleted;
}

bool notInArray(vector<string> vctr, string str){
    for(unsigned long long i=0;i<vctr.size();i++){
        if(vctr[i]==str) return false;
    }
    return true;
}
