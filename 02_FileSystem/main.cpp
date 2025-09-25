#include <iostream>
#include <fstream> // Para creación y lectura de ficheros (archivos/directorios)
#include <filesystem> // Para la administración de ficheros

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem; // Alias para la biblioteca filesystem
using namespace std;

// Función para habilitar UTF-8 en Windows
void configurarConsola() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

// Función para crear un archivo y escribir datos en él
void crearArchivo(const string& ruta){
    // ofstream se incluye en la biblioteca <fstream>, se
    // utiliza para crear y abrir un archivo en la ruta
    // pasada como parámetro
    ofstream archivo(ruta);
    // Verificar que la operación se realizó correctamente
    if (archivo) {
        cout << "Ingrese el contenido del archivo: " << endl;
        string contenido; // Crear un string llamado contenido
        cin.ignore(); // Limpiar el buffer
        // Obtener la información ingresada en consola y
        // entregarla a la variable "contenido"
        getline(cin, contenido);
        archivo << contenido; // Entregar la información almacenada en "contenido" a "archivo"
        archivo.close(); // Cerrar el archivo
        cout << "Archivo creado exitosamente en: " << ruta << endl;
    }
    else {
        cerr << "Error al crear el archivo." << endl;
    }
}

// Función para leer un archivo
void leerArchivo(const string& ruta) {
    // Abrir el archivo que se encuentra
    // en la ruta establecida para que se pueda leer
    ifstream archivo(ruta);
    // Verificar si la operación se llevó a cabo correctamente y continuar
    if (archivo) {
        cout << "Contenido del archivo: " << endl;
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    }
    else {
        cerr << "Error al abrir el archivo. Verifique que existe.";
    }
}

// Función para eliminar un archivo
void eliminarArchivo(const string& ruta) {
    // Si la acción de eliminar el archivo se ejecuta correctamente
    if(fs::remove(ruta)) {
        cout << "Archivo eliminado correctamente." << endl;
    }
    else {
        cerr << "Error al eliminar el archivo, posiblemente el archivo no existe." << endl;
    }
}

// Función para crear un directorio
void crearDirectorio(const string& ruta) {
    // Función para crear un directorio.
    // Para crear varios directorios en un solo comando,
    // se utiliza create_directories
    if(fs::create_directory(ruta)) {
        cout << "Directorio creado correctamente en: " << ruta << endl;
    }
    else {
        cerr << "Error al crear el directorio. Puede que ya exista." << endl;
    }
}

// Función para eliminar un directorio
void eliminarDirectorio(const string& ruta){
    if (fs::remove_all(ruta)) {
        cout << "Directorio eliminado correctamente." << endl;
    }
    else {
        cout << "Error al eliminar el directorio." << endl;
    }
}

// Función para listar el contenido de un directorio
void listarDirectorio(const string& ruta) {
    if(fs::exists(ruta) && fs::is_directory(ruta)) {
        // fs::directory_iterator(ruta) crea un elemento (iterador) que recorre todos
        // los archivos y subdirectorios dentro del directorio especificado en la ruta.
        for (const auto& entrada : fs::directory_iterator(ruta)) {
            cout << (fs::is_directory(entrada) ? "[DIR] " : "[FILE] ")
                 << entrada.path().filename() << endl;
        }
    }
}

// Función para mostrar información de un archivo
void informacionArchivo(const string& ruta) {
    if(fs::exists(ruta)) {
        cout << "Información del archivo " << ruta << ":\n";
        cout << "Tamaño: " << fs::file_size(ruta) << " bytes\n";
        cout << "Última modificación: " << fs::last_write_time(ruta).time_since_epoch().count() << endl;
    }
    else {
        cerr << "El archivo no existe." << endl;
    }
}

// Función principal para utilizar las demás funciones
void menu() {
    int opcion;
    string ruta;

    configurarConsola(); // Asegurar compatibilidad con UTF-8 en Windows

    do {
        cout << "\n--- SISTEMA DE ARCHIVOS EN C++ ---\n";
        cout << "1. Crear archivo\n";
        cout << "2. Leer archivo\n";
        cout << "3. Eliminar archivo\n";
        cout << "4. Crear directorio\n";
        cout << "5. Eliminar directorio\n";
        cout << "6. Listar directorio\n";
        cout << "7. Información del archivo\n";
        cout << "8. Salir\n\n";
        cout << "Seleccione una opción: ";
        cin >> opcion; // El valor ingresado en consola se otorga a la variable opcion

        switch (opcion) {
            case 1:
                cout << "Ingrese la ruta completa del archivo a crear: ";
                cin >> ruta;
                crearArchivo(ruta);
                break;
            case 2:
                cout << "Ingrese la ruta completa del archivo a leer: ";
                cin >> ruta;
                leerArchivo(ruta);
                break;
            case 3:
                cout << "Ingrese la ruta completa del archivo a eliminar: ";
                cin >> ruta;
                eliminarArchivo(ruta);
                break;
            case 4:
                cout << "Ingrese la ruta del directorio a crear: ";
                cin >> ruta;
                crearDirectorio(ruta);
                break;
            case 5:
                cout << "Ingrese la ruta del directorio a eliminar: ";
                cin >> ruta;
                eliminarDirectorio(ruta);
                break;
            case 6:
                cout << "Ingrese la ruta del directorio a listar: ";
                cin >> ruta;
                listarDirectorio(ruta);
                break;
            case 7:
                cout << "Ingrese la ruta completa del archivo: ";
                cin >> ruta;
                informacionArchivo(ruta);
                break;
            case 8:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "La opción ingresada no es válida. Intente de nuevo.\n";
                break;
        }
    } while(opcion != 8);
}

int main() {
    menu();
    return 0;
}
