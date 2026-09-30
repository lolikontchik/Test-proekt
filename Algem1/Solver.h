#pragma once

#include <vector>
#include <string>

class TspSolver {
public:
    TspSolver() = default;
    TspSolver(const std::vector<std::vector<long long>>& matrix, int start);

    void input();
    void output() const;

    void generateRandom(int n, long long minCost = 1, long long maxCost = 1000);
    void setMatrix(const std::vector<std::vector<long long>>& matrix, int start);

    void solveExact();
    void solveNearestNeighbor();

    long long getBestCost() const;
    long long getWorstCost() const;
    std::vector<int> getBestPath() const;
    std::vector<int> getWorstPath() const;
    std::string getMethodName() const;

    static void runTimeExperiments(int maxN = 13, double stopAfterSeconds = 10.0);
    static void runQualityReport(int n, long long minCost, long long maxCost, int runs);

private:
    int n_ = 0;
    int start_ = 0;
    std::vector<std::vector<long long>> d_;

    long long bestCost_ = 0;
    long long worstCost_ = 0;
    std::vector<int> bestPath_;
    std::vector<int> worstPath_;

    std::string method_;
    bool solved_ = false;

    long long pathCost(const std::vector<int>& path) const;
    static bool nextPermutation(std::vector<int>& p);
};
