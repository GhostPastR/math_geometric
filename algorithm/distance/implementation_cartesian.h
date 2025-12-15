#ifndef AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_CARTESIAN_H
#define AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_CARTESIAN_H

#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch::d2::distance_point_algo {

namespace dispatch {

template<typename Point>
struct distance{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "No 'distance' calculations have been implemented for these points.");
    }
};

template<c_point_2d Point>
    requires c_cartesian<Point>
struct distance<Point>{
    inline constexpr static auto get(const Point &a, const Point &b){
        const auto x1 = traits::point::access_point<Point, 0>::get(a);
        const auto y1 = traits::point::access_point<Point, 1>::get(a);
        const auto x2 = traits::point::access_point<Point, 0>::get(b);
        const auto y2 = traits::point::access_point<Point, 1>::get(b);
        return std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2);
    }
};

template<c_point_3d Point>
    requires c_cartesian<Point>
struct distance<Point>{
    inline constexpr static auto get(const Point &a, const Point &b){
        const auto x1 = traits::point::access_point<Point, 0>::get(a);
        const auto y1 = traits::point::access_point<Point, 1>::get(a);
        const auto z1 = traits::point::access_point<Point, 2>::get(a);
        const auto x2 = traits::point::access_point<Point, 0>::get(b);
        const auto y2 = traits::point::access_point<Point, 1>::get(b);
        const auto z2 = traits::point::access_point<Point, 2>::get(b);
        return std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) + std::pow(z2 - z1, 2);
    }
};

template<c_point_2d Point>
    requires c_polar<Point>
struct distance<Point>{
    inline constexpr static auto get(const Point &a, const Point &b){
        const auto r1 = traits::point::access_point<Point, 0>::get(a);
        const auto q1 = traits::point::access_point<Point, 1>::get(a);
        const auto r2 = traits::point::access_point<Point, 0>::get(b);
        const auto q2 = traits::point::access_point<Point, 1>::get(b);
        return std::pow(r1, 2) + std::pow(r2, 2) - 2 * r1 * r2 * std::cos(q1 - q2);
    }
};

template<c_point_3d Point>
    requires c_polar<Point>
struct distance<Point>{
    inline constexpr static auto get(const Point &a, const Point &b){
        const auto r1 = traits::point::access_point<Point, 0>::get(a);
        const auto q1 = traits::point::access_point<Point, 1>::get(a);
        const auto h1 = traits::point::access_point<Point, 2>::get(a);
        const auto r2 = traits::point::access_point<Point, 0>::get(b);
        const auto q2 = traits::point::access_point<Point, 1>::get(b);
        const auto h2 = traits::point::access_point<Point, 2>::get(b);
        return std::pow(r1, 2) + std::pow(r2, 2) - 2 * r1 * r2 * std::cos(q1 - q2) + std::pow(h2 - h1, 2);
    }
};

// template<c_point_3d Point>
//     requires c_spherical<Point>
// struct distance<Point>{
//     inline constexpr static auto get(const Point &a, const Point &b){
//         return distance<Point, system_coordinat::polar, 2>::get(a, b)
//         - 2 * traits::point::access_point<Point, 0>::get(a) * traits::point::access_point<Point, 0>::get(b)
//             * std::sin(traits::point::access_point<Point, 1>::get(a)) * std::sin(traits::point::access_point<Point, 1>::get(b))
//             * (std::cos(traits::point::access_point<Point, 2>::get(a) - traits::point::access_point<Point, 2>::get(b)) - 1);
//     }
// };

}

template<typename Point>
inline constexpr auto distance(const Point &a, const Point &b){
    return std::sqrt(distance_point_algo::dispatch::distance<Point>::get(a, b));
}

}

#endif // AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_CARTESIAN_H
