#include "Solver.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

Matrix makeRandomMatrix(int n, long long minCost, long long maxCost) {
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<long long> dist(minCost, maxCost);

    Matrix m(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j) m[i][j] = dist(rng);
    return m;
}

long long pathCost(const Matrix& d, const std::vector<int>& path) {
    long long s = 0;
    for (size_t i = 0; i + 1 < path.size(); ++i)
        s += d[path[i]][path[i + 1]];
    return s;
}

static bool nextPermutation(std::vector<int>& p) {
    int n = static_cast<int>(p.size());
    int i = n - 2;
    while (i >= 0 && p[i] >= p[i + 1]) --i;
    if (i < 0) return false;

    int j = n - 1;
    while (p[j] <= p[i]) --j;

    std::swap(p[i], p[j]);
    std::reverse(p.begin() + i + 1, p.end());
    return true;
}

void solveExact(const Matrix& d, int start,
    long long& bestCost, std::vector<int>& bestPath,
    long long& worstCost, std::vector<int>& worstPath) {
    int n = static_cast<int>(d.size());

    bestPath.clear();
    worstPath.clear();
    bestCost = 0;
    worstCost = 0;

    if (n == 1) {
        bestCost = worstCost = 0;
        bestPath = worstPath = { start, start };
        return;
    }

    std::vector<int> perm;
    perm.reserve(n - 1);
    for (int i = 0; i < n; ++i)
        if (i != start) perm.push_back(i);
    std::sort(perm.begin(), perm.end());

    bestCost = std::numeric_limits<long long>::max();
    worstCost = -std::numeric_limits<long long>::max();

    std::vector<int> path;
    path.reserve(n + 1);

    do {
        path.clear();
        path.push_back(start);
        path.insert(path.end(), perm.begin(), perm.end());
        path.push_back(start);

        long long cur = pathCost(d, path);

        if (cur < bestCost) { bestCost = cur; bestPath = path; }
        if (cur > worstCost) { worstCost = cur; worstPath = path; }
    } while (nextPermutation(perm));
}

void solveNearestNeighbor(const Matrix& d, int start,
    long long& bestCost, std::vector<int>& bestPath) {
    int n = static_cast<int>(d.size());

    bestPath.clear();
    bestCost = 0;

    if (n <= 1) {
        bestCost = 0;
        bestPath = { start, start };
        return;
    }

    std::vector<bool> visited(n, false);
    bestPath.reserve(n + 1);

    int cur = start;
    visited[cur] = true;
    bestPath.push_back(cur);

    for (int step = 1; step < n; ++step) {
        int bestV = -1;
        long long bestW = std::numeric_limits<long long>::max();
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && d[cur][v] < bestW) {
                bestW = d[cur][v];
                bestV = v;
            }
        }
        bestPath.push_back(bestV);
        visited[bestV] = true;
        cur = bestV;
    }
    bestPath.push_back(start);
    bestCost = pathCost(d, bestPath);
}

void runTimeExperiments(int nStart, int nEnd, int nStep,
    double stopAfterSeconds,
    long long minCost, long long maxCost) {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\nРост времени полного перебора\n";
    std::cout << "Диапазон количества городов: [" << nStart << ".." << nEnd
        << "], шаг = " << nStep
        << ", остановка при времени > " << stopAfterSeconds << " с\n";
    std::cout << "Разброс стоимостей: [" << minCost << ".." << maxCost << "]\n\n";

    if (nStep <= 0) {
        std::cout << "Ошибка: шаг должен быть больше нуля.\n";
        return;
    }

    for (int n = nStart; n <= nEnd; n += nStep) {
        Matrix d = makeRandomMatrix(n, minCost, maxCost);

        long long bestCost = 0, worstCost = 0;
        std::vector<int> bestPath, worstPath;

        auto t1 = std::chrono::steady_clock::now();
        solveExact(d, 0, bestCost, bestPath, worstCost, worstPath);
        auto t2 = std::chrono::steady_clock::now();

        double sec = std::chrono::duration<double>(t2 - t1).count();
        std::cout << "Городов = " << std::setw(3) << n
            << " | время = " << std::setw(10) << sec << " с"
            << " | лучшее = " << bestCost
            << " | худшее = " << worstCost << '\n';

        if (sec > stopAfterSeconds) {
            std::cout << "  слишком долго, дальнейшие размерности пропускаем\n";
            break;
        }
    }
}

void runQualityReport(int n, long long minCost, long long maxCost,
    int runs, bool showDetails) {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nОтчёт: городов = " << n
        << ", разброс стоимостей = [" << minCost << ".." << maxCost << "]"
        << ", запусков = " << runs << "\n";

    double sumQuality = 0.0;
    double sumExactTime = 0.0;
    double sumHeurTime = 0.0;

    for (int run = 1; run <= runs; ++run) {
        Matrix d = makeRandomMatrix(n, minCost, maxCost);

        long long bestCost = 0, worstCost = 0, hcost = 0;
        std::vector<int> bestPath, worstPath, hpath;

        auto t1 = std::chrono::steady_clock::now();
        solveExact(d, 0, bestCost, bestPath, worstCost, worstPath);
        auto t2 = std::chrono::steady_clock::now();
        double exactTime = std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::steady_clock::now();
        solveNearestNeighbor(d, 0, hcost, hpath);
        auto t4 = std::chrono::steady_clock::now();
        double heurTime = std::chrono::duration<double>(t4 - t3).count();

        double quality = (worstCost == bestCost)
            ? 100.0
            : 100.0 * (double)(worstCost - hcost) / (double)(worstCost - bestCost);
        sumQuality += quality;
        sumExactTime += exactTime;
        sumHeurTime += heurTime;

        if (showDetails) {
            std::cout << "Запуск " << run << ":\n";
            std::cout << "  Точный метод:   лучшее = " << std::setw(6) << bestCost
                << " | худшее = " << std::setw(6) << worstCost
                << " | время = " << std::setw(10) << exactTime << " с\n";
            std::cout << "  Жадный метод:   решение = " << std::setw(6) << hcost
                << " | время = " << std::setw(10) << heurTime << " с\n";
            std::cout << "  Качество: " << std::setprecision(2) << quality << " %\n";
            std::cout << std::setprecision(4);
        }
    }

    std::cout << "Среднее качество жадного алгоритма: "
        << std::setprecision(2) << (sumQuality / runs) << " %\n";
    std::cout << "Среднее время точного метода:       "
        << std::setprecision(4) << (sumExactTime / runs) << " с\n";
    std::cout << "Среднее время жадного метода:       "
        << std::setprecision(4) << (sumHeurTime / runs) << " с\n";
}

void runLargeScaleReport(const std::vector<int>& sizes,
    long long minCost, long long maxCost,
    int runs) {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\nКрупномасштабный отчёт (только жадный алгоритм)\n";
    std::cout << "Размерности: ";
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout << sizes[i];
        if (i + 1 < sizes.size()) std::cout << ", ";
    }
    std::cout << " | запусков на размерность: " << runs << "\n";

    for (int n : sizes) {
        std::cout << "\n=============================================\n";
        std::cout << "--- ТЕСТИРОВАНИЕ ДЛЯ ГОРОДОВ = " << n << " ---\n";
        std::cout << "=============================================\n";

        double sumTime = 0.0;
        long long sumCost = 0;

        for (int run = 1; run <= runs; ++run) {
            Matrix d = makeRandomMatrix(n, minCost, maxCost);

            long long cost = 0;
            std::vector<int> path;

            auto t1 = std::chrono::steady_clock::now();
            solveNearestNeighbor(d, 0, cost, path);
            auto t2 = std::chrono::steady_clock::now();
            double sec = std::chrono::duration<double>(t2 - t1).count();

            sumTime += sec;
            sumCost += cost;

            std::cout << "Запуск #" << run
                << " | Жадный [стоимость: " << cost
                << ", время: " << sec << " с]\n";
        }

        if (runs > 1) {
            std::cout << "Среднее: стоимость = " << (sumCost / runs)
                << ", время = " << (sumTime / runs) << " с\n";
        }
    }
}