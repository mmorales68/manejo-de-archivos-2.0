#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
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