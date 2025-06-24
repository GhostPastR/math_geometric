#ifndef SYSTEM_FUNCTION_H
#define SYSTEM_FUNCTION_H

#include <cstddef>
#include <tuple>

template<typename ...Args>
struct Carcass{
protected:
    std::tuple<Args...> property_;
};

template<typename Tuple, typename Func, std::size_t L = std::tuple_size_v<Tuple> - 1>
bool conjunction_tuple(const Tuple &tuple1, const Tuple &tuple2, Func &&func){
    if constexpr(L == 0){
        return func(std::get<L>(tuple1), std::get<L>(tuple2));
    }
    else if constexpr (L > 0){
        auto flag = func(std::get<L>(tuple1), std::get<L>(tuple2));
        return flag && conjunction_tuple<Tuple, Func, L - 1>(tuple1, tuple2, std::forward<Func>(func));
    }
    else{
        static_assert(false, "L < 0");
    }
}

#endif // SYSTEM_FUNCTION_H
