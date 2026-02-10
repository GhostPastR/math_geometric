#ifndef POINT_ALGORITHM_H
#define POINT_ALGORITHM_H

#include <numeric>

#include "../algorithm/matrix_algorithm.h"
#include "math_algorithm.h"


namespace agl::point_algo{

// template<std::floating_point Type, size_t N> requires (N > 0)
// constexpr bool is_co_directional(const std::array<Type, N> &v_r, const std::array<Type, N> &v_a, const std::array<Type, N> &v_b){
//     std::array<Type, N> v1;
//     std::ranges::transform(v_r, v_a, v1.begin(), [](const auto &a, const auto &b){ return b - a; });
//     std::array<Type, N> v2;
//     std::ranges::transform(v_r, v_b, v2.begin(), [](const auto &a, const auto &b){ return b - a; });
//     return matrix_algo::is_co_directional(v1, v2);
// }

}

#endif // POINT_ALGORITHM_H
