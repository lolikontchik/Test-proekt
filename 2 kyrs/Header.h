#pragma once

#include <iostream>

class Fraction {
public:
    // Конструктор по умолчанию и с аргументами по умолчанию
    Fraction(int numerator = 0, int denominator = 1);

    // Аксессоры
    int getNumerator() const;
    void setNumerator(int numerator);

    int getDenominator() const;
    void setDenominator(int denominator);

private:
    int numerator_;
    int denominator_;

    // вспомогательный метод: знаменатель всегда положительный
    void normalizeSign();
};