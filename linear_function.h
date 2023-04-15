//
// Created by shama on 15.04.2023.
//

#ifndef VKR_LINEAR_FUNCTION_H
#define VKR_LINEAR_FUNCTION_H

#include <cstdint>
#include <iostream>
#include <utility>

#include "defines.h"

class LinearFunction {
    friend std::ostream& operator<<(std::ostream& out, const LinearFunction& v);

public:
    LinearFunction(std::uint_least64_t a = 0, std::uint_least64_t b = 0)
            : m_a(a), m_b(b) {}

    template<typename ValueType>
    ValueType operator()(const ValueType& x) {
        return x * m_a + m_b;
    }

    LinearFunction& operator*=(std::uint_least64_t k) {
        m_a *= k;
        m_b *= k;
        return *this;
    }

    LinearFunction& operator+=(std::uint_least64_t b) {
        m_b += b;
        return *this;
    }

    COMPARABLE_AS(std::make_pair(m_a, m_b), std::make_pair(other.m_a, other.m_b))

private:
    std::uint_least64_t m_a;
    std::uint_least64_t m_b;
};

std::ostream& operator<<(std::ostream& out, const LinearFunction& v) {
    return out << v.m_a << "x + " << v.m_b;
}

#endif // VKR_LINEAR_FUNCTION_H
