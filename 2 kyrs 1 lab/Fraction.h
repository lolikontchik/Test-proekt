#pragma once

#include <iostream>

class Fraction {
private:
    int numerator_;
    int denominator_;

    void normalize();

public:
    Fraction();
    Fraction(int numerator, int denominator = 1);

    int getNumerator() const;
    int getDenominator() const;

    void setNumerator(int numerator);
    void setDenominator(int denominator);

    void input();
    void output() const;

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    double toDouble() const;
    static Fraction fromDouble(double value, int precision = 6);

    static int gcd(int a, int b);
    void reduce();
};

std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
std::istream& operator>>(std::istream& in, Fraction& fraction);