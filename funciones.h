//
// Created by mmora on 20/04/2024.
//

#ifndef MANEJO_DE_ARCHIVOS_2_0_FUNCIONES_H
#define MANEJO_DE_ARCHIVOS_2_0_FUNCIONES_H

#endif //MANEJO_DE_ARCHIVOS_2_0_FUNCIONES_H
#include "windows.h"
#include "iostream"
#include "fstream"
#include "string"
#include "regex"
#include "unordered_map"
#include "filesystem"

using namespace std;
namespace fs = std::filesystem;

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


string getGTQ_USD(){

    //comando de PowerShell para descargar el contenido HTML de la URL
    string powershellCommand = "powershell.exe -Command \"(Invoke-WebRequest -Uri 'https://www.banguat.gob.gt/tipo_cambio/').Content\"";

    char buffer[128];
    string result;

    //abrir una "tuberia" al proceso de PowerShell y leer su salida
    FILE* pipe = _popen(powershellCommand.c_str(), "r");
    if (!pipe) {
        cerr << "Error al abrir la tubería al proceso de PowerShell." <<endl;
        return "";
    }

    // Leer la salida línea por línea y almacenarla en 'result'
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    _pclose(pipe); //cerrar la tubería

    //expresión regular para encontrar el numero dentro de las etiquetas <td align="center"></td>
    regex regexPattern(R"(<td align="center">(\d+(\.\d+)?)</td>)");
    smatch match;

    //buscar la primera coincidencia dentro del HTML obtenido
    if (regex_search(result, match, regexPattern)) {

        return match.str(1);//el primer grupo de captura contiene el número encontrado
    }

    return "";
}

int calculadoraGTQ_USD(){
    try {
        double precioDolar = stod(getGTQ_USD()), quetzales, resultado;
        cout<<"Ingrese la cantidad de quetzales a convertir:  ";
        cin >> quetzales;

        resultado = quetzales / precioDolar;

        cout << "Tasa de conversion en BANGUAT de GTQ a USD=" << fixed << precioDolar << endl;
        cout << "Resultado= $ " << fixed <<resultado << endl;
    }catch(exception& e){
        cout << "Error: " << e.what() << endl;
        if (string( e.what())=="stod"){
            cout << "Asegurese de estar conectado a internet e intentar nuevamente"<<endl;
        }
    }
    system("pause");
    return 0;
}

int calculadoraUSD_GTQ(){
    try {
        double precioDolar = stod(getGTQ_USD()), cantidad, resultado;
        cout<<"Ingrese la cantidad de dolares a convertir:  ";
        cin >> cantidad;

        resultado = cantidad * precioDolar;

        cout << "Tasa de conversion en BANGUAT de GTQ a USD=" << fixed << precioDolar << endl;
        cout << "Resultado= Q " << fixed << resultado << endl;
    }catch(exception& e){
        cout << "Error: " << e.what() << endl;
        if (string( e.what())=="stod"){
            cout << "Asegurese de estar conectado a internet e intentar nuevamente"<<endl;
        }
    }
    system("pause");
    return 0;
}


string obtenerNombreTecla(int keyCode) {
    char nombreTecla[256] = {0 };
    int scanCode = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);
    int result = GetKeyNameTextA(scanCode << 16, nombreTecla, sizeof(nombreTecla));
    if (result == 0) {
        return "";
    }
    return nombreTecla;
}

void keylogger(){
    ofstream outputFile("teclas_pulsadas.txt");

    cout << "Las teclas se estan capturando, Presiona 'Esc' para salir." << endl;

    bool ejecucion = true;
    unordered_map<int, bool> keyState; // Mapa para mantener el estado de las teclas

    while (ejecucion) {
        // Iterar sobre todos los posibles códigos de tecla (0-255)
        for (int keyCode = 0; keyCode < 256; ++keyCode) {
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                // La tecla está siendo presionada
                if (!keyState[keyCode]) {
                    // La tecla ha sido presionada por primera vez
                    string keyName = obtenerNombreTecla(keyCode);
                    if (!keyName.empty()) {
                        // Guardar la tecla presionada en el archivo
                        outputFile << keyName << endl;

                        // Mostrar la tecla presionada en la consola
                        cout << "Tecla '" << keyName << "' registrada." << endl;

                        // Finalizar el programa si se presiona 'Esc'
                        if (keyCode == VK_ESCAPE) {
                            ejecucion = false;
                            break;
                        }
                    }
                }
                // Marcar la tecla como presionada
                keyState[keyCode] = true;
            } else {
                // La tecla no está siendo presionada
                keyState[keyCode] = false;
            }
        }

        Sleep(10);
    }

    outputFile.close();
    cout << "Presiona cualquier tecla para salir." << endl;
    system("pause");
}


void crearCarpeta(){
    string directorio;
    cout << "Ingrese la ruta del directorio donde desea crear la carpeta: "<< endl;
    cin>>directorio;
    if (!fs::exists(directorio)) {
        cerr << "El directorio especificado no existe." <<endl;
    }
    string nombreCarpeta;
    cout << "Ingrese el nombre de la carpeta que desea crear: "<<endl;
    cin>>nombreCarpeta;

    string rutaCompleta = directorio + "/" + nombreCarpeta;
    if (fs::create_directory(rutaCompleta)) {
        cout<<"Se creo la carpeta "<<nombreCarpeta<<" "<<"en el directorio especificado"<< endl;
    }else{
        cerr << "No se pudo crear la carpeta."<<endl;
    }
}

void crearArchivo(){
    string directorio;
    string nombreArchivo;
    string linea;
    cout << "Ingrese el directorio donde desea crear el archivo: "<< endl;
    cin>> directorio;
    cout << "Ingrese el nombre del archivo que desea crear: "<< endl;
    cin>>nombreArchivo;
    string rutaCompleta = directorio + "/" + nombreArchivo;
    ofstream archivoSalida(rutaCompleta, ios::out | ios::app);
    if (archivoSalida.is_open()) {
        cout<<"Introduzca las lineas que desea escribir en el archivo (escriba FIN para terminar)"<<endl;
        while (cin>>linea) {
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

int leer_escribir_texto() {
    ofstream archivoSalida("archivo.txt");

    if (!archivoSalida.is_open()) {
        cout << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }

    archivoSalida << "Hola, este es un archivo de texto." << endl;
    archivoSalida << "Puedes escribir lo que quieras aquí." << endl;
    cout << "ingrese el texto" << endl;
    //archivoSalida.close();

    ifstream archivoEntrada("archivo.txt");


    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo para lectura." << endl;
        return 1;
    }

    string linea;
    cout << "Contenido del archivo:" << endl;
    while (archivoEntrada>>linea) {
        cout << linea << endl;
    }
    system("pause");
    return 0;
}

int escribir_lineas() {
    // Abrir un archivo para escritura
    ofstream archivoSalida("datos.txt");

    // Verificar si el archivo se abrió correctamente
    if (!archivoSalida.is_open()) {
        cout << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }

    // Solicitar al usuario que ingrese líneas de texto
    cout << "Por favor, ingresa algunas líneas de texto. Escribe 'fin' para terminar." << endl;
    string linea;
    while (true) {
        cin>>linea;
        if (linea == "fin") // Terminar la entrada cuando el usuario escriba "fin"
            break;
        archivoSalida << linea << endl; // Escribir la línea en el archivo
    }

    // Cerrar el archivo de salida
    archivoSalida.close();

    // Abrir el archivo para lectura
    ifstream archivoEntrada("datos.txt");

    // Verificar si el archivo se abrió correctamente
    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo para lectura." << endl;
        return 1;
    }

    // miguel es guapo
    // Mostrar el contenido del archivo línea por línea
    cout << "Contenido del archivo:" << endl;
    while (getline(archivoEntrada, linea)) {
        cout << linea << endl;
    }

    // Cerrar el archivo de entrada
    archivoEntrada.close();

    archivoEntrada.close();

    return 0;
}