//
// Created by shama on 15.04.2023.
//

#ifndef VKR_TRIE_H
#define VKR_TRIE_H

#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

#include "rational.h"

template<Integral N>
struct Trie {
    Rational first;
    std::vector<Trie<N - 1>> rest;

    Trie() = default;
    Trie(Rational first, std::vector<Trie<N - 1>>&& rest) : first(first), rest(std::move(rest)) {}

    static std::vector<Trie> Search(Rational sum = Rational(1), Rational start = Rational(2)) {
        auto mean = sum / Rational(N);
        std::vector<Trie<N>> res;
        for (Rational a = std::max(Rational::Floor(1 / sum) + Rational(1), start); 1 / a > mean; ++a) {
            auto rest = Trie<N - 1>::Search(sum - 1 / a, a + Rational(1));
            res.emplace_back(a, std::move(rest));
        }
        return std::move(res);
    }
};

template<>
struct Trie<1> {
    Rational first;

    Trie() = default;
    explicit Trie(Rational first) : first(first) {}

    static std::vector<Trie> Search(Rational sum, Rational start) {
        std::vector<Trie<1>> res;
        if (Rational a = 1 / sum; Rational::IsInteger(a) && a >= start) {
            res.emplace_back(a);
        }
        return std::move(res);
    }
};

template<Integral N>
void Iterate(const std::vector<Trie<N>>& tries, std::vector<SafeIntegral>& buffer, std::function<void(const std::vector<SafeIntegral>&)>& callback) {
    for (auto& trie : tries) {
        buffer.emplace_back(trie.first);
        Iterate(trie.rest, buffer, callback);
        buffer.pop_back();
    }
}

template<>
void Iterate<1>(const std::vector<Trie<1>>& tries, std::vector<SafeIntegral>& buffer, std::function<void(const std::vector<SafeIntegral>&)>& callback) {
    for (auto& trie : tries) {
        buffer.emplace_back(trie.first);
        callback(buffer);
        buffer.pop_back();
    }
}

template<Integral N>
void Iterate(const std::vector<Trie<N>>& tries, std::function<void(const std::vector<SafeIntegral>&)> callback) {
    std::vector<SafeIntegral> buffer;
    buffer.reserve(N);
    Iterate<N>(tries, buffer, callback);
}

template<Integral FunctionsCount = 4>
void SearchAndIterate(std::function<void(const std::vector<SafeIntegral>&)> callback) {
    auto startTimePoint = std::chrono::system_clock::now();
    auto trie = Trie<FunctionsCount>::Search();
    std::cout << "% " << std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::system_clock::now() - startTimePoint)).count() << " ms" << std::endl;
    Iterate(trie, callback);
    std::cout << "% " << std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::system_clock::now() - startTimePoint)).count() << " ms" << std::endl;
}

#endif //VKR_TRIE_H
