//
// Created by shama on 15.04.2023.
//

#ifndef VKR_DEFINES_H
#define VKR_DEFINES_H

#define COMPARABLE_AS_OP(LA, RA, OP) \
template<typename Other>             \
auto operator OP(Other ra) const {   \
    auto other = std::remove_reference_t<decltype(*this)>(ra);      \
    return LA OP RA;                 \
}

#define COMPARABLE_AS(LA, RA) \
COMPARABLE_AS_OP(LA, RA, ==)  \
COMPARABLE_AS_OP(LA, RA, !=)  \
COMPARABLE_AS_OP(LA, RA, <=)  \
COMPARABLE_AS_OP(LA, RA, >=)  \
COMPARABLE_AS_OP(LA, RA, <)   \
COMPARABLE_AS_OP(LA, RA, >)

#endif //VKR_DEFINES_H
