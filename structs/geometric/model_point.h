#ifndef MODEL_POINT_H
#define MODEL_POINT_H

#include "algorithm/math_algorithm.h"
#include <algorithm>
#include <array>

namespace agl {

template<typename T>
class Temp;


template<typename T, typename ...Args>
void type(T t, Args &&...value ){
    Temp<T> tt;
}

template<typename Type,
         typename CoordinateSystem,
         std::size_t Dimension>
class model_point{
public:
    constexpr model_point() = default;

    template<typename ...Args>
    constexpr model_point(Args &&...value){
        std::array<Type, Dimension> temp{std::move(value)...};
        std::swap(value_, temp);
    }

    template<std::size_t N>
    constexpr void set_value(const Type &v){
        static_assert(N < Dimension, "model_point N >= Dimension");
        value_[N] = v;
    }

    template<std::size_t N>
    constexpr auto value() const{
        return value_[N];
    }

    constexpr bool is_valid() const{
        return std::ranges::all_of(value_, [](const auto &v){
            return algorithm::is_valid(v) && algorithm::is_valid(v);
        });
    }

    friend constexpr bool operator==(const model_point<Type, CoordinateSystem, Dimension> &p1,
                                     const model_point<Type, CoordinateSystem, Dimension> &p2){
        return p1.compare(p2);
    }

protected:
    bool compare(const model_point<Type, CoordinateSystem, Dimension> &v) const{
        return std::ranges::equal(value_, v.value_, [](const auto &a, const auto &b){
            return agl::algorithm::compare(a, b);
        });
    }

private:
    std::array<Type, Dimension> value_;
};

}

#endif // MODEL_POINT_H
