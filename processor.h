//
// Created by shama on 15.04.2023.
//

#ifndef VKR_PROCESSOR_H
#define VKR_PROCESSOR_H

#include <tuple>

template<typename... F>
class Processor {
    std::tuple<F...> m_callbacks;

public:
    template<typename QueueType>
    void Process(QueueType& queue, typename QueueType::ValueType valueLimit) {
        typename QueueType::ValueType v;
        do {
            v = queue.IterateOnce();
            bool needToStop = (std::get<F>(m_callbacks)(v) || ... || false);
            if (needToStop) {
                break;
            }
        } while (v < valueLimit);
    }
};

#endif //VKR_PROCESSOR_H
