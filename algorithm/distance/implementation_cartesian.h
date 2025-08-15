#ifndef AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_CARTESIAN_H
#define AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_CARTESIAN_H

#include "algorithm/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch::distance_point_algo {

template<typename Point, typename CoordinateSystem, std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "No 'distance' calculations have been implemented for these points.");
    }
};

template<typename Point>
struct distance<Point, cartesian, 2>{
    inline constexpr static auto get(const Point &a, const Point &b){
        return std::pow(traits::access_point<Point, 0>::get(b) - traits::access_point<Point, 0>::get(a), 2)
        + std::pow(traits::access_point<Point, 1>::get(b) - traits::access_point<Point, 1>::get(a), 2);
    }
};

template<typename Point>
struct distance<Point, cartesian, 3>{
    inline constexpr static auto get(const Point &a, const Point &b){
        using acc_point = traits::access_point<Point, 2>;
        return distance<Point, cartesian, 2>::get(a, b) + std::pow(acc_point::get(b) - acc_point::get(a), 2);
    }
};

template<typename Point>
struct distance<Point, polar, 2>{
    inline constexpr static auto get(const Point &a, const Point &b){
        const auto r1 = traits::access_point<Point, 0>::get(a);
        const auto q1 = traits::access_point<Point, 1>::get(a);
        const auto r2 = traits::access_point<Point, 0>::get(b);
        const auto q2 = traits::access_point<Point, 1>::get(b);
        return std::sqrt(std::pow(r1, 2) + std::pow(r2, 2) - 2 * r1 * r2 * std::cos(q1 - q2));
    }
};

template<typename Point>
struct distance<Point, polar, 3>{
    inline constexpr static auto get(const Point &a, const Point &b){
        using acc_point = traits::access_point<Point, 2>;
        return distance<Point, polar, 2>::get(a, b)
               + std::pow(acc_point::get(b) - acc_point::get(a), 2);
    }
};

template<typename Point>
struct distance<Point, spherical, 3>{
    inline constexpr static auto get(const Point &a, const Point &b){
        return distance<Point, polar, 2>::get(a, b)
        - 2 * traits::access_point<Point, 0>::get(a) * traits::access_point<Point, 0>::get(b)
            * std::sin(traits::access_point<Point, 1>::get(a)) * std::sin(traits::access_point<Point, 1>::get(b))
            * (std::cos(traits::access_point<Point, 2>::get(a) - traits::access_point<Point, 2>::get(b)) - 1);
    }
};

}

#endif // AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_CARTESIAN_H
