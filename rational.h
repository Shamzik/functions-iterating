//
// Created by shama on 15.04.2023.
//

#ifndef VKR_RATIONAL_H
#define VKR_RATIONAL_H

#include "save_integral.h"

template<typename Integral>
Integral GCD(Integral a, Integral b) {
    while (a != 0) {
        Integral t = a;
        a = b % a;
        b = t;
    }
    return b;
}

template<typename Integral>
Integral LCM(Integral a, Integral b) {
    return a / GCD(a, b) * b;
}

class Rational {
    SafeIntegral numerator = SafeIntegral(0);
    SafeIntegral denominator = SafeIntegral(1);

    static SafeIntegral Reduce(SafeIntegral& a, SafeIntegral& b) {
        SafeIntegral d = GCD(a, b);
        a /= d;
        b /= d;
        return d;
    }

public:
    Rational() = default;
    explicit Rational(Integral value) : numerator(value) {}
    Rational(Integral numerator, Integral denominator) : numerator(numerator), denominator(denominator) {}
    explicit Rational(SafeIntegral numerator, SafeIntegral denominator = SafeIntegral(1)) : numerator(numerator), denominator(denominator) {}

    Rational& operator++() {
        numerator += denominator;
        return *this;
    }

    Rational operator+=(Rational other) {
        auto d = Reduce(denominator, other.denominator);
        numerator *= other.denominator;
        other.numerator *= denominator;
        numerator += other.numerator;
        Reduce(numerator, d);
        denominator *= d;
        denominator *= other.denominator;
        return *this;
    }

    Rational operator+(Rational other) const {
        Rational res = *this;
        return res += other;
    }

    Rational operator-=(Rational other) {
        auto d = Reduce(denominator, other.denominator);
        numerator *= other.denominator;
        other.numerator *= denominator;
        numerator -= other.numerator;
        Reduce(numerator, d);
        denominator *= d;
        denominator *= other.denominator;
        return *this;
    }

    Rational operator-(Rational other) const {
        Rational res = *this;
        return res -= other;
    }

    Rational operator/=(Rational other) {
        Reduce(numerator, other.numerator);
        Reduce(denominator, other.denominator);
        numerator *= other.denominator;
        denominator *= other.numerator;
        return *this;
    }

    Rational operator/(Rational other) const {
        Rational res = *this;
        return res /= other;
    }

    Rational operator*=(Rational other) {
        Reduce(numerator, other.denominator);
        Reduce(denominator, other.numerator);
        numerator *= other.numerator;
        denominator *= other.denominator;
        return *this;
    }

    Rational operator*(Rational other) const {
        Rational res = *this;
        return res *= other;
    }

    COMPARABLE_AS(numerator * other.denominator, denominator * other.numerator)

    static Rational Ceil(Rational r) {
        return Rational(r.numerator / r.denominator + SafeIntegral(r.numerator % r.denominator != 0 ? 1 : 0));
    }

    static Rational Floor(Rational r) {
        return Rational(r.numerator / r.denominator);
    }

    static bool IsInteger(Rational rational) {
        return rational.denominator == 1;
    }

    explicit operator SafeIntegral() const {
        return numerator / denominator;
    }

    [[nodiscard]] SafeIntegral GetNumerator() const {
        return numerator;
    }

    [[nodiscard]] SafeIntegral GetDenominator() const {
        return denominator;
    }

    [[nodiscard]] static SafeIntegral GetNumerator(Rational r) {
        return r.numerator;
    }

    [[nodiscard]] static SafeIntegral GetDenominator(Rational r) {
        return r.denominator;
    }
};

Rational operator/(Integral x, Rational other) {
    auto res = Rational(x);
    return res /= other;
}

#endif //VKR_RATIONAL_H
