#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Planificación de procesos: Algoritmo FCFS (First Come First Served)

// Estructura para representar un proceso
struct Process {
    string id;
    int arrivalTime; // Tiempo que necesita el proceso para llegar a la cola de ejecución.
    int burstTime; // Tiempo que necesita el proceso para ejecutarse.
    int completionTime; // Tiempo en el que el proceso finaliza.
    int turnAroundTime; // Tiempo total de ejecución (finalización - llegada).
    int waitingTime; // Tiempo que el proceso espera en la cola antes de ejecutarse (turnAroundTime - ejecución).
};

// Método que recibe cada proceso y ejecuta el procesamiento
void fcfsSheduling(vector<Process>& processes) {
    int n = processes.size(); // Tamaño del arreglo de procesos
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    // Ordenamos los procesos por tiempo de llegada
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Calculamos los tiempos de finalización, retorno y espera del primer proceso
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].turnAroundTime = processes[0].completionTime - processes[0].arrivalTime;
    processes[0].waitingTime = 0;

    // Calculamos los tiempos de finalización, retorno y espera de los demás procesos
    for (int i = 1; i < n; i++){
        processes[i].completionTime = max(processes[i-1].completionTime, processes[i-1].arrivalTime) + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        // Calcular sumas totales
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }

    // Mostramos los resultados
    cout << "Proceso\tLlegada\tEjecución\tFinalización\tRetorno\tEspera\n";
    for(const auto& p : processes){
        cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime
             << "\t\t" << p.completionTime << "\t\t" << p.turnAroundTime
             << "\t" << p.waitingTime << endl;
    }

    // Calculamos y mostramos los tiempos promedio
    cout << "\nTiempo promedio de espera: " << (float)totalWaitingTime / n << " unidades" << endl;
    cout << "Tiempo promedio de retorno: " << (float)totalTurnAroundTime / n << " unidades" << endl;
}

int main() {
    vector<Process> processes = {
            {"P1", 0, 5},
            {"P2", 1, 3},
            {"P3", 2, 8},
            {"P4", 3, 6}
    };

    // Ejecutar la planificación FCFS
    fcfsSheduling(processes);

    return 0;
}
