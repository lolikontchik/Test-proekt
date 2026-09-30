#include "Header.h"

#include <iostream>
#include <locale>

int main() {
    setlocale(LC_ALL, "rus");

    Fraction a;
    Fraction b;

    std::cout << "Введите первую дробь: ";
    std::cin >> a;

    if (std::cin.fail()) {
        std::cout << "Ошибка ввода первой дроби.\n";
        return 1;
    }

    std::cout << "Введите вторую дробь: ";
    std::cin >> b;

    if (std::cin.fail()) {
        std::cout << "Ошибка ввода второй дроби.\n";
        return 1;
    }

    std::cout << "\na = " << a << '\n';
    std::cout << "b = " << b << '\n';

    std::cout << "\nАрифметические операции:\n";
    std::cout << "a + b = " << a + b << '\n';
    std::cout << "a - b = " << a - b << '\n';
    std::cout << "a * b = " << a * b << '\n';

    if (b.getNumerator() != 0) {
        std::cout << "a / b = " << a / b << '\n';
    }
    else {
        std::cout << "a / b невозможно: деление на ноль.\n";
    }

    std::cout << std::boolalpha;

    std::cout << "\nСравнение:\n";
    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a != b: " << (a != b) << '\n';
    std::cout << "a < b:  " << (a < b) << '\n';
    std::cout << "a <= b: " << (a <= b) << '\n';
    std::cout << "a > b:  " << (a > b) << '\n';
    std::cout << "a >= b: " << (a >= b) << '\n';

    std::cout << "\nСоставное присваивание:\n";

    Fraction temp = a;

    temp += b;
    std::cout << "temp += b: " << temp << '\n';

    temp = a;
    temp -= b;
    std::cout << "temp -= b: " << temp << '\n';

    temp = a;
    temp *= b;
    std::cout << "temp *= b: " << temp << '\n';

    if (b.getNumerator() != 0) {
        temp = a;
        temp /= b;
        std::cout << "temp /= b: " << temp << '\n';
    }

    std::cout << "\nПреобразование double:\n";
    std::cout << "a в виде double: " << a.toDouble() << '\n';

    Fraction pi = Fraction::fromDouble(3.14159, 4);
    std::cout << "3.14159 -> " << pi << '\n';

    Fraction half = Fraction::fromDouble(0.5, 1);
    std::cout << "0.5 -> " << half << '\n';

    std::cout << "\nНОД:\n";
    std::cout << "НОД(24, 36) = "
        << Fraction::gcd(24, 36) << '\n';

    std::cout << "\nСокращение:\n";

    Fraction fraction(24, 36);

    std::cout << "До сокращения: " << fraction << '\n';

    fraction.reduce();

    std::cout << "После сокращения: " << fraction << '\n';

    return 0;
}