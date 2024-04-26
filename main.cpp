#include <iostream>
#include "funciones.h"

using namespace std;


int main() {
    int select;
    do{
        system("cls");
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout<<"============================================================================================="<<endl;
        cout<<"||**************************************MENU***********************************************||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||     1) Funciones Carlos:BASE DE DATOS DE CLIENTES USANDO UN LOGIN PARA INGRESAR         ||"<<endl;
        cout<<"||        ENCRIPTACION Y DESENCRIPTACION DEL CONTENIDO DE UN ARCHIVO DE TEXTO              ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||     2) Funcion Julio:                                                                   ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||     3) Funciones Cayetano: Crear directorio, Crear archivo                              ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||     4) Funciones Miguel: Conversor de monedas (BANGUAT), keylogger                      ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||     0) Exit                                                                             ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"||                                                                                         ||"<<endl;
        cout<<"============================================================================================="<<endl;
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout<<"SELECIONA UNA OPCION: ";
        cin>>select;

        switch (select){
            case 1:{
                system("cls");
                int opcion;
                do{
                    cout << "[1] INGRESAR A LA BASE DE DATOS." << endl;
                    cout << " [2] ENCRIPTAR/DESENCRIPTAR ARCHIVOS." << endl;
                    cout << " [0] REGRESAR AL MENU ANTERIOR" << endl;
                    cout << "    QUE DESEAS HACER"<<endl;
                    cin >> opcion;
                    switch (opcion) {
                        case 1: {
                            system("cls");
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
                            system("cls");
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
                                    system("pause");
                            }
                        }
                            break;
                        case 0:
                            system("cls");
                            break;
                        default:
                            cout << "OPCION INVALIDA" << endl;
                            system("pause");
                        break;
                    }
                }while(opcion!=0);
            }
                break;
            case 2:
                break;

            case 3:
                int selectC;
                do {
                    system("cls");
                    cout<<"---------------------------------------------------------------------------------------------"<<endl;
                    cout<<"============================================================================================="<<endl;
                    cout<<"||* * * * * * * * * * * * * * * * Funciones por Cayetano * * * * * * * * * * * * * * * * * ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||     1) Crear un Directorio                                                              ||"<<endl;
                    cout<<"||     2) Crear un Archivo                                                                 ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||     0) Regresar al menu principal                                                       ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"============================================================================================="<<endl;
                    cout<<"---------------------------------------------------------------------------------------------"<<endl;
                    cout<<"SELECIONA UNA OPCION: ";
                    cin>>selectC;

                    switch (selectC){
                        case 1:
                            system("cls");
                            crearCarpeta();
                        break;

                        case 2:
                            system("cls");
                            crearArchivo();
                        break;

                        case 0:
                            system("cls");
                        break;

                        default:cout<<"Opcion invalida"<<endl;
                            system("pause");
                        break;
                    }




                }while (selectC!=0);
                break;

            case 4:
                int selectM;
                do{
                    system("cls");
                    cout<<"---------------------------------------------------------------------------------------------"<<endl;
                    cout<<"============================================================================================="<<endl;
                    cout<<"||* * * * * * * * * * * * * * * * Funciones por Miguel * * * * * * * * * * * * * * * * * * ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||     1) Calculadora GTQ a USD (BANGUAT)                                                  ||"<<endl;
                    cout<<"||     2) Calculadora USD a GTQ (BANGUAT)                                                  ||"<<endl;
                    cout<<"||     3) Keylogger (registra las teclas pulsadas en un archivo txt)                       ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||     0) Regresar al menu principal                                                       ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"||                                                                                         ||"<<endl;
                    cout<<"============================================================================================="<<endl;
                    cout<<"---------------------------------------------------------------------------------------------"<<endl;
                    cout<<"SELECIONA UNA OPCION: ";
                    cin>>selectM;

                    switch (selectM){
                        case 1:
                            system("cls");
                            calculadoraGTQ_USD();
                            break;

                        case 2:
                            system("cls");
                            calculadoraUSD_GTQ();
                            break;

                        case 3:
                            system("cls");
                            keylogger();
                            break;

                        case 0:
                            system("cls");
                            break;

                        default:cout<<"Opcion invalida"<<endl;
                        system("pause");
                            break;
                    }


                }while(selectM!=0);
                break;

                case 0:
                cout<<"Saliendo del programa"<<endl;
                system("pause");
                break;

                default:
                cout<<"Opccion invalida"<<endl;
                system("pause");
                break;
        }

    } while (select!=0);

    return 0;
}