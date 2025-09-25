// Algoritmo Swapping (Paginación y gestión de memoria virtual)

#include <iostream>     // Entrada y salida estándar
#include <vector>       // Para manejar listas de procesos
#include <queue>        // Para representar la cola de espera
#include <chrono>       // Para simular el tiempo
#include <thread>       // Para simular espera

using namespace std;
using namespace chrono;

// Estructura que representa un proceso con nombre y duración de
// ejecución
struct Proceso {
    string nombre;
    int tiempoEjecucion; // tiempo dado en segundos

    // El proceso asignará "n" a "nombre" y "t" a "tiempoEjecucion"
    Proceso(string n, int t) : nombre(n), tiempoEjecucion(t) {}
};

// Simulación del Swapping
int ejecutarProceso(const Proceso& p){
    // Carga del proceso
    cout << "Cargando proceso " << p.nombre << " a memoria...\n";
    this_thread::sleep_for(seconds(1)); // Simulación del swap-in

    auto inicio = steady_clock::now(); // Marco el tiempo de inicio de ejecución del proceso

    // Ejecución del proceso
    cout << "Ejecutando " << p.nombre << " por " << p.tiempoEjecucion << " segundos...\n";
    this_thread::sleep_for(seconds(p.tiempoEjecucion));

    // Cierre del proceso
    cout << "Descargando proceso " << p.nombre << " de memoria...\n";
    this_thread::sleep_for(seconds(1)); // Simulación del swap-out

    auto fin = steady_clock::now();

    auto duracion = duration_cast<seconds>(fin - inicio).count() + 2;

    return duracion;
}


// Función principal
int main() {
     // Crear una cola con procesos para ejecutarse
    queue<Proceso> colaListos;
    int usoTotalMemoria = 0;

    // Agregamos procesos a la cola
    colaListos.push(Proceso("Editor de texto", 2));
    colaListos.push(Proceso("Call of duty", 3));
    colaListos.push(Proceso("CLion", 1));

    // Ejecutar todos los procesos uno a uno
    while (!colaListos.empty()) {
        Proceso actual = colaListos.front(); // Toma el primer proceso
        colaListos.pop();                    // Se elimina de la cola

        int duracion = ejecutarProceso(actual); // Se procesa con swap-in, run, swap-out
        usoTotalMemoria += duracion;

        cout << "Tiempo total en memoria del proceso " << actual.nombre << ": " << duracion << " segundos." << endl;
        cout << "---------------------------------\n";
    }

    cout << "Tiempo total del uso de memoria por todos los procesos: " << usoTotalMemoria << " segundos\n";
    cout << "Todos los procesos han sido ejecutados y descargados de memoria.";
    return 0;
}
