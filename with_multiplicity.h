//
// Created by shama on 15.04.2023.
//

#ifndef VKR_WITH_MULTIPLICITY_H
#define VKR_WITH_MULTIPLICITY_H

#include <exception>
#include <iostream>
#include <sstream>

#include "defines.h"

struct MultiplicityException : std::exception {
    unsigned long long value;

    explicit MultiplicityException(unsigned long long value) : value(value) {}
};

template<typename ValueType>
struct WithMultiplicity {
    ValueType value;
    unsigned long long multiplicity;

    explicit WithMultiplicity(ValueType v = {}) : value(v), multiplicity(1) {};

    WithMultiplicity& operator,(WithMultiplicity other) {
        multiplicity += other.multiplicity;
        return *this;
    };
    WithMultiplicity& operator*=(auto other) {
        value *= other;
        return *this;
    }

    WithMultiplicity operator*(auto other) const {
        WithMultiplicity res = *this;
        res *= other;
        return res;
    }

    WithMultiplicity& operator+=(auto other) {
        value += other;
        return *this;
    }

    WithMultiplicity operator+(auto other) const {
        WithMultiplicity res = *this;
        res += other;
        return res;
    }

    COMPARABLE_AS(value, other.value)

    ValueType operator-(ValueType other) const {
        return value - other;
    }

    explicit operator ValueType() {
        return value;
    }
};

template<typename ValueType>
std::ostream& operator<<(std::ostream& out, const WithMultiplicity<ValueType>& v) {
    return out << v.value << ' ' << v.multiplicity;
}

class MultiplicityChecker {
    bool m_success = true;

public:
    ~MultiplicityChecker() {
        std::stringstream output;
        output << (m_success ? "No multiplicity found" : "Multiplicity found") << std::endl;
        std::cout << output.str();
    }

    template<typename ValueType>
    bool operator()(WithMultiplicity<ValueType> v) {
        if (v.multiplicity > 1) {
            m_success = false;
            return true;
        } else {
            return false;
        }
    }
};

#endif //VKR_WITH_MULTIPLICITY_H
