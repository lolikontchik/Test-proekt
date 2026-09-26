#include "Header.h"

#include <iostream>
#include <locale>

int main() {
    Fraction a, b;
    setlocale(LC_ALL, "rus");

    std::cout << "Введите первую дробь (числитель/знаменатель): ";
    if (!(std::cin >> a)) { std::cout << "Ошибка ввода\n"; return 1; }

    std::cout << "Введите вторую дробь (числитель/знаменатель): ";
    if (!(std::cin >> b)) { std::cout << "Ошибка ввода\n"; return 1; }

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "a + b = " << a + b << '\n';
    std::cout << "a - b = " << a - b << '\n';
    std::cout << "a * b = " << a * b << '\n';
    std::cout << "a / b = " << a / b << '\n';

    std::cout << std::boolalpha;
    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a != b: " << (a != b) << '\n';
    std::cout << "a <  b: " << (a < b) << '\n';
    std::cout << "a <= b: " << (a <= b) << '\n';
    std::cout << "a >  b: " << (a > b) << '\n';
    std::cout << "a >= b: " << (a >= b) << '\n';

    return 0;
}