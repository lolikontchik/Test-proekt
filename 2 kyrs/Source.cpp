#include "Header.h"

#include <stdexcept>

// Конструкторы
Fraction::Fraction() = default;

Fraction::Fraction(int numerator, int denominator)
    : numerator_(numerator), denominator_(denominator) {
    if (denominator_ == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю");
    }
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}

// Аксессоры
int Fraction::getNumerator() const {
    return numerator_;
}

int Fraction::getDenominator() const {
    return denominator_;
}

void Fraction::setNumerator(int numerator) {
    numerator_ = numerator;
}

void Fraction::setDenominator(int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю");
    }
    if (denominator < 0) {
        numerator_ = -numerator_;
        denominator = -denominator;
    }
    denominator_ = denominator;
}
// Ввод/вывод
void Fraction::input() {
    int num, den;
    char slash;
    std::cin >> num >> slash >> den;
    if (slash != '/' || den == 0) {
        std::cerr << "Некорректный ввод дроби.\n";
        std::exit(1);
    }
    numerator_ = num;
    denominator_ = den;
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}

void Fraction::output() const {
    std::cout << numerator_ << '/' << denominator_;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f) {
    out << f.numerator_ << '/' << f.denominator_;
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& f) {
    int num, den;
    char slash;
    if (in >> num >> slash >> den && slash == '/' && den != 0) {
        f.numerator_ = num;
        f.denominator_ = den;
        if (f.denominator_ < 0) {
            f.numerator_ = -f.numerator_;
            f.denominator_ = -f.denominator_;
        }
    }
    else {
        in.setstate(std::ios::failbit);
    }
    return in;
}