#include <iostream>
#include <vector>               // Para almacenar la secuencia de referencias
#include <unordered_set>        // Para representar las páginas en memoria
#include <deque>                // Para implementar la ventana de observación

using namespace std;

// Parámetros del algoritmo
const int TOTAL_MARCOS = 6;     // Cantidad total de marcos disponibles en el sistema
const int UMBRAL_FALLOS = 3;    // Umbral de fallos recientes para aumentar marcos
const int VENTANA = 5;          // Tamaño de la ventana de observación

// Función que simula el comportamiento del algoritmo PFF
int simularPFF(const vector<int>& referencias) {
    int marcos_asignados = 3;   // Cantidad inicial
    int fallos_totales = 0;     // Contador global de fallos de página

    deque<int> ventana;         // Últimas páginas accedidas (FIFO)
    unordered_set<int> memoria; // Conjunto de páginas actualmente en memoria

    cout << "Simulación del algoritmo Page Fault Frequency (PFF) iniciada" << endl;

    for(int i = 0; i < referencias.size(); ++i) {
        int pagina = referencias[i];
        bool fallo = false;

        // Verificar si la página está en memoria
        if (memoria.find(pagina) == memoria.end()) {
            fallo = true;
            fallos_totales++;

            // Si no hay espacio en memoria, eliminar la página más antigua
            if (memoria.size() >= marcos_asignados) {
                memoria.erase(ventana.front());
                ventana.pop_front();
            }

            // Insertar la nueva página
            memoria.insert(pagina);
        }

        // Añadir la página a la ventana de observación
        ventana.push_back(pagina);
        if (ventana.size() > VENTANA) {
            ventana.pop_front();
        }

        // Contar fallos recientes en la ventana
        int fallos_recientes = 0;
        unordered_set<int> revisados;
        for (int j = i - VENTANA + 1; j <= i && j >= 0; ++j) {
            int pag = referencias[j];
            if (revisados.find(pag) == revisados.end()) {
                revisados.insert(pag);
                if (memoria.find(pag) == memoria.end()) {
                    fallos_recientes++;
                }
            }
        }

        // Ajustar marcos si se supera el umbral de fallos recientes
        if (fallos_recientes >= UMBRAL_FALLOS && marcos_asignados < TOTAL_MARCOS) {
            marcos_asignados++;
            cout << "Alta frecuencia de fallos detectada. Se aumenta el número de marcos a " << marcos_asignados << endl;
        }
        // Reducir marcos si no hay fallos recientes
        else if (fallos_recientes == 0 && marcos_asignados > 1) {
            marcos_asignados--;
            cout << "Frecuencia baja de fallos. Se reduce el número de marcos a " << marcos_asignados << endl;
        }

        // Mostrar resultado del acceso
        cout << "Acceso a página " << pagina;
        if (fallo) {
            cout << " - Fallo de página" << endl;
        }
        else {
            cout << " - Página presente en memoria" << endl;
        }
    }

    // Mostrar el resumen de la simulación
    cout << "Total de fallos de página: " << fallos_totales << endl;
    return fallos_totales;
}

// Función principal
int main() {
    // Secuencia de referencias de página
    vector<int> referencias = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3};

    // Ejecutar la simulación
    simularPFF(referencias);

    return 0;
}
