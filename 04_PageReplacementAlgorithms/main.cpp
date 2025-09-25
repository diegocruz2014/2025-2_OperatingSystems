#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Algoritmo LRU
int lru(const vector<int>& pages, int frames) {
    list<int> memory; // Lista que almacenará las páginas en memoria
    unordered_map<int, list<int>::iterator> pagesMap;
    int pagesFaults = 0; // contador de fallos de páginas

    // Ciclo para elaborar el proceso con cada página
    for (int page : pages) {
        // Si la página ya está en memoria, se elimina de su posición actual
        if (pagesMap.find(page) != pagesMap.end()) {
            memory.erase(pagesMap[page]);
        }
        // Si la página no se encuentra en memoria, se almacenará
        else {
            // Si la memoria está llena, se elimina la página menos utilizada; es
            // decir, la última en la lista
            if (memory.size() >= frames) {
                int lruPage = memory.back();
                memory.pop_back();
                pagesMap.erase(lruPage);
            }
            pagesFaults++;
        }
        // Se adiciona la nueva página al inicio de la lista
        memory.push_front(page);
        pagesMap[page] = memory.begin();

        // Mostrar el estado actual de la memoria caché
        cout << "Estado actual de la memoria caché: ";
        for (int p : memory) cout << p << " ";
        cout << "| Fallos: " << pagesFaults << endl;
    }
    // Retornar la cantidad de fallos de páginas
    return pagesFaults;
}

// Algoritmo FIFO
int fifo(const vector<int>& pages, int frames) {
    queue<int> memory; // Se utiliza una cola para almacenar el orden de llegada de las páginas en memoria
    unordered_map<int, bool> inMemory; // Se usa un mapa para saber qué páginas están en memoria
    bool found; // Bandera para señalar que se encontró una página en memoria
    int pageFaults = 0; // Contador de fallos de página

    // Elaborar el proceso para cada una de las páginas
    for (int page : pages) {
        found = false;
        if(!inMemory[page]) { // Si no se encuentra una página en memoria
            pageFaults++;
            if (memory.size() == frames) {
                // Si la memoria caché está llena se elimina la primera página en la memoria
                int removed = memory.front();
                memory.pop();
                inMemory[removed] = false;
            }
            memory.push(page);
            inMemory[page] = true;
        }
        else found = true;

        // Mostramos el estado actual de la memoria caché
        cout << "Estado actual de la memoria caché: ";
        queue<int> copy = memory;
        while(!copy.empty()) {
            cout << copy.front() << " ";
            copy.pop();
        }
        cout << "| Fallos: " << pageFaults;
        if(found) cout << " | La página " << page << " ya está en memoria.";
        cout << endl;
    }
    return pageFaults;
}

// Algoritmo óptimo
int optimal(const vector<int>& pages, int frames) {
    vector<int> memory; // lista de páginas en memoria.
    int pagesFaults = 0; // Contador de fallos de página.

    // LLevar a cabo el proceso de simulación con cada página
    for (size_t i = 0; i < pages.size(); i++) {
        // Buscar la página en memoria. Si la página no está en memoria, se produce
        // un fallo de pàgina
        if (find(memory.begin(), memory.end(), pages[i]) == memory.end()) {
            pagesFaults++;
            // Verificar si la memoria está llena
            if (memory.size() == frames) {
                // Las siguientes acciones se realizan si el contenedor memory está lleno
                // Se busca la página que se utilizará el futuro y será reemplazada.
                // farthest: Inicialmente a este elemento se le asigna inicialmente el
                // valor de i y servirá para determinar la referencia más lejana en el futuro.
                // replaceIndex: Se inicia en -1 y almacenará el índice en memory de la página a
                // reemplazar si se encuentra en un futuro. Si no se encuentra en un futuro, será
                // la referencia al último elemento en memory.
                int farthest = i, replaceIndex = -1;
                // Con el siguiente ciclo se recorre cada página cargada en memory
                for (size_t j = 0; j < memory.size(); j++) {
                    size_t k;
                    // Con el siguiente ciclo se busca la próxima referencia de la página actual
                    for (k = i + 1; k < pages.size(); k++) {
                        if (memory[j] == pages[k]) break;
                    }
                    if (k > farthest) {
                        // Determinar la página más lejana en el futuro
                        farthest = k; // Se actualiza farthest
                        replaceIndex = j; // Se actualiza replaceIndex
                    }
                }
                // Reemplazar la página seleccionada
                memory[replaceIndex] = pages[i];
            }
                // Si todavía hay espacio en memory (la memoria aún no está llena), simplemente se
                // añade la nueva página al final de la lista memory.
            else {
                memory.push_back(pages[i]);
            }
        }
        // Mostrar el estado actual del caché
        cout << "Estado actual de la memoria caché: ";
        for (int p: memory) cout << p << " ";
        cout << "| Fallos: " << pagesFaults << endl;
    }
    return pagesFaults;
}

// Algoritmo Reloj
int clock(const vector<int>& pages, int frames) {
    vector<int> memory(frames, -1);
    vector<bool> refBit(frames, false);
    int pagefaults = 0, pointer = 0;

    // Simulación para cada página
    for (int page : pages) {
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) {
            pagefaults++;
            while (refBit[pointer]) {
                refBit[pointer] = false;
                pointer = (pointer + 1) % frames;
            }
            memory[pointer] = page;
            refBit[pointer] = true;
            pointer = (pointer + 1) % frames;
        }
        else {
            refBit[it - memory.begin()] = true;
        }
        // Mostrar el estado actual de la memoria caché
        cout << "Estado actual de la memoria caché: ";
        for (int p : memory) {
            if (p != -1) cout << p;
            cout << " ";
        }
        cout << "| fallos: " << pagefaults << endl;
    }
    return pagefaults;
}

// Función principal
int main() {
    // Crear las variables para la memoria caché y la cantidad de
    // páginas que se obtendrá
    int frames, numPages;
    cout << "Ingrese el tamaño de la memoria caché: ";
    cin >> frames;
    cout << "Ingrese la cantidad de páginas que se procesará: ";
    cin >> numPages;

    // Crear un arreglo que almacene las páginas ingresadas
    vector<int> pages(numPages);

    // Ingresar las páginas para almacenarlas en el arreglo creado
    cout << "Ingrese " << numPages << " números enteros separados por espacios para simular las páginas: ";
    for (int i = 0; i < numPages; i++) cin >> pages[i];

    // Crear cuatro valores enteros para recibir las fallas de cada
    // algoritmo procesado
    int f1, f2, f3, f4;

    cout << "Algoritmo LRU: " << endl;
    f1 = lru(pages, frames);

    cout << "\nAlgoritmo FIFO: " << endl;
    f2 = fifo(pages, frames);

    cout << "\nAlgoritmo Óptimo: " << endl;
    f3 = optimal(pages, frames);

    cout << "\nAlgoritmo Reloj: " << endl;
    f4 = clock(pages, frames);

    cout << "\nCantidad de fallos de página en cada algoritmo: " << endl;
    cout << "LRU: " << f1 << endl;
    cout << "FIFO: " << f2 << endl;
    cout << "Optimal: " << f3 << endl;
    cout << "Clock: " << f4 << endl;
    return 0;
}

