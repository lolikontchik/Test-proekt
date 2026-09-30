#include "Header.h"
#include <iostream>
#include <locale>

int main() {
    setlocale(LC_ALL, "rus");
    // Рост времени полного перебора
    TspSolver::runTimeExperiments(13, 10.0);

    // Отчёты о качестве эвристики
    std::cout << "\nОтчёты о качестве эвристики\n";

    TspSolver::runQualityReport(4, 1, 10, 5);
    TspSolver::runQualityReport(4, 1, 100, 5);
    TspSolver::runQualityReport(4, 1, 1000, 5);

    TspSolver::runQualityReport(6, 1, 100, 5);
    TspSolver::runQualityReport(6, 1, 1000, 5);

    TspSolver::runQualityReport(8, 1, 100, 4);
    TspSolver::runQualityReport(8, 1, 1000, 4);

    TspSolver::runQualityReport(10, 1, 100, 3);
    TspSolver::runQualityReport(10, 1, 1000, 3);

    return 0;
}