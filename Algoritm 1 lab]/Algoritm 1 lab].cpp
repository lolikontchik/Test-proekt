#include "Solver.h"
#include <iostream>
#include <locale>
#include <vector>

int main() {
    setlocale(LC_ALL, "rus");

    const int    timeNStart = 3;
    const int    timeNEnd = 13;
    const int    timeNStep = 1;
    const double timeStop = 10.0;
    const long long timeMin = 1;
    const long long timeMax = 1000;

    struct QualityCase {
        int n;
        long long minCost;
        long long maxCost;
        int runs;
    };
    const std::vector<QualityCase> qualityCases = {
        { 4,   1,   10, 5 },
        { 4,   1,  100, 5 },
        { 4,   1, 1000, 5 },
        { 6,   1,  100, 5 },
        { 6,   1, 1000, 5 },
        { 8,   1,  100, 4 },
        { 8,   1, 1000, 4 },
        { 10,  1,  100, 3 },
        { 10,  1, 1000, 3 },
        { 11,  1, 1000, 3 },
    };
    const bool qualityShowDetails = true;

    const std::vector<int> largeSizes = { 100, 1000 };
    const long long largeMin = 1;
    const long long largeMax = 1000;
    const int       largeRuns = 4;

    std::cout << "=============================================\n";
    std::cout << "--- ТЕСТ 1. Рост времени полного перебора ---\n";
    std::cout << "=============================================\n";
    runTimeExperiments(timeNStart, timeNEnd, timeNStep,
        timeStop, timeMin, timeMax);

    std::cout << "\n=============================================\n";
    std::cout << "--- ТЕСТ 2. Качество жадного алгоритма ---\n";
    std::cout << "=============================================\n";
    for (const auto& c : qualityCases) {
        runQualityReport(c.n, c.minCost, c.maxCost,
            c.runs, qualityShowDetails);
    }

    std::cout << "\n=============================================\n";
    std::cout << "--- ТЕСТ 3. Жадный алгоритм на больших N ---\n";
    std::cout << "=============================================\n";
    runLargeScaleReport(largeSizes, largeMin, largeMax, largeRuns);

    return 0;
}