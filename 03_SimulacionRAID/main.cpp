#include <iostream>
#include <fstream>
using namespace std;

// Función para escribir RAID 0
void writeRAID0(const string& data, const string& disk1, const string& disk2){
    ofstream out1(disk1), out2(disk2);
    // Verificar si los dos archivos se crearon correctamente
    if (!out1 || !out2){
        cerr << "Error al abrir los discos\n";
        return;
    }
    // Si los archivos se crearon bien, continúo ingresando información en ellos
    for (size_t i = 0; i < data.size(); i++){
        if (i % 2 == 0){
            out1 << data[i]; // Caracteres en posiciones pares van hacia el disco 1
        }
        else {
            out2 << data[i]; // Caracteres en posiciones impares van hacia el disco 2
        }
    }
    // Cerrar los archivos
    out1.close();
    out2.close();
}

// Función para leer RAID0
void readRAID0(const string& disk1, const string& disk2){
    ifstream in1(disk1), in2(disk2);

    // Verificar si los dos archivos se abrieron correctamente
    if (!in1 || !in2){
        cerr << "Error al abrir los discos\n";
        return;
    }

    // Si los archivos se abrieron correctamente, continúo ingresando información en ellos
    string data1, data2, result;
    getline(in1, data1);
    getline(in2, data2);

    // Se obtiene las longitudes de las cadenas data1 y data2
    size_t len1 = data1.size(), len2 = data2.size();
    size_t maxLen = max(len1, len2);

    // Simulación de lectura de RAID 0 en dos discos
    for(size_t i=0; i < maxLen; i++){
        if (i < len1) result += data1[i];
        if (i < len2) result += data2[i];
    }

    //Mostrar resultados
    cout << "Datos leídos en RAID 0: " << result << endl;
}

// Función para escribir en RAID 1
void writeRAID1(const string& data, const string& disk1, const string& disk2){
    ofstream out1(disk1), out2(disk2);

    // Verificar si se crearon correctamente los archivos que simulan discos
    if(!out1 || !out2){
        cerr << "Error al abrir los discos\n";
        return;
    }

    // Si es correcto, continuamos
    out1 << data;
    out2 << data;
    cout << "Datos almacenados en RAID 1,\n";

    // Cerrar los archivos
    out1.close();
    out2.close();
}

// Función para leer RAID 1
void readRAID1(const string& disk1, const string& disk2) {
    ifstream in1(disk1), in2(disk2);

    // Verificar si se obtuvieron los discos simulados correctamente
    if(!in1 || !in2) {
        cerr << "Error al abrir el disco\n";
        return;
    }

    // Si es correcto, continuamos
    string data1, data2;
    getline(in1, data1);
    cout << "Datos leídos de RAID 1 (disk1): " << data1 << endl;
    getline(in2, data2);
    cout << "Datos leídos de RAID 1 (disk2): " << data2 << endl;
}

// Función principal
int main() {
    int option;
    string data;
    string disk1 = "disk1.txt", disk2 = "disk2.txt";
    cout << "Simulador de RAID en C++\n"
            "1. Escribir en RAID 0\n"
            "2. Leer RAID 0\n"
            "3. Escribir en RAID 1\n"
            "4. Leer RAID 1\n"
            "5. Salir\n";

    while (true) {
        cout << "Seleccione una opción: ";
        cin >> option;
        cin.ignore(); // Limpiar la consola

        switch (option) {
            case 1:
                cout << "Ingrese los datos para RAID 0: ";
                getline(cin, data);
                writeRAID0(data, disk1, disk2);
                break;
            case 2:
                readRAID0(disk1, disk2);
                break;
            case 3:
                cout << "Ingrese datos para RAID 1: ";
                getline(cin, data);
                writeRAID1(data, disk1, disk2);
                break;
            case 4:
                readRAID1(disk1, disk2);
                break;
            case 5:
                cout << "Saliendo...\n";
                return 0;
            default:
                cout << "Opción no válida\n";
        }
    }
}
