#include <net.h>

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

void red::readFile(){
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

void red::addToChanges(string str){
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
void red::updateLocalData(vector<enrutador>* vctr){
    map<char,int> guide {{'A',0},{'B',1},{'C',2},{'D',3},{'E',4},{'F',5},{'G',6}};
    for(auto it = changes.cbegin(); it != changes.cend(); it++){
        char origin = (*it).first[0], end = (*it).first[1];
        if(origin!=end){

            int indexO = guide.find(origin)->second, indexE = guide.find(end)->second;
            (*vctr)[indexO].setCost((*it).second, indexE);
            (*vctr)[indexE].setCost((*it).second, indexO);

        }
    }
}

void red::printChanges(){
    for(auto it = changes.cbegin(); it != changes.cend(); it++){
        cout<<(*it).first<<" -> "<<(*it).second<<endl;
    }
}
