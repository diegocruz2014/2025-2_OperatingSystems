#include <iostream>
#include <thread> // Para crear y manipular múltiples hilos
#include <mutex> // Para utilizar mutex (algo como un embudo) y garantizar exlusión mútua
#include <array> // Para usar vectores fijos
#include <chrono> // Para simular pausas (pensar/comer)

using namespace std;

// Se define la cantidad de filósofos (y tenedores)
const int numFilosofos = 5;

// Se declara un arreglo de mutexes para representar los tenedores
array<mutex, numFilosofos> tenedores;

// Función que simula el comportamiento de cada filósofo
void filosofo(int id) {
    int izquierda = id; // Tenedor a la izquierda del filósofo
    int derecha = (id + 1) % numFilosofos; // Tenedor a la derecha del filósofo

    while (true) {
        // Fase de pensar
        cout << "Filosofo " << id << " está pensando...\n";
        this_thread::sleep_for(chrono::milliseconds(500)); // Pausa de 0.5 segundos

        // Prevenir interbloqueo cambiando el orden en que se toman los tenedores
        if (id % 2 == 0) {
            // Filósofos con id par toman primero el tenedor izquierdo, luego el derecho
            tenedores[izquierda].lock(); // Toma el tenedor izquierdo
            tenedores[derecha].lock(); // Toma el tenedor derecho
        }
        else {
            // Filósofos con id impar toman primero el tenedor derecho, luego el izquierdo
            tenedores[derecha].lock(); // Toma el tenedor derecho
            tenedores[izquierda].lock(); // Toma el tenedor izquierdo
        }

        // Fase de comer
        cout << "Filósofo " << id << " está comiendo\n";
        this_thread::sleep_for(chrono::milliseconds(1000)); // Pausa de un (1) segundo

        // Soltar los tenedores después de comer
        tenedores[izquierda].unlock(); // Suelta el tenedor izquierdo
        tenedores[derecha].unlock(); // Suelta el tenedor derecho
    }
}

// Método principal
int main() {
    // Crear un arreglo de hilos, uno por cada filósofo
    array<thread, numFilosofos> filosofos;

    // Iniciar cada hilo con la función filosofo() pasándole su id
    for (int i = 0; i < numFilosofos; ++i) {
        filosofos[i] = thread(filosofo, i);
    }

    // Unir los hilos (aunque en este caso no finalizarán porque
    // cada filósofo tiene en su interior un bucle infinito
    for (auto& f : filosofos)
    {
        f.join(); // Espera a que el hilo termine (en este caso, nunca termina)
    }

    return 0;
}



