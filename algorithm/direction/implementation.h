#ifndef AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H
#define AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H

#include <cmath>
#include "algorithm/tag_algoritm.h"
#include "algorithm/traits.h"
#include "algorithm/math_algorithm.h"

namespace agl::algorithm::dispatch {

template<typename Object1, typename Object2, typename ObjectDirection, typename CoordinateSystem, std::size_t Dimension, typename TypeObjectDirection>
struct direction{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No 'direction' calculations have been implemented for these objects.");
    }
};

template<typename Point, typename ObjectDirection>
struct direction<Point, Point, ObjectDirection, cartesian, 2, direction_angle>{
    inline constexpr static auto get(const Point &a, const Point &b){
        ObjectDirection temp(std::atan2(traits::access_point<Point, 0>::get(b) - traits::access_point<Point, 0>::get(a),
                              traits::access_point<Point, 1>::get(b) - traits::access_point<Point, 1>::get(a)));
        return temp += (temp < 0) ? algorithm::pi_in_2<typename traits::type_coordinate<Point>::type> : ObjectDirection{};
    }
};

template<typename Point, typename ObjectDirection>
struct direction<Point, Point, ObjectDirection, cartesian, 2, direction_vector>{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "Not implemented.");
    }
};

template<typename Point, typename ObjectDirection>
struct direction<Point, Point, ObjectDirection, cartesian, 3, direction_vector>{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "Not implemented.");
    }
};

}



namespace agl::algorithm::geometry {

template<typename Object1, typename Object2, typename ObjectDirection>
inline constexpr auto direction(const Object1 &a, const Object2 &b){
    using type_coordinate_system1 = traits::coordinate_system<Object1>::system;
    using type_coordinate_system2 = traits::coordinate_system<Object2>::system;
    using direction_object = direction_object<ObjectDirection>::type_direction_object;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(std::is_same_v<type_coordinate_system1, type_coordinate_system2>, "Error!");
    static_assert(std::is_same_v<type_coordinate_system1, type_coordinate_system2>, "Error!");
    static_assert((dimension1 == dimension2) && (dimension1 > decltype(dimension1){}), "Error!");

    return dispatch::direction<Object1, Object2, ObjectDirection, type_coordinate_system1, dimension1, direction_object>::get(a,b);
}

}


#endif // AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H
