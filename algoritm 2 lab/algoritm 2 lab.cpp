#include <iostream>
#include <string>
#include <locale>
#include "BoyerMoore.h"

static void printIndices(const std::vector<int>& indices)
{
    std::cout << "[";
    for (std::size_t i = 0; i < indices.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << ", ";
        }
        std::cout << indices[i];
    }
    std::cout << "]" << std::endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    std::string text;
    std::string pattern;

    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    std::cout << "Введите искомую подстроку: ";
    std::getline(std::cin, pattern);

    std::cout << "Длина текста: " << text.size() << std::endl;

    // 1. Первое вхождение
    std::cout << "Первое вхождение: "
        << findFirst(text, pattern) << std::endl;

    // 2. Все вхождения
    std::cout << "Все вхождения: ";
    printIndices(findAll(text, pattern));

    // 3. Вхождения в диапазоне (запрашиваем у пользователя)
    int begin = 0;
    int end = 0;
    std::cout << "Введите начало диапазона: ";
    std::cin >> begin;
    std::cout << "Введите конец диапазона: ";
    std::cin >> end;

    std::cout << "findAll(" << begin << ", " << end << "): ";
    printIndices(findAll(text, pattern, begin, end));

    return 0;
}