#ifndef POINT_ALGORITHM_H
#define POINT_ALGORITHM_H

#include <numeric>

#include "../algorithm/matrix_algorithm.h"
#include "math_algorithm.h"


namespace agl::point_algo{

// возвращает направление отрезка от текущей точки до заданной точки(входной параметр методы).
template<std::floating_point Type>
constexpr auto angle(const Type &x1, const Type &y1, const Type &x2, const Type &y2){
    Type temp(function_angle<Type>::atan2(x2 - x1, y2 - y1));
    return temp += (temp < 0) ? algorithm::pi_in_2<Type> : 0.0;
}

//возвращает длину между 2-мя точками.
template<std::floating_point Type, size_t N> requires (N > 0)
constexpr auto distance(const std::array<Type, N> &v_a, const std::array<Type, N> &v_b){
    std::array<Type, N> v;
    std::ranges::transform(v_a, v_b, v.begin(), [](const auto &a, const auto &b){ return b - a; });
    return matrix_algo::module<Type,N>(v);
}

//метод расчитывает координаты новой точки
template<std::floating_point Type, std::floating_point TypeAngle, std::floating_point TypeRange>
constexpr auto new_point(const Type &x, const Type &y, const TypeAngle &angle, const TypeRange &range) -> std::pair<Type,Type>{
    return {x + range * function_angle<Type>::sin(angle),
            y + range * function_angle<Type>::cos(angle)};
}

//метод преобразует текущие координаты относительно заданной точки и угла поворота
template<std::floating_point Type, std::floating_point TypeAngle>
constexpr auto rotate(const Type &x, const Type &y, const TypeAngle &angle, const Type &rx, const Type &ry) -> std::pair<Type,Type>{
    const auto sinAngle = -function_angle<Type>::sin(angle);
    const auto cosAngle = function_angle<Type>::cos(angle);
    auto vector = matrix_algo::mul<Type, 2>({cosAngle, -sinAngle, sinAngle, cosAngle}, {x - rx, y - ry});
    return {vector[0] + rx, vector[1] + ry};
}

// метод возвращает среднию точку между точками.
template<std::floating_point Type, size_t N> requires (N > 0)
constexpr std::array<Type, N> midplane(const std::array<Type, N> &v_a, const std::array<Type, N> &v_b){
    std::array<Type, N> v;
    std::ranges::transform(v_a, v_b, v.begin(), [](const auto &a, const auto &b){ return std::midpoint(a, b); });
    return v;
}



template<std::floating_point Type>
constexpr auto convert_polar(const Type &rx, const Type &ry, const Type &x, const Type &y) -> std::pair<Type,Type>{
    return {distance<Type, 2>({rx, ry}, {x, y}), angle(rx, ry, x, y)};
}


template<std::floating_point Type>
constexpr auto convert_decart(const Type &fi, const Type &psi, const Type &rx, const Type &ry) -> std::pair<Type,Type>{
    return new_point(rx, ry, fi, psi);
}


template<std::floating_point Type, size_t N> requires (N > 0)
constexpr bool is_co_directional(const std::array<Type, N> &v_r, const std::array<Type, N> &v_a, const std::array<Type, N> &v_b){
    std::array<Type, N> v1;
    std::ranges::transform(v_r, v_a, v1.begin(), [](const auto &a, const auto &b){ return b - a; });
    std::array<Type, N> v2;
    std::ranges::transform(v_r, v_b, v2.begin(), [](const auto &a, const auto &b){ return b - a; });
    return matrix_algo::is_co_directional(v1, v2);
}

}

#endif // POINT_ALGORITHM_H
