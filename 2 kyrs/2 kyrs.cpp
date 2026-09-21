#include "Header.h"

#include <iostream>

int main() {
    Fraction a(1, 2);
    Fraction b(3, 4);

    std::cout << "a = " << a.getNumerator() << '/' << a.getDenominator() << '\n';
    std::cout << "b = " << b.getNumerator() << '/' << b.getDenominator() << '\n';

    return 0;
}