#include <iostream>
#include "funciones.h"

using namespace std;


int main() {
    int select;
    do{
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout<<"============================================================================================="<<endl;
        cout<<"||**************************************MENU***********************************************||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||     1) Funcion Carlos:BASE DE DATOS DE CLIENTES USANDO UN LOGIN PARA INGRESAR           ||"<<endl;
        cout<<"||        ENCRIPTACION Y DESENCRIPTACION DEL CONTENIDO DE UN ARCHIVO DE TEXTO              ||"<<endl;
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
        cout<<"SELECIONA UNA OPCION: ";
        cin>>select;

        switch (select){
            case 1:{
                int opcion;
                do{
                    cout << "[1] INGRESAR A LA BASE DE DATOS." << endl;
                    cout << " [2] ENCRIPTAR/DESENCRIPTAR ARCHIVOS." << endl;
                    cout << " [3] REGRESAR AL MENU ANTERIOR" << endl;
                    cout << "    QUE DESEAS HACER"<<endl;
                    cin >> opcion;
                    switch (opcion) {
                        case 1: {
                            string usuario,password,lectura;
                            int oportunidades=3;
                            bool corte=false;
                            ifstream fi("password.txt");
                            if(fi.fail()) {
                                cout << "FALLO AL ABRIR EL ARCHIVO." << endl;
                            }else{
                                while(oportunidades>0){
                                    cout<<"~~~~~~~~~~~~~~~~~"<<endl;
                                    cout<<" INICIO DE SESION"<<endl;
                                    cout<<" ~~~~~~~~~~~~~~~~~"<<endl;
                                    cout<<"NOMBRE DE USUARIO"<<endl;
                                    cin>>usuario;
                                    cout<<"CONTRASENA"<<endl;
                                    cin>>password;
                                    oportunidades--;
                                    fi.seekg(0);
                                    while(!fi.eof() && corte==false){
                                        fi>>lectura;
                                        if(lectura==usuario){
                                            fi>>lectura;
                                            if(lectura==password) {
                                                cout<<"ACCESO PERMITIDO." << endl;
                                                corte = true;
                                                oportunidades = 0;
                                                int opcion = 0;
                                                vector<string> vNombres, vApellidos, vTelefonos;
//MENU DE OPCIONES
                                                do {
                                                    cout<<endl<<"***BASE DE DATOS DE CLIENTES***"<<endl;

                                                    cout<<"[1].AGREGAR UN NUEVO CLIENTE."<<endl;
                                                    cout<<"[2].BUSCAR UN CLIENTE."<<endl;
                                                    cout<<"[3].MODIFICAR UN CLIENTE."<<endl;
                                                    cout<<"[4].BORRAR UN CLIENTE."<<endl;
                                                    cout<<"[5].VER LISTA DE CLIENTES."<<endl;
                                                    cout<<"[6].CERRAR EL PROGRAMA."<<endl;
                                                    cout<<"QUE QUIERES HACER:";
                                                    cin>>opcion;
                                                    if (opcion<1 || opcion>5){
                                                        cout<<"ERROR AL ELEGIR. PRUEBA DE NUEVO"<<endl;
                                                    }
                                                    switch (opcion) {
                                                        case 1:{
                                                            ofstream ficheroEscritura("clientes.txt",ios::app);
                                                            nuevoCliente(ficheroEscritura);
                                                            ficheroEscritura.close();
                                                        }
                                                            break;
                                                        case 2:{
                                                            ifstream ficheroLectura("clientes.txt");
                                                            buscarCliente(ficheroLectura);
                                                            ficheroLectura.close();
                                                        }
                                                            break;
                                                        case 3:{
                                                            ifstream ficheroLectura2("clientes.txt");
                                                            modificarCliente(vNombres,vApellidos,vTelefonos,ficheroLectura2);
                                                            ficheroLectura2.close();
                                                        }
                                                            break;
                                                        case 4:{
                                                            ifstream ficheroLectura3("clientes.txt");
                                                            borrarCliente(vNombres,vApellidos,vTelefonos,ficheroLectura3);
                                                            ficheroLectura3.close();
                                                        }
                                                            break;
                                                        case 5:{
                                                            leerArchivo();
                                                        }
                                                            break;
                                                    }
                                                }while (opcion!=6);

                                            }
                                        }
                                    }
                                    if(!corte)
                                        cout<<"USUARIO O CONTRASENA NO VALIDOS"<<endl;
                                }
                                if(oportunidades==0 && corte==false)
                                    cout<<"ACCESO DENEGADO."<<endl;
                            }
                            fi.close();

                        }
                            break;
                        case 2: {
                            Cryptographer cryptographer;
                            SimpleCrypt simpleCrypt;

                            string inputFile, outputFile;
                            char choice;

                            cout << "Ingrese la ruta del archivo de entrada: ";
                            cin >> inputFile;
                            cout << "Ingrese la ruta del archivo de salida: ";
                            cin >> outputFile;

                            cout << "Elija una opción:\n";
                            cout << "1. Cifrar\n";
                            cout << "2. Descifrar\n";
                            cin >> choice;

                            switch (choice) {
                                case '1':
                                    cryptographer.encryptFile(inputFile, outputFile, simpleCrypt);
                                    break;
                                case '2':
                                    cryptographer.decryptFile(inputFile, outputFile, simpleCrypt);
                                    break;
                                default:
                                    cout << "Opción no válida" << endl;
                            }
                        }
                            break;
                        case 3:
                            break;
                        default:
                            cout << "OPCION INVALIDA" << endl;
                    }
                }while(opcion!=3);
            }
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
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