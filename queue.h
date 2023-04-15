//
// Created by shama on 15.04.2023.
//

#ifndef VKR_QUEUE_H
#define VKR_QUEUE_H

#include <array>
#include <cstdint>
#include <queue>

#include "linear_function.h"

template<unsigned FunctionsCount = 3, typename VT = std::uint_least64_t,
        typename QueueType = std::queue<VT>>
class Queue {
    std::array<QueueType, FunctionsCount> m_queues;
    std::array<LinearFunction, FunctionsCount> m_functions;
    VT m_front;

public:
    typedef VT ValueType;

    template<
            typename... Functions,
            std::enable_if_t<sizeof...(Functions) == FunctionsCount, bool> = true>
    explicit Queue(VT initValue, Functions... p)
            : m_functions{p...}, m_front{initValue} {}

    template<typename OtherIntegral>
    explicit Queue(const std::array<LinearFunction, FunctionsCount>& functions,
                   VT initValue = 1)
            : m_front{initValue}, m_functions{functions} {
    }

    ValueType IterateOnce() {
        auto value = m_front;
        std::size_t toPop = FunctionsCount;
        for (std::size_t i = 0; i != FunctionsCount; ++i) {
            auto y = m_functions[i](value);
            if (y != value) {
                m_queues[i].push(y);
            }
            if (!m_queues[i].empty() &&
                (toPop == FunctionsCount ||
                 m_queues[i].front() < m_queues[toPop].front())) {
                toPop = i;
            }
        }
        m_front = m_queues[toPop].front();
        m_queues[toPop].pop();
        for (std::size_t i = toPop + 1; i != FunctionsCount; ++i) {
            if (!m_queues[i].empty() && m_queues[i].front() == m_front) {
                m_front, m_queues[i].front();
                m_queues[i].pop();
            }
        }
        return value;
    }
};

#endif // VKR_QUEUE_H
