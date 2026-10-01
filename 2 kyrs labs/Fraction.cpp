#include "Header.h"
#include <cmath>
#include <cstdlib>
#include <limits>

// Конструкторы

Fraction::Fraction()
    : numerator_(0), denominator_(1) {
}

Fraction::Fraction(int numerator, int denominator)
    : numerator_(numerator), denominator_(denominator) {
    if (denominator_ == 0) {
        throw std::invalid_argument(
            "Знаменатель не может быть равен нулю"
        );
    }

    normalize();
}

// Нормализация дроби

void Fraction::normalize() {
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
        throw std::invalid_argument(
            "Знаменатель не может быть равен нулю"
        );
    }

    denominator_ = denominator;
    normalize();
}

// Ввод и вывод

void Fraction::input() {
    std::cin >> *this;
}

void Fraction::output() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& out,
    const Fraction& fraction) {
    out << fraction.numerator_ << '/'
        << fraction.denominator_;

    return out;
}

std::istream& operator>>(std::istream& in,
    Fraction& fraction) {
    int numerator;
    int denominator;
    char slash;

    if (!(in >> numerator >> slash >> denominator)) {
        return in;
    }

    if (slash != '/' || denominator == 0) {
        in.setstate(std::ios::failbit);
        return in;
    }

    fraction.numerator_ = numerator;
    fraction.denominator_ = denominator;
    fraction.normalize();

    return in;
}

// Арифметические операции

Fraction Fraction::operator+(const Fraction& other) const {
    Fraction result(
        numerator_ * other.denominator_
        + other.numerator_ * denominator_,
        denominator_ * other.denominator_
    );

    result.reduce();
    return result;
}

Fraction Fraction::operator-(const Fraction& other) const {
    Fraction result(
        numerator_ * other.denominator_
        - other.numerator_ * denominator_,
        denominator_ * other.denominator_
    );

    result.reduce();
    return result;
}

Fraction Fraction::operator*(const Fraction& other) const {
    Fraction result(
        numerator_ * other.numerator_,
        denominator_ * other.denominator_
    );

    result.reduce();
    return result;
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator_ == 0) {
        throw std::invalid_argument(
            "Нельзя делить на нулевую дробь"
        );
    }

    Fraction result(
        numerator_ * other.denominator_,
        denominator_ * other.numerator_
    );

    result.reduce();
    return result;
}

// Составное присваивание

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
}

// Сравнение

bool Fraction::operator==(const Fraction& other) const {
    return numerator_ * other.denominator_
        == other.numerator_ * denominator_;
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const {
    return numerator_ * other.denominator_
        < other.numerator_ * denominator_;
}

bool Fraction::operator<=(const Fraction& other) const {
    return *this < other || *this == other;
}

bool Fraction::operator>(const Fraction& other) const {
    return other < *this;
}

bool Fraction::operator>=(const Fraction& other) const {
    return other < *this || *this == other;
}

// Преобразование в double

double Fraction::toDouble() const {
    return static_cast<double>(numerator_)
        / denominator_;
}

// Создание дроби из double

Fraction Fraction::fromDouble(double value, int precision) {
    if (precision < 0) {
        throw std::invalid_argument(
            "Точность не может быть отрицательной"
        );
    }

    int factor = 1;

    for (int i = 0; i < precision; ++i) {
        if (factor > std::numeric_limits<int>::max() / 10) {
            throw std::overflow_error(
                "Слишком большая точность"
            );
        }

        factor *= 10;
    }

    int numerator = static_cast<int>(
        std::round(value * factor)
        );

    Fraction result(numerator, factor);
    result.reduce();

    return result;
}

// НОД

int Fraction::gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);

    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

// Сокращение

void Fraction::reduce() {
    int divisor = gcd(numerator_, denominator_);

    if (divisor != 0) {
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    normalize();
}