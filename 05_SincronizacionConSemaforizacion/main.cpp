#include <iostream>
#include <thread> // Creación y manejo de hilos
#include <mutex> // Sincronización con mutexes y variables de condición
#include <queue> // Procesos y representación del buffer
#include <chrono> // Medir el tiempo en cada proceso
#include <condition_variable>

using namespace std;

// Variables globales
const int bufferSize = 5; // Se define la capacidad máxima del buffer
queue<int> buffer;
mutex mtx; // Protege el acceso al buffer
// Señales para controlar cuando el productor o el consumidor deben esperar
condition_variable buffer_not_full, buffer_not_empty;

int item = 0; // Cuenta los ítems producidos

void productor(int id) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100)); // Simular tiempo de producción
        unique_lock<mutex> lock(mtx); // Permite el paso de los elementos uno a uno
        buffer_not_full.wait(lock, []() { return buffer.size() < bufferSize; });

        item++; // Aumenta la cuenta de item
        buffer.push(item);
        cout << "Productor " << id << " produjo item " << item << ". Buffer: " << buffer.size() << endl;

        buffer_not_empty.notify_one(); // Notifica al consumidor
    }
}

void consumidor(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        buffer_not_empty.wait(lock, []() {return !buffer.empty(); });

        int consumed_item  = buffer.front(); // Otorgo a consumed_item el primer elemento de la cola
        buffer.pop();
        cout << "Consumidor " << id << " consumió item " << consumed_item << ". Buffer: " << buffer.size() << endl;

        buffer_not_full.notify_one(); // Notifica al productor

        lock.unlock(); // Se desbloquea el elemento tipo mutex para que el hilo pase
        this_thread::sleep_for(chrono::milliseconds(150)); // Simula el tiempo de consumo
    }
}


int main() {
    // Crear hilos productores y consumidores
    thread prod1(productor, 1);
    thread cons1(consumidor, 1);
    thread cons2(consumidor, 2);

    prod1.join();
    cons1.join();
    cons2.join();

    return 0;
}
