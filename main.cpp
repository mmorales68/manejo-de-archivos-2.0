#include "iostream"
#include "funciones.h"

using namespace std;

int main() {

    int select;

    do{
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout<<"============================================================================================="<<endl;
        cout<<"|| Seleccione una de las siguientes opciones:                                              ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||     1) Funcion Carlos: Ejecuta...                                                       ||"<<endl;
        cout<<"||     2) Funcion Julio:                                                                   ||"<<endl;
        cout<<"||     3) Funcion Moreno:                                                                  ||"<<endl;
        cout<<"||     4) Funcion Miguel:                                                                  ||"<<endl;
        cout<<"||     0) Exit                                                                             ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"============================================================================================="<<endl;
        cout<<"---------------------------------------------------------------------------------------------"<<endl;

        cin>>select;

        switch (select){
            case 1:
                cout<<"HOLAAA";
                carlos();
                break;
            case 2:
                julio();
                break;
            case 3:
                moreno();
                break;
            case 4:
                miguel();
                break;
            case 0:
                cout<<"Saliendo del programa"<<endl;
                system("pause");
                break;
            default:
                cout<<"Opccion invalida"<<endl;
                break;
        }

    } while (select!=0);

    return 0;
}
