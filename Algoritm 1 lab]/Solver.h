#pragma once

#include <vector>
#include <string>

using Matrix = std::vector<std::vector<long long>>;

Matrix makeRandomMatrix(int n, long long minCost, long long maxCost);

long long pathCost(const Matrix& d, const std::vector<int>& path);

void solveExact(const Matrix& d, int start,
    long long& bestCost, std::vector<int>& bestPath,
    long long& worstCost, std::vector<int>& worstPath);

void solveNearestNeighbor(const Matrix& d, int start,
    long long& bestCost, std::vector<int>& bestPath);

void runTimeExperiments(int nStart, int nEnd, int nStep,
    double stopAfterSeconds,
    long long minCost, long long maxCost);

void runQualityReport(int n, long long minCost, long long maxCost,
    int runs, bool showDetails = true);

void runLargeScaleReport(const std::vector<int>& sizes,
    long long minCost, long long maxCost,
    int runs);