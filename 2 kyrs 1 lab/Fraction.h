#pragma once

#include <iostream>

class Fraction {
private:
    int numerator_;
    int denominator_;

    void normalize();

public:
    // Конструкторы
    Fraction();
    Fraction(int numerator, int denominator = 1);

    // Аксессоры
    int getNumerator() const;
    int getDenominator() const;

    void setNumerator(int numerator);
    void setDenominator(int denominator);

    // Ввод и вывод
    void input();
    void output() const;

    // Арифметические операции
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    // Составное присваивание
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    // Сравнение
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    // double
    double toDouble() const;
    static Fraction fromDouble(double value, int precision = 6);

    // НОД и сокращение
    static int gcd(int a, int b);
    void reduce();

    // Потоковый ввод и вывод
    friend std::ostream& operator<<(std::ostream& out,
        const Fraction& fraction);

    friend std::istream& operator>>(std::istream& in,
        Fraction& fraction);
};