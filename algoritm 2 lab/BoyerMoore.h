#pragma once

#include <string>
#include <vector>

// 1. Индекс первого вхождения подстроки в тексте
int findFirst(const std::string& text, const std::string& pattern);

// 2. Индексы всех вхождений подстроки в тексте
std::vector<int> findAll(const std::string& text, const std::string& pattern);

// 3. Индексы вхождений подстроки в тексте в диапазоне
std::vector<int> findAll(const std::string& text,
    const std::string& pattern,
    int begin,
    int end);