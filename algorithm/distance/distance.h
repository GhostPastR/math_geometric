#ifndef AGL_ALGORITHM_DISTANCE_DISTANCE_H
#define AGL_ALGORITHM_DISTANCE_DISTANCE_H

#include <cmath>
#include "algorithm/distance/tag_algoritm.h"

namespace agl::algorithm {

namespace dispatch {

template<typename Object1, typename Object2, typename DistanceAlgorithm, typename CoordinateSystem, std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No 'distance' calculations have been implemented for these objects.");
    }
};

namespace distance_point_algo {

template<typename Point, typename CoordinateSystem, size_t Dimension>
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
        const auto q2 = traits::access_point<Point, 0>::get(b);
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


template<typename Point, typename CoordinateSystem, std::size_t Dimension>
struct distance<Point, Point, distance_point, CoordinateSystem, Dimension>{
    inline constexpr static auto get(const Point &a, const Point &b){
        return std::sqrt(distance_point_algo::distance<Point, CoordinateSystem, Dimension>::get(a, b));
    }
};

}


namespace geometry {

template<typename Object1, typename Object2>
inline constexpr auto distance(const Object1 &a, const Object2 &b){
    using type_algorithm = algorithm<typename traits::tag<Object1>::type_tag,
                                     typename traits::tag<Object2>::type_tag>::type_algorithm;
    using type_coordinate_system1 = traits::coordinate_system<Object1>::type_coordinate;
    using type_coordinate_system2 = traits::coordinate_system<Object2>::type_coordinate;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(!std::is_same_v<type_algorithm, undefined>, "Error!");
    static_assert(std::is_same_v<type_coordinate_system1, type_coordinate_system2>, "Error!");
    static_assert((dimension1 == dimension2) && (dimension1 > decltype(dimension1){}), "Error!");

    return dispatch::distance<Object1, Object2, type_algorithm, type_coordinate_system1, dimension1>::get(a,b);
}

}

}

#endif // AGL_ALGORITHM_DISTANCE_DISTANCE_H
