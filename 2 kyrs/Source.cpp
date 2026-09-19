#include "Header.h"


// Конструктор
Fraction::Fraction(int numerator, int denominator)
    : numerator_(numerator), denominator_(denominator) {
    if (denominator_ == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю");
    }
    normalizeSign();
}

// Аксессоры
int Fraction::getNumerator() const {
    return numerator_;
}

void Fraction::setNumerator(int numerator) {
    numerator_ = numerator;
    normalizeSign();
}

int Fraction::getDenominator() const {
    return denominator_;
}

void Fraction::setDenominator(int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю");
    }
    denominator_ = denominator;
    normalizeSign();
}

// вспомогательный метод
void Fraction::normalizeSign() {
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}