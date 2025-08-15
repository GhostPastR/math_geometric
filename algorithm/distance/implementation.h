#ifndef AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_H
#define AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_H

#include <cmath>
#include "algorithm/distance/implementation_geo.h"
#include "algorithm/tag_algoritm.h"
#include "implementation_cartesian.h"

namespace agl::algorithm::dispatch {

template<typename Object1, typename Object2, typename DistanceAlgorithm, typename CoordinateSystem, std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No 'distance' calculations have been implemented for these objects.");
    }
};

template<typename Point, typename CoordinateSystem, std::size_t Dimension>
struct distance<Point, Point, distance_point, CoordinateSystem, Dimension>{
    inline constexpr static auto get(const Point &a, const Point &b){
        return std::sqrt(distance_point_algo::distance<Point, CoordinateSystem, Dimension>::get(a, b));
    }
};

template<typename Point, std::size_t Dimension>
struct distance<Point, Point, distance_point, geographical, Dimension>{
    inline constexpr static auto get(const Point &a, const Point &b){
        using system = traits::geo_coordinate_system<Point>::system;
        return geo_distance::distance<Point, system, Dimension>(a, b);
    }
};

}


namespace agl::algorithm::geometry {

template<typename Object1, typename Object2>
inline constexpr auto distance(const Object1 &a, const Object2 &b){
    using type_algorithm = algorithm_distance<typename traits::tag<Object1>::type_tag,
                                              typename traits::tag<Object2>::type_tag>::type_algorithm;
    using type_coordinate_system1 = traits::coordinate_system<Object1>::system;
    using type_coordinate_system2 = traits::coordinate_system<Object2>::system;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(!std::is_same_v<type_algorithm, undefined>, "Error!");
    static_assert(std::is_same_v<type_coordinate_system1, type_coordinate_system2>, "Error!");
    static_assert((dimension1 == dimension2) && (dimension1 > decltype(dimension1){}), "Error!");

    return dispatch::distance<Object1, Object2, type_algorithm, type_coordinate_system1, dimension1>::get(a,b);
}

}


#endif // AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_H
