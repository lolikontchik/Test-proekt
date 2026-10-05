#include "Solver.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

// Конструкторы
TspSolver::TspSolver(const std::vector<std::vector<long long>>& matrix, int start)
    : n_(static_cast<int>(matrix.size())),
    start_(start),
    d_(matrix) {
}

// Ввод / вывод
void TspSolver::input() {
    std::cout << "Введите количество городов и начальный город: ";
    std::cin >> n_ >> start_;

    d_.assign(n_, std::vector<long long>(n_));
    std::cout << "Введите матрицу стоимостей " << n_ << "x" << n_ << ":\n";
    for (int i = 0; i < n_; ++i)
        for (int j = 0; j < n_; ++j)
            std::cin >> d_[i][j];

    solved_ = false;
}

void TspSolver::output() const {
    if (!solved_) {
        std::cout << "Решение ещё не найдено.\n";
        return;
    }
    std::cout << "Метод: " << method_ << '\n';
    std::cout << "Лучшая стоимость: " << bestCost_ << '\n';
    std::cout << "Лучший маршрут:   ";
    for (int v : bestPath_) std::cout << (v + 1) << ' ';
    std::cout << '\n';

    if (!worstPath_.empty()) {
        std::cout << "Худшая стоимость: " << worstCost_ << '\n';
        std::cout << "Худший маршрут:   ";
        for (int v : worstPath_) std::cout << (v + 1) << ' ';
        std::cout << '\n';
    }
}

// Установка / генерация
void TspSolver::setMatrix(const std::vector<std::vector<long long>>& matrix, int start) {
    n_ = static_cast<int>(matrix.size());
    start_ = start;
    d_ = matrix;
    solved_ = false;
    bestPath_.clear();
    worstPath_.clear();
    bestCost_ = worstCost_ = 0;
}

void TspSolver::generateRandom(int n, long long minCost, long long maxCost) {
    d_ = makeRandomMatrix(n, minCost, maxCost);
    n_ = n;
    start_ = 0;
    solved_ = false;
    bestPath_.clear();
    worstPath_.clear();
    bestCost_ = worstCost_ = 0;
}

std::vector<std::vector<long long>>
TspSolver::makeRandomMatrix(int n, long long minCost, long long maxCost) {
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<long long> dist(minCost, maxCost);

    std::vector<std::vector<long long>> m(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j) m[i][j] = dist(rng);
    return m;
}

// Геттеры
long long TspSolver::getBestCost() const { return bestCost_; }
long long TspSolver::getWorstCost() const { return worstCost_; }
std::vector<int> TspSolver::getBestPath() const { return bestPath_; }
std::vector<int> TspSolver::getWorstPath() const { return worstPath_; }
std::string TspSolver::getMethodName() const { return method_; }
int TspSolver::getN() const { return n_; }
int TspSolver::getStart() const { return start_; }

// Вспомогательные
long long TspSolver::pathCost(const std::vector<int>& path) const {
    long long s = 0;
    for (size_t i = 0; i + 1 < path.size(); ++i)
        s += d_[path[i]][path[i + 1]];
    return s;
}

bool TspSolver::nextPermutation(std::vector<int>& p) {
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

// Точный алгоритм — полный перебор
void TspSolver::solveExact() {
    method_ = "Полный перебор";
    worstPath_.clear();
    worstCost_ = 0;

    if (n_ == 1) {
        bestCost_ = worstCost_ = 0;
        bestPath_ = worstPath_ = { start_, start_ };
        solved_ = true;
        return;
    }

    std::vector<int> perm;
    perm.reserve(n_ - 1);
    for (int i = 0; i < n_; ++i)
        if (i != start_) perm.push_back(i);
    std::sort(perm.begin(), perm.end());

    bestCost_ = std::numeric_limits<long long>::max();
    worstCost_ = -std::numeric_limits<long long>::max();
    bestPath_.clear();

    std::vector<int> path;
    path.reserve(n_ + 1);

    do {
        path.clear();
        path.push_back(start_);
        path.insert(path.end(), perm.begin(), perm.end());
        path.push_back(start_);

        long long cur = pathCost(path);

        if (cur < bestCost_) { bestCost_ = cur; bestPath_ = path; }
        if (cur > worstCost_) { worstCost_ = cur; worstPath_ = path; }
    } while (nextPermutation(perm));

    solved_ = true;
}

// Эвристика — метод худшей строки 
void TspSolver::solveWorstRow() {
    method_ = "Метод худшей строки (WorstRow, итеративный)";
    worstPath_.clear();
    worstCost_ = 0;

    if (n_ <= 1) {
        bestCost_ = 0;
        bestPath_ = { start_, start_ };
        solved_ = true;
        return;
    }

    std::vector<bool> visited(n_, false);
    bestPath_.clear();
    bestPath_.reserve(n_ + 1);

    int cur = start_;
    visited[cur] = true;
    bestPath_.push_back(cur);

    for (int step = 1; step < n_; ++step) {
        int worstV = -1;
        long long worstW = -std::numeric_limits<long long>::max();
        for (int v = 0; v < n_; ++v) {
            if (!visited[v] && d_[cur][v] > worstW) {
                worstW = d_[cur][v];
                worstV = v;
            }
        }
        bestPath_.push_back(worstV);
        visited[worstV] = true;
        cur = worstV;
    }
    bestPath_.push_back(start_);
    bestCost_ = pathCost(bestPath_);
    solved_ = true;
}

// 1
void TspSolver::runTimeExperiments(int nStart, int nEnd, int nStep,
    double stopAfterSeconds,
    long long minCost, long long maxCost) {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\nРост времени полного перебора\n";
    std::cout << "Диапазон n: [" << nStart << ".." << nEnd
        << "], шаг = " << nStep
        << ", стоп при времени > " << stopAfterSeconds << " s\n";
    std::cout << "Разброс стоимостей: [" << minCost << ".." << maxCost << "]\n\n";

    if (nStep <= 0) {
        std::cout << "Ошибка: шаг должен быть > 0.\n";
        return;
    }

    for (int n = nStart; n <= nEnd; n += nStep) {
        TspSolver solver;
        solver.generateRandom(n, minCost, maxCost);

        auto t1 = std::chrono::steady_clock::now();
        solver.solveExact();
        auto t2 = std::chrono::steady_clock::now();

        double sec = std::chrono::duration<double>(t2 - t1).count();
        std::cout << "n = " << std::setw(3) << n
            << " | time = " << std::setw(10) << sec << " s"
            << " | best = " << solver.getBestCost()
            << " | worst = " << solver.getWorstCost() << '\n';

        if (sec > stopAfterSeconds) {
            std::cout << "  слишком долго, дальнейшие n пропускаем\n";
            break;
        }
    }
}

// 2
void TspSolver::runQualityReport(int n, long long minCost, long long maxCost,
    int runs, bool showDetails) {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nОтчёт: n = " << n
        << ", разброс стоимостей = [" << minCost << ".." << maxCost << "]"
        << ", запусков = " << runs << "\n";

    double sumQuality = 0.0;
    double sumExactTime = 0.0;
    double sumHeurTime = 0.0;

    for (int run = 1; run <= runs; ++run) {
        auto m = makeRandomMatrix(n, minCost, maxCost);

        TspSolver exact(m, 0);
        TspSolver heur(m, 0);

        auto t1 = std::chrono::steady_clock::now();
        exact.solveExact();
        auto t2 = std::chrono::steady_clock::now();
        double exactTime = std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::steady_clock::now();
        heur.solveWorstRow();
        auto t4 = std::chrono::steady_clock::now();
        double heurTime = std::chrono::duration<double>(t4 - t3).count();

        long long best = exact.getBestCost();
        long long worst = exact.getWorstCost();
        long long hcost = heur.getBestCost();

        double quality = (worst == best)
            ? 100.0
            : 100.0 * (double)(worst - hcost) / (double)(worst - best);
        sumQuality += quality;
        sumExactTime += exactTime;
        sumHeurTime += heurTime;

        if (showDetails) {
            std::cout << "Запуск " << run << ":\n";
            std::cout << "  Точное:    лучшее = " << std::setw(6) << best
                << " | худшее = " << std::setw(6) << worst
                << " | время = " << std::setw(10) << exactTime << " s\n";
            std::cout << "  Эвристика: решение = " << std::setw(6) << hcost
                << " | время = " << std::setw(10) << heurTime << " s\n";
            std::cout << "  Качество: " << std::setprecision(2) << quality << " %\n";
            std::cout << std::setprecision(4);
        }
    }

    std::cout << "Среднее качество эвристики: "
        << std::setprecision(2) << (sumQuality / runs) << " %\n";
    std::cout << "Среднее время точного метода: "
        << std::setprecision(4) << (sumExactTime / runs) << " s\n";
    std::cout << "Среднее время эвристики:      "
        << std::setprecision(4) << (sumHeurTime / runs) << " s\n";
}

// 3
void TspSolver::runLargeScaleReport(const std::vector<int>& sizes,
    long long minCost, long long maxCost,
    int runs) {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\nКрупномасштабный отчёт (только WorstRow)\n";
    std::cout << "Размеры: ";
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout << sizes[i];
        if (i + 1 < sizes.size()) std::cout << ", ";
    }
    std::cout << " | запусков на размер: " << runs << "\n";

    for (int n : sizes) {
        std::cout << "\n=============================================\n";
        std::cout << "--- ТЕСТИРОВАНИЕ ДЛЯ N = " << n << " ---\n";
        std::cout << "=============================================\n";

        double sumTime = 0.0;
        long long sumCost = 0;

        for (int run = 1; run <= runs; ++run) {
            TspSolver solver;
            solver.generateRandom(n, minCost, maxCost);

            auto t1 = std::chrono::steady_clock::now();
            solver.solveWorstRow();
            auto t2 = std::chrono::steady_clock::now();
            double sec = std::chrono::duration<double>(t2 - t1).count();

            sumTime += sec;
            sumCost += solver.getBestCost();

            std::cout << "Run #" << run
                << " | WorstRow [Cost: " << solver.getBestCost()
                << ", Time: " << sec << "s]\n";
        }

        if (runs > 1) {
            std::cout << "Среднее: Cost = " << (sumCost / runs)
                << ", Time = " << (sumTime / runs) << "s\n";
        }
    }
}