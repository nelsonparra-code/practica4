#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <router.h>
#include <net.h>

using namespace std;
/*
 * El archivo que se lee se llama 'routes.txt' y se encuentra en "../practica4/BD/routes.txt",
 * cuando el programa se encuentre en el directorio "../practica4/".
 *
 * El programa reconoce como rutas a {A,B,C,D,E,F,G} exactas. Es decir, se deben escribir en mayuscula y sin caracter adicional alguno.
 *
 * El programa no diferencia entre 2 caminos de igual costo. Si esas rutas comparten la propiedad de ser las de menor costo,
 * el programa va a mostrar la primera hallada.
 */
int main()
{
    router A, B, C, D, E, F, G;
    vector<router> enrutadores {A,B,C,D,E,F,G};
    vector<router>* ptrEnr = &enrutadores;
    net red;

    int inputMethod,action=-1;

    cout<<"\nPara leer de un archivo (routes.txt), seleccione (1).\n"
        <<"Para ingresar rutas por consola, ingrese (2).\n";
    cin>>inputMethod;

    if(inputMethod==1){
        red.readFile();
        red.updateLocalData(ptrEnr);
    }
    else if(inputMethod==2){
        cout<<"\nIngrese la ruta de la siguiente forma:\n"
            <<"<enrutador origen><enrutador destino>,<costo ruta>\n";
        while(true){
            string inRoute;
            cout<<"~ ";
            cin>>inRoute;
            if(inRoute=="*") break;
            else red.addToChanges(inRoute);
        }
        red.updateLocalData(ptrEnr);
    }

    while(action!=0){
        cout<<"\nPara calcular ruta mas eficiente, seleccione (1).\n"
            <<"Para modificar o agregar una ruta, ingrese (2).\n"
            <<"Para salir, ingrese (0).\n";
        cin>>action;
        if(action==1){
            char _origin, _end;
            cout<<"\nIngrese enrutador de origen: ";
            cin>>_origin;
            cout<<"Ingrese enrutador de llegada: ";
            cin>>_end;
            red.calculateRoutes(enrutadores,_origin,_end);
        }
        else if(action==2){
            cout<<"\nIngrese la ruta de la siguiente forma:\n"
                <<"<enrutador origen><enrutador destino>,<costo ruta>\n"
                <<"NOTAS:\n1. Para eliminar una conexion, ingrese -1 en el <costo ruta>\n"
                <<"2. Para terminar el proceso, ingrese *.\n";
            while(true){
                string inRoute;
                cout<<"~ ";
                cin>>inRoute;
                if(inRoute=="*") break;
                else red.addToChanges(inRoute);
            }
            red.updateLocalData(ptrEnr);
        }
        else if(action!=0){
            cout<<"\nOpcion invalida, intente de nuevo.\n";
        }
    }

    cout<<"\n\nMuchas gracias por usar nuestros servicios.\n";

    system("PAUSE");

    return 0;
}
