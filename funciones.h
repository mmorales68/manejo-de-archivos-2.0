//
// Created by mmora on 20/04/2024.
//

#ifndef MANEJO_DE_ARCHIVOS_2_0_FUNCIONES_H
#define MANEJO_DE_ARCHIVOS_2_0_FUNCIONES_H

#endif //MANEJO_DE_ARCHIVOS_2_0_FUNCIONES_H
#include "windows.h"
#include "iostream"
#include "fstream"
#include "vector"

using namespace std;

void nuevoCliente(ofstream &f){
    string nombre,apellidos,telefono;
    cin.ignore();
    cout<<"INGRESA EL NOMBRE DEL CLIENTE."<<endl;
    getline(cin,nombre);
    cout<<"INGRESA LOS APELLIDOS DEL CLIENTE."<<endl;
    getline(cin,apellidos);
    cout<<"INGRESA EL NUMERO DE TELEFONO DEL CLIENTE."<<endl;
    getline(cin,telefono);
    f<<nombre<<endl<<apellidos<<endl<<telefono<<endl;
}

void buscarCliente(ifstream &f){
    string nombre,apellidos,telefono,busqueda;
    bool encontrado=false;
    cin.ignore();
    cout<<"QUE CLIENTE QUIERES BUSCAR:"<<endl;
    getline(cin,busqueda);
    while(!f.eof()){
        if(!f.eof()){
            getline(f,nombre);
            getline(f,apellidos);
            getline(f,telefono);
            if ((busqueda==nombre || busqueda==apellidos || busqueda==telefono)&&(!f.eof())) {
                cout<<"CLIENTE ENCONTRADO."<<endl;
                cout<<nombre<<" "<<apellidos<<" "<<telefono<<endl;
                encontrado=true;
            }
        }
    }
    if(encontrado==false){
        cout<<"NO HAY NINGUN CLIENTE CON ESE DATO."<<endl;
    }
}

void reescribirArchivo(vector<string> &a,vector<string> &b,vector<string> &c, ofstream &f){
    cout<<a.size()<<" "<<b.size()<<" "<<c.size()<<endl;
    for(unsigned int i=0; i<a.size(); i++)
        f<<a.at(i)<<endl<<b.at(i)<<endl<<c.at(i)<<endl;
    f.close();
}

void modificarCliente(vector<string> &a,vector<string> &b,vector<string> &c,ifstream &f) {
    string nombre, apellidos, telefono, busqueda;
    a.clear();
    b.clear();
    c.clear();
    bool encontrado = false;
    char seguro = 'N';
    unsigned int indice = 0;
    cin.ignore();
    cout << "QUE CLIENTE DESEAR MODIFICAR" << endl;
    getline(cin, busqueda);
    while (!f.eof()) {
        getline(f, nombre);
        if (!f.eof())
            a.push_back(nombre);
        getline(f, apellidos);
        if (!f.eof())
            b.push_back(apellidos);
        getline(f, telefono);
        if (!f.eof())
            c.push_back(telefono);
        if (busqueda == nombre || busqueda == apellidos || busqueda == telefono) {
            cout << "CLIENTE ENCONTRADO." << endl;
            cout << nombre << " " << apellidos << " " << telefono << endl;
            encontrado = true;
            cout << "SEGURO QUE DESEAS MODIFICARLOS (S/N)" << endl;
            cin >> seguro;
            cin.ignore();
            if (seguro == 'S'|| seguro=='s') {
                cout << "VAMOS A CAMBIAR LOS DATOS DEL USUARIO SELECCIONADO." << endl;
                cout << "INGRESA EL NUEVO NOMBRE." << endl;
                getline(cin, nombre);
                a.at(indice) = nombre;
                cout << "INGRESA LOS NUEVOS APELLIDOS." << endl;
                getline(cin, apellidos);
                b.at(indice) = apellidos;
                cout << "INGRESA EL NUEVO NUMERO DE TELEFONO." << endl;
                getline(cin, telefono);
                c.at(indice) = telefono;
            }
        }
        indice++;
    }
    if (encontrado == false)
        cout << "NO HAY NINGUN CLIENTE CON ESE DATO." << endl;
    f.close();
    ofstream ficheroEscritura2("clientes.txt");
    reescribirArchivo(a,b,c,ficheroEscritura2);
    ficheroEscritura2.close();
}

void borrarCliente(vector<string> &a,vector<string> &b,vector<string> &c,ifstream &f){
    string nombre,apellidos,telefono,busqueda;
    a.clear();
    b.clear();
    c.clear();
    bool encontrado=false;
    char seguro='N';
    unsigned int indice=0;
    cin.ignore();
    cout<<"QUE CLIENTE DESEAS BORRAR: "<<endl;
    getline(cin,busqueda);
    while(!f.eof()){
        getline(f,nombre);
        if(!f.eof())
            a.push_back(nombre);
        getline(f,apellidos);
        if(!f.eof())
            b.push_back(apellidos);
        getline(f,telefono);
        if(!f.eof())
            c.push_back(telefono);
        if(busqueda==nombre || busqueda==apellidos || busqueda==telefono){
            cout<<"CLIENTE ENCONTRADO."<<endl;
            cout<<nombre<<" "<<apellidos<<" "<<telefono<<endl;
            encontrado= true;
            cout<<"SEGURO QUE DESEAS BORRAR EL CLIENTE (S/N)"<<endl;
            cin>>seguro;
            cin.ignore();
            if(seguro=='S'|| seguro=='s'){
                a.pop_back();
                b.pop_back();
                c.pop_back();
            }
        }indice++;
    }
    if(encontrado== false)
        cout<<"NO HAY NINGUN CLIENTE CON ESE DATO."<<endl;
    f.close();
    ofstream ficheroEscritura3("clientes.txt");
    reescribirArchivo(a,b,c,ficheroEscritura3);
    ficheroEscritura3.close();
}

void leerArchivo(){
    string texto;
    fstream archivo;
    archivo.open("clientes.txt",std::ios::in);
    if (archivo.fail()==true){
        cout<<"NO SE PUDO LEER TU ARCHIVO POR: "<<strerror(errno)<<"\n";
        return ;
    }
    while (!archivo.eof()){
        getline(archivo,texto);
        cout<<texto<<"\n"<<" ";
    }
}

class Crypt {

public:
    virtual char encrypt(char c) = 0;
    virtual char decrypt(char c) = 0;
};

class SimpleCrypt : public Crypt {

public:
    char encrypt(char c) override {
        return c + 5;
    }

    char decrypt(char c) override {
        return c - 5;
    }
};

class Cryptographer {
public:
    void encryptFile(const string& inputFile, const string& outputFile, Crypt& crypt) {
        ifstream inFile(inputFile, ios::binary);
        ofstream outFile(outputFile, ios::binary);

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Error al abrir el archivo" << endl;
            return;
        }

        char ch;
        while (inFile.get(ch)) {
            outFile.put(crypt.encrypt(ch));
        }

        cout << "Archivo cifrado correctamente." << endl;

        inFile.close();
        outFile.close();
    }

    void decryptFile(const string& inputFile, const string& outputFile, Crypt& crypt) {
        ifstream inFile(inputFile, ios::binary);
        ofstream outFile(outputFile, ios::binary);

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Error al abrir el archivo" << endl;
            return;
        }

        char ch;
        while (inFile.get(ch)) {
            outFile.put(crypt.decrypt(ch));
        }

        cout << "Archivo descifrado correctamente." << endl;

        inFile.close();
        outFile.close();
    }
};