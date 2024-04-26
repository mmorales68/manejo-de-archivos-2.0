#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
using namespace std;

using namespace std;
void crearCarpeta();
void crearArchivo();

int main (){
    crearCarpeta();
    crearArchivo();
}

void crearCarpeta(){
    string directorio;
    cout << "Ingrese la ruta del directorio donde desea crear la carpeta: "<< endl;
    getline(cin, directorio);
    if (!fs::exists(directorio)) {
        cerr << "El directorio especificado no existe." <<endl;
    }
    string nombreCarpeta;
    cout << "Ingrese el nombre de la carpeta que desea crear: "<<endl;
    getline(cin, nombreCarpeta);
    string rutaCompleta = directorio + "/" + nombreCarpeta;
    if (fs::create_directory(rutaCompleta)) {
        cout<<"Se creo la carpeta "<<nombreCarpeta<<" "<<"en el directorio especificado"<< endl;
    } else {
        cerr << "No se pudo crear la carpeta."<<endl;
        }
}

void crearArchivo(){
    string directorio;
    string nombreArchivo;
    string linea;
    cout << "Ingrese el directorio donde desea crear el archivo: "<< endl;
    getline(cin, directorio);
    cout << "Ingrese el nombre del archivo que desea crear: "<< endl;
    getline(cin, nombreArchivo);
    string rutaCompleta = directorio + "/" + nombreArchivo;
    ofstream archivoSalida(rutaCompleta, ios::out | ios::app);
    if (archivoSalida.is_open()) {
        cout<<"Introduzca las lineas que desea escribir en el archivo (escriba FIN para terminar)"<<endl;
        while (getline(cin, linea)) {
            if (linea == "FIN") {
                break;  // Salir del ciclo si el usuario escribe 'FIN'
            }
            archivoSalida << linea << endl;
        }
        archivoSalida.close();  // Cierra el archivo después de terminar de escribir
        cout << "El archivo se ha guardado correctamente en: " << rutaCompleta << endl;
    } else {
        cout << "Error: no se pudo abrir el archivo en el directorio especificado.\n"<< endl;
        }
}