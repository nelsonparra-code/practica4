#include <functions.h>

void deleteRoutes(vector<string>* vctor, string route){
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
}
