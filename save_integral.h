//
// Created by shama on 15.04.2023.
//

#ifndef VKR_SAVE_INTEGRAL_H
#define VKR_SAVE_INTEGRAL_H

#include <stdexcept>

#include "defines.h"

typedef unsigned long long Integral;

class SafeIntegral {
    static constexpr Integral MAX_VALUE = ~Integral(0);

    Integral value;

public:
    explicit SafeIntegral(Integral value = Integral()) : value(value) {}

    SafeIntegral& operator+=(SafeIntegral other) {
        if (MAX_VALUE - value >= other.value) {
            value += other.value;
            return *this;
        } else {
            throw std::overflow_error("unsigned long long overflowed");
        }
    }

    SafeIntegral operator+(SafeIntegral other) const {
        SafeIntegral res = *this;
        return res += other;
    }

    SafeIntegral& operator-=(SafeIntegral other) {
        value -= other.value;
        return *this;
    }

    SafeIntegral operator-(SafeIntegral other) const {
        SafeIntegral res = *this;
        return res -= other;
    }

    SafeIntegral& operator*=(SafeIntegral other) {
        if (value == 0 || MAX_VALUE / value >= other.value) {
            value *= other.value;
            return *this;
        } else {
            throw std::overflow_error("unsigned long long overflowed");
        }
    }

    SafeIntegral operator*(SafeIntegral other) const {
        SafeIntegral res = *this;
        return res *= other;
    }

    SafeIntegral& operator/=(SafeIntegral other) {
        value /= other.value;
        return *this;
    }

    SafeIntegral operator/(SafeIntegral other) const {
        SafeIntegral res = *this;
        return res /= other;
    }

    SafeIntegral& operator%=(SafeIntegral other) {
        value %= other.value;
        return *this;
    }

    SafeIntegral operator%(SafeIntegral other) const {
        SafeIntegral res = *this;
        return res %= other;
    }

    COMPARABLE_AS(value, other.value)

    [[nodiscard]] Integral toIntegral() const {
        return value;
    }

    explicit operator Integral() const {
        return value;
    }
};

std::ostream& operator<<(std::ostream& out, const SafeIntegral& v) {
    return out << v.toIntegral();
}


#endif //VKR_SAVE_INTEGRAL_H
